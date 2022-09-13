#if defined(RVV)
#include <riscv_vector.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "arm_nn_types.h"
#include "test_data.h"

q31_t base_nn_requantize(const q31_t val, const q31_t multiplier, const q31_t shift)
{
    const int64_t total_shift = 31 - shift;
    const int64_t new_val = val * (int64_t)multiplier;

    int32_t result = new_val >> (total_shift - 1);
    result = (result + 1) >> 1;

    return result;
}

int base_nn_vec_mat_mult_t_s8(const q7_t *lhs,
                                const q7_t *rhs,
                                const q31_t *bias,
                                q7_t *dst,
                                const int32_t lhs_offset,
                                const int32_t rhs_offset,
                                const int32_t dst_offset,
                                const int32_t dst_multiplier,
                                const int32_t dst_shift,
                                const int32_t rhs_cols, //filter_dims->n
                                const int32_t rhs_rows, //output_dims->c
                                const int32_t activation_min,
                                const int32_t activation_max,
                                const int32_t address_offset)
{
    const int32_t row_loop_cnt = rhs_rows / 3;

    for (int i_row_loop_cnt = 0; i_row_loop_cnt < row_loop_cnt; i_row_loop_cnt++)
    {
        const q7_t *lhs_ptr = lhs;
        const q7_t *rhs_ptr_0 = &rhs[0];
        const q7_t *rhs_ptr_1 = &rhs[rhs_cols];
        const q7_t *rhs_ptr_2 = &rhs[rhs_cols * 2];

        q31_t res00 = 0;
        q31_t res01 = 0;
        q31_t res02 = 0;
        if (bias)
        {
            res00 = *bias++;
            res01 = *bias++;
            res02 = *bias++;
        }
        for (int32_t rhs_cols_idx = 0; rhs_cols_idx < rhs_cols; ++rhs_cols_idx)
        {
            const q31_t rhs_value0 = (int8_t)*rhs_ptr_0;
            const q31_t rhs_value1 = (int8_t)*rhs_ptr_1;
            const q31_t rhs_value2 = (int8_t)*rhs_ptr_2;
            const q31_t lhs_value = (int8_t)*lhs_ptr + lhs_offset;

            res00 += lhs_value * rhs_value0;
            res01 += lhs_value * rhs_value1;
            res02 += lhs_value * rhs_value2;

            ++rhs_ptr_0;
            ++rhs_ptr_1;
            ++rhs_ptr_2;
            ++lhs_ptr;
        }
        // Quantize down
        res00 = base_nn_requantize(res00, dst_multiplier, dst_shift);
        res01 = base_nn_requantize(res01, dst_multiplier, dst_shift);
        res02 = base_nn_requantize(res02, dst_multiplier, dst_shift);

        // Add offset
        res00 += dst_offset;
        res01 += dst_offset;
        res02 += dst_offset;

        // Clamp the result
        res00 = MAX(res00, activation_min);
        res00 = MIN(res00, activation_max);
        res01 = MAX(res01, activation_min);
        res01 = MIN(res01, activation_max);
        res02 = MAX(res02, activation_min);
        res02 = MIN(res02, activation_max);

        *dst = (q7_t)res00;
        *(dst + address_offset) = (q7_t)res01;
        *(dst + 2 * address_offset) = (q7_t)res02;
        dst += 3 * address_offset;

        rhs += 3 * rhs_cols;

    }

    const int loop_cnt = rhs_rows % 3;

    for (int i_loop_cnt = 0; i_loop_cnt < loop_cnt; i_loop_cnt++)
    {
        const q7_t *lhs_ptr = &lhs[0];
        const q7_t *rhs_ptr = &rhs[0];

        q31_t res00 = 0;
        if (bias)
        {
            res00 = *bias++;
        }

        for (int32_t rhs_cols_idx = 0; rhs_cols_idx < rhs_cols; ++rhs_cols_idx)
        {
            q31_t rhs_value0 = (int8_t)rhs_ptr[0];
            q31_t lhs_value = (int8_t)lhs_ptr[0] + lhs_offset;

            res00 += lhs_value * rhs_value0;

            ++rhs_ptr;
            ++lhs_ptr;
        }

        // Quantize down
        res00 = base_nn_requantize(res00, dst_multiplier, dst_shift);

        // Add offset
        res00 += dst_offset;

        // Clamp the result
        res00 = MAX(res00, activation_min);
        res00 = MIN(res00, activation_max);

        *dst = (int8_t)res00;
        dst += address_offset;
        rhs += rhs_cols;
    }
}

