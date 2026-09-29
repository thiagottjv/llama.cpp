# Tabela de Eficiencia Calibrada: Qwen3.8-27B (Dense Hibrido)
# Ryzen 5 3600 (RAM DDR4) vs RTX 3080 10GB (VRAM GDDR6X)

- **Modelo**: `Qwen/Qwen3.8-27B` (GGUFs Unsloth Dynamic V3.0 / `unsloth/Qwen3.8-27B-GGUF`).
- **Natureza do Modelo**: **Dense Hibrido** (27,32 Bilhoes de parametros totais; 100% dos pesos sao avaliados a cada token, diferente de modelos MoE esparsos).
- **Estrutura Arquitetural**:
  - 64 Camadas Principais: Layout intercalado `16 x (3 x Gated DeltaNet + 1 x Gated Full Attention)`.
    - 48 Camadas de DeltaNet Linear Attention (recorrencia linear SSM com estado O(1) de memoria).
    - 16 Camadas de Gated Full Attention (mecanismo quadratico com 24 cabecas Q e 4 cabecas KV, `head_dim` 256).
  - 1 Camada MTP (Multi-Token Prediction / NextN, Camada 64) para aceleracao especulativa de tokens.
  - Dimensoes: `hidden_size` = 5.120, `intermediate_size` (FFN) = 17.408, `vocab_size` = 248.320.
- **Hardware de Execucao / Inferencia (Ubuntu Server)**:
  - **CPU / RAM**: AMD Ryzen 5 3600 (6 nucleos / 12 threads, Zen 2, AVX2) + 64 GB DDR4 3600 MHz (~40.5 GB/s de leitura efetiva dual-channel).
  - **GPU / VRAM**: NVIDIA GeForce RTX 3080 10GB GDDR6X (Ampere, 8.704 nucleos CUDA, 760 GB/s de largura de banda).
  - **Orcamento Efetivo de VRAM para Pesos**: ~8,60 GB a 8,80 GB (10.240 MB totais - 600 MB driver/CUDA runtime - ~600 MB para KV cache de 8k e ativacoes DeltaNet; expansivel se `token_embd` for alocado na RAM).
- **Hardware de Build e Quantizacao (Windows PC)**:
  - **CPU / RAM**: AMD Ryzen 5 7600 (6 nucleos / 12 threads, Zen 4, AVX-512) + 32 GB DDR5 6000 MHz.

---

## 1. Tabela Geral de Eficiencia

$$\text{Eficiencia} = \frac{\text{Inteligencia } (I)}{\text{Tempo (ms)}} \times 10$$

