#include "llama-expert-tier.h"
#include "llama-model.h"
#include "llama-impl.h"
#include "ggml-backend.h"
#include "ggml-alloc.h"
#include "ggml-cpp.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
    struct tier_entry {
        ggml_tensor * dst_hot   = nullptr;
        ggml_tensor * hot_lut   = nullptr;
        ggml_tensor * cold_mask = nullptr;
        ggml_tensor * counts    = nullptr;
    };

    struct layer_tier {
        int il = -1;
        int n_experts = 0;
        int hot_s = 0;

        std::vector<ggml_tensor *> src_tensors;
        std::vector<ggml_tensor *> dst_hots;
        ggml_tensor * hot_lut   = nullptr;
        ggml_tensor * cold_mask = nullptr;
        ggml_tensor * counts    = nullptr;

        std::vector<int32_t> slot_to_expert;
        std::vector<float>   expert_scores;
        std::vector<int32_t> hot_lut_cpu;
        std::vector<int32_t> cold_mask_cpu;
    };

    std::mutex g_mtx;
    std::unordered_map<ggml_tensor *, tier_entry> g_table;
    std::vector<layer_tier> g_layers;
    bool  g_fused_active = false;
    float g_target_p = 0.85f;

    std::vector<ggml_context_ptr>        g_ctxs;
    std::vector<ggml_backend_buffer_ptr> g_bufs;
}

void llama_expert_tier_free() {
    std::lock_guard<std::mutex> lk(g_mtx);
    g_table.clear();
    g_layers.clear();
    g_ctxs.clear();
    g_bufs.clear();
    g_fused_active = false;
}

bool llama_expert_tier_has(struct ggml_tensor * w) {
    std::lock_guard<std::mutex> lk(g_mtx);
    return g_table.find(w) != g_table.end();
}

static ggml_tensor * remap_ids(ggml_context * ctx,
                              ggml_tensor * lut,
                              ggml_tensor * selected,
                              int n_expert_used,
                              int n_tokens) {
    ggml_tensor * flat_ids = ggml_reshape_1d(ctx,
        ggml_cont(ctx, selected), n_expert_used * n_tokens);
    ggml_tensor * r = ggml_get_rows(ctx, lut, flat_ids);
    return ggml_reshape_2d(ctx, r, n_expert_used, n_tokens);
}

struct ggml_tensor * llama_expert_tier_build(struct ggml_context * ctx,
                                             struct ggml_tensor  * w,
                                             struct ggml_tensor  * cur,
                                             struct ggml_tensor  * ids,
                                             struct ggml_tensor  * w_s) {
    tier_entry ent;
    {
        std::lock_guard<std::mutex> lk(g_mtx);
        auto it = g_table.find(w);
        if (it == g_table.end()) {
            return nullptr;
        }
        ent = it->second;
    }

    const int n_expert_used = (int) ids->ne[0];
    const int n_tokens      = (int) ids->ne[1];

    ggml_tensor * ids_hot = remap_ids(ctx, ent.hot_lut, ids, n_expert_used, n_tokens);
    ggml_tensor * hot     = ggml_mul_mat_id(ctx, ent.dst_hot, cur, ids_hot);

    (void) w_s;

    return hot;
}

bool llama_expert_tier_begin_fused(struct ggml_tensor * gate_w,
                                   struct ggml_tensor * up_w,
                                   struct ggml_tensor * down_w,
                                   struct ggml_tensor * ids) {
    g_fused_active = false;
    if (!gate_w || !up_w || !down_w || !ids) {
        return false;
    }
    std::lock_guard<std::mutex> lk(g_mtx);
    if (g_table.find(gate_w) == g_table.end() ||
        g_table.find(up_w)   == g_table.end() ||
        g_table.find(down_w) == g_table.end()) {
        return false;
    }
    g_fused_active = true;
    return true;
}

