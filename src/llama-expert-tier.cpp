#include "llama-expert-tier.h"
#include "llama-model.h"
#include "llama-impl.h"
#include "ggml-backend.h"
#include "ggml-cpp.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
    struct tier_entry {
        ggml_tensor * dst_hot    = nullptr;
        ggml_tensor * hot_lut    = nullptr;
        ggml_tensor * cold_mask  = nullptr;
        ggml_tensor * counts     = nullptr;
        ggml_tensor * exp_scores = nullptr;
        float target_p_min       = 1.0f;
        float target_p_max       = 1.0f;
    };

    struct layer_tier {
        int il = -1;
        int n_experts = 0;
        int hot_s = 0;

        std::vector<ggml_tensor *> src_tensors;
        std::vector<ggml_tensor *> dst_hots;
        ggml_tensor * hot_lut    = nullptr;
        ggml_tensor * cold_mask  = nullptr;
        ggml_tensor * counts     = nullptr;
        ggml_tensor * exp_scores = nullptr;

        float target_p_min       = 1.0f;
        float target_p_max       = 1.0f;

        std::vector<int32_t> slot_to_expert;
        std::vector<float>   expert_scores;
        std::vector<float>   expert_scores_norm;
        std::vector<float>   expert_imatrix_norm;
        std::vector<int32_t> hot_lut_cpu;
        std::vector<int32_t> cold_mask_cpu;
    };

    struct candidate_swap {
        int layer_idx;
        int slot_p;
        int e_in;
        int e_out;
        float cold_score;
        float hot_score;
        float gain;
    };

    std::mutex g_mtx;
    std::unordered_map<ggml_tensor *, tier_entry> g_table;
    std::vector<layer_tier> g_layers;
    std::deque<candidate_swap> g_swap_queue;
    std::atomic<bool> g_has_pending_swaps{false};
    thread_local bool g_fused_active = false;

    std::vector<ggml_context_ptr>        g_ctxs;
    std::vector<ggml_backend_buffer_ptr> g_bufs;
    ggml_backend_t                       g_transfer_backend = nullptr;
}