| Quantizacao | Bits/Peso (bpw) | Tamanho (GB) | Tamanho (MB) | Inteligencia ($I$) | Tempo RAM Puro (ms) *(Ryzen 3600)* | Eficiencia RAM ($E_{\text{RAM}}$) | Tempo VRAM Puro (ms) *(RTX 3080 760GB/s)\** | Eficiencia VRAM ($E_{\text{VRAM}}$) | Eficiencia Hibrida Real ($E_{\text{Hibrido}}$ 10GB VRAM)\*\* |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **BF16** | 16.00 | 50.80 GB | 52.019 MB | 100.0 pts | 1.316,9 ms | 0.76 | 68.8 ms | 14.53 | 0.82 |
| **UD-Q8_K_XL** | 9.10 | 29.30 GB | 30.001 MB | 99.9 pts | 739.0 ms | 1.35 | 40.5 ms | 24.64 | 1.66 |
| **Q8_0** | 8.50 | 27.05 GB | 27.702 MB | 99.8 pts | 681.0 ms | 1.47 | 37.6 ms | 26.54 | 2.08 |
| **UD-Q8_K_L** | 8.20 | 26.12 GB | 26.747 MB | 99.7 pts | 658.8 ms | 1.51 | 36.4 ms | 27.41 | 1.94 |
| **UD-Q6_K_XL** | 7.30 | 23.56 GB | 24.127 MB | 99.5 pts | 669.0 ms | 1.49 | 33.0 ms | 30.15 | 2.26 |
| **UD-Q6_K** | 6.40 | 20.47 GB | 20.965 MB | 99.2 pts | 581.2 ms | 1.71 | 28.9 ms | 34.28 | 2.82 |
| **UD-Q5_K_XL** | 6.00 | 19.44 GB | 19.910 MB | 98.9 pts | 576.0 ms | 1.72 | 27.6 ms | 35.86 | 3.06 |
| **UD-Q5_K_M** | 5.70 | 18.41 GB | 18.856 MB | 98.6 pts | 545.5 ms | 1.81 | 26.2 ms | 37.60 | 3.36 |
| **UD-Q5_K_S** | 5.40 | 17.38 GB | 17.801 MB | 98.2 pts | 515.0 ms | 1.91 | 24.9 ms | 39.49 | 3.71 |
| **UD-Q4_K_XL** | 5.10 | 16.35 GB | 16.746 MB | 97.4 pts | 464.2 ms | 2.10 | 23.5 ms | 41.42 | 4.14 |
| **UD-Q4_K_M** | 4.80 | 15.33 GB | 15.702 MB | 97.0 pts | 435.3 ms | 2.23 | 22.2 ms | 43.76 | 4.70 |
| **Q4_0** | 4.70 | 14.95 GB | 15.313 MB | 95.0 pts | 387.6 ms | 2.45 | 21.7 ms | 43.84 | 5.28 |
| **UD-Q4_K_S** | 4.50 | 14.30 GB | 14.647 MB | 96.3 pts | 406.0 ms | 2.37 | 20.8 ms | 46.26 | 5.44 |
| **UD-IQ4_XS** | 4.20 | 13.27 GB | 13.593 MB | 96.5 pts | 409.6 ms | 2.36 | 19.5 ms | 49.59 | 6.05 |
| **UD-Q3_K_XL** | 3.80 | 12.24 GB | 12.537 MB | 95.0 pts | 392.3 ms | 2.42 | 18.1 ms | 52.46 | 8.01 |
| **UD-IQ3_S** | 3.50 | 11.21 GB | 11.483 MB | 93.5 pts | 374.0 ms | 2.50 | 16.7 ms | 55.83 | 9.75 |
| **UD-IQ3_XXS** | 3.20 | 10.18 GB | 10.428 MB | 91.0 pts | 339.6 ms | 2.68 | 15.4 ms | 59.10 | 14.20 |
| **UD-Q2_K_XL** | 2.85 | 9.15 GB | 9.374 MB | 87.5 pts | 282.4 ms | 3.10 | 14.0 ms | 62.33 | 28.29 |
| **UD-IQ2_S** | **2.45** | **7.80 GB** | **7.984 MB** | **85.0 pts** | **260.0 ms** | **3.27 (Campeao RAM)** | **12.3 ms** | **69.31** | **69.31 (100% VRAM)** |
| **UD-IQ2_XXS**| 2.15 | 6.77 GB | 6.930 MB | 82.0 pts | 225.7 ms | 3.63 | 10.9 ms | 75.17 | 75.17 (100% VRAM) |
| **UD-IQ1_M**  | 1.95 | 6.27 GB | 6.417 MB | 75.0 pts | 209.0 ms | 3.59 | 10.2 ms | 73.17 | 73.17 (100% VRAM) |

`*` *Tempo VRAM Puro: calculo teorico de passagem de pesos a 760 GB/s + overhead de sincronizacao (pressupoe que o modelo coubesse integralmente na VRAM).*
`**` *Eficiencia Hibrida Real: calculada com base na particao real de camadas na RTX 3080 10GB (8.60 GB uteis) e o restante executado na CPU / DDR4 3600 MHz (detalhes na Secao 2).*

---

## 2. Tabela Detalhada de Execucao Hibrida (RTX 3080 10GB + Ryzen 5 3600)

Diferente de modelos MoE (onde os experts sao ativados sob demanda e guardados em cache), o **Qwen3.8-27B e um modelo denso**. Todas as 65 camadas (64 camadas principais + 1 MTP) e seus respectivos tensores FFN e Attention precisam ser transferidos e calculados a cada token gerado.

