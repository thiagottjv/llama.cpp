# Resumo do Sweep de Benchmark (--expert-target-p)

- Data: 2026-09-09 18:42:44
- Modelo: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- VRAM Experts: `25`

| Target P | Prompt (t/s) | Pred (t/s) | Latency (s) | Speedup vs Base |
|:--------:|:------------:|:----------:|:-----------:|:---------------:|
| 1.00 | 215.13 | 16.79 | 58.11s | 1.00x |
| 0.95 | 413.19 | 17.50 | 51.92s | 1.04x |
| 0.90 | 422.64 | 18.91 | 45.48s | 1.13x |
| 0.85 | 449.33 | 20.22 | 46.96s | 1.20x |
| 0.80 | 434.12 | 21.66 | 44.79s | 1.29x |
| 0.75 | 501.11 | 23.56 | 38.82s | 1.40x |
| 0.70 | 481.80 | 24.97 | 35.64s | 1.49x |


---

## Resumo do Sweep: 2026-09-10 07:43:28

- **Data**: 2026-09-10 07:43:28
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Experts (`--n-vram-experts`)**: `25`
- **Max Swaps (`--expert-swap-max`)**: `2`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py  --url localhost:8080   --bench qualitative   --category coding   --osl 1024   --concurrency 1   --limit 4`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/buildhot/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --n-vram-experts 25 --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf \
  --expert-target-p <TARGET_P> --expert-swap-max 2 \
  --cache-type-k q8_0 --cache-type-v q8_0 -ngl 999 -c 16024 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 2048 --temp 1 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P | Prompt (t/s) | Pred (t/s) | Latency (s) | Speedup vs Base |
|:--------:|:------------:|:----------:|:-----------:|:---------------:|
| 0.90 | 334.59 | 21.74 | 52.70s | 1.00x |
| 0.85 | 520.08 | 23.30 | 43.90s | 1.07x |
| 0.80 | 486.53 | 24.86 | 42.15s | 1.14x |
| 0.75 | 528.43 | 26.93 | 41.92s | 1.24x |


---

## Resumo do Sweep: 2026-09-10 21:05:05

- **Data**: 2026-09-10 21:05:05
- **Modelo**: `Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `1500 MiB`
- **Target-P testados**: `[0.85, 0.8, 0.75]`
- **Swap-Max testados**: `[0.1, 0.2, 0.3, 0.4, 0.5]`
- **Imatrix**: `imatrix_unsloth.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q4_K_XL/Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf \
  --expert-imatrix /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q6_K_XL/imatrix_unsloth.gguf --vram-expert-budget-mb 1500 \
  --expert-target-p <TARGET_P> --expert-swap-max <SWAP_MAX> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 256 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P | Swap Max | Prompt (t/s) | Pred (t/s) | Latency (s) | Speedup vs Base |
|:--------:|:--------:|:------------:|:----------:|:-----------:|:---------------:|
| 0.85 | 0.10 | 25.43 | 13.76 | 82.37s | 1.00x |
| 0.85 | 0.20 | 26.26 | 14.93 | 92.11s | 1.09x |
| 0.85 | 0.30 | 25.48 | 14.64 | 81.91s | 1.06x |
| 0.85 | 0.40 | 26.53 | 14.75 | 92.36s | 1.07x |
| 0.85 | 0.50 | 24.20 | 14.12 | 80.60s | 1.03x |
| 0.80 | 0.10 | 29.96 | 15.63 | 76.48s | 1.14x |
| 0.80 | 0.20 | 28.86 | 15.12 | 76.59s | 1.10x |
| 0.80 | 0.30 | 30.59 | 15.33 | 81.22s | 1.11x |
| 0.80 | 0.40 | 30.19 | 15.71 | 75.42s | 1.14x |
| 0.80 | 0.50 | 31.12 | 15.87 | 75.84s | 1.15x |
| 0.75 | 0.10 | 30.98 | 16.59 | 72.81s | 1.21x |
| 0.75 | 0.20 | 32.99 | 16.70 | 68.93s | 1.21x |
| 0.75 | 0.30 | 29.55 | 16.58 | 70.89s | 1.20x |
| 0.75 | 0.40 | 33.23 | 16.71 | 69.06s | 1.21x |
| 0.75 | 0.50 | 30.12 | 17.13 | 71.15s | 1.24x |


---

## Resumo do Sweep: 2026-09-10 23:56:51

- **Data**: 2026-09-10 23:56:51
- **Modelo**: `Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `1500 MiB`
- **Target-P testados**: `[0.75, 0.7, 0.65]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.1, 0.15, 0.2, 0.25]`
- **Imatrix**: `imatrix_unsloth.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q4_K_XL/Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf \
  --expert-imatrix /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q6_K_XL/imatrix_unsloth.gguf --vram-expert-budget-mb 1500 \
  --expert-target-p <TARGET_P> --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 256 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:--------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 1.00 | 0.10 | 27.58 | 18.33 | 17.25 | 21.73 | 63.94s | 1.00x |
| 0.75 | 1.00 | 0.15 | 28.15 | 18.12 | 17.16 | 21.78 | 61.65s | 0.99x |
| 0.75 | 1.00 | 0.20 | 23.79 | 16.56 | 15.85 | 19.50 | 67.97s | 0.90x |
| 0.75 | 1.00 | 0.25 | 25.35 | 17.30 | 16.31 | 20.73 | 66.94s | 0.94x |
| 0.70 | 1.00 | 0.10 | 27.66 | 17.52 | 16.85 | 20.51 | 64.63s | 0.96x |
| 0.70 | 1.00 | 0.15 | 27.97 | 18.61 | 17.56 | 22.44 | 60.26s | 1.02x |
| 0.70 | 1.00 | 0.20 | 25.48 | 18.42 | 17.34 | 21.34 | 67.43s | 1.01x |
| 0.70 | 1.00 | 0.25 | 24.69 | 17.97 | 17.34 | 21.17 | 62.14s | 0.98x |
| 0.65 | 1.00 | 0.10 | 29.94 | 18.78 | 18.30 | 22.33 | 58.08s | 1.02x |
| 0.65 | 1.00 | 0.15 | 26.69 | 17.91 | 17.68 | 20.55 | 59.08s | 0.98x |
| 0.65 | 1.00 | 0.20 | 28.58 | 18.47 | 18.02 | 21.20 | 60.40s | 1.01x |
| 0.65 | 1.00 | 0.25 | 29.37 | 19.09 | 18.36 | 21.70 | 61.28s | 1.04x |


---

## Resumo do Sweep: 2026-09-11 16:23:00

- **Data**: 2026-09-11 16:23:00
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2600 MiB`
- **Target-P Min testados**: `[1.0]`
- **Target-P Max testados**: `[1.0]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.05, 0.15, 0.25]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2600 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 256 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 1.00 | 1.00 | 0.05 | 36.40 | 20.03 | 20.25 | 20.64 | 47.41s | 1.00x |
| 1.00 | 1.00 | 0.15 | 35.13 | 20.17 | 20.31 | 20.78 | 49.89s | 1.01x |
| 1.00 | 1.00 | 0.25 | 35.35 | 20.06 | 20.13 | 20.58 | 51.86s | 1.00x |


---

## Resumo do Sweep: 2026-09-11 16:59:37

- **Data**: 2026-09-11 16:59:37
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.5, 0.6, 0.7, 0.8, 0.9]`
- **Target-P Max testados**: `[1.0]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.1]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.50-1.00 | 1.00 | 0.10 | 37.52 | 21.46 | 21.59 | 21.97 | 46.99s | 1.00x |
| 0.60-1.00 | 1.00 | 0.10 | 38.21 | 21.00 | 21.25 | 21.64 | 44.77s | 0.98x |
| 0.70-1.00 | 1.00 | 0.10 | 36.60 | 20.73 | 20.97 | 21.37 | 45.76s | 0.97x |
| 0.80-1.00 | 1.00 | 0.10 | 36.00 | 20.57 | 20.79 | 21.23 | 46.79s | 0.96x |
| 0.90-1.00 | 1.00 | 0.10 | 35.24 | 20.55 | 20.75 | 21.26 | 47.58s | 0.96x |


---

## Resumo do Sweep: 2026-09-11 17:29:28

- **Data**: 2026-09-11 17:29:28
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.85]`
- **Target-P Max testados**: `[0.9, 0.92, 0.94, 0.96, 0.98, 1.0]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.1]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.85-0.90 | 1.00 | 0.10 | 43.26 | 22.30 | 22.17 | 22.45 | 52.09s | 1.00x |
| 0.85-0.92 | 1.00 | 0.10 | 40.93 | 21.65 | 21.54 | 22.12 | 57.76s | 0.97x |
| 0.85-0.94 | 1.00 | 0.10 | 40.79 | 21.31 | 21.16 | 21.62 | 56.29s | 0.96x |
| 0.85-0.96 | 1.00 | 0.10 | 38.40 | 20.54 | 20.48 | 20.74 | 56.04s | 0.92x |
| 0.85-0.98 | 1.00 | 0.10 | 37.34 | 20.22 | 20.07 | 20.57 | 63.59s | 0.91x |
| 0.85-1.00 | 1.00 | 0.10 | 36.54 | 19.85 | 19.85 | 20.11 | 55.21s | 0.89x |


---

## Resumo do Sweep: 2026-09-11 21:28:23

- **Data**: 2026-09-11 21:28:23
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.9, 0.92, 0.94, 0.96, 0.98, 1.0]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.1]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70-0.90 | 1.00 | 0.10 | 45.87 | 23.29 | 23.46 | 23.90 | 42.23s | 1.00x |
| 0.70-0.92 | 1.00 | 0.10 | 43.40 | 23.26 | 23.40 | 23.90 | 43.36s | 1.00x |
| 0.70-0.94 | 1.00 | 0.10 | 41.86 | 22.87 | 23.04 | 23.47 | 43.08s | 0.98x |
| 0.70-0.96 | 1.00 | 0.10 | 39.53 | 21.99 | 22.19 | 22.66 | 44.40s | 0.94x |
| 0.70-0.98 | 1.00 | 0.10 | 38.08 | 21.06 | 21.29 | 21.74 | 45.55s | 0.90x |
| 0.70-1.00 | 1.00 | 0.10 | 35.81 | 20.62 | 20.85 | 21.22 | 46.06s | 0.89x |


---

## Resumo do Sweep: 2026-09-12 07:47:26

- **Data**: 2026-09-12 07:47:26
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.3, 0.4, 0.5, 0.6, 0.7, 0.8]`
- **Target-P Max testados**: `[0.8]`
- **Swap-Max testados**: `[1.0]`
- **Attenuation testados**: `[0.1]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latência Média | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.30-0.80 | 1.00 | 0.10 | 63.12 | 28.49 | 28.81 | 29.57 | 33.48s | 1.00x |
| 0.40-0.80 | 1.00 | 0.10 | 59.10 | 28.21 | 28.36 | 29.32 | 36.13s | 0.99x |
| 0.50-0.80 | 1.00 | 0.10 | 59.90 | 27.28 | 27.45 | 28.14 | 36.41s | 0.96x |
| 0.60-0.80 | 1.00 | 0.10 | 54.71 | 26.97 | 27.13 | 27.75 | 37.21s | 0.95x |
| 0.70-0.80 | 1.00 | 0.10 | 55.67 | 26.95 | 27.32 | 28.00 | 34.61s | 0.95x |
| 0.80 | 1.00 | 0.10 | 52.20 | 26.44 | 26.61 | 27.26 | 37.97s | 0.93x |



===========================================================================================================================
                                           TABELA CONSOLIDADA DE RESULTADOS
===========================================================================================================================
Target P (Min-Max) | Swap Max   | Atten   | Prompt t/s  | Pred (Orig) | Pred (Pond) | Pred (S/Warm) | Latencia   | Speedup
---------------------------------------------------------------------------------------------------------------------------
0.80               | 0.10       | 0.05    | 57.96       | 25.53       | 25.76       | 26.15         | 36.68    s | 1.00   x
0.80               | 0.10       | 0.10    | 53.22       | 25.92       | 25.97       | 26.71         | 41.11    s | 1.02   x
0.80               | 0.10       | 0.20    | 56.30       | 25.37       | 25.44       | 25.80         | 40.87    s | 0.99   x
0.80               | 0.20       | 0.05    | 56.71       | 25.38       | 25.49       | 25.91         | 39.73    s | 0.99   x
0.80               | 0.20       | 0.10    | 56.79       | 25.85       | 26.10       | 26.70         | 36.89    s | 1.01   x
0.80               | 0.20       | 0.20    | 52.27       | 25.84       | 25.86       | 26.49         | 41.85    s | 1.01   x
0.80               | 0.50       | 0.05    | 54.85       | 25.77       | 26.08       | 26.58         | 36.09    s | 1.01   x
0.80               | 0.50       | 0.10    | 55.25       | 25.53       | 25.59       | 26.07         | 41.27    s | 1.00   x
0.80               | 0.50       | 0.20    | 53.29       | 25.74       | 25.84       | 26.41         | 40.05    s | 1.01   x
0.80               | 0.70       | 0.05    | 56.34       | 25.75       | 25.87       | 26.43         | 39.50    s | 1.01   x
0.80               | 0.70       | 0.10    | 53.33       | 26.15       | 26.18       | 27.00         | 41.05    s | 1.02   x
0.80               | 0.70       | 0.20    | 54.40       | 25.80       | 25.94       | 26.64         | 39.39    s | 1.01   x
0.80               | 1.00       | 0.05    | 55.02       | 25.57       | 25.82       | 26.22         | 36.54    s | 1.00   x
0.80               | 1.00       | 0.10    | 52.61       | 25.87       | 25.91       | 26.52         | 41.61    s | 1.01   x
0.80               | 1.00       | 0.20    | 50.74       | 26.01       | 26.15       | 26.81         | 38.99    s | 1.02   x
===========================================================================================================================

---

## Resumo do Sweep: 2026-09-12 22:35:18

- **Data**: 2026-09-12 22:35:18
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.0, 0.1, 0.2]`
- **Imatrix-Weight testados**: `[0.0]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.00 | 0.20 | 0.05 | 51.28 | 23.82 | 23.67 | 24.23 | 51.60s | 1.00x |
| 0.80 | 0.10 | 0.20 | 0.05 | 54.06 | 24.16 | 24.13 | 24.27 | 45.09s | 1.01x |
| 0.80 | 0.20 | 0.20 | 0.05 | 54.51 | 23.99 | 23.87 | 24.24 | 47.14s | 1.01x |


---

## Resumo do Sweep: 2026-09-12 23:38:04

- **Data**: 2026-09-12 23:38:04
- **Modelo**: `Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.0, 0.1, 0.2, 0.3, 0.4, 0.5]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.00 | 0.20 | 0.05 | 51.95 | 24.03 | 23.79 | 24.24 | 53.20s | 1.00x |
| 0.80 | 0.10 | 0.10 | 0.20 | 0.05 | 55.21 | 24.21 | 24.04 | 24.52 | 51.13s | 1.01x |
| 0.80 | 0.10 | 0.20 | 0.20 | 0.05 | 55.11 | 24.21 | 24.02 | 24.36 | 49.41s | 1.01x |
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 55.49 | 24.26 | 24.09 | 24.40 | 47.34s | 1.01x |
| 0.80 | 0.10 | 0.40 | 0.20 | 0.05 | 55.57 | 24.28 | 24.17 | 24.50 | 48.17s | 1.01x |
| 0.80 | 0.10 | 0.50 | 0.20 | 0.05 | 56.36 | 24.28 | 24.04 | 24.45 | 53.93s | 1.01x |


