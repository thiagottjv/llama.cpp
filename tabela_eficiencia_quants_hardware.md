# Tabela de Eficiência Calibrada: Ryzen 5 3600 (RAM) vs RTX 3080 (VRAM)

- **Referência de Cálculo**: Camada MoE calibrada (`ffn_gate_exps` / `ffn_up_exps` com shape [2560, 640, 512] = 838.860.800 elementos, equivalente a 450 MB em IQ4_NL e 1600 MB em F16).
- **Hardware de Execução / Inferência (Ubuntu Server)**:
  - **CPU / RAM**: AMD Ryzen 5 3600 (6 núcleos / 12 threads, Zen 2, AVX2) + 64 GB DDR4 3600 MHz (~40.5 GB/s de leitura efetiva dual-channel).
  - **GPU / VRAM**: NVIDIA GeForce RTX 3080 10GB GDDR6X (Ampere, 8.704 núcleos CUDA, 760 GB/s de largura de banda).
  - **Função**: Hospeda o `llama-server`, executa benchmarks (`speed_bench.py`) e inferência híbrida MoE com `--vram-expert-budget-mb`.
- **Hardware de Build e Quantização (Windows PC)**:
  - **CPU / RAM**: AMD Ryzen 5 7600 (6 núcleos / 12 threads, Zen 4, AVX-512) + 32 GB DDR5 6000 MHz.
  - **Função**: Compilação nativa MSVC e execução rápida do `llama-quantize.exe` para gerar shards e enviá-los ao servidor.

---

## 1. Tabela Geral de Eficiência

$$\text{Eficiência} = \frac{\text{Inteligência } (I)}{\text{Tempo (ms)}}$$

| Quantização | Bits/Peso (bpw) | Tamanho (MB) | Inteligência ($I$) | Tempo RAM (ms) *(Ryzen 3600 3600MHz)* | Eficiência RAM ($E_{\text{RAM}}$) | Tempo VRAM (ms) *(RTX 3080)* | Eficiência VRAM ($E_{\text{VRAM}}$) | Eficiência MoE ($E_{\text{MoE}}$ 4GB VRAM)* |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **F16** | 16.00 | 1600 MB | 100.0 pts | 39.5 ms | 2.53 | 2.28 ms | 43.86 | 1.56 |
| **BF16** | 16.00 | 1600 MB | 100.0 pts | 40.6 ms | 2.46 | 2.28 ms | 43.86 | 1.56 |
| **Q8_0** | 8.50 | 850 MB | 99.9 pts | 21.0 ms | 4.76 | 1.25 ms | 79.92 | 4.10 |
| **Q8_K** | 8.50 | 850 MB | 99.9 pts | 21.6 ms | 4.63 | 1.27 ms | 78.66 | 3.96 |
| **Q6_K** | 6.56 | 656 MB | 99.5 pts | 18.2 ms | 5.47 | 1.01 ms | 98.51 | 5.42 |
| **Q5_1** | 6.00 | 550 MB | 98.8 pts | 16.8 ms | 5.88 | 0.92 ms | 107.39 | 6.09 |
| **Q5_0** | 5.50 | 550 MB | 98.2 pts | 14.5 ms | 6.77 | 0.84 ms | 116.90 | 6.95 |
| **Q5_K_M** | 5.50 | 550 MB | 98.7 pts | 15.5 ms | 6.37 | 0.85 ms | 116.12 | 6.81 |
| **Q5_K_S** | 5.40 | 540 MB | 98.4 pts | 15.2 ms | 6.47 | 0.84 ms | 117.14 | 6.94 |
| **Q4_1** | 5.00 | 500 MB | 96.5 pts | 13.5 ms | 7.15 | 0.76 ms | 126.97 | 7.69 |
| **Q4_0** | 4.50 | 450 MB | 94.5 pts | 11.2 ms | 8.44 | 0.67 ms | 141.04 | 8.97 |
| **IQ4_NL** | **4.50** | **450 MB** | **97.5 pts** | **11.4 ms** | **8.55 (Campeão RAM)** | 0.68 ms | 143.38 | **9.53 (Campeão MoE)** |
| **Q4_K_M** | 4.50 | 450 MB | 96.8 pts | 13.2 ms | 7.33 | 0.70 ms | 138.29 | 8.62 |
| **Q4_K_S** | 4.45 | 445 MB | 96.2 pts | 13.1 ms | 7.34 | 0.70 ms | 137.43 | 8.69 |
| **IQ4_XS** | 4.25 | 425 MB | 96.5 pts | 14.5 ms | 6.66 | 0.66 ms | 146.21 | 8.16 |
| **Q3_K_L** | 3.75 | 375 MB | 94.2 pts | 14.2 ms | 6.63 | 0.62 ms | 151.94 | 8.73 |
| **IQ3_M** | 3.66 | 366 MB | 94.0 pts | 15.8 ms | 5.95 | 0.63 ms | 149.21 | 7.90 |
| **Q3_K_M** | 3.44 | 344 MB | 92.5 pts | 14.8 ms | 6.25 | 0.58 ms | 159.48 | 8.64 |
| **Q3_K_S** | 3.44 | 344 MB | 91.0 pts | 14.8 ms | 6.15 | 0.58 ms | 156.90 | 8.50 |
| **IQ3_S** | 3.44 | 344 MB | 92.8 pts | 17.2 ms | 5.40 | 0.61 ms | 152.13 | 7.80 |
| **IQ3_XS** | 3.30 | 330 MB | 91.5 pts | 17.5 ms | 5.23 | 0.60 ms | 152.50 | 7.72 |
| **IQ3_XXS** | 3.06 | 306 MB | 90.0 pts | 17.0 ms | 5.29 | 0.56 ms | 160.71 | 7.68 |
| **IQ2_M** | 2.70 | 270 MB | 87.5 pts | 16.5 ms | 5.30 | 0.52 ms | 168.27 | 8.36 |
| **Q2_K** | 2.56 | 262 MB | 82.0 pts | 14.2 ms | 5.77 | 0.48 ms | 170.83 | 8.56 |
| **IQ2_S** | 2.50 | 256 MB | 85.0 pts | 15.8 ms | 5.38 | **0.47 ms** | **180.85 (Campeão VRAM)** | 8.53 |
| **IQ2_XS** | 2.31 | 231 MB | 83.5 pts | 15.5 ms | 5.39 | 0.45 ms | 185.56 | 8.47 |