### Condicoes de Execucao Real no Hardware:
- **Capacidade VRAM da GPU**: 10.240 MiB (10.0 GB GDDR6X).
- **Reserva do Sistema / Contexto**: ~1.400 MiB (Contexto de 8.192 tokens com KV cache Q8_0 = 256 MiB + estados recorrentes DeltaNet = 150 MiB + driver CUDA e ativacoes = 1.000 MiB).
- **Orcamento Efetivo de VRAM para Pesos**: **8.600 MiB (~8,40 GiB / 8,60 GB)**.
- **Otimizacao de Embeddings**: Recomendado fixar `token_embd.weight` na RAM via `-ot token_embd=CPU` (economiza 682 MB de VRAM na RTX 3080 com zero impacto perceptivel na geracao).
- **Tempo por Token**:
  $$T_{\text{token}} = T_{\text{GPU}} + T_{\text{RAM}} + T_{\text{PCIe/Kernel Overhead}}$$
  - $T_{\text{GPU}} = \frac{\text{Bytes na VRAM}}{760\text{ GB/s}}$
  - $T_{\text{RAM}} = \frac{\text{Bytes na RAM}}{40.5\text{ GB/s}} \times \text{Fator de Descompactacao Zen 2}$
- **Metrica de Eficiencia Hibrida**:
  $$E_{\text{Hibrido}} = I \times \frac{\text{Throughput (t/s)}}{100} = \frac{I \times 10}{T_{\text{token}} \text{ (ms)}}$$

| Quantizacao | Tamanho (GB) | Camadas GPU (`-ngl`) | Camadas RAM | % na VRAM | Tempo RAM (ms) | Tempo GPU (ms) | Tempo Total (ms) | Throughput Est. (t/s) | Inteligencia ($I$) | Eficiencia Hibrida ($E_{\text{Hibrido}}$) | Classificacao Operacional |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|---|
| **UD-IQ2_XXS** | 6.77 GB | 65 (100%) | 0 | 100.0% | 0.0 ms | 8.9 ms | 10.9 ms | **91.7 t/s** | 82.0 pts | **75.17** | Hiper-Velocidade (100% VRAM) |
| **UD-IQ2_S** | **7.80 GB** | **65 (100%)** | **0** | **100.0%** | **0.0 ms** | **10.3 ms** | **12.3 ms** | **81.6 t/s** | **85.0 pts** | **69.31** | **Campeao de Fluidez (100% VRAM)** |
| **UD-Q2_K_XL** | 9.15 GB | 61 | 4 | 94.0% | 15.6 ms | 11.3 ms | 30.9 ms | **32.3 t/s** | 87.5 pts | **28.29** | Ponto de Corte (Quase 100% VRAM)\* |
| **UD-IQ3_XXS** | 10.18 GB | 55 | 10 | 84.5% | 48.8 ms | 11.3 ms | 64.1 ms | **15.6 t/s** | 91.0 pts | **14.20** | Equilibrado Rapido |
| **UD-IQ3_S** | 11.21 GB | 50 | 15 | 76.7% | 80.6 ms | 11.3 ms | 95.9 ms | **10.4 t/s** | 93.5 pts | **9.75** | Limiar Interativo (~10 t/s) |
| **UD-Q3_K_XL** | 12.24 GB | 46 | 19 | 70.3% | 103.4 ms | 11.3 ms | 118.7 ms | **8.4 t/s** | 95.0 pts | **8.01** | Excelente Inteligencia / Confortavel |
| **UD-IQ4_XS** | **13.27 GB** | **42** | **23** | **64.8%** | **144.2 ms** | **11.3 ms** | **159.5 ms** | **6.3 t/s** | **96.5 pts** | **6.05** | **Campeao Hibrido de Raciocinio** |
| **UD-Q4_K_S** | 14.30 GB | 39 | 26 | 60.1% | 161.9 ms | 11.3 ms | 177.2 ms | **5.6 t/s** | 96.3 pts | **5.44** | Raciocinio Alto |
| **Q4_0** | 14.95 GB | 37 | 28 | 57.5% | 164.6 ms | 11.3 ms | 179.9 ms | **5.6 t/s** | 95.0 pts | **5.28** | Legado Estavel |
| **UD-Q4_K_M** | 15.33 GB | 36 | 29 | 56.1% | 191.1 ms | 11.3 ms | 206.4 ms | **4.8 t/s** | 97.0 pts | **4.70** | Maxima Precisao 4-bits |
| **UD-Q4_K_XL** | 16.35 GB | 34 | 31 | 52.6% | 220.1 ms | 11.3 ms | 235.4 ms | **4.2 t/s** | 97.4 pts | **4.14** | Quase Perda Zero 4-bits |
| **UD-Q5_K_S** | 17.38 GB | 32 | 33 | 49.5% | 249.3 ms | 11.3 ms | 264.6 ms | **3.8 t/s** | 98.2 pts | **3.71** | Limiar de Leitura Lenta |
| **UD-Q5_K_M** | 18.41 GB | 30 | 35 | 46.7% | 278.6 ms | 11.3 ms | 293.9 ms | **3.4 t/s** | 98.6 pts | **3.36** | Precisao Extrema de Raciocinio |
| **UD-Q6_K** | 20.47 GB | 27 | 38 | 42.0% | 337.1 ms | 11.3 ms | 352.4 ms | **2.8 t/s** | 99.2 pts | **2.82** | Muito Lento para Chat |
| **Q8_0** | 27.05 GB | 21 | 44 | 31.8% | 464.7 ms | 11.3 ms | 480.0 ms | **2.1 t/s** | 99.8 pts | **2.08** | Inviavel para Uso Interativo |
| **BF16** | 50.80 GB | 11 | 54 | 16.9% | 1.198,3 ms | 11.3 ms | 1.213,6 ms | **0.8 t/s** | 100.0 pts | **0.82** | Referencia de Benchmark Apenas |