void llama_expert_tier_free() {
    std::lock_guard<std::mutex> lk(g_mtx);
    if (g_transfer_backend) {
        ggml_backend_free(g_transfer_backend);
        g_transfer_backend = nullptr;
    }
    g_table.clear();
    g_layers.clear();
    g_swap_queue.clear();
    g_has_pending_swaps.store(false, std::memory_order_relaxed);
    g_ctxs.clear();
    g_bufs.clear();
    g_fused_active = false;
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

static void copy_expert_tensor_slot(ggml_tensor * src, ggml_tensor * dst, int ex_src, int slot_dst) {
    const size_t slot_bytes = src->nb[2];
    const char * src_data = (const char *) ggml_get_data(src);

    if (src_data) {
        if (g_transfer_backend) {
            ggml_backend_tensor_set_async(g_transfer_backend, dst, src_data + (size_t) ex_src * slot_bytes,
                                          (size_t) slot_dst * slot_bytes, slot_bytes);
        } else {
            ggml_backend_tensor_set(dst, src_data + (size_t) ex_src * slot_bytes,
                                    (size_t) slot_dst * slot_bytes, slot_bytes);
        }
    } else {
        std::vector<uint8_t> tmp(slot_bytes);
        ggml_backend_tensor_get(src, tmp.data(), (size_t) ex_src * slot_bytes, slot_bytes);
        if (g_transfer_backend) {
            ggml_backend_tensor_set_async(g_transfer_backend, dst, tmp.data(),
                                          (size_t) slot_dst * slot_bytes, slot_bytes);
            ggml_backend_synchronize(g_transfer_backend);
        } else {
            ggml_backend_tensor_set(dst, tmp.data(), (size_t) slot_dst * slot_bytes, slot_bytes);
        }
    }
}

ggml_tensor * llama_expert_tier_build(ggml_context * ctx,
                                     ggml_tensor  * w,
                                     ggml_tensor  * cur,
                                     ggml_tensor  * ids,
                                     ggml_tensor  * w_s) {
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

bool llama_expert_tier_begin_fused(ggml_tensor * gate_w,
                                   ggml_tensor * up_w,
                                   ggml_tensor * down_w,
                                   ggml_tensor * ids) {
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

ggml_tensor * llama_expert_tier_end_fused(ggml_context * ctx,
                                         ggml_tensor  * gate_w,
                                         ggml_tensor  * up_w,
                                         ggml_tensor  * down_w,
                                         ggml_tensor  * x,
                                         ggml_tensor  * ids,
                                         ggml_tensor  * weights,
                                         int32_t        act) {
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

    return ggml_moe_cold(ctx, gate_w, up_w, down_w, x, ids, ent.cold_mask, ent.counts, weights, act,
                         ent.target_p_min, ent.target_p_max, ent.exp_scores);
}

bool llama_expert_tier_init(llama_model * model,
                            const std::vector<std::vector<int>> & layer_expert_order,
                            const std::vector<int> & layer_hot_s,
                            const float * layer_target_p_min,
                            const float * layer_target_p_max,
                            const std::vector<std::vector<float>> & layer_scores_norm) {
    if (!model || layer_hot_s.empty()) {
        return false;
    }

    llama_expert_tier_free();

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

    ggml_backend_buffer_type_t gpu_buft  = ggml_backend_dev_buffer_type(gpu_dev);
    ggml_backend_buffer_type_t cpu_buft  = ggml_backend_cpu_buffer_type();
    ggml_backend_buffer_type_t host_buft = ggml_backend_dev_host_buffer_type(gpu_dev);
    if (!host_buft) {
        host_buft = cpu_buft;
    }

    g_transfer_backend = ggml_backend_dev_init(gpu_dev, nullptr);

    int n_layers = (int) model->layers.size();
    int total_tiered_tensors = 0;
    bool early_exit_active = false;
    if (layer_target_p_min && layer_target_p_max) {
        for (int il = 0; il < n_layers; ++il) {
            if (layer_target_p_min[il] < 1.0f || layer_target_p_max[il] < 1.0f) {
                early_exit_active = true;
                break;
            }
        }
    }

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
        const int hot_s = (il < (int) layer_hot_s.size()) ? std::min(layer_hot_s[il], n_experts) : 0;
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
            /* .mem_size   = */ ggml_tensor_overhead() * 4,
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

        ggml_tensor * hot_lut    = ggml_new_tensor_2d(ctx_gpu.get(), GGML_TYPE_I32, 1, n_experts);
        ggml_tensor * cold_mask  = ggml_new_tensor_1d(ctx_cpu.get(), GGML_TYPE_I32, n_experts);
        ggml_tensor * counts     = ggml_new_tensor_1d(ctx_cpu.get(), GGML_TYPE_I32, n_experts + 1);
        ggml_tensor * exp_scores = ggml_new_tensor_1d(ctx_cpu.get(), GGML_TYPE_F32, n_experts);

        ggml_backend_buffer_t buf_gpu = ggml_backend_alloc_ctx_tensors_from_buft(ctx_gpu.get(), gpu_buft);
        if (!buf_gpu) {
            LLAMA_LOG_ERROR("%s: failed to allocate GPU buffer for layer %d (%d hot experts)\n",
                __func__, il, hot_s);
            return false;
        }
        ggml_backend_buffer_set_usage(buf_gpu, GGML_BACKEND_BUFFER_USAGE_WEIGHTS);
        ggml_backend_buffer_clear(buf_gpu, 0);

        ggml_backend_buffer_t buf_cpu = ggml_backend_alloc_ctx_tensors_from_buft(ctx_cpu.get(), host_buft);
        if (!buf_cpu) {
            LLAMA_LOG_ERROR("%s: failed to allocate CPU buffer for layer %d\n", __func__, il);
            return false;
        }
        ggml_backend_buffer_set_usage(buf_cpu, GGML_BACKEND_BUFFER_USAGE_WEIGHTS);
        ggml_backend_buffer_clear(buf_cpu, 0);

        // Copy top-S expert weights
        for (size_t i = 0; i < exps_tensors.size(); ++i) {
            for (int p = 0; p < hot_s; ++p) {
                copy_expert_tensor_slot(exps_tensors[i], dst_hots[i], rank[p], p);
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

        std::vector<float> norm_init(n_experts, 0.5f);
        if (il < (int) layer_scores_norm.size() && (int) layer_scores_norm[il].size() == n_experts) {
            norm_init = layer_scores_norm[il];
        }
        ggml_backend_tensor_set(exp_scores, norm_init.data(), 0, n_experts * sizeof(float));

        const float l_target_p_min = layer_target_p_min ? layer_target_p_min[il] : 1.0f;
        const float l_target_p_max = layer_target_p_max ? layer_target_p_max[il] : 1.0f;

        {
            std::lock_guard<std::mutex> lk(g_mtx);
            for (size_t i = 0; i < exps_tensors.size(); ++i) {
                tier_entry ent;
                ent.dst_hot      = dst_hots[i];
                ent.hot_lut      = hot_lut;
                ent.cold_mask    = cold_mask;
                ent.counts       = counts;
                ent.exp_scores   = exp_scores;
                ent.target_p_min = l_target_p_min;
                ent.target_p_max = l_target_p_max;
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
            lt.exp_scores = exp_scores;
            lt.target_p_min = l_target_p_min;
            lt.target_p_max = l_target_p_max;
            lt.slot_to_expert.resize(hot_s);
            for (int p = 0; p < hot_s; ++p) {
                lt.slot_to_expert[p] = rank[p];
            }
            lt.expert_scores.assign(n_experts, 0.0f);
            lt.expert_scores_norm = norm_init;
            lt.expert_imatrix_norm = norm_init;
            lt.hot_lut_cpu = h_lut;
            lt.cold_mask_cpu = c_mask;
            g_layers.push_back(std::move(lt));
        }

        g_ctxs.push_back(std::move(ctx_gpu));
        g_ctxs.push_back(std::move(ctx_cpu));
        g_bufs.push_back(ggml_backend_buffer_ptr(buf_gpu));
        g_bufs.push_back(ggml_backend_buffer_ptr(buf_cpu));
    }

    if (early_exit_active) {
        LLAMA_LOG_INFO("%s: initialized expert tier (%d tensors offloaded, granular early exit active)\n",
            __func__, total_tiered_tensors);
    } else {
        LLAMA_LOG_INFO("%s: initialized expert tier (%d tensors offloaded, early exit disabled: 100%% precision)\n",
            __func__, total_tiered_tensors);
    }

    if (g_transfer_backend) {
        ggml_backend_synchronize(g_transfer_backend);
    }

    return total_tiered_tensors > 0;
}

static bool execute_single_swap_internal(const candidate_swap & cs) {
    if (cs.layer_idx < 0 || cs.layer_idx >= (int) g_layers.size()) {
        return false;
    }
    auto & lt = g_layers[cs.layer_idx];
    const int e_out = cs.e_out;
    const int e_in  = cs.e_in;
    const int p     = cs.slot_p;

    // Validate that slot_p still holds e_out and e_in is still cold
    if (p < 0 || p >= lt.hot_s || lt.slot_to_expert[p] != e_out || lt.cold_mask_cpu[e_in] != 1) {
        return false;
    }

    for (size_t i = 0; i < lt.src_tensors.size(); ++i) {
        copy_expert_tensor_slot(lt.src_tensors[i], lt.dst_hots[i], e_in, p);
    }
    if (g_transfer_backend) {
        ggml_backend_synchronize(g_transfer_backend);
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

    LLAMA_LOG_INFO("%s: L%d swapped expert %d (score %.1f) -> slot %d (evicted %d, score %.1f, gain: +%.1f)\n",
                   __func__, lt.il, e_in, cs.cold_score, p, e_out, cs.hot_score, cs.gain);
    return true;
}

int32_t llama_expert_tier_drain_queue(int max_swaps) {
    if (!g_has_pending_swaps.load(std::memory_order_relaxed)) {
        return 0;
    }

    std::lock_guard<std::mutex> lk(g_mtx);
    if (g_swap_queue.empty()) {
        g_has_pending_swaps.store(false, std::memory_order_relaxed);
        return 0;
    }

    int executed = 0;
    const bool drain_all = (max_swaps <= 0);
    while (!g_swap_queue.empty() && (drain_all || executed < max_swaps)) {
        candidate_swap cs = g_swap_queue.front();
        g_swap_queue.pop_front();
        if (execute_single_swap_internal(cs)) {
            executed++;
        }
    }
    if (executed > 0 && g_transfer_backend) {
        ggml_backend_synchronize(g_transfer_backend);
    }
    if (g_swap_queue.empty()) {
        g_has_pending_swaps.store(false, std::memory_order_relaxed);
    }
    return executed;
}

size_t llama_expert_tier_queue_size() {
    std::lock_guard<std::mutex> lk(g_mtx);
    return g_swap_queue.size();
}

int32_t llama_expert_tier_update(float swap_frac, float attenuation, float imatrix_weight) {
    if (swap_frac <= 0.0f) {
        return 0;
    }

    std::lock_guard<std::mutex> lk(g_mtx);
    if (g_layers.empty()) {
        return 0;
    }

    int total_vram_experts = 0;
    for (const auto & lt : g_layers) {
        total_vram_experts += lt.hot_s;
    }
    if (total_vram_experts <= 0) {
        return 0;
    }

    const int global_max_swaps = std::max(1, (int) std::round(swap_frac * (float) total_vram_experts));

    int layers_active = 0;
    attenuation = std::max(0.0f, std::min(1.0f, attenuation));
    imatrix_weight = std::max(0.0f, std::min(1.0f, imatrix_weight));
    const float decay = 1.0f - attenuation;
    const float margin = 0.05f;
    const float min_diff = 1.0f;

    // Step 1: Update EMA scores from access counts for each layer
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
            lt.expert_scores[e] = lt.expert_scores[e] * decay + (float) cnt[e] * attenuation;
        }
    }

    if (layers_active == 0) {
        return 0;
    }

    // Update normalized global scores if dynamic token scaling is active
    bool has_dynamic_p = false;
    for (const auto & lt : g_layers) {
        if (lt.target_p_max > lt.target_p_min) {
            has_dynamic_p = true;
            break;
        }
    }
    if (has_dynamic_p) {
        float global_min = 1e30f;
        float global_max = -1e30f;
        for (const auto & lt : g_layers) {
            for (float s : lt.expert_scores) {
                if (s < global_min) global_min = s;
                if (s > global_max) global_max = s;
            }
        }
        const float diff = global_max - global_min;
        for (auto & lt : g_layers) {
            if (!lt.exp_scores) continue;
            for (int e = 0; e < lt.n_experts; ++e) {
                lt.expert_scores_norm[e] = diff > 1e-6f ? (lt.expert_scores[e] - global_min) / diff : 0.5f;
            }
            ggml_backend_tensor_set(lt.exp_scores, lt.expert_scores_norm.data(), 0, lt.n_experts * sizeof(float));
        }
    }

    // Step 2: Form candidate swaps across ALL layers as a whole
    std::vector<candidate_swap> all_candidates;

    for (size_t l_idx = 0; l_idx < g_layers.size(); ++l_idx) {
        auto & lt = g_layers[l_idx];
        if (!lt.counts || lt.hot_s <= 0 || lt.hot_s >= lt.n_experts) {
            continue;
        }

        // scale normalized imatrix score [0, 1] to match average EMA count magnitude (~1-5)
        constexpr float IMATRIX_SCORE_SCALE = 5.0f;

        auto get_expert_retention_score = [&](int ex) -> float {
            float s = lt.expert_scores[ex];
            if (imatrix_weight > 0.0f && ex < (int) lt.expert_imatrix_norm.size()) {
                const float s_norm = lt.expert_imatrix_norm[ex];
                s = (1.0f - imatrix_weight) * s + imatrix_weight * (s_norm * IMATRIX_SCORE_SCALE);
            }
            return s;
        };

        // Sort hot slots by current retention score ascending
        struct hot_slot_info {
            int p;
            int ex;
            float score;
        };
        std::vector<hot_slot_info> hot_slots;
        hot_slots.reserve(lt.hot_s);
        for (int p = 0; p < lt.hot_s; ++p) {
            const int ex = lt.slot_to_expert[p];
            hot_slots.push_back({ p, ex, get_expert_retention_score(ex) });
        }
        std::sort(hot_slots.begin(), hot_slots.end(), [](const hot_slot_info & a, const hot_slot_info & b) {
            return a.score < b.score;
        });

        // Collect and sort cold experts by current retention score descending
        struct cold_exp_info {
            int ex;
            float score;
        };
        std::vector<cold_exp_info> cold_exps;
        for (int ex = 0; ex < lt.n_experts; ++ex) {
            if (lt.cold_mask_cpu[ex] == 1) {
                cold_exps.push_back({ ex, get_expert_retention_score(ex) });
            }
        }
        std::sort(cold_exps.begin(), cold_exps.end(), [](const cold_exp_info & a, const cold_exp_info & b) {
            return a.score > b.score;
        });

        // Match cold experts to hot slots
        const int max_pairs = std::min((int) hot_slots.size(), (int) cold_exps.size());
        for (int k = 0; k < max_pairs; ++k) {
            const float cold_score = cold_exps[k].score;
            const float hot_score  = hot_slots[k].score;
            const float thresh     = hot_score * (1.0f + margin) + min_diff;

            if (cold_score > thresh) {
                all_candidates.push_back({
                    (int) l_idx,
                    hot_slots[k].p,
                    cold_exps[k].ex,
                    hot_slots[k].ex,
                    cold_score,
                    hot_score,
                    cold_score - hot_score
                });
            } else {
                break;
            }
        }
    }

    if (all_candidates.empty()) {
        g_swap_queue.clear();
        g_has_pending_swaps.store(false, std::memory_order_relaxed);
        return 0;
    }

    // Step 3: Sort all candidate swaps globally by gain descending
    std::stable_sort(all_candidates.begin(), all_candidates.end(), [](const candidate_swap & a, const candidate_swap & b) {
        return a.gain > b.gain;
    });

    // Step 4: Populate async swap queue (up to global_max_swaps)
    g_swap_queue.clear();
    int count_queued = 0;
    for (const auto & cs : all_candidates) {
        if (count_queued >= global_max_swaps) {
            break;
        }
        g_swap_queue.push_back(cs);
        count_queued++;
    }
    g_has_pending_swaps.store(!g_swap_queue.empty(), std::memory_order_release);

    // Step 5: Immediately execute the first swap from queue
    int executed = 0;
    if (!g_swap_queue.empty()) {
        candidate_swap first_swap = g_swap_queue.front();
        g_swap_queue.pop_front();
        if (execute_single_swap_internal(first_swap)) {
            executed++;
        }
        if (g_swap_queue.empty()) {
            g_has_pending_swaps.store(false, std::memory_order_relaxed);
        }
    }

    LLAMA_LOG_INFO("%s: global cycle: active_layers=%d/%zu, candidates=%zu, queued=%d, executed=%d (remaining: %zu)\n",
                   __func__, layers_active, g_layers.size(), all_candidates.size(), count_queued, executed, g_swap_queue.size());

    return executed;
}

bool llama_model_init_expert_tier(
        struct llama_model * model,
        const int32_t      * expert_order,
        size_t               n_expert_order,
        const int32_t      * layer_hot_s_arr,
        const float        * layer_target_p_min,
        const float        * layer_target_p_max,
        const float        * layer_scores_norm) {
    std::vector<std::vector<int>> order;
    std::vector<int> layer_hot_s;
    std::vector<std::vector<float>> scores_norm;
    if (model) {
        int n_layers = (int) model->layers.size();
        if (expert_order && n_expert_order > 0 && n_layers > 0) {
            int n_exp_per_layer = (int) (n_expert_order / n_layers);
            order.resize(n_layers);
            for (int il = 0; il < n_layers; ++il) {
                order[il].assign(expert_order + il * n_exp_per_layer,
                                 expert_order + (il + 1) * n_exp_per_layer);
            }
        }
        if (layer_hot_s_arr && n_layers > 0) {
            layer_hot_s.assign(layer_hot_s_arr, layer_hot_s_arr + n_layers);
        }
        if (layer_scores_norm && n_layers > 0 && expert_order && n_expert_order > 0) {
            int n_exp_per_layer = (int) (n_expert_order / n_layers);
            scores_norm.resize(n_layers);
            for (int il = 0; il < n_layers; ++il) {
                scores_norm[il].assign(layer_scores_norm + il * n_exp_per_layer,
                                       layer_scores_norm + (il + 1) * n_exp_per_layer);
            }
        }
    }
    return llama_expert_tier_init(model, order, layer_hot_s,
        layer_target_p_min, layer_target_p_max,
        scores_norm);
}

void llama_model_free_expert_tier(void) {
    llama_expert_tier_free();
}

int32_t llama_model_expert_tier_update(struct llama_model * model, float swap_frac, float attenuation, float imatrix_weight) {
    (void) model;
    return llama_expert_tier_update(swap_frac, attenuation, imatrix_weight);
}

int32_t llama_model_expert_tier_drain_queue(struct llama_model * model, int max_swaps) {
    (void) model;
    return llama_expert_tier_drain_queue(max_swaps);
}

size_t llama_model_expert_tier_queue_size(struct llama_model * model) {
    (void) model;
    return llama_expert_tier_queue_size();
}

size_t llama_model_layer_expert_bytes(const struct llama_model * model, int32_t il) {
    if (!model || il < 0 || il >= (int32_t) model->layers.size()) {
        return 0;
    }
    const auto & layer = model->layers[il];
    size_t exp_bytes = 0;
    auto add_exp_tensor = [&](const ggml_tensor * t) {
        if (t && t->ne[2] > 0) {
            exp_bytes += ggml_nbytes(t) / (size_t) t->ne[2];
        }
    };
    add_exp_tensor(layer.ffn_gate_exps);
    add_exp_tensor(layer.ffn_up_exps);
    add_exp_tensor(layer.ffn_down_exps);
    add_exp_tensor(layer.ffn_gate_up_exps);
    return exp_bytes;
}