---

## Resumo do Sweep: 2026-09-13 00:12:41

- **Data**: 2026-09-13 00:12:41
- **Modelo**: `Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `1800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q4_K_XL/Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 1800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 31.14 | 16.27 | 15.97 | 17.56 | 70.69s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 00:21:28

- **Data**: 2026-09-13 00:21:28
- **Modelo**: `Qwen3.8-Flash-Next-Q4_K_S-00001-of-00003.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `1800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--bartowski--Qwen3.8-Flash-Next-GGUF/snapshots/928589fdb66c6ff07f22ac561e3fbce76553548f/Qwen3.8-Flash-Next-Q4_K_S/Qwen3.8-Flash-Next-Q4_K_S-00001-of-00003.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 1800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 34.06 | 17.34 | 17.28 | 19.69 | 65.33s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 00:34:31

- **Data**: 2026-09-13 00:34:31
- **Modelo**: `Qwen3.8-Flash-Next-Q4_K_S-00001-of-00003.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--bartowski--Qwen3.8-Flash-Next-GGUF/snapshots/928589fdb66c6ff07f22ac561e3fbce76553548f/Qwen3.8-Flash-Next-Q4_K_S/Qwen3.8-Flash-Next-Q4_K_S-00001-of-00003.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 34.91 | 18.41 | 18.47 | 20.35 | 59.09s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 00:58:34

- **Data**: 2026-09-13 00:58:34
- **Modelo**: `Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `1800 MiB`
- **Target-P Min testados**: `[0.3, 0.4, 0.5, 0.6, 0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q4_K_XL/Qwen3.8-Flash-Next-UD-Q4_K_XL-00001-of-00004.gguf \
  --expert-imatrix /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q6_K_XL/imatrix_unsloth.gguf --vram-expert-budget-mb 1800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.30 | 0.10 | 0.30 | 0.20 | 0.05 | 71.72 | 28.78 | 28.50 | 30.26 | 38.30s | 1.00x |
| 0.40 | 0.10 | 0.30 | 0.20 | 0.05 | 57.93 | 25.87 | 25.41 | 28.06 | 47.31s | 0.90x |
| 0.50 | 0.10 | 0.30 | 0.20 | 0.05 | 51.68 | 23.23 | 22.70 | 24.48 | 57.26s | 0.81x |
| 0.60 | 0.10 | 0.30 | 0.20 | 0.05 | 40.25 | 20.71 | 20.16 | 23.21 | 62.98s | 0.72x |
| 0.70 | 0.10 | 0.30 | 0.20 | 0.05 | 34.23 | 17.66 | 17.29 | 19.80 | 72.62s | 0.61x |


---

## Resumo do Sweep: 2026-09-13 07:13:43

- **Data**: 2026-09-13 07:13:43
- **Modelo**: `Qwen3.8-Flash-Next-APEX-I-Compact-00001-of-00006.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--mudler--Qwen3.8-Flash-Next-APEX-GGUF/snapshots/d0ab3614ca01f71533ad8b15844bd75853da27db/Qwen3.8-Flash-Next-APEX-I-Compact-00001-of-00006.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 55.93 | 25.46 | 25.21 | 25.85 | 48.07s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 16:28:06

