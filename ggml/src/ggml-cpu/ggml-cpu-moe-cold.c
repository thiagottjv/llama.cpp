#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include "ggml.h"
#include "ggml-impl.h"
#include "ggml-cpu-impl.h"
#include "ggml-cpu.h"
#include "ops.h"
#include "ggml-cpu-moe-cold.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <malloc.h>
#elif !defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__OpenBSD__)
#include <alloca.h>
#endif

#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
    #define NOMINMAX
#endif
#include <windows.h>
#endif

#if defined(_MSC_VER) && !defined(__clang__)

typedef volatile LONG atomic_int;

typedef enum {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
} memory_order;

static LONG atomic_fetch_add_explicit(atomic_int * ptr, LONG inc, memory_order mo) {
    GGML_UNUSED(mo);
    return InterlockedExchangeAdd(ptr, inc);
}

#else
#include <stdatomic.h>
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#define PREFETCH(p) ((void) 0)
#else
#define PREFETCH(p) __builtin_prefetch(p, 0, 3)
#endif

struct cold_slot_info {
    int   id;
    float weight;
};

// compute active cold slot mask for token t using target cumulative probability mass
static uint64_t moe_cold_active_slot_mask(
        const struct ggml_tensor * ids,
        const int32_t * cold_mask,
        const struct ggml_tensor * weights,
        const struct ggml_tensor * scores,
        int64_t t,
        int n_ids,
        int n_as,
        float target_p_min,
        float target_p_max) {
    float gpu_mass = 0.0f;
    int n_cold = 0;
    struct cold_slot_info cold_slots[64];

    const int max_ids = n_ids > 0 ? (n_ids < 64 ? n_ids : 64) : 1;

    float weighted_score_sum = 0.0f;
    float total_w = 0.0f;
    const float * exp_scores = scores ? (const float *) scores->data : NULL;

    for (int id = 0; id < max_ids; id++) {
        const int32_t e = *(const int32_t *) ((const char *) ids->data + t*ids->nb[1] + id*ids->nb[0]);
        if (e < 0 || e >= n_as) {
            continue;
        }
        float w = 1.0f / (float) max_ids;
        if (weights) {
            w = *(const float *) ((const char *) weights->data + t*weights->nb[2] + id*weights->nb[1]);
        }
        if (exp_scores) {
            weighted_score_sum += w * exp_scores[e];
            total_w += w;
        }
        if (cold_mask[e] == 0) {
            gpu_mass += w;
        } else {
            cold_slots[n_cold].id = id;
            cold_slots[n_cold].weight = w;
            n_cold++;
        }
    }

    if (n_cold == 0) {
        return 0;
    }

    // Dynamic early exit interpolation based on global expert scores (fixed when min == max)
    float effective_target_p = target_p_max;
    if (target_p_max > target_p_min && exp_scores && total_w > 0.0f) {
        float avg_score = weighted_score_sum / total_w;
        if (avg_score < 0.0f) avg_score = 0.0f;
        if (avg_score > 1.0f) avg_score = 1.0f;
        effective_target_p = target_p_max - avg_score * (target_p_max - target_p_min);
    } else {
        effective_target_p = target_p_min;
    }

    // if effective_target_p is <= 0.0f or gpu mass already reaches effective_target_p, CPU computes zero experts
    if (effective_target_p <= 0.0f || gpu_mass >= effective_target_p) {
        return 0;
    }

    // if effective_target_p >= 1.0f, compute all cold experts
    if (effective_target_p >= 1.0f) {
        uint64_t mask = 0;
        for (int i = 0; i < n_cold; i++) {
            mask |= (1ULL << cold_slots[i].id);
        }
        return mask;
    }

    // sort cold slots by weight descending
    for (int i = 0; i < n_cold - 1; i++) {
        int best = i;
        for (int j = i + 1; j < n_cold; j++) {
            if (cold_slots[j].weight > cold_slots[best].weight) {
                best = j;
            }
        }
        if (best != i) {
            struct cold_slot_info tmp = cold_slots[i];
            cold_slots[i] = cold_slots[best];
            cold_slots[best] = tmp;
        }
    }

    // select top cold experts until cumulative mass (gpu + cpu) reaches effective_target_p
    uint64_t mask = 0;
    float curr_mass = gpu_mass;
    for (int i = 0; i < n_cold; i++) {
        mask |= (1ULL << cold_slots[i].id);
        curr_mass += cold_slots[i].weight;
        if (curr_mass >= effective_target_p) {
            break;
        }
    }
    return mask;
}