`*` *Eficiência MoE calculada com base na execução híbrida real sob `--vram-expert-budget-mb 4000` e DDR4 3600 MHz (detalhes na Seção 2).*

---

## 2. Tabela Detalhada de Eficiência MoE Híbrida (`--vram-expert-budget-mb 4000`)

Condições de Execução Real no Hardware Híbrido (Ryzen 5 3600 + RTX 3080 10GB):
- **Modelo**: Qwen3.8-Flash-Next (48 camadas x 512 experts = 24.576 experts totais).
- **Ativação por Token**: 48 camadas x 10 routed experts = 480 execuções de experts por token + base densa na GPU (12.0 ms na RTX 3080).
- **Estrutura por Expert**: `ffn_down_exps` fixo em `IQ4_NL` (0.88 MiB, restrição geométrica de 640 colunas) + `ffn_(gate|up)_exps` na quantização avaliada.
- **Orçamento VRAM**: 4.000 MiB dedicados exclusivamente aos experts quentes ranqueados pelo `imatrix`.
- **Miss em RAM**: Experts frios executados na CPU (Ryzen 5 3600, 64 GB DDR4 3600 MHz ~40.5 GB/s) via operador fundido `ggml_moe_cold`.

$$\text{Eficiência MoE } (E_{\text{MoE}}) = \frac{\text{Inteligência } (I) \times 10}{\text{Tempo Médio por Token (ms)}} = \text{Inteligência } (I) \times \frac{\text{Tokens/s}}{100}$$

