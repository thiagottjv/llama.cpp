# Guia de Otimizacao de Memoria e Protecao contra OOM no Ubuntu Server

Este guia detalha como configurar o Linux (Ubuntu Server) para executar modelos MoE gigantes (como o Qwen 3.8 Flash Next) com seguranca maxima de memoria RAM, garantindo que o modelo **nunca seja enviado para a Swap** e que o **OOM-Killer do Linux nunca finalize o `llama-server`**.

---

## 1. Principios de Funcionamento

1. **`--mlock` (Memory Lock)**:
   - Utiliza a chamada de sistema `mlock()` do kernel Linux.
   - Marca as paginas do modelo com a flag `PG_mlocked`.
   - O kernel e proibido de mover qualquer pagina travada para o disco (Swap).
2. **`MemorySwapMax=0` (cgroups v2)**:
   - Proibe explicitamente que qualquer alocacao do processo (inclusive KV Cache de contexto) vaze para o swap.
3. **`OOMScoreAdjust=-1000`**:
   - Imuniza o processo contra o OOM-Killer. Se faltar memoria fisica, o Linux encerra qualquer processo secundario antes de tocar no `llama-server`.
4. **`vm.swappiness = 1`**:
   - Configura a agressividade do kernel: o swap so sera ativado quando a RAM fisica estiver 99% ocupada.

---

## 2. Passo 1: Criacao de Swapfile Seguro (NVMe)

O swap serve como valvula de escape para processos auxiliares (SSH, cron, daemons do sistema), evitando travamentos gerais.

```bash
# 1. Cria um arquivo de 16 GB
sudo fallocate -l 16G /swapfile

# 2. Ajusta permissoes estritas
sudo chmod 600 /swapfile

# 3. Formata como swap
sudo mkswap /swapfile

# 4. Ativa o swap
sudo swapon /swapfile

# 5. Adiciona ao /etc/fstab para persistir entre reinicializacoes
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
```

---

## 3. Passo 2: Ajustes de Kernel (`/etc/sysctl.conf`)

Edite o arquivo de parametros do kernel:

```bash
sudo nano /etc/sysctl.conf
```

Adicione ao final do arquivo:

```ini
# Evita uso proativo de swap; so usa em casos extremos de emergencia
vm.swappiness = 1

# Forca o descarte rapido de cache de arquivos/inodes da RAM
vm.vfs_cache_pressure = 200

# Reserva 512 MB estritos para operacoes criticas do kernel
vm.min_free_kbytes = 524288
```

Aplique imediatamente sem reiniciar:

```bash
sudo sysctl -p
```

---

## 4. Passo 3: Liberar Limite de `memlock` para o Usuario

Por padrao, usuarios comuns possuem limite baixo de memoria travavel por `mlock`.

Edite `/etc/security/limits.conf`:

```bash
sudo nano /etc/security/limits.conf
```

Adicione ao final do arquivo:

```text
* soft memlock unlimited
* hard memlock unlimited
```

---

## 5. Passo 4: Servico Systemd Blindado (`llama-server.service`)

Criar um servico systemd e a forma recomendada para gerenciar o `llama-server`, pois permite aplicar cotas de cgroups v2 e imunidade contra OOM.

Crie o arquivo `/etc/systemd/system/llama-server.service`:

```ini
[Unit]
Description=Llama Server MoE High Performance
After=network.target

[Service]
Type=simple
User=ai
WorkingDirectory=/home/ai/llama.cpp

# 1. Permite memlock infinito na DDR4
LimitMEMLOCK=infinity

# 2. Imunidade total ao OOM Killer (-1000 = nunca matar)
OOMScoreAdjust=-1000

# 3. Proibicao absoluta de usar Swap para este processo
MemorySwapMax=0

# 4. Prioridade de protecao de memoria RAM
MemoryLow=56G

# 5. Comando de execucao
ExecStart=/home/ai/llama.cpp/build/bin/llama-server \
  -m /home/ai/models/Qwen3.8-Flash-Next-TTJV-q2/Qwen3.8-Flash-Next-TTJV-q2-00001-of-00008.gguf \
  --host 0.0.0.0 --port 8080 \
  --vram-expert-budget-mb 3000 \
  -eee 3,39,0.60,0.80 \
  --mlock

Restart=on-failure
RestartSec=5s

[Install]
WantedBy=multi-user.target
```

Ative e inicie o servico:

```bash
sudo systemctl daemon-reload
sudo systemctl enable --now llama-server
```

---

## 6. Comandos Uteis para Verificacao e Monitoramento

1. **Verificar se a memoria esta travada (sem swap)**:
   ```bash
   # Mostra o status de memoria travada (VmLck) do processo
   grep -E 'VmLck|VmSwap|VmRSS' /proc/$(pgrep llama-server | head -1)/status
   ```
   - `VmLck`: Mostra a memoria travada fisicamente na RAM pelo `--mlock` (~56 GB).
   - `VmSwap`: Mostra a memoria em swap (deve ser rigorosamente `0 kB`).
   - `VmRSS`: Memoria fisica residente total utilizada pelo processo.

2. **Monitorar uso de Swap e RAM em tempo real**:
   ```bash
   free -h
   swapon --show
   vmstat 1 5
   ```

3. **Verificar logs do servico**:
   ```bash
   journalctl -u llama-server -f
   ```
