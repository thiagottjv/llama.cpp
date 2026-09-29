#!/usr/bin/env python3
"""
sweep_bench.py: Automated sweep benchmark for llama-server.
Supports flexible string format for parameters:
  - "inicio|fim|step" (ex: "0.90|0.75|-0.05" ou "0.05|0.20|0.05")
  - "val1, val2, val3" (ex: "0.85, 0.80, 0.75")
  - "val" (ex: "0.80")
"""

import sys
import os
import time
import re
import json
import signal
import subprocess
import argparse
from urllib.request import urlopen, Request
from urllib.error import URLError

DEFAULT_SERVER_BIN = "/home/ai/llama.cpp/build/bin/llama-server"
DEFAULT_MODEL = "/home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf"
DEFAULT_IMATRIX = "/home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf"
DEFAULT_TEMPLATE = "/home/ai/chat_template_22.5.jinja"
DEFAULT_BENCH_CMD = "python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1"

def parse_range_or_list(s, default_val="0.80"):
    """
    Parses a string into a list of floats:
      - "start|end|step": generates range from start to end with step
      - "v1,v2,v3": explicit comma-separated list
      - "v": single value
    """
    if s is None:
        s = default_val
    s = str(s).strip()
    if not s:
        s = default_val

    if "|" in s:
        parts = [float(p.strip()) for p in s.split("|") if p.strip()]
        if len(parts) != 3:
            raise ValueError(f"Formato com '|' deve conter exatamente 3 valores (inicio|fim|step). Recebido: '{s}'")
        start, end, step = parts[0], parts[1], parts[2]
        if step == 0:
            raise ValueError(f"Step nao pode ser zero em '{s}'")

        if start < end and step < 0:
            step = abs(step)
        elif start > end and step > 0:
            step = -abs(step)

        values = []
        curr = start
        eps = abs(step) * 1e-4
        if step > 0:
            while curr <= end + eps:
                values.append(round(curr, 4))
                curr += step
        else:
            while curr >= end - eps:
                values.append(round(curr, 4))
                curr += step
        return values
    elif "," in s:
        return [round(float(p.strip()), 4) for p in s.split(",") if p.strip()]
    else:
        return [round(float(s), 4)]

def parse_early_exit_configs(s):
    """
    Parses early exit rules sweep configuration:
      - Multiple configurations to sweep separated by '|'
      - Each configuration can have multiple rules separated by ';'
      - Ex: "0,7,0.50,0.70;8,39,0.70,0.80 | 0,7,0.60,0.75;8,39,0.75,0.85"
    """
    if s is None:
        return [None]
    s = str(s).strip()
    if not s:
        return [None]
    configs = [c.strip() for c in s.split("|") if c.strip()]
    return configs if configs else [None]

def wait_for_server(url, timeout=180):
    start = time.time()
    health_url = url.rstrip("/") + "/health"
    while time.time() - start < timeout:
        try:
            req = Request(health_url, headers={"User-Agent": "sweep-bench"})
            with urlopen(req, timeout=2) as resp:
                if resp.status == 200:
                    return True
        except Exception:
            pass
        time.sleep(1.0)
    return False

def warmup_bench(bench_cmd, limit=1):
    print(f"[*] Aquecendo modelo na RAM com benchmark previo...")
    warm_cmd = bench_cmd
    if "--limit" in warm_cmd:
        warm_cmd = re.sub(r"--limit\s+\d+", f"--limit {limit}", warm_cmd)
    else:
        warm_cmd += f" --limit {limit}"

    # During warmup, generating 16 tokens is sufficient to warm up kernels and cache
    if "--osl" in warm_cmd:
        warm_cmd = re.sub(r"--osl\s+\d+", "--osl 16", warm_cmd)

    # If category all is requested, warm up with just one category to avoid wasting 30+ minutes
    if "--category all" in warm_cmd:
        if "throughput" in warm_cmd:
            warm_cmd = warm_cmd.replace("--category all", "--category mixed")
        else:
            warm_cmd = warm_cmd.replace("--category all", "--category coding")

    temp_warmup_json = "sweep_warmup_temp.json"
    if "--output" in warm_cmd:
        warm_cmd = re.sub(r"--output\s+\S+", f"--output {temp_warmup_json}", warm_cmd)
    else:
        warm_cmd += f" --output {temp_warmup_json}"

    try:
        res = subprocess.run(
            warm_cmd,
            shell=True,
            capture_output=True,
            text=True,
            timeout=600
        )
        if os.path.exists(temp_warmup_json):
            try:
                os.remove(temp_warmup_json)
            except Exception:
                pass
        print(f"[+] Aquecimento previo concluido com sucesso!")
        return True
    except Exception as e:
        print(f"[!] Aviso no aquecimento: {e}")
        return False