- **Data**: 2026-09-13 16:28:06
- **Modelo**: `Qwen3.8-Flash-Next-AP-IQ4_XS.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.3]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-IQ4_XS/Qwen3.8-Flash-Next-AP-IQ4_XS.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.30 | 0.20 | 0.05 | 35.30 | 20.10 | 19.96 | 20.44 | 58.36s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 20:51:24

- **Data**: 2026-09-13 20:51:24
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0, 0.1, 0.2]`
- **Imatrix-Weight testados**: `[0.0]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.00 | 0.20 | 0.05 | 49.24 | 23.19 | 23.21 | 24.27 | 46.80s | 1.00x |
| 0.70 | 0.10 | 0.20 | 0.05 | 54.62 | 24.56 | 24.50 | 25.47 | 44.63s | 1.06x |
| 0.70 | 0.20 | 0.20 | 0.05 | 58.41 | 25.78 | 25.41 | 26.35 | 47.43s | 1.11x |


---

## Resumo do Sweep: 2026-09-13 20:55:41

- **Data**: 2026-09-13 20:55:41
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.3]`
- **Imatrix-Weight testados**: `[0.0]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.30 | 0.20 | 0.05 | 56.04 | 24.66 | 24.80 | 26.07 | 45.12s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 21:16:51

- **Data**: 2026-09-13 21:16:51
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.0, 0.1, 0.2, 0.3, 0.4, 0.5]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/Qwen3.8-Flash-Next-AD-4.27bpw-Q4_K_M/imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.00 | 0.20 | 0.05 | 58.56 | 25.66 | 25.03 | 25.59 | 47.99s | 1.00x |
| 0.70 | 0.20 | 0.10 | 0.20 | 0.05 | 53.01 | 25.12 | 24.79 | 26.27 | 48.05s | 0.98x |
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 57.53 | 24.91 | 24.63 | 24.98 | 47.30s | 0.97x |
| 0.70 | 0.20 | 0.30 | 0.20 | 0.05 | 55.23 | 25.56 | 25.60 | 25.78 | 40.05s | 1.00x |
| 0.70 | 0.20 | 0.40 | 0.20 | 0.05 | 57.12 | 25.17 | 25.02 | 25.16 | 42.76s | 0.98x |
| 0.70 | 0.20 | 0.50 | 0.20 | 0.05 | 53.74 | 24.57 | 24.55 | 25.55 | 44.09s | 0.96x |


---

## Resumo do Sweep: 2026-09-13 22:23:46

- **Data**: 2026-09-13 22:23:46
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.0, 0.1, 0.2, 0.3, 0.4, 0.5]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/models/hub/models--unsloth--Qwen3.8-Flash-Next-GGUF/snapshots/38bb39ee97821de2c9009abb7e93950eec396e66/UD-Q6_K_XL/imatrix_unsloth.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.00 | 0.20 | 0.05 | 57.37 | 25.81 | 25.63 | 26.34 | 42.36s | 1.00x |
| 0.70 | 0.20 | 0.10 | 0.20 | 0.05 | 56.59 | 25.76 | 25.65 | 26.13 | 41.09s | 1.00x |
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 52.10 | 24.33 | 24.28 | 24.82 | 44.01s | 0.94x |
| 0.70 | 0.20 | 0.30 | 0.20 | 0.05 | 49.65 | 24.28 | 24.02 | 25.97 | 47.92s | 0.94x |
| 0.70 | 0.20 | 0.40 | 0.20 | 0.05 | 51.39 | 25.31 | 24.95 | 25.71 | 48.74s | 0.98x |
| 0.70 | 0.20 | 0.50 | 0.20 | 0.05 | 48.05 | 24.03 | 23.63 | 25.43 | 51.79s | 0.93x |


---

## Resumo do Sweep: 2026-09-13 22:40:12

- **Data**: 2026-09-13 22:40:12
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.0, 0.1, 0.2, 0.3, 0.4, 0.5]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.00 | 0.20 | 0.05 | 55.08 | 25.85 | 26.01 | 26.89 | 38.74s | 1.00x |
| 0.70 | 0.20 | 0.10 | 0.20 | 0.05 | 56.20 | 27.04 | 27.27 | 28.47 | 36.65s | 1.05x |
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 61.95 | 27.43 | 27.54 | 28.56 | 37.35s | 1.06x |
| 0.70 | 0.20 | 0.30 | 0.20 | 0.05 | 60.12 | 27.02 | 27.20 | 27.85 | 36.59s | 1.05x |
| 0.70 | 0.20 | 0.40 | 0.20 | 0.05 | 64.07 | 27.15 | 27.25 | 28.12 | 37.76s | 1.05x |
| 0.70 | 0.20 | 0.50 | 0.20 | 0.05 | 67.00 | 27.32 | 27.49 | 28.22 | 36.20s | 1.06x |


---

## Resumo do Sweep: 2026-09-13 23:09:24

- **Data**: 2026-09-13 23:09:24
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.75]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 0.20 | 0.20 | 0.20 | 0.05 | 45.39 | 23.01 | 23.07 | 25.59 | 43.32s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 23:18:21

- **Data**: 2026-09-13 23:18:21
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.75]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 0.10 | 0.20 | 0.20 | 0.05 | 50.57 | 23.47 | 23.41 | 24.15 | 45.84s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 23:22:32

- **Data**: 2026-09-13 23:22:32
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70-0.75 | 0.10 | 0.20 | 0.20 | 0.05 | 47.33 | 24.46 | 24.68 | 26.53 | 40.44s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 23:25:17

- **Data**: 2026-09-13 23:25:17
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70-0.75 | 0.20 | 0.20 | 0.20 | 0.05 | 54.38 | 25.46 | 25.52 | 25.87 | 41.38s | 1.00x |


---

## Resumo do Sweep: 2026-09-13 23:56:42

- **Data**: 2026-09-13 23:56:42
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AP-Q5_K_XL/Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 31.21 | 19.32 | 19.61 | 22.35 | 49.38s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 00:01:22

- **Data**: 2026-09-14 00:01:22
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.6]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.0]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 3 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AP-Q5_K_XL/Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.60 | 0.20 | 0.00 | 0.05 | 51.51 | 23.03 | 22.91 | 24.47 | 47.39s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 00:07:00

- **Data**: 2026-09-14 00:07:00
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.6]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/Qwen3.8-Flash-Next-AP-Q5_K_XL/Qwen3.8-Flash-Next-AP-Q5_K_XL.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.60 | 0.20 | 0.20 | 0.20 | 0.05 | 49.84 | 24.42 | 22.97 | 25.08 | 58.64s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 01:04:28

- **Data**: 2026-09-14 01:04:28
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.65]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.65-0.75 | 0.10 | 0.20 | 0.20 | 0.05 | 49.71 | 23.58 | 23.44 | 24.48 | 46.60s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 01:09:03

- **Data**: 2026-09-14 01:09:03
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.75]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 0.20 | 0.20 | 0.20 | 0.05 | 54.90 | 24.59 | 24.43 | 24.78 | 47.14s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 01:14:00

- **Data**: 2026-09-14 01:14:00
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.20 | 0.20 | 0.05 | 50.80 | 22.44 | 22.19 | 22.65 | 53.41s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 01:21:04

- **Data**: 2026-09-14 01:21:04
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.05]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.05 | 0.20 | 0.20 | 0.05 | 47.02 | 22.70 | 22.63 | 23.03 | 48.97s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 01:36:09

- **Data**: 2026-09-14 01:36:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/pi/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/pi/llama.cpp/build/bin/llama-server --fit off -m /home/pi/nvme/models/hub/models--agentionai--Qwen3.8-Flash-Next-AP-GGUF/snapshots/0061a60e46ad672a73cec31cb627dc841d4760a4/AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/pi/nvme/bartowski-Qwen3.8-Flash-Next-IQ4_XS/Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/pi/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 52.33 | 24.67 | 24.42 | 25.63 | 48.71s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 18:53:59

- **Data**: 2026-09-14 18:53:59
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 65.06 | 27.65 | 27.49 | 28.23 | 41.41s | 1.00x |


---

## Resumo do Sweep: 2026-09-14 23:54:29

- **Data**: 2026-09-14 23:54:29
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 44.38 | 21.46 | 20.42 | 24.78 | 53.71s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 14:37:37

- **Data**: 2026-09-15 14:37:37
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 2 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 32.44 | 20.18 | 20.00 | 24.22 | 49.53s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 15:04:38

- **Data**: 2026-09-15 15:04:38
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 2 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 31.08 | 21.64 | 21.17 | 27.21 | 46.54s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 20:13:11

- **Data**: 2026-09-15 20:13:11
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 71.01 | 27.09 | 26.44 | 26.89 | 41.94s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 20:19:09

- **Data**: 2026-09-15 20:19:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.10 | 0.20 | 0.20 | 0.05 | 79.77 | 28.62 | 28.22 | 28.35 | 40.09s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 21:28:03

- **Data**: 2026-09-15 21:28:03
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 80.17 | 28.95 | 28.51 | 28.66 | 38.52s | 1.00x |


---

## Resumo do Sweep: 2026-09-15 23:48:16

- **Data**: 2026-09-15 23:48:16
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 71.90 | 26.16 | 25.39 | 25.41 | 46.03s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 00:10:33

- **Data**: 2026-09-16 00:10:33
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 70.65 | 28.02 | 27.79 | 27.67 | 39.92s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 00:16:40

- **Data**: 2026-09-16 00:16:40
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 79.21 | 28.04 | 27.92 | 27.69 | 37.38s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 00:22:35

- **Data**: 2026-09-16 00:22:35
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 65536 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 78.44 | 28.29 | 27.55 | 28.15 | 45.38s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 00:30:12

- **Data**: 2026-09-16 00:30:12
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 120000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 75.94 | 27.84 | 27.58 | 27.74 | 42.89s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 01:33:21

- **Data**: 2026-09-16 01:33:21
- **Modelo**: `Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/hub/models--ISTA-DASLab--Qwen3.8-Flash-Next-GSQ-RCO-GGUF/snapshots/1c04b8102ca5346f1faf4d9914503e378d713021/IQ3_XXS/Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 47.83 | 23.41 | 22.61 | 23.39 | 53.11s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 02:17:35

