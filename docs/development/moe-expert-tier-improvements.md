# MoE Expert Tiering: Future Improvements

This document tracks identified optimization and architecture enhancement opportunities for the dynamic MoE expert offloading and swapping subsystem in llama.cpp.

---

## 1. Pinned Host Memory for Async Zero-Copy DMA

### Context
Cold expert weights in CPU RAM currently reside in standard host memory (mmap or malloc). Moving an expert to GPU (copy_expert_tensor_slot via ggml_backend_tensor_set) uses standard pageable transfers.

### Proposal
- Allocate cold expert CPU buffers with page-locked (pinned) memory (cudaHostRegister or GGML_BACKEND_CPU_BUFFER_TYPE_PINNED).
- Execute transfers using a dedicated asynchronous CUDA transfer stream (cudaMemcpyAsync), decoupled from the main compute stream.

### Benefits
- Minimal swap latency: PCIe transfer time decreases from ~0.10ms to ~0.02-0.03ms per expert.
- Zero compute stall: The swap of one expert occurs concurrently with attention computation of the next token.

---

## 2. Weighted Inertia with Imatrix (Warmup Phase)

### Context
At the beginning of a short session or request (<50 tokens), EMA activation counts are sparse. Early eviction decisions might displace globally important experts before sufficient runtime evidence accumulates.

### Proposal
- Combine static imatrix calibration importance with dynamic EMA frequency:
  S_effective = (1 - lambda) * S_imatrix + lambda * S_EMA
  where:
  lambda = min(1.0, tokens_processed / warmup_tokens) (e.g. warmup_tokens = 512)

### Benefits
- Preserves stability during short user prompts.
- Smoothly transitions from calibration priors to user-specific domain adaptation.

---

## 3. Layer-Aware Adaptive Early Exit

### Context
In deep MoE models (e.g. 48 layers), initial layers (0 to 10) extract lower-level syntactic patterns where tail experts contribute minimally. Later layers (25 to 45) concentrate high-level semantic reasoning.

### Proposal
- Parameterize target_p as a function of layer index or depth:
  - Initial layers: aggressive exit threshold (e.g. 0.65 - 0.70)
  - Deep layers: conservative threshold (e.g. 0.95 - 0.97)

### Benefits
- Further reduces CPU compute in superficial layers.
- Guarantees full precision where multi-step reasoning occurs.

---

## 4. Real-time Observability in llama-server

### Context
In production deployments, operators need visibility into VRAM tier efficiency.

### Proposal
- Expose metrics in the /metrics Prometheus endpoint:
  - llama_moe_vram_hit_rate: Cumulative routing probability served directly by VRAM.
  - llama_moe_queue_pending: Number of expert swaps waiting in the async queue.
  - llama_moe_cold_experts_computed: Count of cold experts evaluated by CPU.
  - llama_moe_swaps_total: Total completed hot-swaps.