def stop_process(proc):
    if proc and proc.poll() is None:
        try:
            proc.send_signal(signal.SIGINT)
            proc.wait(timeout=15)
        except Exception:
            try:
                proc.kill()
                proc.wait(timeout=5)
            except Exception:
                pass

def parse_bench_output(output):
    # Match coding or overall row:
    # coding    4        30.00          15.49         74.980s      n/a
    pattern = r"(?:overall|coding)\s+\d+\s+([\d\.]+)\s+([\d\.]+)\s+([\d\.]+)s"
    matches = re.findall(pattern, output)
    if matches:
        last = matches[-1]
        return {
            "prompt_ts": float(last[0]),
            "pred_ts": float(last[1]),
            "latency": float(last[2])
        }
    return None

def main():
    parser = argparse.ArgumentParser(description="Sweep benchmark para llama-server com expert early-exit granular")
    parser.add_argument("--expert-early-exit", "-eee", dest="expert_early_exit", type=str, default=None,
                        help="Regras de early-exit: 'start,end,min,max' (multiplas configs separadas por '|', multiplas regras separadas por ';')")
    parser.add_argument("--swap-max", "--esm", "--expert-swap-max", dest="swap_max", type=str, default="0.10",
                        help="Valores de swap-max: 'inicio|fim|step', 'v1,v2,v3' ou 'v' (default: 0.10)")
    parser.add_argument("--attenuation", "--eda", "--expert-attenuation", dest="attenuation", type=str, default="0.15",
                        help="Valores de taxa de atenuacao: 'inicio|fim|step', 'v1,v2,v3' ou 'v' (default: 0.15, decay = 1 - rate)")
    parser.add_argument("--imatrix-weight", "--eiw", "--expert-imatrix-weight", dest="imatrix_weight", type=str, default="0.0",
                        help="Valores de peso persistente do imatrix: 'inicio|fim|step', 'v1,v2,v3' ou 'v' (default: 0.0)")
    parser.add_argument("--veb", "--vram-expert-budget-mb", type=int, default=2600,
                        help="Orcamento de VRAM em MiB para experts (default: 2600)")
    parser.add_argument("--server-bin", default=DEFAULT_SERVER_BIN, help="Caminho do binario do llama-server")
    parser.add_argument("--model", default=DEFAULT_MODEL, help="Caminho do modelo GGUF")
    parser.add_argument("--imatrix", default=DEFAULT_IMATRIX, help="Caminho do imatrix.gguf")
    parser.add_argument("--template", default=DEFAULT_TEMPLATE, help="Caminho do chat template jinja")
    parser.add_argument("--ctx-size", "-c", type=int, default=65536, help="Tamanho do contexto (default: 65536)")
    parser.add_argument("--ubatch", "-ub", type=int, default=512, help="Microbatch size (default: 512)")
    parser.add_argument("--batch", "-b", type=int, default=2048, help="Batch size (default: 2048)")
    parser.add_argument("--cache-type-k", default="q5_0", help="Quantizacao KV cache K (default: q8_0)")
    parser.add_argument("--cache-type-v", default="q4_1", help="Quantizacao KV cache V (default: q4_0)")
    parser.add_argument("--threads", type=int, default=6, help="Threads CPU (default: 6)")
    parser.add_argument("--threads-batch", type=int, default=12, help="Threads batch CPU (default: 12)")
    parser.add_argument("--limit", "--bench-limit", type=int, default=4, help="Numero de amostras por teste (default: 4)")
    parser.add_argument("--bench-cmd", default=DEFAULT_BENCH_CMD, help="Comando do speed_bench")
    parser.add_argument("--host", default="http://127.0.0.1:8080", help="URL do servidor")
    parser.add_argument("--log-file", default="/home/ai/llama.cpp/server_sweep.log", help="Arquivo de log do servidor")
    parser.add_argument("--out-md", default="/home/ai/llama.cpp/sweep_results.md", help="Arquivo markdown de resumo")

    args = parser.parse_args()

    early_exit_configs  = parse_early_exit_configs(args.expert_early_exit)
    swap_max_list       = parse_range_or_list(args.swap_max, default_val="0.10")
    atten_list          = parse_range_or_list(args.attenuation, default_val="0.15")
    imatrix_weight_list = parse_range_or_list(args.imatrix_weight, default_val="0.0")

    combinations = [
        (eee, esm, eda, eiw)
        for eee in early_exit_configs
        for esm in swap_max_list
        for eda in atten_list
        for eiw in imatrix_weight_list
    ]

    results = []
    current_server = None

    def cleanup_signal(sig, frame):
        print("\n[!] Recebido sinal de interrupcao. Encerrando servidor...")
        stop_process(current_server)
        sys.exit(1)

    signal.signal(signal.SIGINT, cleanup_signal)
    signal.signal(signal.SIGTERM, cleanup_signal)

    print("=================================================================")
    print(f"  Benchmark Sweep: expert-early-exit granular, imatrix-weight, swap-max e attenuation")
    print(f"  Early-Exit configs a testar: {early_exit_configs}")
    print(f"  Imatrix-Weight testar      : {imatrix_weight_list}")
    print(f"  Swap-Max a testar          : {swap_max_list}")
    print(f"  Attenuation a testar       : {atten_list}")
    print(f"  Total de testes            : {len(combinations)}")
    print(f"  VRAM Budget (MiB)          : {args.veb}")
    print(f"  Modelo                     : {os.path.basename(args.model)}")
    print("=================================================================\n")

    temp_json_path = "sweep_bench_temp.json"

    for idx, (eee, esm, eda, eiw) in enumerate(combinations, 1):
        print(f"-----------------------------------------------------------------")
        desc = []
        if eee:
            desc.append(f"early-exit = {eee}")
        else:
            desc.append("early-exit = desativado (1.00)")
        if eiw > 0.0 or any(w > 0.0 for w in imatrix_weight_list):
            desc.append(f"imatrix-weight = {eiw:.2f}")
        desc.append(f"swap-max = {esm:.2f}")
        desc.append(f"atten = {eda:.2f}")
        print(f"[*] [{idx}/{len(combinations)}] Testando: " + " | ".join(desc))
        print(f"-----------------------------------------------------------------")