- **Data**: 2026-09-16 02:17:35
- **Modelo**: `Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/hub/models--ISTA-DASLab--Qwen3.8-Flash-Next-GSQ-RCO-GGUF/snapshots/1c04b8102ca5346f1faf4d9914503e378d713021/IQ3_XXS/Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 40.64 | 21.48 | 20.87 | 21.26 | 58.85s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 02:36:47

- **Data**: 2026-09-16 02:36:47
- **Modelo**: `Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/hub/models--ISTA-DASLab--Qwen3.8-Flash-Next-GSQ-RCO-GGUF/snapshots/1c04b8102ca5346f1faf4d9914503e378d713021/IQ3_XXS/Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 49.55 | 23.24 | 22.30 | 23.10 | 56.64s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 03:01:51

- **Data**: 2026-09-16 03:01:51
- **Modelo**: `Qwen3.8-Flash-Next-AD-5.00bpw-Q5_K_M-M64-00001-of-00033.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/hub/models--AtomicChat--Qwen3.8-Flash-Next-GGUF/snapshots/142262902a46f7daed19c79d0771534c8106ad59/Qwen3.8-Flash-Next-AD-5.00bpw-Q5_K_M-M64/Qwen3.8-Flash-Next-AD-5.00bpw-Q5_K_M-M64-00001-of-00033.gguf \
  --expert-imatrix /home/ai/models/hub/models--AtomicChat--Qwen3.8-Flash-Next-GGUF/snapshots/142262902a46f7daed19c79d0771534c8106ad59/imatrix.gguf --vram-expert-budget-mb 2000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 63.30 | 26.73 | 26.18 | 26.47 | 47.78s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 05:19:42

- **Data**: 2026-09-16 05:19:42
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 120000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 67.11 | 25.66 | 25.31 | 25.14 | 43.93s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 05:26:26

- **Data**: 2026-09-16 05:26:26
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 120000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 74.95 | 28.19 | 27.84 | 28.07 | 40.53s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 10:58:15

- **Data**: 2026-09-16 10:58:15
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 110000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 70.15 | 28.00 | 27.63 | 27.62 | 39.72s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 11:09:09

- **Data**: 2026-09-16 11:09:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3000 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3000 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 110000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 70.01 | 27.74 | 27.49 | 27.31 | 38.04s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 11:40:12

- **Data**: 2026-09-16 11:40:12
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 69.75 | 27.21 | 26.76 | 26.84 | 42.53s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 11:52:30

- **Data**: 2026-09-16 11:52:30
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2700 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2700 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 68.79 | 27.64 | 27.28 | 27.36 | 40.86s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 12:14:51

- **Data**: 2026-09-16 12:14:51
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `2900 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 2900 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 65.71 | 27.49 | 27.40 | 27.02 | 39.85s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 12:50:00

- **Data**: 2026-09-16 12:50:00
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 72.37 | 28.49 | 28.39 | 27.99 | 38.60s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 12:59:57

- **Data**: 2026-09-16 12:59:57
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3500 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3500 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 73.27 | 28.14 | 27.68 | 27.78 | 42.58s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 13:31:10

- **Data**: 2026-09-16 13:31:10
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3500 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3500 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 75.12 | 28.24 | 27.56 | 27.87 | 41.78s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 14:06:40

- **Data**: 2026-09-16 14:06:40
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3500 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3500 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 73.95 | 26.51 | 25.44 | 25.59 | 44.75s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 14:52:36

- **Data**: 2026-09-16 14:52:36
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3500 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3500 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 74.88 | 27.22 | 26.73 | 26.85 | 41.61s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 14:59:00

- **Data**: 2026-09-16 14:59:00
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3500 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3500 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q8_0 --cache-type-v q4_0 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 75.23 | 28.57 | 28.04 | 28.04 | 38.48s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 15:17:44

- **Data**: 2026-09-16 15:17:44
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 86.17 | 29.68 | 28.93 | 29.07 | 42.57s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 15:24:28