struct ggml_tensor * llama_expert_tier_end_fused(struct ggml_context * ctx,
                                                 struct ggml_tensor  * gate_w,
                                                 struct ggml_tensor  * up_w,
                                                 struct ggml_tensor  * down_w,
                                                 struct ggml_tensor  * x,
                                                 struct ggml_tensor  * ids,
                                                 struct ggml_tensor  * weights,
                                                 int32_t               act) {
    if (!g_fused_active) {
        return nullptr;
    }
    g_fused_active = false;

    tier_entry ent;
    {
        std::lock_guard<std::mutex> lk(g_mtx);
        auto it = g_table.find(down_w);
        if (it == g_table.end()) {
            return nullptr;
        }
        ent = it->second;
    }

    return ggml_moe_cold(ctx, gate_w, up_w, down_w, x, ids, ent.cold_mask, ent.counts, weights, act, g_target_p);
}

bool llama_expert_tier_init(struct llama_model * model,
                            int32_t n_vram_experts,
                            const std::vector<std::vector<int>> & layer_expert_order,
                            float target_p) {
    if (!model || n_vram_experts <= 0) {
        return false;
    }

    llama_expert_tier_free();
    g_target_p = target_p;

    // Look for GPU device in model
    ggml_backend_dev_t gpu_dev = nullptr;
    for (const auto & d : model->devices) {
        if (ggml_backend_dev_type(d.dev) == GGML_BACKEND_DEVICE_TYPE_GPU) {
            gpu_dev = d.dev;
            break;
        }
    }
    if (!gpu_dev) {
        LLAMA_LOG_WARN("%s: no GPU device found for expert tier offloading\n", __func__);
        return false;
    }

    ggml_backend_buffer_type_t gpu_buft = ggml_backend_dev_buffer_type(gpu_dev);
    ggml_backend_buffer_type_t cpu_buft = ggml_backend_cpu_buffer_type();

    int n_layers = (int) model->layers.size();
    int total_tiered_tensors = 0;

    for (int il = 0; il < n_layers; ++il) {
        auto & layer = model->layers[il];
        std::vector<ggml_tensor *> exps_tensors;
        if (layer.ffn_gate_exps) exps_tensors.push_back(layer.ffn_gate_exps);
        if (layer.ffn_up_exps)   exps_tensors.push_back(layer.ffn_up_exps);
        if (layer.ffn_down_exps) exps_tensors.push_back(layer.ffn_down_exps);
        if (layer.ffn_gate_up_exps) exps_tensors.push_back(layer.ffn_gate_up_exps);

        if (exps_tensors.empty()) {
            continue;
        }

        const int n_experts = (int) exps_tensors[0]->ne[2];
        const int hot_s = std::min((int) n_vram_experts, n_experts);
        if (hot_s <= 0) {
            continue;
        }

        std::vector<int> rank(n_experts);
        if (il < (int) layer_expert_order.size() && (int) layer_expert_order[il].size() == n_experts) {
            rank = layer_expert_order[il];
        } else {
            for (int ex = 0; ex < n_experts; ++ex) {
                rank[ex] = ex;
            }
        }

        ggml_init_params p_gpu = {
            /* .mem_size   = */ ggml_tensor_overhead() * (exps_tensors.size() + 2),
            /* .mem_buffer = */ nullptr,
            /* .no_alloc   = */ true,
        };
        ggml_context_ptr ctx_gpu(ggml_init(p_gpu));
        if (!ctx_gpu) {
            LLAMA_LOG_ERROR("%s: failed to create GPU context for layer %d\n", __func__, il);
            return false;
        }

        ggml_init_params p_cpu = {
            /* .mem_size   = */ ggml_tensor_overhead() * 2,
            /* .mem_buffer = */ nullptr,
            /* .no_alloc   = */ true,
        };
        ggml_context_ptr ctx_cpu(ggml_init(p_cpu));
        if (!ctx_cpu) {
            LLAMA_LOG_ERROR("%s: failed to create CPU context for layer %d\n", __func__, il);
            return false;
        }

        std::vector<ggml_tensor *> dst_hots(exps_tensors.size());
        for (size_t i = 0; i < exps_tensors.size(); ++i) {
            auto * src = exps_tensors[i];
            dst_hots[i] = ggml_new_tensor_3d(ctx_gpu.get(), src->type, src->ne[0], src->ne[1], hot_s + 1);
            ggml_set_name(dst_hots[i], (std::string(src->name) + ".hot").c_str());
        }

        ggml_tensor * hot_lut   = ggml_new_tensor_2d(ctx_gpu.get(), GGML_TYPE_I32, 1, n_experts);
        ggml_tensor * cold_mask = ggml_new_tensor_1d(ctx_cpu.get(), GGML_TYPE_I32, n_experts);
        ggml_tensor * counts    = ggml_new_tensor_1d(ctx_cpu.get(), GGML_TYPE_I32, n_experts + 1);

        ggml_backend_buffer_t buf_gpu = ggml_backend_alloc_ctx_tensors_from_buft(ctx_gpu.get(), gpu_buft);
        if (!buf_gpu) {
            LLAMA_LOG_ERROR("%s: failed to allocate GPU buffer for layer %d (%d hot experts)\n",
                __func__, il, hot_s);
            return false;
        }
        ggml_backend_buffer_set_usage(buf_gpu, GGML_BACKEND_BUFFER_USAGE_WEIGHTS);
        ggml_backend_buffer_clear(buf_gpu, 0);

        ggml_backend_buffer_t buf_cpu = ggml_backend_alloc_ctx_tensors_from_buft(ctx_cpu.get(), cpu_buft);
        if (!buf_cpu) {
            LLAMA_LOG_ERROR("%s: failed to allocate CPU buffer for layer %d\n", __func__, il);
            return false;
        }
        ggml_backend_buffer_set_usage(buf_cpu, GGML_BACKEND_BUFFER_USAGE_WEIGHTS);
        ggml_backend_buffer_clear(buf_cpu, 0);

        // Copy top-S expert weights
        for (size_t i = 0; i < exps_tensors.size(); ++i) {
            auto * src = exps_tensors[i];
            auto * dst = dst_hots[i];
            const size_t slot_bytes = ggml_nbytes(src) / (size_t) src->ne[2];
            const char * src_data = (const char *) ggml_get_data(src);

            if (src_data) {
                for (int p = 0; p < hot_s; ++p) {
                    const int ex = rank[p];
                    ggml_backend_tensor_set(dst, src_data + (size_t) ex * slot_bytes,
                                            (size_t) p * slot_bytes, slot_bytes);
                }
            } else {
                std::vector<uint8_t> tmp(slot_bytes);
                for (int p = 0; p < hot_s; ++p) {
                    const int ex = rank[p];
                    ggml_backend_tensor_get(src, tmp.data(), (size_t) ex * slot_bytes, slot_bytes);
                    ggml_backend_tensor_set(dst, tmp.data(), (size_t) p * slot_bytes, slot_bytes);
                }
            }
        }

        // Initialize hot_lut and cold_mask
        std::vector<int32_t> h_lut(n_experts, hot_s);
        std::vector<int32_t> c_mask(n_experts, 1);
        for (int p = 0; p < hot_s; ++p) {
            const int ex = rank[p];
            h_lut[ex] = p;
            c_mask[ex] = 0;
        }

        ggml_backend_tensor_set(hot_lut, h_lut.data(), 0, n_experts * sizeof(int32_t));
        ggml_backend_tensor_set(cold_mask, c_mask.data(), 0, n_experts * sizeof(int32_t));

        {
            std::lock_guard<std::mutex> lk(g_mtx);
            for (size_t i = 0; i < exps_tensors.size(); ++i) {
                tier_entry ent;
                ent.dst_hot   = dst_hots[i];
                ent.hot_lut   = hot_lut;
                ent.cold_mask = cold_mask;
                ent.counts    = counts;
                g_table[exps_tensors[i]] = ent;
                total_tiered_tensors++;
            }

            layer_tier lt;
            lt.il = il;
            lt.n_experts = n_experts;
            lt.hot_s = hot_s;
            lt.src_tensors = exps_tensors;
            lt.dst_hots = dst_hots;
            lt.hot_lut = hot_lut;
            lt.cold_mask = cold_mask;
            lt.counts = counts;
            lt.slot_to_expert.resize(hot_s);
            for (int p = 0; p < hot_s; ++p) {
                lt.slot_to_expert[p] = rank[p];
            }
            lt.expert_scores.assign(n_experts, 0.0f);
            lt.hot_lut_cpu = h_lut;
            lt.cold_mask_cpu = c_mask;
            g_layers.push_back(std::move(lt));
        }

        g_ctxs.push_back(std::move(ctx_gpu));
        g_ctxs.push_back(std::move(ctx_cpu));
        g_bufs.push_back(ggml_backend_buffer_ptr(buf_gpu));
        g_bufs.push_back(ggml_backend_buffer_ptr(buf_cpu));
    }

    LLAMA_LOG_INFO("%s: initialized expert tier with %d VRAM experts per layer (%d tensors offloaded, target p: %.2f)\n",
        __func__, n_vram_experts, total_tiered_tensors, target_p);

    return total_tiered_tensors > 0;
}