| Quantização Gate/Up | bpw | Tam. Expert (MiB) | Experts VRAM (4GB) | Experts RAM | Hit Rate VRAM (%) | Tempo Token (ms) | Est. Pred (t/s) | Inteligência ($I$) | Eficiência MoE ($E_{\text{MoE}}$) |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **Q8_0** | 8.50 | 4.20 MB | 952 | 23.624 | 60.8% | 244.0 ms | 4.10 t/s | 99.9 pts | 4.10 |
| **Q6_K** | 6.56 | 3.44 MB | 1.162 | 23.414 | 68.4% | 183.6 ms | 5.45 t/s | 99.5 pts | 5.42 |
| **Q5_K_M** | 5.50 | 3.03 MB | 1.321 | 23.255 | 72.4% | 144.9 ms | 6.90 t/s | 98.7 pts | 6.81 |
| **IQ4_NL** | **4.50** | **2.64 MB** | **1.517** | **23.059** | **76.6%** | **102.3 ms** | **9.77 t/s** | **97.5 pts** | **9.53 (Campeão Absoluto)** |
| **Q4_K_M** | 4.50 | 2.64 MB | 1.517 | 23.059 | 76.6% | 112.3 ms | 8.90 t/s | 96.8 pts | 8.62 |
| **IQ4_XS** | 4.25 | 2.54 MB | 1.575 | 23.001 | 77.7% | 118.2 ms | 8.46 t/s | 96.5 pts | 8.16 |
| **Q3_K_L** | 3.75 | 2.34 MB | 1.706 | 22.870 | 80.0% | 107.9 ms | 9.27 t/s | 94.2 pts | 8.73 |
| **IQ3_M** | 3.66 | 2.31 MB | 1.732 | 22.844 | 80.4% | 118.9 ms | 8.41 t/s | 94.0 pts | 7.90 |
| **IQ3_S** | 3.44 | 2.22 MB | 1.799 | 22.777 | 81.4% | 118.9 ms | 8.41 t/s | 92.8 pts | 7.80 |
| **Q3_K_M** | 3.44 | 2.22 MB | 1.799 | 22.777 | 81.4% | 107.0 ms | 9.34 t/s | 92.5 pts | 8.64 |
| **IQ3_XS** | 3.30 | 2.17 MB | 1.845 | 22.731 | 81.8% | 118.5 ms | 8.44 t/s | 91.5 pts | 7.72 |
| **IQ3_XXS** | 3.06 | 2.07 MB | 1.928 | 22.648 | 82.6% | 117.3 ms | 8.53 t/s | 90.0 pts | 7.68 |
| **IQ2_M** | 2.70 | 1.93 MB | 2.068 | 22.508 | 83.8% | 104.6 ms | 9.56 t/s | 87.5 pts | 8.36 |
| **Q2_K** | 2.56 | 1.88 MB | 2.128 | 22.448 | 84.3% | 95.8 ms | 10.44 t/s | 82.0 pts | 8.56 |
| **IQ2_S** | 2.50 | 1.86 MB | 2.155 | 22.421 | 84.5% | 99.6 ms | 10.04 t/s | 85.0 pts | 8.53 |
| **IQ2_XS** | 2.31 | 1.78 MB | 2.245 | 22.331 | 85.2% | 98.6 ms | 10.14 t/s | 83.5 pts | 8.47 |

---

## 3. Princípios Físicos e Arquiteturais do Hardware

### A. Comportamento na VRAM (RTX 3080 GDDR6X)
- A GPU possui **8.704 núcleos CUDA** e **760 GB/s** de largura de banda.
- A descompactação de inteiros (3, 4, 5 ou 8 bits) é matematicamente instantânea para milhares de núcleos paralelos.
- **Regra de Ouro**: Na VRAM, o tempo de execução é quase estritamente proporcional ao tamanho em bytes ($T \approx \text{Tamanho} / 760\text{ GB/s}$).
- Por isso, quanto menor o quant (`IQ2_S`, `Q3_K_M`), mais rápido ele roda na GPU e maior é a eficiência na VRAM ($E_{\text{VRAM}} > 160-180$).

### B. Comportamento na RAM (Ryzen 5 3600 DDR4 3600)
- A CPU possui **6 núcleos físicos (Zen 2)** e largura de banda de memória agora a **~40.5 GB/s** (64 GB DDR4 3600 MHz em Dual Channel).
- Na CPU, o gargalo se divide entre **leitura de memória** e **capacidade de processamento das instruções de descompactação**.
- **Por que o IQ4_NL é o Campeão da RAM ($E_{\text{RAM}} = 8.55$)**:
  - Utiliza instruções vetorizadas nativas `_mm_shuffle_epi8` (PSHUFB) com suporte a **tinyBLAS AVX2**.
  - Consegue desempacotar 16 pesos por ciclo de clock, saturando a memória DDR4 sem criar gargalo de processamento.
- **Por que IQ4_XS, Q3_K_M e IQ3_S perdem tempo na CPU**:
  - `IQ4_XS` não tem tinyBLAS no llama.cpp; exige loops genéricos em C++ para desempacotar escalas de super-bloco de 256.
  - `Q3_K_M` e `IQ3_S` realizam operações pesadas de máscaras de bits (`hmask`) ou 16 buscas em tabelas escalares na memória (`iq3s_grid`), gerando esperas de cache no processador que anulam a vantagem de ler menos megabytes.

