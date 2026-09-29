# MoE Expert Tiering: Future Improvements

This document tracks identified optimization and architecture enhancement opportunities for the dynamic MoE expert offloading and swapping subsystem in llama.cpp.

---

## 1. Pinned Host Memory & Async Zero-Copy DMA (Implemented)

### Status
Implemented in this branch via `host_buft` (`ggml_backend_dev_host_buffer_type`) and a dedicated transfer backend instance (`g_transfer_backend`).

### Implementation
- CPU buffers allocated with pinned host memory where supported by the device backend.
- Dedicated transfer stream handles tensor slot transfers (`ggml_backend_tensor_set_async`), avoiding compute stream stalls during dynamic swaps.

---

## 2. Weighted Inertia with Imatrix (Implemented)

### Status
Implemented in this branch via `--expert-imatrix-weight` (`-eiw`).

### Context
At the beginning of a short session or request (<50 tokens), EMA activation counts are sparse. Early eviction decisions might displace globally important experts before sufficient runtime evidence accumulates.

### Implementation
- Combines static imatrix calibration importance with dynamic EMA frequency:
  `S_effective = (1 - imatrix_weight) * S_EMA + imatrix_weight * (S_imatrix_norm * IMATRIX_SCORE_SCALE)`
- Preserves stability during short user prompts and avoids churn of structurally critical experts.

---

## 3. Granular Layer-Specific Early Exit & Imatrix Energy Profiling (Implemented)

### Status
Implemented in this branch via `--expert-early-exit` (`-eee`), supporting repeatable rules with syntax `START,END,MIN[,MAX]` or `START,END,TARGET_P`.

### Context
In deep MoE models (e.g. 48 layers), activation energy across layers is non-uniform: some layers exhibit severe energy peaks (requiring high retention to prevent perplexity degradation), while others form low-energy valleys or plateaus where aggressive early exit yields massive compute savings with negligible quality loss.

### Implementation
- **Granular CLI Rules**:
  - Repeatable parameter: `-eee START,END,MIN[,MAX]` (e.g. `-eee 0,0,1.0 -eee 1,3,0.90 -eee 4,39,0.60,0.80 -eee 40,47,0.95`).
  - Supports comma, semicolon, or pipe separators for multi-rule strings.
  - When omitted, early exit is strictly disabled (target-p = 1.0, 100% precision).
- **Token Confidence Scaling**:
  - Within each layer's defined `[min, max]` interval, routing dynamically adjusts target-p per token based on router confidence.
  - Easy tokens drop to `min` for maximum throughput; harder tokens scale up to `max`.
  - If only a single value is provided (e.g. `-eee 1,3,0.90`), min == max and target-p is fixed for that layer range.
- **Layer-by-Layer Energy Chart**:
  - Displays imatrix activation energy (`in_sum2` across MoE tensors + attn) and classifications (`PEAK`, `VALLEY`, `PLATEAU`) alongside effective target-p settings.
  - **Logging Level**: The 48-layer energy chart is conditioned on verbosity level 4 (`-lv 4`, `--verbosity 4`, or `-v`), keeping standard startup logs clean while remaining available on demand.

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

---

## 5. Adaptive Prefetch Distance for Cold MoE Kernels (i+2 / i+4)

### Context
The current CPU fused MoE kernel (`ggml_moe_cold`) prefetches one row ahead (`i + 1`) during dot product loops. Under high thread count or saturated memory bus queues, memory access latency increases.

### Proposal
- Detect page size (e.g. Linux 2MB HugePages vs 4KB pages) or memory subsystem saturation.
- Expand software prefetch distance from `i + 1` to `i + 2` or `i + 4` when HugePages are detected, hiding memory queue delays without premature TLB misses.