int32_t llama_expert_tier_update(int32_t max_swaps) {
    if (max_swaps <= 0) {
        return 0;
    }

    std::lock_guard<std::mutex> lk(g_mtx);
    if (g_layers.empty()) {
        return 0;
    }

    LLAMA_LOG_INFO("%s: checking expert tier (max_swaps=%d, %zu layers)\n",
                   __func__, max_swaps, g_layers.size());

    int32_t total_swaps = 0;
    int layers_active = 0;
    const float decay = 0.85f;
    const float margin = 0.05f;
    const float min_diff = 1.0f;

    for (auto & lt : g_layers) {
        if (!lt.counts || lt.hot_s <= 0 || lt.hot_s >= lt.n_experts) {
            continue;
        }

        std::vector<int32_t> cnt(lt.n_experts + 1, 0);
        ggml_backend_tensor_get(lt.counts, cnt.data(), 0, (lt.n_experts + 1) * sizeof(int32_t));

        if (cnt[lt.n_experts] == 0) {
            continue;
        }
        layers_active++;

        std::vector<int32_t> zero(lt.n_experts + 1, 0);
        ggml_backend_tensor_set(lt.counts, zero.data(), 0, (lt.n_experts + 1) * sizeof(int32_t));

        for (int e = 0; e < lt.n_experts; ++e) {
            lt.expert_scores[e] = lt.expert_scores[e] * decay + (float) cnt[e];
        }

        for (int sw = 0; sw < max_swaps; ++sw) {
            int min_p = -1;
            float min_hot_score = 1e30f;
            for (int p = 0; p < lt.hot_s; ++p) {
                const int ex = lt.slot_to_expert[p];
                if (lt.expert_scores[ex] < min_hot_score) {
                    min_hot_score = lt.expert_scores[ex];
                    min_p = p;
                }
            }

            int max_cold_ex = -1;
            float max_cold_score = -1.0f;
            for (int ex = 0; ex < lt.n_experts; ++ex) {
                if (lt.cold_mask_cpu[ex] == 1) {
                    if (lt.expert_scores[ex] > max_cold_score) {
                        max_cold_score = lt.expert_scores[ex];
                        max_cold_ex = ex;
                    }
                }
            }

            if (min_p < 0 || max_cold_ex < 0) {
                break;
            }

            const float thresh = min_hot_score * (1.0f + margin) + min_diff;

            // Log diagnostic info for layer 0 or layer 24 (midpoint)
            if (sw == 0 && (lt.il == 0 || lt.il == (int) g_layers.size() / 2)) {
                LLAMA_LOG_INFO("%s: L%d stats: tokens=%d, min_hot=e%d(score=%.1f), max_cold=e%d(score=%.1f), thresh=%.1f\n",
                               __func__, lt.il, cnt[lt.n_experts],
                               (min_p >= 0 ? lt.slot_to_expert[min_p] : -1), min_hot_score,
                               max_cold_ex, max_cold_score, thresh);
            }

            if (max_cold_score <= thresh) {
                break;
            }

            const int e_out = lt.slot_to_expert[min_p];
            const int e_in  = max_cold_ex;
            const int p     = min_p;

            for (size_t i = 0; i < lt.src_tensors.size(); ++i) {
                auto * src = lt.src_tensors[i];
                auto * dst = lt.dst_hots[i];
                const size_t slot_bytes = ggml_nbytes(src) / (size_t) src->ne[2];
                const char * src_data = (const char *) ggml_get_data(src);

                if (src_data) {
                    ggml_backend_tensor_set(dst, src_data + (size_t) e_in * slot_bytes,
                                            (size_t) p * slot_bytes, slot_bytes);
                } else {
                    std::vector<uint8_t> tmp(slot_bytes);
                    ggml_backend_tensor_get(src, tmp.data(), (size_t) e_in * slot_bytes, slot_bytes);
                    ggml_backend_tensor_set(dst, tmp.data(), (size_t) p * slot_bytes, slot_bytes);
                }
            }

            lt.hot_lut_cpu[e_out] = lt.hot_s;
            lt.hot_lut_cpu[e_in]  = p;

            lt.cold_mask_cpu[e_out] = 1;
            lt.cold_mask_cpu[e_in]  = 0;

            lt.slot_to_expert[p] = e_in;

            const int32_t val_sentinel = lt.hot_s;
            const int32_t val_p = p;
            ggml_backend_tensor_set(lt.hot_lut, &val_sentinel, (size_t) e_out * sizeof(int32_t), sizeof(int32_t));
            ggml_backend_tensor_set(lt.hot_lut, &val_p,        (size_t) e_in  * sizeof(int32_t), sizeof(int32_t));

            const int32_t val_one  = 1;
            const int32_t val_zero = 0;
            ggml_backend_tensor_set(lt.cold_mask, &val_one,  (size_t) e_out * sizeof(int32_t), sizeof(int32_t));
            ggml_backend_tensor_set(lt.cold_mask, &val_zero, (size_t) e_in  * sizeof(int32_t), sizeof(int32_t));

            LLAMA_LOG_INFO("%s: layer %d swapped expert %d (score %.1f) -> slot %d (evicted %d, score %.1f)\n",
                           __func__, lt.il, e_in, max_cold_score, p, e_out, min_hot_score);

            total_swaps++;
        }
    }

    LLAMA_LOG_INFO("%s: cycle complete (layers_active=%d/%zu, swaps=%d)\n",
                   __func__, layers_active, g_layers.size(), total_swaps);

    if (total_swaps > 0) {
        LLAMA_LOG_INFO("%s: dynamically swapped %d experts into VRAM\n", __func__, total_swaps);
    }

    return total_swaps;
}

bool llama_model_init_expert_tier(
        struct llama_model * model,
        int32_t              n_vram_experts,
        const int32_t      * expert_order,
        size_t               n_expert_order,
        float                target_p) {
    std::vector<std::vector<int>> order;
    if (model && expert_order && n_expert_order > 0) {
        int n_layers = (int) model->layers.size();
        if (n_layers > 0) {
            int n_exp_per_layer = (int) (n_expert_order / n_layers);
            order.resize(n_layers);
            for (int il = 0; il < n_layers; ++il) {
                order[il].assign(expert_order + il * n_exp_per_layer,
                                 expert_order + (il + 1) * n_exp_per_layer);
            }
        }
    }
    return llama_expert_tier_init(model, n_vram_experts, order, target_p);
}

void llama_model_free_expert_tier(void) {
    llama_expert_tier_free();
}

int32_t llama_model_expert_tier_update(struct llama_model * model, int32_t max_swaps) {
    (void) model;
    return llama_expert_tier_update(max_swaps);
}
