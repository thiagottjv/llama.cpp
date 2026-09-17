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

## 3. Layer-Aware Adaptive Early Exit (Implemented)

### Status
Implemented in this branch via `--expert-target-p-depth-delta` (`-etpdd`).

### Context
In deep MoE models (e.g. 48 layers), initial layers (0 to 10) extract lower-level syntactic patterns where tail experts contribute minimally. Later layers (25 to 45) concentrate high-level semantic reasoning.

### Implementation
- Parameterizes target_p as a linear depth slope across layers:
  `target_p(layer) = clamp(target_p_base + (depth_frac - 0.5) * 2 * depth_delta, 0.05, 1.0)`
- Reduces CPU compute in superficial layers while preserving full precision in deep layers.

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