// fused cold-expert MoE: computes down(act(gate(x)) * up(x)) only for slots
// whose expert is cold (cold_mask[e] == 1); hot slots are zeroed.
// src = {gate, up, down, x, ids, cold_mask}; op param 0 = act (0 silu, 1 gelu)
void ggml_compute_forward_moe_cold(
        const struct ggml_compute_params * params,
              struct ggml_tensor * dst) {

    const struct ggml_tensor * w_gate = dst->src[0];
    const struct ggml_tensor * w_up   = dst->src[1];
    const struct ggml_tensor * w_down = dst->src[2];
    const struct ggml_tensor * x      = dst->src[3];
    const struct ggml_tensor * ids    = dst->src[4];
    const struct ggml_tensor * mask   = dst->src[5];
    int32_t * counts = dst->src[6] ? (int32_t *) dst->src[6]->data : NULL;
    const struct ggml_tensor * weights = dst->src[7];
    const struct ggml_tensor * scores  = dst->src[8];
    const int32_t act          = ggml_get_op_params_i32(dst, 0);
    const float   target_p_min = ggml_get_op_params_f32(dst, 1);
    const float   target_p_max = ggml_get_op_params_f32(dst, 2);

    const int32_t * cold_mask = (const int32_t *) mask->data;

    const int ith = params->ith;
    const int nth = params->nth;

    const enum ggml_type type_g = w_gate->type;
    const enum ggml_type type_u = w_up->type;
    const enum ggml_type type_d = w_down->type;
    GGML_ASSERT(x->type == GGML_TYPE_F32);
    GGML_ASSERT(dst->type == GGML_TYPE_F32);
    GGML_ASSERT(x->ne[1] == 1 && x->nb[0] == sizeof(float));

    const int64_t ne_embd  = x->ne[0];
    const int64_t n_ff     = (w_gate == w_up) ? (w_gate->ne[1] / 2) : w_gate->ne[1];
    const int64_t n_tokens = x->ne[2];
    const int64_t n_out    = w_down->ne[1];
    const int n_ids = ids->ne[0];
    const int n_as  = w_gate->ne[2];

    // early check: skip CPU execution if no cold experts are selected
    bool has_cold = false;
    for (int64_t t = 0; t < n_tokens; t++) {
        if (moe_cold_active_slot_mask(ids, cold_mask, weights, scores, t, n_ids, n_as, target_p_min, target_p_max) != 0) {
            has_cold = true;
            break;
        }
    }

    if (!has_cold) {
        if (ith == 0) {
            memset(dst->data, 0, ggml_nbytes(dst));
            if (counts) {
                for (int64_t t = 0; t < n_tokens; t++) {
                    for (int id = 0; id < n_ids; id++) {
                        const int32_t e = *(const int32_t *) ((const char *) ids->data + t*ids->nb[1] + id*ids->nb[0]);
                        if (e >= 0 && e < n_as) {
                            counts[e]++;
                            counts[n_as]++;
                        }
                    }
                }
            }
        }
        return;
    }

    ggml_vec_dot_t    const vec_dot_g = ggml_get_type_traits_cpu(type_g)->vec_dot;
    enum ggml_type    const vdt_g     = ggml_get_type_traits_cpu(type_g)->vec_dot_type;
    ggml_from_float_t const from_fx_g = ggml_get_type_traits_cpu(vdt_g)->from_float;

    ggml_vec_dot_t    const vec_dot_u = ggml_get_type_traits_cpu(type_u)->vec_dot;
    enum ggml_type    const vdt_u     = ggml_get_type_traits_cpu(type_u)->vec_dot_type;
    ggml_from_float_t const from_fx_u = ggml_get_type_traits_cpu(vdt_u)->from_float;

    ggml_vec_dot_t    const vec_dot_d = ggml_get_type_traits_cpu(type_d)->vec_dot;
    enum ggml_type    const vdt_d     = ggml_get_type_traits_cpu(type_d)->vec_dot_type;
    ggml_from_float_t const from_fa   = ggml_get_type_traits_cpu(vdt_d)->from_float;

    const size_t q_embd_g = ggml_row_size(vdt_g, ne_embd);
    const size_t q_embd_u = (vdt_u == vdt_g) ? q_embd_g : ggml_row_size(vdt_u, ne_embd);
    const size_t q_ff     = ggml_row_size(vdt_d, n_ff);

    void * wdata_cur = params->wdata;

    char * xq_g = (char *) incr_ptr_aligned(&wdata_cur, n_tokens*q_embd_g, sizeof(int64_t));
    char * xq_u = (vdt_u == vdt_g) ? xq_g : (char *) incr_ptr_aligned(&wdata_cur, n_tokens*q_embd_u, sizeof(int64_t));

    int64_t * matrix_row_counts =
        (int64_t *) incr_ptr_aligned(&wdata_cur, n_as*sizeof(int64_t), sizeof(int64_t));

    struct mmid_row_mapping * matrix_rows =
        (struct mmid_row_mapping *) incr_ptr_aligned(&wdata_cur, n_as*(int64_t)n_ids*n_tokens*sizeof(struct mmid_row_mapping), sizeof(int64_t));

    int64_t * col0 =
        (int64_t *) incr_ptr_aligned(&wdata_cur, n_as*sizeof(int64_t), sizeof(int64_t));

    char (*atomic_current_chunk)[CACHE_LINE_SIZE] =
        (char (*)[CACHE_LINE_SIZE]) incr_ptr_aligned(&wdata_cur, CACHE_LINE_SIZE*n_as, CACHE_LINE_SIZE);

    const int64_t maxc = (int64_t) n_ids*n_tokens;
    float * gate_out = (float *) incr_ptr_aligned(&wdata_cur, 2*n_ff*maxc*sizeof(float), CACHE_LINE_SIZE);
    float * up_out   = gate_out + n_ff*maxc;
    char  * act_q    = (char *)  incr_ptr_aligned(&wdata_cur, q_ff*maxc, CACHE_LINE_SIZE);

    GGML_ASSERT(params->wsize >= (size_t)((char *) wdata_cur - (char *) params->wdata));

    // quantize x once, shared by all experts
    for (int64_t t = ith; t < n_tokens; t += nth) {
        const float * x_token = (const float *) ((const char *) x->data + t*x->nb[2]);
        from_fx_g(x_token, xq_g + t*q_embd_g, ne_embd);
        if (vdt_u != vdt_g) {
            from_fx_u(x_token, xq_u + t*q_embd_u, ne_embd);
        }
    }

    if (ith == 0) {
        memset(dst->data, 0, ggml_nbytes(dst));
        memset(matrix_row_counts, 0, n_as*sizeof(int64_t));

        for (int64_t t = 0; t < n_tokens; t++) {
            const uint64_t active_mask = moe_cold_active_slot_mask(ids, cold_mask, weights, scores, t, n_ids, n_as, target_p_min, target_p_max);

            for (int id = 0; id < n_ids; id++) {
                const int32_t e = *(const int32_t *) ((const char *) ids->data + t*ids->nb[1] + id*ids->nb[0]);
                GGML_ASSERT(e >= 0 && e < n_as);
                if (counts) {
                    counts[e]++;
                    counts[n_as]++;
                }
                if (cold_mask[e] == 0) {
                    continue;
                }
                if ((active_mask & (1ULL << id)) == 0) {
                    continue;
                }
                matrix_rows[e*(int64_t)n_ids*n_tokens + matrix_row_counts[e]] = (struct mmid_row_mapping) {id, (int32_t) t};
                matrix_row_counts[e]++;
            }
        }

        int64_t coff = 0;
        for (int e = 0; e < n_as; e++) {
            col0[e] = coff;
            coff += matrix_row_counts[e];
        }
    }

    // reset phase-A chunk counters
    for (int e = ith; e < n_as; e += nth) {
        atomic_int * ctr = (atomic_int *)(atomic_current_chunk + e);
        *ctr = nth;
    }

    ggml_barrier(params->threadpool);

    // phase A: gate/up dots for all cold slots into gate_out/up_out
    for (int cur_a = 0; cur_a < n_as; ++cur_a) {
        const int64_t cne1 = matrix_row_counts[cur_a];
        if (cne1 == 0) {
            continue;
        }
        const char * wg = (const char *) w_gate->data + cur_a*w_gate->nb[2];
        const char * wu = (w_gate == w_up) ? (wg + n_ff*w_gate->nb[1])
                        : ((const char *) w_up->data + cur_a*w_up->nb[2]);

        const int64_t nr0 = n_ff;
        const int64_t nr1 = cne1;

        int chunk_size = 16;
        if (nr1 == 1) {
            chunk_size = 64;
        }
        const bool disable_chunking = ggml_is_numa();
        int64_t nchunk0 = (nr0 + chunk_size - 1)/chunk_size;
        int64_t nchunk1 = (nr1 + chunk_size - 1)/chunk_size;
        if (nchunk0*nchunk1 < nth*4 || disable_chunking) {
            nchunk0 = nr0 > nr1 ? nth : 1;
            nchunk1 = nr0 > nr1 ? 1 : nth;
        }
        const int64_t dr0 = (nr0 + nchunk0 - 1)/nchunk0;
        const int64_t dr1 = (nr1 + nchunk1 - 1)/nchunk1;

        int current_chunk = ith;
        atomic_int * ctr = (atomic_int *)(atomic_current_chunk + cur_a);

        while (current_chunk < nchunk0*nchunk1) {
            const int64_t ith0 = current_chunk % nchunk0;
            const int64_t ith1 = current_chunk / nchunk0;
            const int64_t ir0_start = dr0*ith0, ir0_end = MIN(ir0_start + dr0, nr0);
            const int64_t ir1_start = dr1*ith1, ir1_end = MIN(ir1_start + dr1, nr1);

            for (int64_t c = ir1_start; c < ir1_end; c++) {
                const struct mmid_row_mapping rm = matrix_rows[cur_a*(int64_t)n_ids*n_tokens + c];
                const char * xcol_g = xq_g + (int64_t) rm.i2*q_embd_g;
                const char * xcol_u = xq_u + (int64_t) rm.i2*q_embd_u;
                float * gout = gate_out + (col0[cur_a] + c)*n_ff;
                float * uout = up_out   + (col0[cur_a] + c)*n_ff;
                for (int64_t i = ir0_start; i < ir0_end; i++) {
                    PREFETCH(wg + (i + 1)*w_gate->nb[1]);
                    PREFETCH(wu + (i + 1)*w_up->nb[1]);
                    vec_dot_g(ne_embd, &gout[i], 0, wg + i*w_gate->nb[1], 0, xcol_g, 0, 1);
                    vec_dot_u(ne_embd, &uout[i], 0, wu + i*w_up->nb[1], 0, xcol_u, 0, 1);
                }
            }

            if (nth >= nchunk0*nchunk1) {
                break;
            }
            current_chunk = atomic_fetch_add_explicit(ctr, 1, memory_order_relaxed);
        }
    }

    ggml_barrier(params->threadpool);

    // phase B: activation (SwiGLU/GELU) + quantize intermediate
    const int64_t total_cols = n_as > 0 ? (col0[n_as - 1] + matrix_row_counts[n_as - 1]) : 0;

    for (int64_t c = ith; c < total_cols; c += nth) {
        float * go = gate_out + c*n_ff;
        const float * uo = up_out + c*n_ff;
        if (act == 1) {
            for (int64_t i = 0; i < n_ff; i++) {
                const float g = go[i];
                const float gelu_g = 0.5f * g * (1.0f + tanhf(0.7978845608028654f * g * (1.0f + 0.044715f * g * g)));
                go[i] = gelu_g * uo[i];
            }
        } else {
            for (int64_t i = 0; i < n_ff; i++) {
                const float g = go[i];
                const float silu_g = g / (1.0f + expf(-g));
                go[i] = silu_g * uo[i];
            }
        }
        from_fa(go, act_q + c*q_ff, n_ff);
    }

    if (ith == 0) {
        for (int e = 0; e < n_as; e++) {
            atomic_int * ctr = (atomic_int *)(atomic_current_chunk + e);
            *ctr = nth;
        }
    }

    ggml_barrier(params->threadpool);

    // phase C: down dots for all cold slots, scattered into dst
    for (int cur_a = 0; cur_a < n_as; ++cur_a) {
        const int64_t cne1 = matrix_row_counts[cur_a];
        if (cne1 == 0) {
            continue;
        }
        const char * wd = (const char *) w_down->data + cur_a*w_down->nb[2];

        const int64_t nr0 = n_out;
        const int64_t nr1 = cne1;

        int chunk_size = 16;
        if (nr1 == 1) {
            chunk_size = 64;
        }
        const bool disable_chunking = ggml_is_numa();
        int64_t nchunk0 = (nr0 + chunk_size - 1)/chunk_size;
        int64_t nchunk1 = (nr1 + chunk_size - 1)/chunk_size;
        if (nchunk0*nchunk1 < nth*4 || disable_chunking) {
            nchunk0 = nr0 > nr1 ? nth : 1;
            nchunk1 = nr0 > nr1 ? 1 : nth;
        }
        const int64_t dr0 = (nr0 + nchunk0 - 1)/nchunk0;
        const int64_t dr1 = (nr1 + nchunk1 - 1)/nchunk1;

        int current_chunk = ith;
        atomic_int * ctr = (atomic_int *)(atomic_current_chunk + cur_a);

        while (current_chunk < nchunk0*nchunk1) {
            const int64_t ith0 = current_chunk % nchunk0;
            const int64_t ith1 = current_chunk / nchunk0;
            const int64_t ir0_start = dr0*ith0, ir0_end = MIN(ir0_start + dr0, nr0);
            const int64_t ir1_start = dr1*ith1, ir1_end = MIN(ir1_start + dr1, nr1);

            for (int64_t c = ir1_start; c < ir1_end; c++) {
                const struct mmid_row_mapping rm = matrix_rows[cur_a*(int64_t)n_ids*n_tokens + c];
                const char * acol = act_q + (col0[cur_a] + c)*q_ff;
                float * dst_col = (float *) ((char *) dst->data + rm.i1*dst->nb[1] + (int64_t) rm.i2*dst->nb[2]);
                for (int64_t j = ir0_start; j < ir0_end; j++) {
                    float res = 0.0f;
                    vec_dot_d(n_ff, &res, 0, wd + j*w_down->nb[1], 0, acol, 0, 1);
                    dst_col[j] += res;
                }
            }

            if (nth >= nchunk0*nchunk1) {
                break;
            }
            current_chunk = atomic_fetch_add_explicit(ctr, 1, memory_order_relaxed);
        }
    }
}