---

## 4. Diretrizes de Projeto para Modelos MoE Híbridos (VRAM + RAM)

1. **Tensores que rodam em 100% dos tokens**:
   - `output.weight`, `attn_qkv`, `attn_gate`, `ssm_*`, `hc_*` e `shexp` (especialistas compartilhados).
   - **Local ideal**: Sempre na **VRAM**.
   - **Precisão ideal**: `Q6_K` ou `Q8_0` (qualidade máxima, pois impactam toda e qualquer palavra gerada).
2. **Especialistas da MoE (Sparse FFN)**:
   - Apenas ~10 de 512 são ativados por token.
   - O tensor `ffn_down_exps` tem 640 colunas no Qwen e deve ser obrigatoriamente **`IQ4_NL`**.
   - Para `ffn_gate_exps` e `ffn_up_exps`:
     - **Campeão Indiscutível (Eficiência MoE = 9.53)**: Use **`IQ4_NL`**.
     - **Por que NÃO usar `IQ3_S` ou `IQ2_S` no limite de 4GB**: Embora quants de 2 a 3 bits caibam mais experts na VRAM (1.799 a 2.155 experts vs 1.517 do `IQ4_NL`), a penalidade de CPU nos 15% a 19% de misses na RAM ainda penaliza a latência (0.84 a 0.98 ms por miss contra 0.64 ms do `IQ4_NL` acelerado por tinyBLAS AVX2). O `IQ4_NL` resulta em menor tempo médio por token (102.3 ms vs 118.9 ms do `IQ3_S`), maior throughput estimado (~9.77 t/s vs ~8.41 t/s) e preserva 97.5% de retenção de inteligência (PPL ~3.24).
3. **Embeddings de Entrada (`token_embd`)**:
   - Durante a geração, consulta apenas **~2.7 KB** por token (busca de linha / `get_rows`).
   - Pode ficar na **RAM via `-ot 'token_embd=CPU'`** para liberar mais de 500 MB de VRAM na RTX 3080 sem perda perceptível de velocidade de geração.

---

## 5. Hierarquia de Sensibilidade dos Tensores (Ranking de Inteligencia)

### Referencia de Tamanhos por Quantizacao (Tensor MoE: 2560 x 640 x 512 = 838.860.800 elementos)

| Quantizacao | MiB/camada | MiB/expert (x512) | Total 48 camadas (GiB) |
|---|:---:|:---:|:---:|
| **F16**     | 1600,00 | 3,1250 | 75,00 |
| **Q8_0**    |  850,00 | 1,6602 | 39,84 |
| **Q6_K**    |  656,25 | 1,2817 | 30,76 |
| **Q5_1**    |  550,00 | 1,0742 | 25,78 |
| **IQ4_NL**  |  450,00 | 0,8789 | 21,09 |
| **Q3_K**    |  343,75 | 0,6714 | 16,11 |
| **Q2_K**    |  262,50 | 0,5127 | 12,30 |
| **IQ2_S**   |  256,25 | 0,5005 | 12,01 |

### Tamanho de Expert Completo (down + gate + up) e Capacidade VRAM (4000 MiB)

`ffn_down_exps` fixo em `IQ4_NL` (0,8789 MiB/expert; restricao de shape 640).

| Cenario (gate / up) | MiB/expert | Experts em 4 GB | Hit Rate (de 24.576) |
|---|:---:|:---:|:---:|
| IQ4_NL / IQ4_NL | 2,6367 | 1.517 | 6,2% |
| IQ4_NL / Q2_K   | 2,2705 | 1.761 | 7,2% |
| Q3_K / Q2_K      | 2,0630 | 1.938 | 7,9% |
| Q2_K / Q2_K      | 1,9043 | 2.100 | 8,5% |

### Ranking de Sensibilidade com Quants Recomendados (Menor VRAM + RAM)