#
        server_cmd = [
            #"sudo", "prlimit", "--memlock=unlimited",
            "env", "GGML_CUDA_ENABLE_UNIFIED_MEMORY=1",
            args.server_bin,
            "--fit", "off",
            "-m", args.model,
            "--expert-imatrix", args.imatrix,
            "--vram-expert-budget-mb", str(args.veb),
        ]
        if eee:
            for rule in eee.split(";"):
                rule = rule.strip()
                if rule:
                    server_cmd.extend(["--expert-early-exit", rule])

        server_cmd.extend([
            "--expert-imatrix-weight", str(eiw),
            "--expert-swap-max", str(esm),
            "--expert-attenuation", str(eda),
            "--cache-type-k", args.cache_type_k,
            "--cache-type-v", args.cache_type_v,
            "-ngl", "999",
            "-c", str(args.ctx_size),
            #"--load-mode", "mlock",
            "--load-mode", "mmap",
            "-cmoe",
            #"--n-cpu-moe", "48",
            "--lazy-mode", "on",
            "-ot", "^token_embd=CPU",
            "--threads", str(args.threads),
            "--threads-batch", str(args.threads_batch),
            "--parallel", "1",
            "--flash-attn", "on",
            "-b", str(args.batch),
            "-ub", str(args.ubatch),
            "--temp", "0.6",
            "--top-p", "0.95",
            "--min-p", "0.0",
            "--top-k", "20",
            "--presence_penalty", "0.0",
            "--repeat-penalty", "1",
            "--jinja",
            "--chat-template-file", args.template,
            "--reasoning-format", "deepseek",
            "--warmup",
            "--host", "0.0.0.0",
            "--cors-origins", "http://localhost:8080",
            "--alias", "local-model"#, "-v", "-lv", "4"
        ])

        with open(args.log_file, "w") as log_f:
            current_server = subprocess.Popen(
                server_cmd,
                stdout=log_f,
                stderr=subprocess.STDOUT
            )

        print(f"[+] Servidor iniciado (PID: {current_server.pid}). Aguardando modelo...")
        if not wait_for_server(args.host, timeout=180):
            print(f"[!] ERRO: Servidor nao respondeu no healthcheck dentro do tempo limite. Verifique {args.log_file}")
            stop_process(current_server)
            current_server = None
            continue

        bench_cmd = args.bench_cmd
        if args.limit is not None:
            if "--limit" in bench_cmd:
                bench_cmd = re.sub(r"--limit\s+\d+", f"--limit {args.limit}", bench_cmd)
            else:
                bench_cmd += f" --limit {args.limit}"

        if "--output" in bench_cmd:
            m = re.search(r"--output\s+(\S+)", bench_cmd)
            cur_json = m.group(1) if m else temp_json_path
        else:
            bench_cmd += f" --output {temp_json_path}"
            cur_json = temp_json_path

        if os.path.exists(cur_json):
            try:
                os.remove(cur_json)
            except Exception:
                pass

        warmup_bench(bench_cmd, limit=1)

        print(f"[+] Servidor pronto! Executando benchmark oficial: {bench_cmd}")
        bench_start = time.time()
        bench_proc = subprocess.run(
            bench_cmd,
            shell=True,
            capture_output=True,
            text=True
        )
        bench_time = time.time() - bench_start

        raw_output = bench_proc.stdout + "\n" + bench_proc.stderr
        print(raw_output.strip())

        parsed = parse_bench_output(raw_output)

        pred_orig = None
        pred_pond = None
        pred_no_warmup = None
        prompt_ts = None
        latency_val = None

        if os.path.exists(cur_json):
            try:
                with open(cur_json, "r", encoding="utf-8") as jf:
                    jdata = json.load(jf)
                sample_results = [r for r in jdata.get("results", []) if r.get("ok")]
                speeds = [r["predicted_per_second"] for r in sample_results if r.get("predicted_per_second") is not None]
                comp_tokens = [r.get("completion_tokens", 0) for r in sample_results]
                pred_ms = [r.get("predicted_ms", 0.0) for r in sample_results if r.get("predicted_ms") is not None]

                if speeds:
                    pred_orig = sum(speeds) / len(speeds)
                    if len(speeds) > 1:
                        # Exclui a 1a rodada (warmup) e calcula a media de todas as rodadas seguintes
                        pred_no_warmup = sum(speeds[1:]) / len(speeds[1:])
                    else:
                        pred_no_warmup = speeds[0]

                tot_sec = sum(pred_ms) / 1000.0
                if tot_sec > 0:
                    pred_pond = sum(comp_tokens) / tot_sec
                elif speeds:
                    pred_pond = pred_orig

                summary = jdata.get("summary", [])
                ov = next((s for s in summary if s.get("category") == "overall"), None)
                if not ov and summary:
                    ov = summary[-1]
                if ov:
                    prompt_ts = ov.get("avg_prompt_t_s")
                    latency_val = ov.get("avg_latency")
            except Exception as e:
                print(f"[!] Aviso ao ler {cur_json}: {e}")

        if parsed:
            if prompt_ts is None:
                prompt_ts = parsed["prompt_ts"]
            if latency_val is None:
                latency_val = parsed["latency"]
            if pred_orig is None:
                pred_orig = parsed["pred_ts"]
            if pred_pond is None:
                pred_pond = pred_orig
            if pred_no_warmup is None:
                pred_no_warmup = pred_orig

        if pred_orig is not None:
            ee_label = eee if eee else "disabled (1.00)"
            res_item = {
                "early_exit_label": ee_label,
                "early_exit": eee,
                "imatrix_weight": eiw,
                "swap_max": esm,
                "attenuation": eda,
                "prompt_ts": prompt_ts if prompt_ts is not None else 0.0,
                "pred_orig": pred_orig,
                "pred_pond": pred_pond if pred_pond is not None else pred_orig,
                "pred_no_warmup": pred_no_warmup if pred_no_warmup is not None else pred_orig,
                "latency": latency_val if latency_val is not None else 0.0
            }
            results.append(res_item)
            print(f"[>] Resultado: Prompt={res_item['prompt_ts']:.2f} t/s | Pred(Orig)={res_item['pred_orig']:.2f} | Pred(Pond)={res_item['pred_pond']:.2f} | Pred(S/Warm)={res_item['pred_no_warmup']:.2f} | Latencia={res_item['latency']:.2f}s")
        else:
            print("[!] Aviso: Nao foi possivel extrair metricas da saida do benchmark.")

        print("[+] Finalizando servidor...")
        stop_process(current_server)
        current_server = None
        time.sleep(3.0)

    if not results:
        print("\n[!] Nenhum resultado coletado com sucesso.")
        return

    base_pred = results[0]["pred_orig"] if results[0]["pred_orig"] > 0 else 1.0

    show_iw = any(r["imatrix_weight"] > 0.0 for r in results) or len(imatrix_weight_list) > 1

    headers = [("Early-Exit Rules", 35)]
    if show_iw:
        headers.append(("Imatr W", 9))
    headers.extend([
        ("Swap Max", 10),
        ("Atten", 7),
        ("Prompt t/s", 11),
        ("Pred (Orig)", 11),
        ("Pred (Pond)", 11),
        ("Pred (S/Warm)", 13),
        ("Latencia", 10),
        ("Speedup", 8)
    ])

    total_w = sum(w for _, w in headers) + (len(headers) - 1) * 3

    md_headers = ["Early-Exit Rules"]
    if show_iw:
        md_headers.append("Imatrix Weight")
    md_headers.extend([
        "Swap Max", "Atten", "Prompt t/s",
        "Pred t/s (Original)", "Pred t/s (Ponderada)",
        "Pred t/s (Sem Warmup)", "Latencia Media", "Speedup"
    ])
    header = "| " + " | ".join(md_headers) + " |"
    sep    = "|:" + ":|:".join("-" * max(3, len(h)) for h in md_headers) + ":|"

    sample_server_cmd = (
        f"{args.server_bin} --fit off -m {args.model} \\\n"
        f"  --expert-imatrix {args.imatrix} --vram-expert-budget-mb {args.veb} \\\n"
        f"  --expert-early-exit <START,END,MIN[,MAX]> \\\n"
        f"  --expert-imatrix-weight <IMATRIX_WEIGHT> \\\n"
        f"  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \\\n"
        f"  --cache-type-k {args.cache_type_k} --cache-type-v {args.cache_type_v} -ngl 999 -c {args.ctx_size} \\\n"
        f"  --load-mode mmap -cmoe --lazy-mode on --threads {args.threads} --threads-batch {args.threads_batch} \\\n"
        f"  --parallel 1 --flash-attn on -b {args.batch} -ub {args.ubatch} --temp 0.6 --top-p 0.95 \\\n"
        f"  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \\\n"
        f"  --jinja --chat-template-file {args.template} --reasoning-format deepseek \\\n"
        f"  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model"
    )

    lines = [
        f"## Resumo do Sweep: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        "",
        f"- **Data**: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        f"- **Modelo**: `{os.path.basename(args.model)}`",
        f"- **VRAM Budget (`--vram-expert-budget-mb`)**: `{args.veb} MiB`",
        f"- **Early-Exit configs testadas**: `{early_exit_configs}`",
        f"- **Imatrix-Weight testados**: `{imatrix_weight_list}`",
        f"- **Swap-Max testados**: `{swap_max_list}`",
        f"- **Attenuation testados**: `{atten_list}`",
        f"- **Imatrix**: `{os.path.basename(args.imatrix)}`",
        f"- **Comando de Benchmark**: `{bench_cmd}`",
        f"- **Parametros do Servidor (`llama-server`)**:",
        "```bash",
        sample_server_cmd,
        "```",
        "",
        header,
        sep
    ]

    hdr_line = " | ".join(f"{h:<{w}}" for h, w in headers)
    print("\n" + "=" * total_w)
    print(" " * max(0, (total_w - 36) // 2) + "TABELA CONSOLIDADA DE RESULTADOS")
    print("=" * total_w)
    print(hdr_line)
    print("-" * total_w)

    for r in results:
        speedup = r["pred_orig"] / base_pred
        cols = [f"{r['early_exit_label']:<35}"]
        md_cols = [f"{r['early_exit_label']}"]
        if show_iw:
            cols.append(f"{r['imatrix_weight']:<9.2f}")
            md_cols.append(f"{r['imatrix_weight']:.2f}")
        cols.extend([
            f"{r['swap_max']:<10.2f}",
            f"{r['attenuation']:<7.2f}",
            f"{r['prompt_ts']:<11.2f}",
            f"{r['pred_orig']:<11.2f}",
            f"{r['pred_pond']:<11.2f}",
            f"{r['pred_no_warmup']:<13.2f}",
            f"{r['latency']:<9.2f}s",
            f"{speedup:<7.2f}x"
        ])
        md_cols.extend([
            f"{r['swap_max']:.2f}",
            f"{r['attenuation']:.2f}",
            f"{r['prompt_ts']:.2f}",
            f"{r['pred_orig']:.2f}",
            f"{r['pred_pond']:.2f}",
            f"{r['pred_no_warmup']:.2f}",
            f"{r['latency']:.2f}s",
            f"{speedup:.2f}x"
        ])
        row_str = " | ".join(cols)
        print(row_str)

        md_row = "| " + " | ".join(md_cols) + " |"
        lines.append(md_row)

    print("=" * total_w + "\n")

    file_exists = os.path.exists(args.out_md) and os.path.getsize(args.out_md) > 0
    with open(args.out_md, "a", encoding="utf-8") as f:
        if file_exists:
            f.write("\n\n---\n\n")
        f.write("\n".join(lines) + "\n")

    print(f"[+] Relatorio adicionado com sucesso ao historico em: {args.out_md}")

if __name__ == "__main__":
    main()
