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
// layer_expert_order: optional per-layer ranking of expert IDs (descending importance).
// layer_hot_s: number of hot experts allocated per layer.
// target_p_min, target_p_max: cumulative probability range (equal for fixed target, default: 1.0 = disabled).
// layer_scores_norm: per-layer normalized global scores [0.0, 1.0] for active experts.
bool llama_expert_tier_init(llama_model * model,
                            const std::vector<std::vector<int>> & layer_expert_order,
                            const std::vector<int> & layer_hot_s,
                            float target_p_min = 1.0f,
                            float target_p_max = 1.0f,
                            const std::vector<std::vector<float>> & layer_scores_norm = {},
                            float target_p_depth_delta = 0.0f);

// Clear and free all expert tier structures and VRAM buffers.
void llama_expert_tier_free();

// Drop-in hook called from build_lora_mm_id.
// Returns hot GPU result (or hot+cold if not fused).
ggml_tensor * llama_expert_tier_build(ggml_context * ctx,
                                      ggml_tensor  * w,
                                      ggml_tensor  * cur,
                                      ggml_tensor  * ids,
                                      ggml_tensor  * w_s);

// Begin fused MoE layer (called before gate/up/down expert matmuls).
bool llama_expert_tier_begin_fused(ggml_tensor * gate_w,
                                   ggml_tensor * up_w,
                                   ggml_tensor * down_w,
                                   ggml_tensor * ids);

// End fused MoE layer (called after down matmul to create ggml_moe_cold node).
ggml_tensor * llama_expert_tier_end_fused(ggml_context * ctx,
                                          ggml_tensor  * gate_w,
                                          ggml_tensor  * up_w,
                                          ggml_tensor  * down_w,
                                          ggml_tensor  * x,
                                          ggml_tensor  * ids,
                                          ggml_tensor  * weights,
                                          int32_t        act);

// Update dynamic expert cache based on activation counts globally across all layers.
// swap_frac: max fraction of total VRAM experts to swap across the model (default: 0.0f, 0 to disable).
// attenuation: EMA attenuation rate (default: 0.15f, decay = 1 - attenuation).
// imatrix_weight: weight of persistent imatrix importance in retention score (default: 0.0f, 0 to disable).
// Returns total number of expert swaps executed immediately.
int32_t llama_expert_tier_update(float swap_frac = 0.0f, float attenuation = 0.15f, float imatrix_weight = 0.0f);

// Drain up to max_swaps from the pending swap queue (max_swaps <= 0 drains all).
// Returns number of swaps executed.
int32_t llama_expert_tier_drain_queue(int max_swaps = 1);

// Returns current number of pending expert swaps in queue.
size_t llama_expert_tier_queue_size();