- **Data**: 2026-09-16 15:24:28
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 83.64 | 29.85 | 29.12 | 29.47 | 39.54s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 15:28:43

- **Data**: 2026-09-16 15:28:43
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 84.81 | 29.74 | 29.33 | 29.52 | 37.57s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 15:44:05

- **Data**: 2026-09-16 15:44:05
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 82.94 | 30.09 | 29.67 | 29.84 | 37.34s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 16:00:40

- **Data**: 2026-09-16 16:00:40
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 82.56 | 30.10 | 29.77 | 29.68 | 36.60s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 16:06:21

- **Data**: 2026-09-16 16:06:21
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 83.16 | 30.10 | 29.55 | 29.93 | 41.10s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 16:14:47

- **Data**: 2026-09-16 16:14:47
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 84.09 | 29.88 | 29.63 | 29.53 | 36.40s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 16:21:35

- **Data**: 2026-09-16 16:21:35
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 81.00 | 30.06 | 29.84 | 29.71 | 37.60s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 17:16:29

- **Data**: 2026-09-16 17:16:29
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 84.10 | 30.20 | 29.85 | 29.91 | 36.35s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 17:20:35

- **Data**: 2026-09-16 17:20:35
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 83.84 | 29.65 | 29.37 | 29.23 | 36.79s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 17:25:00

- **Data**: 2026-09-16 17:25:00
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.7]`
- **Target-P Max testados**: `[0.7]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.70 | 0.20 | 0.20 | 0.20 | 0.05 | 82.58 | 30.00 | 29.19 | 29.70 | 42.74s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 22:23:19

- **Data**: 2026-09-16 22:23:19
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.75]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 0.20 | 0.20 | 0.20 | 0.05 | 72.86 | 27.77 | 27.38 | 27.32 | 40.69s | 1.00x |


---

## Resumo do Sweep: 2026-09-16 22:27:59

- **Data**: 2026-09-16 22:27:59
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.75]`
- **Target-P Max testados**: `[0.75]`
- **Depth-Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.75 | 0.20 | 0.20 | 0.20 | 0.05 | 73.82 | 28.13 | 27.84 | 27.76 | 38.40s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 00:27:28

- **Data**: 2026-09-17 00:27:28
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.20 | 0.20 | 0.05 | 59.66 | 26.14 | 25.87 | 25.77 | 43.03s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 00:46:03

- **Data**: 2026-09-17 00:46:03
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 4096 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.20 | 0.20 | 0.05 | 58.48 | 26.01 | 25.36 | 25.67 | 45.21s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 01:04:09

- **Data**: 2026-09-17 01:04:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.0, 0.8]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.00 | 0.20 | 0.20 | 0.05 | 286.73 | 51.47 | 51.40 | 51.50 | 7.85s | 1.00x |
| 0.80 | 0.20 | 0.20 | 0.05 | 57.88 | 25.82 | 25.38 | 25.54 | 45.06s | 0.50x |


---

## Resumo do Sweep: 2026-09-17 11:06:15

- **Data**: 2026-09-17 11:06:15
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.0]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.00 | 0.20 | 0.20 | 0.05 | 36.11 | 19.02 | 18.87 | 18.91 | 56.86s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 11:22:10

- **Data**: 2026-09-17 11:22:10
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `0 MiB`
- **Target-P Min testados**: `[0.0]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.0]`
- **Swap-Max testados**: `[0.0]`
- **Attenuation testados**: `[0.0]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 0 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 2048 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.00 | 0.00 | 0.00 | 72.62 | 16.19 | 16.18 | 16.14 | 63.56s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 11:30:44

- **Data**: 2026-09-17 11:30:44
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Min testados**: `[0.0]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.00 | 0.20 | 0.20 | 0.05 | 37.12 | 19.37 | 19.19 | 19.23 | 58.78s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 11:38:23

- **Data**: 2026-09-17 11:38:23
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Min testados**: `[0.0]`
- **Target-P Max testados**: `[0.0]`
- **Depth-Delta testados**: `[0.0]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.00 | 0.20 | 0.20 | 0.05 | 37.92 | 19.51 | 19.34 | 19.32 | 57.10s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 12:07:42

- **Data**: 2026-09-17 12:07:42
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.1, 0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.10 | 0.20 | 0.20 | 0.05 | 60.55 | 25.97 | 25.69 | 25.61 | 42.87s | 1.00x |
| 0.80 | 0.20 | 0.20 | 0.20 | 0.05 | 63.43 | 26.05 | 25.82 | 25.68 | 42.53s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 12:25:19

- **Data**: 2026-09-17 12:25:19
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.0, 0.3]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.00 | 0.20 | 0.20 | 0.05 | 56.49 | 25.73 | 25.16 | 25.42 | 49.50s | 1.00x |
| 0.80 | 0.30 | 0.20 | 0.20 | 0.05 | 67.56 | 27.08 | 26.48 | 26.87 | 44.43s | 1.05x |


---

## Resumo do Sweep: 2026-09-17 12:55:09

- **Data**: 2026-09-17 12:55:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Min testados**: `[0.8]`
- **Target-P Max testados**: `[0.8]`
- **Depth-Delta testados**: `[0.15]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.15 | 0.20 | 0.20 | 0.05 | 63.38 | 26.69 | 26.29 | 26.22 | 40.83s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 13:49:17

- **Data**: 2026-09-17 13:49:17
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Min testados**: `[0.85]`
- **Target-P Max testados**: `[0.85]`
- **Depth-Delta testados**: `[0.1]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-min <TARGET_P_MIN> --expert-target-p-max <TARGET_P_MAX> \
  --expert-target-p-depth-delta <DEPTH_DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P (Min-Max) | Depth Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.85 | 0.10 | 0.20 | 0.20 | 0.05 | 53.13 | 24.49 | 24.05 | 24.19 | 46.31s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 16:57:11

- **Data**: 2026-09-17 16:57:11
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `[0.7]`
- **Target-P Mid testados**: `[0.75]`
- **Target-P Late testados**: `[0.8]`
- **Delta testados**: `[0.15]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <P_EARLY> --expert-target-p-mid <P_MID> --expert-target-p-late <P_LATE> \
  --expert-target-p-delta <DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [E, M, L] | Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.70,0.75,0.80] | 0.15 | 0.20 | 0.20 | 0.05 | 52.40 | 26.23 | 26.52 | 26.49 | 50.71s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 17:02:46

- **Data**: 2026-09-17 17:02:46
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `[0.8]`
- **Target-P Mid testados**: `[0.8]`
- **Target-P Late testados**: `[0.8]`
- **Delta testados**: `[0.15]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <P_EARLY> --expert-target-p-mid <P_MID> --expert-target-p-late <P_LATE> \
  --expert-target-p-delta <DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [E, M, L] | Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0.80 | 0.15 | 0.20 | 0.20 | 0.05 | 45.46 | 40.03 | 39.88 | 40.11 | 35.68s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 17:27:32