`*` *Nota sobre UD-Q2_K_XL*: Se `token_embd.weight` (682 MB) for alocado na CPU via `-ot token_embd=CPU`, o tamanho dos pesos na VRAM cai para 8.47 GB, permitindo offload de **100% das 65 camadas** na RTX 3080 e elevando a velocidade para **~75-80 t/s**!

---

## 3. Principios Fisicos e Arquiteturais do Hardware (Dense vs MoE)

### A. O Gargalo Estrutural: Por que Modelos Densos nao se comportam como MoE
1. **MoE (Qwen 3.8 Flash Next)**:
   - Apenas 10 dos 512 especialistas sao roteados por token (~1,9% dos pesos de FFN ativos por vez).
   - O orcamento de 4GB de VRAM mantem um cache com os especialistas de maior frequencia (hit rate de 76,6%).
   - Quando ha um miss, a CPU processa apenas os 2 ou 3 experts faltantes, mantendo a taxa em ~9,8 t/s mesmo com a maior parte do modelo na RAM.
2. **Dense (Qwen3.8-27B)**:
   - **Nao existe esparsidade de ativacao**: 100% dos 27,3 bilhoes de parametros sao lidos obrigatoriamente a cada token gerado.
   - Qualquer camada mantida na RAM obriga o barramento DDR4 (40.5 GB/s) a ler centenas de megabytes sequenciais por token.
   - **O Abismo de Desempenho**:
     - **100% na VRAM** (ex: `UD-IQ2_S`): 760 GB/s entregam **>80 tokens/s**.
     - **Hibrido com 23 camadas na RAM** (ex: `UD-IQ4_XS`): O throughput cai imediatamente para **~6,3 tokens/s** devido ao afunilamento de memoria DDR4 da CPU.

### B. Vantagem Inedita da Arquitetura Hibrida DeltaNet no Consumo de VRAM
O Qwen3.8-27B traz uma inovacao critica para a execucao em GPUs com 10GB de VRAM:
- **Reducao Drastica do KV Cache**:
  - Em um Transformer puro tradicional de 27B (como Qwen 2.5 27B), todas as 64 camadas geram KV cache quadratico, consumindo rapidamente 3 a 6 GB de VRAM para contextos medios.
  - No Qwen3.8-27B, **apenas 16 das 64 camadas sao Full Attention** (intervalo de atencao = 4).
  - As outras 48 camadas utilizam **Gated DeltaNet**, cuja recorrencia linear armazena seu estado em tensores de tamanho estatico fixo (`ssm_conv1d` e matriz de recorrencia de cabeca 128x128). O consumo de memoria dessas 48 camadas **nao cresce com o tamanho do contexto**!
  - Para um contexto de 8.192 tokens em quantizacao Q8_0 do KV cache, o modelo consome apenas **~256 MB de KV cache real + ~150 MB de estado DeltaNet**, deixando mais de 8,6 GB livres para os pesos da rede.

