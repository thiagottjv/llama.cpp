#pragma once

#include "ggml.h"
#include <string>
#include <vector>

struct llama_model;

// Expert tier: drop-in offloading of top-S MoE experts to GPU VRAM while
// keeping cold experts in CPU RAM.
//
// When active:
// - Hot experts are evaluated on GPU via ggml_mul_mat_id into dst_hot
// - Cold experts are evaluated on CPU via fused ggml_moe_cold
// - The two results are added together in build_moe_ffn

// Initialize expert tier for the given model.
// n_vram_experts: number of experts per layer to keep in VRAM.
// layer_expert_order: optional per-layer ranking of expert IDs (descending importance).
// target_p: target cumulative routing probability mass for active experts (default: 0.85).
bool llama_expert_tier_init(struct llama_model * model,
                            int32_t n_vram_experts,
                            const std::vector<std::vector<int>> & layer_expert_order = {},
                            float target_p = 0.85f);

// Clear and free all expert tier structures and VRAM buffers.
void llama_expert_tier_free();

// Check if expert weight tensor w is registered in the expert tier.
bool llama_expert_tier_has(struct ggml_tensor * w);

// Drop-in hook called from build_lora_mm_id.
// Returns hot GPU result (or hot+cold if not fused).
struct ggml_tensor * llama_expert_tier_build(struct ggml_context * ctx,
                                             struct ggml_tensor  * w,
                                             struct ggml_tensor  * cur,
                                             struct ggml_tensor  * ids,
                                             struct ggml_tensor  * w_s);

// Begin fused MoE layer (called before gate/up/down expert matmuls).
bool llama_expert_tier_begin_fused(struct ggml_tensor * gate_w,
                                   struct ggml_tensor * up_w,
                                   struct ggml_tensor * down_w,
                                   struct ggml_tensor * ids);

// End fused MoE layer (called after down matmul to create ggml_moe_cold node).
struct ggml_tensor * llama_expert_tier_end_fused(struct ggml_context * ctx,
                                                 struct ggml_tensor  * gate_w,
                                                 struct ggml_tensor  * up_w,
                                                 struct ggml_tensor  * down_w,
                                                 struct ggml_tensor  * x,
                                                 struct ggml_tensor  * ids,
                                                 struct ggml_tensor  * weights,
                                                 int32_t               act);

// Update dynamic expert cache based on activation counts.
// Swaps up to max_swaps cold experts with hot experts per layer.
// Returns total number of expert swaps executed.
int32_t llama_expert_tier_update(int32_t max_swaps = 1);