- **Data**: 2026-09-17 17:27:32
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `[0.725]`
- **Target-P Mid testados**: `[0.8]`
- **Target-P Late testados**: `[0.875]`
- **Delta testados**: `[0.075]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <P_EARLY> --expert-target-p-mid <P_MID> --expert-target-p-late <P_LATE> \
  --expert-target-p-delta <DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [E, M, L] | Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.72,0.80,0.88] | 0.07 | 0.20 | 0.20 | 0.05 | 51.87 | 25.02 | 24.66 | 24.81 | 47.90s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 17:49:38

- **Data**: 2026-09-17 17:49:38
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `[0.7]`
- **Target-P Mid testados**: `[0.7]`
- **Target-P Late testados**: `[1.1]`
- **Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <P_EARLY> --expert-target-p-mid <P_MID> --expert-target-p-late <P_LATE> \
  --expert-target-p-delta <DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [E, M, L] | Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.70,0.70,1.10] | 0.20 | 0.20 | 0.20 | 0.05 | 46.73 | 23.33 | 22.99 | 23.18 | 50.14s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 17:59:49

- **Data**: 2026-09-17 17:59:49
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `[0.6]`
- **Target-P Mid testados**: `[0.7]`
- **Target-P Late testados**: `[1.1]`
- **Delta testados**: `[0.2]`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <P_EARLY> --expert-target-p-mid <P_MID> --expert-target-p-late <P_LATE> \
  --expert-target-p-delta <DELTA> --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [E, M, L] | Delta | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:------------------:|:-----:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.60,0.70,1.10] | 0.20 | 0.20 | 0.20 | 0.05 | 51.64 | 25.05 | 24.44 | 24.80 | 49.04s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 18:21:36

- **Data**: 2026-09-17 18:21:36
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.5,0.60']`
- **Target-P Mid testados**: `['0.8,0.9']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.5,0.60, 0.8,0.9, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 72.17 | 30.02 | 29.30 | 29.62 | 40.51s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 18:52:58

- **Data**: 2026-09-17 18:52:58
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.8,0.9']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.8,0.9, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 61.69 | 27.07 | 26.71 | 26.83 | 41.79s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 19:04:30

- **Data**: 2026-09-17 19:04:30
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.6,0.8']`
- **Target-P Mid testados**: `['0.8,0.9']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.6,0.8, 0.8,0.9, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 68.09 | 28.40 | 27.96 | 28.01 | 41.48s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 19:53:34

- **Data**: 2026-09-17 19:53:34
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.8']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.8, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 62.95 | 27.41 | 26.92 | 27.16 | 42.42s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 20:07:01

- **Data**: 2026-09-17 20:07:01
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.8']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.8, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 65.04 | 27.13 | 26.75 | 26.80 | 40.53s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 20:31:06

- **Data**: 2026-09-17 20:31:06
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.8']`
- **Target-P Mid testados**: `['0.8']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.8, 0.8, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 55.23 | 26.08 | 25.33 | 25.75 | 47.77s | 1.00x |


---

## Resumo do Sweep: 2026-09-17 20:39:14

- **Data**: 2026-09-17 20:39:14
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.9,0.95] | 0.20 | 0.20 | 0.05 | 67.44 | 28.43 | 28.14 | 28.03 | 39.78s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 02:08:50

- **Data**: 2026-09-18 02:08:50
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.9']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.9] | 0.20 | 0.20 | 0.05 | 69.05 | 28.81 | 27.82 | 28.55 | 45.31s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 02:15:01

- **Data**: 2026-09-18 02:15:01
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95] | 0.20 | 0.20 | 0.05 | 63.54 | 27.86 | 27.39 | 27.65 | 41.57s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 02:20:33

- **Data**: 2026-09-18 02:20:33
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.90,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.90,1.0] | 0.20 | 0.20 | 0.05 | 67.32 | 28.51 | 28.03 | 28.35 | 44.00s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 02:26:05

- **Data**: 2026-09-18 02:26:05
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 65.59 | 27.56 | 27.07 | 27.27 | 41.28s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 12:08:49

- **Data**: 2026-09-18 12:08:49
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.5,0.8']`
- **Target-P Mid testados**: `['0.5,0.8|0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.5,0.8, 0.5,0.8|0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 54.78 | 25.03 | 24.63 | 24.70 | 43.08s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 12:19:09

- **Data**: 2026-09-18 12:19:09
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.5,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.5,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 54.05 | 36.81 | 36.86 | 37.73 | 37.72s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 13:27:02

- **Data**: 2026-09-18 13:27:02
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.5,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench throughput_16k --category all --osl 1024 --concurrency 1 --limit 2 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.5,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 32.85 | 20.34 | 20.23 | 20.41 | 320.45s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 14:21:23

- **Data**: 2026-09-18 14:21:23
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench throughput_16k --category all --osl 1024 --concurrency 1 --limit 2 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

---

## Resumo do Sweep: 2026-09-18 19:04:30

- **Data**: 2026-09-18 19:04:30
- **Modelo**: `Qwen3.8-Flash-Next-Custom-Opt-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `5200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-Custom-Opt-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 5200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 64.39 | 27.59 | 27.21 | 27.70 | 40.85s | 1.00x |


---

## Resumo do Sweep: 2026-09-18 19:07:53

- **Data**: 2026-09-18 19:07:53
- **Modelo**: `Qwen3.8-Flash-Next-Custom-Opt-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `5200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-Custom-Opt-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 5200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 65.82 | 28.11 | 27.81 | 28.37 | 39.70s | 1.00x |


---

## Resumo do Sweep: 2026-09-19 00:03:25

- **Data**: 2026-09-19 00:03:25
- **Modelo**: `Qwen3.8-Flash-Next-Custom-HQ-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-Custom-HQ-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 57.48 | 24.16 | 23.67 | 24.14 | 46.81s | 1.00x |


---

## Resumo do Sweep: 2026-09-19 11:07:06

- **Data**: 2026-09-19 11:07:06
- **Modelo**: `Qwen3.8-Flash-Next-Custom-Atomic-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-Custom-Atomic-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 29.85 | 17.57 | 16.44 | 18.74 | 67.61s | 1.00x |


---

## Resumo do Sweep: 2026-09-19 13:57:48

- **Data**: 2026-09-19 13:57:48
- **Modelo**: `Qwen3.8-Flash-Next-Custom-Atomic-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3800 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-Custom-Atomic-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3800 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 4096 -ub 1024 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 36.99 | 21.32 | 21.07 | 21.42 | 53.37s | 1.00x |


---

## Resumo do Sweep: 2026-09-19 18:57:16

- **Data**: 2026-09-19 18:57:16
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 58.95 | 25.53 | 25.23 | 25.59 | 44.20s | 1.00x |


---

## Resumo do Sweep: 2026-09-20 11:05:52

- **Data**: 2026-09-20 11:05:52
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4900 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_unsloth.gguf --vram-expert-budget-mb 4900 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 57.80 | 26.98 | 26.77 | 26.82 | 44.67s | 1.00x |


---

## Resumo do Sweep: 2026-09-20 19:33:25

- **Data**: 2026-09-20 19:33:25
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 65.11 | 26.47 | 26.28 | 26.62 | 43.51s | 1.00x |


---

## Resumo do Sweep: 2026-09-20 21:42:43

- **Data**: 2026-09-20 21:42:43
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 39.59 | 22.00 | 21.73 | 22.21 | 53.37s | 1.00x |


---

## Resumo do Sweep: 2026-09-20 23:23:23

- **Data**: 2026-09-20 23:23:23
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 60.58 | 25.42 | 25.23 | 25.50 | 45.10s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 03:38:51

- **Data**: 2026-09-21 03:38:51
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4800 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4800 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 60.82 | 26.63 | 26.28 | 26.62 | 46.86s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 03:42:11

- **Data**: 2026-09-21 03:42:11
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4800 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4800 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 64.92 | 27.28 | 27.12 | 27.33 | 40.08s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 10:24:50

- **Data**: 2026-09-21 10:24:50
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3600 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3600 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 57.08 | 24.62 | 24.37 | 24.64 | 49.22s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 10:28:58

- **Data**: 2026-09-21 10:28:58
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3600 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3600 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 61.25 | 24.99 | 24.60 | 25.01 | 53.06s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 12:19:38

- **Data**: 2026-09-21 12:19:38
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 54.37 | 25.60 | 25.39 | 25.76 | 43.49s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 12:23:09

- **Data**: 2026-09-21 12:23:09
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 59.46 | 26.12 | 25.94 | 26.12 | 42.73s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 14:32:24

- **Data**: 2026-09-21 14:32:24
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 58.46 | 21.20 | 21.03 | 21.21 | 49.63s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 14:36:56

- **Data**: 2026-09-21 14:36:56
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 57.99 | 21.44 | 21.04 | 21.61 | 56.82s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 14:52:19

- **Data**: 2026-09-21 14:52:19
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 49.72 | 20.33 | 20.06 | 21.14 | 62.50s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 15:13:14

- **Data**: 2026-09-21 15:13:14
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 39.11 | 19.58 | 19.57 | 20.12 | 55.08s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 15:18:40

- **Data**: 2026-09-21 15:18:40
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 41.24 | 20.23 | 20.14 | 20.24 | 58.05s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 15:35:05

- **Data**: 2026-09-21 15:35:05
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.7']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.7, 0.95] | 0.20 | 0.20 | 0.05 | 49.45 | 22.76 | 22.64 | 22.97 | 48.01s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 15:52:27