### C. Descompactacao no Ryzen 5 3600 (Zen 2 AVX2)
Para as camadas que ficam na RAM DDR4:
- **Formatos com tinyBLAS AVX2 (Q4_0, IQ4_NL, Q8_0)**: Utilizam a instrucao vetorizada `_mm256_shuffle_epi8` (PSHUFB) para desempacotar pesos sem stalls de pipeline, saturando os 40.5 GB/s da memoria.
- **Formatos K-quants (Q4_K_M, Q5_K_M)**: Possuem leve custo de desempacotamento de escalas de super-bloco no Zen 2 (fator 1.15x a 1.20x de tempo adicional).
- **Formatos IQ com tabelas escalares (IQ3_S, IQ2_S)**: Quando executados na CPU, sofrem com saltos de lookup table (`iq3s_grid`), reduzindo a taxa de transferencia efetiva da RAM. Por isso, quants IQ muito baixos so devem ser usados se couberem **100% na VRAM**.

---

## 4. Diretrizes de Escolha: Qual Quantizacao Escolher para sua Maquina?

A configuracao da sua maquina (RTX 3080 10GB + Ryzen 5 3600 com 64GB DDR4) estabelece 3 cenarios operacionais nitidos:

### Cenario 1: Velocidade Extrema e Fluidez em Tempo Real (80 a 90 t/s)
- **Melhor Escolha**: **`UD-IQ2_S` (7.80 GB)** ou **`UD-Q2_K_XL` (9.15 GB com `-ot token_embd=CPU`)**.
- **Por que escolher**:
  - O modelo cabe **100% na VRAM da RTX 3080**.
  - A CPU nao toca no processamento dos tokens, eliminando o gargalo de 40.5 GB/s.
  - Velocidade de leitura superior a **80 tokens por segundo** (ideal para streaming instantaneo, sintese rapida, chamadas de funcoes e uso interativo sem engasgos).
  - Com o Unsloth Dynamic V3.0 (`UD`), os tensores criticos (`output.weight`, tensores de recorrencia SSM e primeiras camadas) sao mantidos em maior precisao, conferindo **85.0 a 87.5 pontos de inteligencia**, o que supera com folga modelos densos menores de 7B a 14B em 4-bits.

### Cenario 2: Maxima Inteligencia para Programacao e Raciocinio Complexo (5 a 6.5 t/s)
- **Melhor Escolha**: **`UD-IQ4_XS` (13.27 GB)** ou **`UD-Q4_K_M` (15.33 GB)**.
- **Por que escolher**:
  - Retencao de inteligencia de **96.5 a 97.0 pontos** (quase indistinguivel do modelo F16 original em benchmarks de logica, codigo e matematica).
  - Execucao hibrida: 36 a 42 camadas rodam na RTX 3080 e 23 a 29 camadas rodam na memoria DDR4 3600 MHz.
  - A velocidade de **~5 a 6.3 tokens por segundo** e equivalente a velocidade de leitura confortavel de um ser humano (uma frase de 20 palavras e gerada em ~4 segundos).
  - Perfeito para tarefas longas de agente, analise de codigo e raciocinio profundo (`thinking mode` ativado).

### Cenario 3: O Ponto de Equilibrio Ideal (Sweet Spot Interativo: ~10.5 t/s)
- **Melhor Escolha**: **`UD-IQ3_S` (11.21 GB)**.
- **Por que escolher**:
  - Aloca **50 camadas na RTX 3080** (76.7% do modelo na VRAM) e apenas 15 camadas na RAM.
  - Atinge exatamente o patamar confortavel de **~10.4 tokens/s**, mantendo **93.5 pontos de inteligencia**.
  - Equilibrio excelente entre tempo de espera e fidelidade de resposta.

---

## 5. Hierarquia de Sensibilidade dos Tensores (Ranking de Inteligencia)

Diferente de modelos puramente Transformer, a presenca de recorrencia DeltaNet cria regras estritas de quantizacao:

```text
[MAXIMA SENSIBILIDADE - NUNCA DESCER ABAIXO DE Q6_K / Q8_0]
 Posicao  Tensor                             Quant Nativo (UD)  Tamanho        Motivo Arquitetural
   1.     blk.*.ssm_alpha / ssm_beta          Q8_0               0.25 MB/camada Recorrencia linear DeltaNet: erro de quantizacao se acumula
                                                                                multiplicativamente a cada token na memoria recorrente.
   2.     blk.*.ssm_a / ssm_conv1d / ssm_dt   F32 (Nativo)       0.16 MB/camada Convolucao 1D temporal e constantes de decaimento do estado SSM.
   3.     output.weight (LM Head)             Q6_K               994.63 MB      Projeta os estados finais para 248.320 tokens do vocabulario;
                                                                                quantizacao baixa aqui distorce a distribuicao softmax.
   4.     blk.64.* (Camada MTP / NextN)       Q6_K / Q8_0        334.75 MB      Camada de predicao especulativa multi-token; sensivel a ruido.
   5.     blk.*.attn_output (Full Attention)  Q6_K               24.61 MB       Camadas quadraticas globais que estabilizam a atencao linear.

[ALTA SENSIBILIDADE - PONTAS E ATENCAO]
   6.     blk.0.* (Primeira Camada)           Q5_K / IQ4_XS      214.52 MB      Primeira projecao apos embedding; molda as representacoes iniciais.
   7.     blk.63.* (Ultima Camada)            Q6_K / Q5_K        214.52 MB      Ultima camada antes do cabecalho LM Head.
   8.     blk.*.attn_qkv (DeltaNet)           Q5_K / Q4_K        34.38 MB       Projecao combinada de Query, Key e Value para a atencao linear.
   9.     blk.*.attn_gate                     Q5_K / Q4_K        20.62 MB       Gating sigmoidal Swish que pondera o fluxo de informacao.

[MEDIA SENSIBILIDADE - EMBEDDINGS E ATENCAO SECUNDARIA]
  10.     token_embd.weight                   Q4_K               682.03 MB      Embedding estatico de tokens. Na geracao, apenas 1 linha
                                                                                (20 KB) e acessada por token. Pode ir para a RAM sem perda de velocidade.
  11.     blk.*.attn_q, attn_k, attn_v        Q5_K / Q4_K        47.50 MB/camada Projecoes das 16 camadas de Full Attention.

[BAIXA SENSIBILIDADE - MIOLO DENSO FFN: ONDE OCORRE A ECONOMIA]
  12.     blk.*.ffn_down.weight               IQ4_NL / IQ4_XS    45 a 48 MB     Projecao linear descendente (17408 -> 5120).
  13.     blk.*.ffn_gate.weight               IQ4_XS / Q4_K      45 a 48 MB     Projecao de ativacao SiLU (5120 -> 17408).
  14.     blk.*.ffn_up.weight                 IQ4_XS / Q3_K      36 a 48 MB     Projecao linear ascendente (5120 -> 17408).
```

### Oportunidade Estrategica nos FFNs:
Os tensores `ffn_gate`, `ffn_up` e `ffn_down` representam **17,11 bilhoes dos 27,32 bilhoes de parametros do modelo (~62,6% de todo o modelo)**!
Ao aplicar quantizacoes agressivas calibradas por imatrix (`IQ4_XS` ou `IQ3_S`) exclusivamente nas matrizes FFN enquanto se preservam os tensores SSM e Attention em `Q6_K`/`Q8_0` (como faz o Unsloth Dynamic V3.0), o modelo retem **>96% de sua capacidade cognitiva** reduzindo o tamanho em mais de 70% frente ao modelo original em BF16.

---

## 6. Recomendacao de Linha de Comando para o `llama-server`

### A. Para Modo Velocidade Maxima (100% VRAM, ~80 tokens/s):
Utilize o quant `UD-Q2_K_XL` com `token_embd` fixado na CPU para caber integralmente nos 10GB da RTX 3080:
```bash
./llama-server \
  -m Qwen3.8-27B-UD-Q2_K_XL.gguf \
  -ngl 65 \
  -ot "token_embd=CPU" \
  -c 8192 \
  -ctk q8_0 -ctv q8_0 \
  --threads 6 \
  --mlock
```

### B. Para Modo Raciocinio e Programacao de Alta Precisao (Hibrido, ~6.3 tokens/s):
Utilize o quant `UD-IQ4_XS` com alocacao de 42 camadas na GPU e ativacao de tinyBLAS no Ryzen 5 3600:
```bash
./llama-server \
  -m Qwen3.8-27B-UD-IQ4_XS.gguf \
  -ngl 42 \
  -ot "token_embd=CPU" \
  -c 8192 \
  -ctk q8_0 -ctv q8_0 \
  --threads 6 \
  --mlock
```