#if defined(RVV)
void rvv_requantize(int32_t *src, int32_t multiplier, int32_t shift, int channel_size)
{
    vint32m4_t _val, _mulh, _res;
    while (channel_size > 0) {
        int vl = vsetvl_e32m4(channel_size);
        _val = vle32_v_i32m4(src, vl);
        _mulh = vmulh_vx_i32m4(_val, multiplier, vl);
        _res;
        if (shift < 0) {
            _res = vssra_vx_i32m4(_mulh, -shift - 1, vl);
        } else {
            _res = vsll_vx_i32m4(_mulh, shift + 1, vl);
        }
        vse32_v_i32m4(src, _res, vl);
        src += vl;
        channel_size -= vl;
    }
}


// add output_zeropint
void rvv_saturated_int8(int32_t *src, int8_t *dst, int32_t out_zp, int size)
{
    while (size > 0) {
        int vl = vsetvl_e32m2(size);
        vint32m4_t _tmp = vle32_v_i32m4(src, vl);
        _tmp = vadd_vx_i32m4(_tmp, out_zp, vl);

        vint16m2_t _tmp1 = vnclip_wx_i16m2(_tmp, 0, vl);
        vint8m1_t _tmp2 = vnclip_wx_i8m1(_tmp1, 0, vl);

        vse8_v_i8m1(dst, _tmp2, vl);
        src += vl;
        dst += vl;
        size -= vl;
    }
}

void rvv_fully_connected_s8_internel(const int8_t *input, const int32_t input_offset,
                                     int32_t *output, const int32_t output_offset,
                                     int8_t *weight, const int32_t *bias,
                                     int32_t rhs_cols, int32_t rhs_rows)
{
    int32_t vl;
    vint32m4_t acc, mul;
    vint8m1_t weight_vec;
    vint16m2_t double_weight_vec;

    // z(output) = W(weight) * a(input) + b(bias)
    while (rhs_rows > 0) {
        vl = vsetvl_e8m1(rhs_rows);
        acc = vle32_v_i32m4(bias, vl);

        for (int i = 0; i < rhs_cols; ++i) {
            weight_vec = vle8_v_i8m1(weight, vl);
            double_weight_vec = vsext_vf2_i16m2(weight_vec, vl);
            mul = vwmul_vx_i32m4(double_weight_vec, (input[i] + input_offset), vl);
            acc = vadd_vv_i32m4(acc, mul, vl);

            vse32_v_i32m4(output, acc, vl);
            weight += vl;
        }
        acc = vadd_vx_i32m4(acc, output_offset, vl);
        vse32_v_i32m4(output, acc, vl);

        bias += vl;
        output += vl;
        rhs_rows -= vl;
    }
}
#endif
int rvv_fully_connected_s8(const cmsis_nn_context *ctx,
                        const cmsis_nn_fc_params *fc_params,
                        const cmsis_nn_per_tensor_quant_params *quant_params,
                        const cmsis_nn_dims *input_dims,
                        const q7_t *input,
                        const cmsis_nn_dims *filter_dims,
                        const q7_t *kernel,
                        const cmsis_nn_dims *bias_dims,
                        const int32_t *bias,
                        const cmsis_nn_dims *output_dims,
                        q7_t *output)
{
    (void)bias_dims;
    (void)ctx;
    (void)fc_params->filter_offset;

    int32_t batch_cnt = input_dims->n;
#if defined(RVV)
    int32_t *tmp = (int32_t *)malloc(output_dims->c * sizeof(int32_t));
    memset(tmp, 0x0, output_dims->c * sizeof(int32_t));
#endif
    while (batch_cnt)
    {
#if defined(RVV)
        rvv_fully_connected_s8_internel(
            input, fc_params->input_offset, tmp, fc_params->output_offset, (int8_t *)kernel, bias, filter_dims->n, output_dims->c
            );

        rvv_requantize(tmp, quant_params->multiplier, quant_params->shift,
                       output_dims->c);

        rvv_saturated_int8(tmp, output, fc_params->output_offset, output_dims->c);
#else
        base_nn_vec_mat_mult_t_s8(input,
                                 kernel,
                                 bias,
                                 output,
                                 fc_params->input_offset,
                                 0,
                                 fc_params->output_offset,
                                 quant_params->multiplier,
                                 quant_params->shift,
                                 filter_dims->n, /* col_dim or accum_depth */
                                 output_dims->c, /* row_dim or output_depth */
                                 fc_params->activation.min,
                                 fc_params->activation.max,
                                 1L);
#endif
        input += filter_dims->n;
        output += output_dims->c;
        batch_cnt--;
    }
    return 0;
}