- **Data**: 2026-09-21 15:52:27
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7,0.8']`
- **Target-P Mid testados**: `['0.7,0.8']`
- **Target-P Late testados**: `['0.95,1.0']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7,0.8, 0.7,0.8, 0.95,1.0] | 0.20 | 0.20 | 0.05 | 42.12 | 22.82 | 22.69 | 22.93 | 47.40s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 15:55:53

- **Data**: 2026-09-21 15:55:53
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.7']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.7, 0.95] | 0.20 | 0.20 | 0.05 | 51.26 | 25.64 | 25.43 | 25.88 | 44.56s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 18:15:45

- **Data**: 2026-09-21 18:15:45
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.7']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.7, 0.95] | 0.20 | 0.20 | 0.05 | 48.98 | 25.14 | 25.03 | 25.37 | 42.41s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 18:19:21

- **Data**: 2026-09-21 18:19:21
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.7']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.7, 0.95] | 0.20 | 0.20 | 0.05 | 51.53 | 25.23 | 25.11 | 25.30 | 42.85s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 18:22:40

- **Data**: 2026-09-21 18:22:40
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Target-P Early testados**: `['0.7']`
- **Target-P Mid testados**: `['0.7']`
- **Target-P Late testados**: `['0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-target-p-early <MIN[,MAX]> --expert-target-p-mid <MIN[,MAX]> --expert-target-p-late <MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Target P [Early, Mid, Late] | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:---------------------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| [0.7, 0.7, 0.95] | 0.20 | 0.20 | 0.05 | 51.41 | 25.20 | 25.22 | 25.31 | 41.96s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 19:33:08

- **Data**: 2026-09-21 19:33:08
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Early-Exit configs testadas**: `['0,3,0.95;4,23,0.7;24,39,0.8;40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.95;4,23,0.7;24,39,0.8;40,47,0.95 | 0.20 | 0.20 | 0.05 | 50.14 | 24.89 | 24.67 | 24.94 | 46.24s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 19:38:13

- **Data**: 2026-09-21 19:38:13
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Early-Exit configs testadas**: `['0,3,0.90;4,39,0.6,0.8;40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.90;4,39,0.6,0.8;40,47,0.95 | 0.20 | 0.20 | 0.05 | 46.63 | 24.53 | 24.17 | 24.74 | 49.37s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 19:44:02

- **Data**: 2026-09-21 19:44:02
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,3,0.90;4,39,0.6,0.8;40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.90;4,39,0.6,0.8;40,47,0.95 | 0.20 | 0.20 | 0.05 | 46.80 | 24.14 | 23.99 | 24.22 | 45.91s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 19:48:48

- **Data**: 2026-09-21 19:48:48
- **Modelo**: `Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-AP-Q4_K_M/Qwen3.8-Flash-Next-AP-Q4_K_M-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 52.24 | 25.36 | 25.23 | 25.37 | 44.18s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 19:53:59

- **Data**: 2026-09-21 19:53:59
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 64.81 | 27.33 | 27.03 | 27.40 | 45.85s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 20:00:55

- **Data**: 2026-09-21 20:00:55
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 71.98 | 27.54 | 27.38 | 27.59 | 39.33s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 20:04:58

- **Data**: 2026-09-21 20:04:58
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3900 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 3900 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 65.65 | 26.94 | 26.79 | 27.06 | 40.20s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 20:09:09

- **Data**: 2026-09-21 20:09:09
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 54.64 | 23.40 | 22.49 | 22.23 | 49.68s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 20:14:22

- **Data**: 2026-09-21 20:14:22
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.5,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 69.95 | 27.36 | 27.15 | 27.50 | 42.75s | 1.00x |


---

## Resumo do Sweep: 2026-09-21 23:58:27

- **Data**: 2026-09-21 23:58:27
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.6,0.7; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.6,0.7; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 65.83 | 27.29 | 27.10 | 27.42 | 40.62s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 00:41:07

- **Data**: 2026-09-22 00:41:07
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 65.13 | 26.50 | 26.20 | 26.55 | 44.31s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 00:46:36

- **Data**: 2026-09-22 00:46:36
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1 | 0.20 | 0.20 | 0.05 | 64.95 | 26.74 | 26.57 | 26.91 | 40.77s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 00:52:19

- **Data**: 2026-09-22 00:52:19
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1 | 0.20 | 0.20 | 0.05 | 66.74 | 26.57 | 26.41 | 26.70 | 41.55s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 02:35:40

- **Data**: 2026-09-22 02:35:40
- **Modelo**: `Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,1; 1,3,0.90,1; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/export/hub/models--ISTA-DASLab--Qwen3.8-Flash-Next-GSQ-RCO-GGUF/snapshots/2c4721899b4382bd07dfb61ae4fbad90c09caf7d/IQ3_XXS/Qwen3.8-Flash-Next-GSQ-RCO-IQ3_XXS-00001-of-00002.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,1; 1,3,0.90,1; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.90,1 | 0.20 | 0.20 | 0.05 | 29.15 | 19.47 | 19.05 | 19.86 | 65.04s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 10:28:22

- **Data**: 2026-09-22 10:28:22
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.9,0.95; 1,3,0.90,0.95; 4,23,0.7; 24,39,0.8; 40,47,0.90,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.9,0.95; 1,3,0.90,0.95; 4,23,0.7; 24,39,0.8; 40,47,0.90,0.95 | 0.20 | 0.20 | 0.05 | 49.10 | 21.72 | 21.62 | 24.06 | 47.49s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 10:42:24

- **Data**: 2026-09-22 10:42:24
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.85; 1,3,0.8; 4,23,0.7; 24,39,0.8; 40,47,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.85; 1,3,0.8; 4,23,0.7; 24,39,0.8; 40,47,0.95 | 0.20 | 0.20 | 0.05 | 47.36 | 23.13 | 22.91 | 24.52 | 49.34s | 1.00x |



---

## Resumo do Sweep: 2026-09-22 15:27:52

- **Data**: 2026-09-22 15:27:52
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 59.08 | 27.24 | 27.27 | 28.53 | 46.14s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 15:34:45

- **Data**: 2026-09-22 15:34:45
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 42.71 | 20.98 | 20.79 | 22.94 | 56.17s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 15:48:54

- **Data**: 2026-09-22 15:48:54
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 48.69 | 26.10 | 26.33 | 27.67 | 34.99s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 15:56:36

- **Data**: 2026-09-22 15:56:36
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_atomicchat.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_atomicchat.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 46.24 | 23.81 | 22.95 | 25.30 | 55.01s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 16:03:11

- **Data**: 2026-09-22 16:03:11
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 54.28 | 23.57 | 22.28 | 25.86 | 52.17s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 16:09:31

- **Data**: 2026-09-22 16:09:31
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 50.28 | 23.28 | 22.03 | 23.93 | 48.98s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 16:15:04

- **Data**: 2026-09-22 16:15:04
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 54.25 | 26.05 | 26.03 | 27.63 | 42.22s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 17:51:30

- **Data**: 2026-09-22 17:51:30
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,3,0.80; 4,23,0.7,0.8; 24,39,0.7,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 67.92 | 30.18 | 30.16 | 30.63 | 34.93s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 18:06:45

- **Data**: 2026-09-22 18:06:45
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.8; 1,23,0.8; 24,39,0.8; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.8; 1,23,0.8; 24,39,0.8; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 61.75 | 30.44 | 30.66 | 31.33 | 31.70s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 18:13:37

- **Data**: 2026-09-22 18:13:37
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.95,1; 1,23,0.85; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.95,1; 1,23,0.85; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 56.78 | 26.91 | 27.49 | 29.34 | 33.50s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 18:21:35

- **Data**: 2026-09-22 18:21:35
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 56.57 | 29.37 | 29.51 | 30.12 | 34.24s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 23:38:17

- **Data**: 2026-09-22 23:38:17
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4200 MiB`
- **Early-Exit configs testadas**: `['0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4200 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 64.23 | 27.20 | 26.49 | 27.10 | 41.51s | 1.00x |


---

## Resumo do Sweep: 2026-09-22 23:43:34

- **Data**: 2026-09-22 23:43:34
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.95; 1,23,0.85; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 62.46 | 27.98 | 27.94 | 28.21 | 37.36s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 00:00:48

- **Data**: 2026-09-23 00:00:48
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 65.87 | 28.86 | 28.73 | 29.08 | 38.36s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 00:45:16

- **Data**: 2026-09-23 00:45:16
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.7; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.7; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 71.73 | 30.02 | 29.82 | 30.25 | 37.71s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 09:38:42

- **Data**: 2026-09-23 09:38:42
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.7; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.7; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 70.99 | 30.40 | 30.30 | 30.72 | 35.62s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 11:44:59

- **Data**: 2026-09-23 11:44:59
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 64.95 | 28.57 | 28.47 | 28.88 | 37.83s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 13:09:05

- **Data**: 2026-09-23 13:09:05
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 62.72 | 27.86 | 27.79 | 28.04 | 38.63s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 16:54:30

- **Data**: 2026-09-23 16:54:30
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,0,0.90; 1,23,0.8; 24,39,0.85; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 56.02 | 26.96 | 26.75 | 26.93 | 41.64s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 17:02:14

- **Data**: 2026-09-23 17:02:14
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,3,0.90; 4,23,0.7; 24,39,0.8; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.90; 4,23,0.7; 24,39,0.8; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 52.86 | 26.70 | 26.31 | 27.06 | 42.61s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 17:09:19

- **Data**: 2026-09-23 17:09:19
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4100 MiB`
- **Early-Exit configs testadas**: `['0,3,0.90; 4,15,0.7; 16,19,0.8; 20,27,0.7; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4100 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q5_0 --cache-type-v q4_1 -ngl 999 -c 131072 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.90; 4,15,0.7; 16,19,0.8; 20,27,0.7; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 54.88 | 25.89 | 25.45 | 26.05 | 48.12s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 17:36:58

- **Data**: 2026-09-23 17:36:58
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.6; 16,19,0.8; 20,27,0.6; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 100000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 12 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.6; 16,19,0.8; 20,27,0.6; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 67.52 | 30.41 | 30.14 | 30.49 | 37.68s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 17:52:33

- **Data**: 2026-09-23 17:52:33
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.75; 16,19,0.85; 20,27,0.75; 28,35,0.85; 36,39,0.75; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.75; 16,19,0.85; 20,27,0.75; 28,35,0.85; 36,39,0.75; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 55.76 | 24.71 | 24.45 | 25.47 | 49.08s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 19:08:11

- **Data**: 2026-09-23 19:08:11
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4000 MiB`
- **Early-Exit configs testadas**: `['0,3,0.95,1; 4,15,0.85; 16,19,0.9; 20,27,0.85; 28,35,0.9; 36,39,0.95; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4000 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.95,1; 4,15,0.85; 16,19,0.9; 20,27,0.85; 28,35,0.9; 36,39,0.95; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 49.78 | 21.97 | 21.82 | 22.14 | 50.50s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 19:13:54

- **Data**: 2026-09-23 19:13:54
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Early-Exit configs testadas**: `['0,3,0.95,1; 4,15,0.85; 16,19,0.9; 20,27,0.85; 28,35,0.9; 36,39,0.95; 40,47,0.95,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.95,1; 4,15,0.85; 16,19,0.9; 20,27,0.85; 28,35,0.9; 36,39,0.95; 40,47,0.95,1 | 0.20 | 0.20 | 0.05 | 52.12 | 22.81 | 22.68 | 23.62 | 49.97s | 1.00x |


---

## Resumo do Sweep: 2026-09-23 19:42:04

- **Data**: 2026-09-23 19:42:04
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4400 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.65; 16,19,0.8; 20,27,0.65; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4400 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.65; 16,19,0.8; 20,27,0.65; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 63.77 | 27.92 | 27.73 | 28.58 | 40.41s | 1.00x |


---

## Resumo do Sweep: 2026-09-24 10:50:39

- **Data**: 2026-09-24 10:50:39
- **Modelo**: `Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `3700 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.65; 16,19,0.8; 20,27,0.65; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Qwen3.8-Flash-Next-UD-IQ4_XS/Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_unsloth.gguf.gguf --vram-expert-budget-mb 3700 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.65; 16,19,0.8; 20,27,0.65; 28,35,0.8; 36,39,0.7; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 34.71 | 21.50 | 21.31 | 22.05 | 55.82s | 1.00x |


---

## Resumo do Sweep: 2026-09-24 13:00:22

- **Data**: 2026-09-24 13:00:22
- **Modelo**: `Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4700 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.75; 16,19,0.85; 20,27,0.75; 28,35,0.85; 36,39,0.75; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_unsloth.gguf.gguf --vram-expert-budget-mb 4700 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.75; 16,19,0.85; 20,27,0.75; 28,35,0.85; 36,39,0.75; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 45.18 | 23.38 | 23.58 | 24.55 | 46.28s | 1.00x |


---

## Resumo do Sweep: 2026-09-24 13:05:11

- **Data**: 2026-09-24 13:05:11
- **Modelo**: `Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4600 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.7; 16,19,0.7; 20,27,0.7; 28,35,0.7; 36,39,0.7; 40,47,0.9,0.95']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `imatrix_unsloth.gguf.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-UD-IQ4_XS-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/imatrix_unsloth.gguf.gguf --vram-expert-budget-mb 4600 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.7; 16,19,0.7; 20,27,0.7; 28,35,0.7; 36,39,0.7; 40,47,0.9,0.95 | 0.20 | 0.20 | 0.05 | 57.13 | 25.56 | 25.53 | 26.77 | 43.94s | 1.00x |


---

## Resumo do Sweep: 2026-09-24 15:59:30

- **Data**: 2026-09-24 15:59:30
- **Modelo**: `Qwen3.8-Flash-Next-TTJV-IQ4_XS-00001-of-00008.gguf`
- **VRAM Budget (`--vram-expert-budget-mb`)**: `4300 MiB`
- **Early-Exit configs testadas**: `['0,3,0.9,0.95; 4,15,0.7; 16,19,0.75; 20,27,0.7; 28,35,0.75; 36,39,0.75; 40,45,0.9,0.95; 46,47,1']`
- **Imatrix-Weight testados**: `[0.2]`
- **Swap-Max testados**: `[0.2]`
- **Attenuation testados**: `[0.05]`
- **Imatrix**: `bartowski-Qwen3.8-Flash-Next-imatrix.gguf`
- **Comando de Benchmark**: `python3 /home/ai/llama.cpp/tools/server/bench/speed-bench/speed_bench.py --url localhost:8080 --bench qualitative --category coding --osl 1024 --concurrency 1 --limit 4 --output sweep_bench_temp.json`
- **Parametros do Servidor (`llama-server`)**:
```bash
/home/ai/llama.cpp/build/bin/llama-server --fit off -m /home/ai/models/Custom/Qwen3.8-Flash-Next-TTJV-IQ4_XS-00001-of-00008.gguf \
  --expert-imatrix /home/ai/models/bartowski-Qwen3.8-Flash-Next-imatrix.gguf --vram-expert-budget-mb 4300 \
  --expert-early-exit <START,END,MIN[,MAX]> \
  --expert-imatrix-weight <IMATRIX_WEIGHT> \
  --expert-swap-max <SWAP_MAX> --expert-attenuation <ATTENUATION> \
  --cache-type-k q4_0 --cache-type-v q4_0 -ngl 999 -c 90000 \
  --load-mode mmap -cmoe --lazy-mode on --threads 6 --threads-batch 6 \
  --parallel 1 --flash-attn on -b 2048 -ub 512 --temp 0.6 --top-p 0.95 \
  --min-p 0.0 --top-k 20 --presence_penalty 0.0 --repeat-penalty 1 \
  --jinja --chat-template-file /home/ai/chat_template_22.5.jinja --reasoning-format deepseek \
  --warmup --host 0.0.0.0 --cors-origins http://localhost:8080 --alias local-model
```

| Early-Exit Rules | Imatrix Weight | Swap Max | Atten | Prompt t/s | Pred t/s (Original) | Pred t/s (Ponderada) | Pred t/s (Sem Warmup) | Latencia Media | Speedup |
|:----------------:|:--------------:|:--------:|:-----:|:----------:|:-------------------:|:--------------------:|:---------------------:|:--------------:|:-------:|
| 0,3,0.9,0.95; 4,15,0.7; 16,19,0.75; 20,27,0.7; 28,35,0.75; 36,39,0.75; 40,45,0.9,0.95; 46,47,1 | 0.20 | 0.20 | 0.05 | 55.56 | 25.28 | 25.16 | 25.88 | 44.84s | 1.00x |