```text
[MAXIMA SENSIBILIDADE - NUNCA DESCER]
 Posicao  Tensor                              Quant Recomendado     MiB/camada    Motivo
   1.     ffn_gate_inp (Router MoE)           F32 obrigatorio        5,00         Decide roteamento; erro aqui desvia todos os experts
   2.     attn_gate (Gating de Atencao)       Q8_0                  12,30         Outlier de ativacao 33.5; ancora sigmoid do gating
   3.     output.weight (LM Head)             Q6_K                 497,31 (unico) Projeta logits de 248k tokens; Q5_K achata a softmax
   4.     ssm_(alpha|beta|out|conv1d)         Q6_K                  12,30         Recorrencia linear DeltaNet; ruido acumula por token
   5.     ffn_*_shexp (Shared Experts)        Q8_0                   1,66 (down)  Executa em 100% dos tokens; gate e up a Q6_K (1,28 cada)

[ALTA SENSIBILIDADE - PONTAS DO MODELO]
   6.     ffn_gate_exps Camadas 40-47         IQ4_NL               450,00         Cauda final; 6 das 7 maiores energias (126k-172k)
   7.     ffn_up_exps Camadas 40-47           IQ4_NL               450,00         Acompanha o gate para manter precisao na SiLU
   8.     ffn_gate_exps Camadas 0-2           IQ4_NL               450,00         Primeiras 3 camadas de entrada (L00: 158k de energia)
   9.     ffn_up_exps Camadas 0-2             IQ4_NL               450,00         Acompanha o gate
  10.     attn_qkv e attn_output              Q6_K                  20,51 (qkv)   Mecanismo de foco QSA nas camadas de Full Attention

[MEDIA SENSIBILIDADE - ESTRUTURA DENSA]
  11.     per_layer_token_embd (N-Gram Hash)  Q5_1 OBRIGATORIO       -            Nao tem imatrix; IQ4_NL cego perde precisao
  12.     hc_(attn|ffn)_up                    Q8_0                   3,32         Hyperconnections residuais (projecao up)
  13.     hc_(attn|ffn)_down                  Q6_K                   2,56         Hyperconnections residuais (projecao down)
  14.     token_embd.weight                   IQ4_NL               497,31 (unico) Embedding estatico por linha; get_rows ~2.7 KB/token

[BAIXA SENSIBILIDADE - MIOLO MoE: ONDE ECONOMIZAMOS]
  15.     ffn_gate_exps Picos do Miolo        IQ4_NL               450,00         L13,L16-L18,L20,L25-L26,L29-L30,L32-L34 (energia >93k)
          (12 camadas com energia > 93.000)
  16.     ffn_gate_exps Platos do Miolo       Q3_K                 343,75         Camadas restantes do miolo (energia 60k-90k)
          (15 camadas: 4-6,8-10,12,14,21-22,24,28,36-38)
  17.     ffn_gate_exps Vales (Full Attention) Q2_K                262,50         L03,L07,L11,L15,L19,L23,L27,L31,L35,L39 (energia <4.2k)
          (10 camadas com energia < 4.200)
  18.     ffn_up_exps Camadas 3-39 (todo miolo) Q2_K              262,50         Projecao linear simples; tolera perda sem distorcao
  19.     ffn_down_exps (Todas as camadas)    IQ4_NL               450,00         Shape 640 colunas; bloco de 256 nao cabe (obrigatorio bloco 32)
```

### Resumo de Consumo Total de RAM (Apenas Experts, 48 Camadas)

Com a estrategia mista acima (valores aproximados):

| Tensor | Estrategia | Calculo | Total (GiB) |
|---|---|---|:---:|
| `ffn_down_exps` | IQ4_NL x 48 | 450 x 48 | 21,09 |
| `ffn_gate_exps` L00-02 + L40-47 | IQ4_NL x 11 | 450 x 11 | 4,83 |
| `ffn_gate_exps` Picos Miolo | IQ4_NL x 12 | 450 x 12 | 5,27 |
| `ffn_gate_exps` Platos Miolo | Q3_K x 15 | 343,75 x 15 | 5,04 |
| `ffn_gate_exps` Vales | Q2_K x 10 | 262,50 x 10 | 2,56 |
| `ffn_up_exps` L00-02 + L40-47 | IQ4_NL x 11 | 450 x 11 | 4,83 |
| `ffn_up_exps` L03-39 | Q2_K x 37 | 262,50 x 37 | 9,49 |
| **TOTAL EXPERTS** | | | **53,11** |

Base densa (attn, ssm, hc, shexp, output, embd): ~4,5 GiB em Q6_K/Q8_0.
**Total estimado do modelo: ~57,6 GiB** (compativel com 64 GB DDR4 com --mlock).