int main(void)
{
    q7_t output[FULLY_CONNECTED_NULL_BIAS_0_DST_SIZE] = {0};
    cmsis_nn_context ctx;
    cmsis_nn_fc_params fc_params;
    cmsis_nn_per_tensor_quant_params quant_params;
    cmsis_nn_dims input_dims;
    cmsis_nn_dims filter_dims;
    cmsis_nn_dims bias_dims;
    cmsis_nn_dims output_dims;
    const q31_t *bias_data = fully_connected_null_bias_0_biases;
    const q7_t *kernel_data = fully_connected_null_bias_0_weights_transpose;
    const q7_t *input_data = fully_connected_null_bias_0_input;
    const q7_t *output_ref = fully_connected_null_bias_0_output_ref;
    const int32_t output_ref_size = FULLY_CONNECTED_NULL_BIAS_0_DST_SIZE;
    input_dims.n = FULLY_CONNECTED_NULL_BIAS_0_INPUT_BATCHES;
    input_dims.w = FULLY_CONNECTED_NULL_BIAS_0_INPUT_W;
    input_dims.h = FULLY_CONNECTED_NULL_BIAS_0_INPUT_H;
    input_dims.c = FULLY_CONNECTED_NULL_BIAS_0_IN_CH;
    filter_dims.n = FULLY_CONNECTED_NULL_BIAS_0_ACCUMULATION_DEPTH;
    filter_dims.c = FULLY_CONNECTED_NULL_BIAS_0_OUT_CH;
    output_dims.n = FULLY_CONNECTED_NULL_BIAS_0_INPUT_BATCHES;
    output_dims.c = FULLY_CONNECTED_NULL_BIAS_0_OUT_CH;
    fc_params.input_offset = FULLY_CONNECTED_NULL_BIAS_0_INPUT_OFFSET;
    fc_params.filter_offset = 0;
    fc_params.output_offset = FULLY_CONNECTED_NULL_BIAS_0_OUTPUT_OFFSET;
    fc_params.activation.min = FULLY_CONNECTED_NULL_BIAS_0_OUT_ACTIVATION_MIN;
    fc_params.activation.max = FULLY_CONNECTED_NULL_BIAS_0_OUT_ACTIVATION_MAX;
    quant_params.multiplier = FULLY_CONNECTED_NULL_BIAS_0_OUTPUT_MULTIPLIER;
    quant_params.shift = FULLY_CONNECTED_NULL_BIAS_0_OUTPUT_SHIFT;

    int32_t buf_size = 0;
    ctx.buf = malloc(buf_size);
    ctx.size = buf_size;
    rvv_fully_connected_s8(&ctx,
                            &fc_params,
                            &quant_params,
                            &input_dims,
                            input_data,
                            &filter_dims,
                            kernel_data,
                            &bias_dims,
                            bias_data,
                            &output_dims,
                            output);

    if (ctx.buf)
    {
        memset(ctx.buf, 0, buf_size);
        free(ctx.buf);
    }
}