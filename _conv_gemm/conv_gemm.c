#if defined(RVV)
#include <riscv_vector.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "arm_nn_types.h"
#include "basic/test_data.h"

q31_t nn_doubling_high_mult_no_sat(const q31_t m1, const q31_t m2)
{
    q31_t result = 0;
    union nn_long_long mult;

    // Rounding offset to add for a right shift of 31
    mult.word.low = 1 << 30;
    mult.word.high = 0;

    // Gets resolved as a SMLAL instruction
    mult.long_long = mult.long_long + (q63_t)m1 * m2;

    // Utilize all of the upper 32 bits. This is the doubling step
    // as well.
    result = (int32_t)(mult.long_long >> 31);

    return result;
}

q31_t nn_divide_by_power_of_two(const q31_t dividend, const q31_t exponent)
{
    q31_t result = 0;
    const q31_t remainder_mask = (1 << exponent) - 1;
    int32_t remainder = remainder_mask & dividend;

    // Basic division
    result = dividend >> exponent;

    // Adjust 'result' for rounding (mid point away from zero)
    q31_t threshold = remainder_mask >> 1;
    if (result < 0)
        threshold++;

    if (remainder > threshold)
        result++;

    return result;
}

void q7_to_q15_with_offset(const q7_t *src, q15_t *dst, uint32_t block_size, q15_t offset)
{
    int block_cnt;
    /* Loop over block_size number of values */
    block_cnt = block_size;
    while (block_cnt > 0)
    {
        *dst++ = (q15_t)*src++ + offset;

        /* Decrement the loop counter */
        block_cnt--;
    }
}
q31_t nn_requantize(const q31_t val, const q31_t multiplier, const q31_t shift)
{
    return nn_divide_by_power_of_two(nn_doubling_high_mult_no_sat(val * (1 << LEFT_SHIFT(shift)), multiplier),RIGHT_SHIFT(shift));
}

q7_t *nn_mat_mult_kernel_s8_s16(const q7_t *input_a,
                                    const q15_t *input_b,
                                    const uint16_t output_ch,
                                    const int32_t *out_shift,
                                    const int32_t *out_mult,
                                    const int32_t out_offset,
                                    const int16_t activation_min,
                                    const int16_t activation_max,
                                    const uint16_t num_col_a,
                                    const int32_t *const output_bias,
                                    q7_t *out_0)
{
    /* set up the second output pointers */
    q7_t *out_1 = out_0 + output_ch;
    const int32_t *bias = output_bias;

    uint16_t row_count = output_ch / 2;
    const q7_t *ip_a0 = input_a; // input_a => filter
    /* this loop over rows in A */
    while (row_count)
    {
        /* setup pointers for B */
        const q15_t *ip_b0 = input_b; // input_a => input_col_1
        const q15_t *ip_b1 = ip_b0 + num_col_a; // input_col_2

        /* align the second pointer for A */
        const q7_t *ip_a1 = ip_a0 + num_col_a;

        q31_t ch_0_out_0 = 0;
        q31_t ch_0_out_1 = 0;
        q31_t ch_1_out_0 = 0;
        q31_t ch_1_out_1 = 0;
        /* Init accumulator with bias for channel N and N + 1 */
        if (bias)
        {
            ch_0_out_0 = *bias;
            ch_0_out_1 = *bias++;
            ch_1_out_0 = *bias;
            ch_1_out_1 = *bias++;
        }
        uint16_t col_count = num_col_a;
        while (col_count)
        {
            q7_t a0 = *ip_a0++;
            q15_t b0 = *ip_b0++;
            q7_t a1 = *ip_a1++;
            q15_t b1 = *ip_b1++;

            ch_0_out_0 += a0 * b0;
            ch_0_out_1 += a0 * b1;
            ch_1_out_0 += a1 * b0;
            ch_1_out_1 += a1 * b1;
            col_count--;
        } /* while over col_count */
        ch_0_out_0 = nn_requantize(ch_0_out_0, *out_mult, *out_shift);
        ch_0_out_0 += out_offset;
        ch_0_out_0 = MAX(ch_0_out_0, activation_min);
        ch_0_out_0 = MIN(ch_0_out_0, activation_max);
        *out_0++ = (q7_t)ch_0_out_0;

        ch_0_out_1 = nn_requantize(ch_0_out_1, *out_mult, *out_shift);
        ch_0_out_1 += out_offset;
        ch_0_out_1 = MAX(ch_0_out_1, activation_min);
        ch_0_out_1 = MIN(ch_0_out_1, activation_max);
        *out_1++ = (q7_t)ch_0_out_1;
        out_mult++;
        out_shift++;

        ch_1_out_0 = nn_requantize(ch_1_out_0, *out_mult, *out_shift);
        ch_1_out_0 += out_offset;
        ch_1_out_0 = MAX(ch_1_out_0, activation_min);
        ch_1_out_0 = MIN(ch_1_out_0, activation_max);
        *out_0++ = (q7_t)ch_1_out_0;

        ch_1_out_1 = nn_requantize(ch_1_out_1, *out_mult, *out_shift);
        ch_1_out_1 += out_offset;
        ch_1_out_1 = MAX(ch_1_out_1, activation_min);
        ch_1_out_1 = MIN(ch_1_out_1, activation_max);
        *out_1++ = (q7_t)ch_1_out_1;
        out_mult++;
        out_shift++;

        /* skip row */
        ip_a0 += num_col_a;
        row_count--;
    }

    /* compute the last odd numbered row if any */
    if (output_ch & 0x1)
    {
        /* setup pointers for B */
        const q15_t *ip_b0 = input_b;
        const q15_t *ip_b1 = ip_b0 + num_col_a;

        q31_t ch_0_out_0 = 0;
        q31_t ch_0_out_1 = 0;

        /* load the bias */
        if (bias)
        {
            ch_0_out_0 = *bias;
            ch_0_out_1 = *bias++;
        }
        uint16_t col_count = num_col_a;
        while (col_count)
        {
            q7_t a0 = *ip_a0++;
            q15_t b0 = *ip_b0++;
            q15_t b1 = *ip_b1++;

            ch_0_out_0 += a0 * b0;
            ch_0_out_1 += a0 * b1;
            col_count--;
        }
        ch_0_out_0 = nn_requantize(ch_0_out_0, *out_mult, *out_shift);
        ch_0_out_0 += out_offset;
        ch_0_out_0 = MAX(ch_0_out_0, activation_min);
        ch_0_out_0 = MIN(ch_0_out_0, activation_max);
        *out_0++ = (q7_t)ch_0_out_0;

        ch_0_out_1 = nn_requantize(ch_0_out_1, *out_mult, *out_shift);
        ch_0_out_1 += out_offset;
        ch_0_out_1 = MAX(ch_0_out_1, activation_min);
        ch_0_out_1 = MIN(ch_0_out_1, activation_max);
        *out_1++ = (q7_t)ch_0_out_1;
        out_mult++;
        out_shift++;
    }
    out_0 += output_ch;
    return out_0;
}

static void copy_q7(q7_t *target, const q7_t *base, int32_t length)
{
#ifdef RVV
    int32_t vl = 0;
    vint8m1_t op_1;
    while(length > 0)
    {
        vl = vsetvl_e8m1(length);
        op_1 = vle8_v_i8m1(base, vl);
        vse8_v_i8m1(target, op_1, vl);
        base += vl;
        target += vl;
        length -= vl;
    }
#else
    memcpy(target, base, length);
#endif
}

#ifdef RVV
vint32m1_t rvv_requantize(vint32m1_t src, int32_t vl, int32_t multiplier, int32_t shift)
{
    vint32m1_t mul, res;
    mul = vmulh_vx_i32m1(src, multiplier, vl);
    if (shift < 0) {
        res = vssra_vx_i32m1(mul, -shift - 1, vl);
    } else {
        res = vsll_vx_i32m1(mul, shift + 1, vl);
    }
    return res;
}
#endif

#ifdef RVV
q7_t *rvv_nn_mat_mult_s8(const q7_t *input_row, // filter
                         const q7_t *input_col, // input data
                         const uint16_t output_ch,
                         const uint16_t col_batches,
                         const int32_t *output_shift,
                         const int32_t *output_mult,
                         const int32_t out_offset,
                         const int32_t col_offset,
                         const int32_t row_offset,
                         const int16_t activation_min,
                         const int16_t activation_max,
                         const uint16_t row_len,
                         const int32_t *const bias,
                         q7_t *out)
{
    (void)row_offset;
    int32_t vl = 0;
    if (col_batches == 4)
    {
        for (int i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
        {
            int32_t row_len_tmp = row_len;
            const int8_t *ip_r0 = input_row + (i_out_ch * row_len);
            const int8_t *ip_c0 = input_col;
            const int8_t *ip_c1 = input_col + row_len;
            const int8_t *ip_c2 = input_col + (2 * row_len);
            const int8_t *ip_c3 = input_col + (3 * row_len);

            int32_t acc_0 = 0;
            int32_t acc_1 = 0;
            int32_t acc_2 = 0;
            int32_t acc_3 = 0;

            vint32m1_t vm_temp_0, acc_0_temp, acc_1_temp, acc_2_temp, acc_3_temp;
            int32_t test[100];
            while (row_len_tmp > 0)
            {
                vl = vsetvl_e8m1(row_len_tmp);
                vm_temp_0 = vmv_v_x_i32m1(0, vl);

                vint32m4_t offset = vmv_v_x_i32m4(col_offset, vl);
                row_len_tmp -= vl;

                vint32m4_t c0 = vsext_vf4(vle8_v_i8m1(ip_c0, vl), vl);
                ip_c0 += vl;

                c0 = vadd_vv_i32m4(c0, offset, vl);

                vint32m4_t c1 = vsext_vf4(vle8_v_i8m1(ip_c1, vl), vl);
                ip_c1 += vl;
                c1 = vadd_vv_i32m4(c1, offset, vl);

                vint32m4_t c2 = vsext_vf4(vle8_v_i8m1(ip_c2, vl), vl);
                ip_c2 += vl;
                c2 = vadd_vv_i32m4(c2, offset, vl);

                vint32m4_t c3 = vsext_vf4(vle8_v_i8m1(ip_c3, vl), vl);
                ip_c3 += vl;
                c3 = vadd_vv_i32m4(c3, offset, vl);

                vint32m4_t r0 = vsext_vf4(vle8_v_i8m1(ip_r0, vl), vl);
                ip_r0 += vl;

                acc_0_temp = vredsum_vs_i32m4_i32m1(vm_temp_0, vmul_vv_i32m4(r0, c0, vl), vm_temp_0, vl);
                acc_0 = vmv_x_s_i32m1_i32(acc_0_temp);

                acc_1_temp = vredsum_vs_i32m4_i32m1(vm_temp_0, vmul_vv_i32m4(r0, c1, vl), vm_temp_0, vl);
                acc_1 = vmv_x_s_i32m1_i32(acc_1_temp);

                acc_2_temp = vredsum_vs_i32m4_i32m1(vm_temp_0, vmul_vv_i32m4(r0, c2, vl), vm_temp_0, vl);
                acc_2 = vmv_x_s_i32m1_i32(acc_2_temp);

                acc_3_temp = vredsum_vs_i32m4_i32m1(vm_temp_0, vmul_vv_i32m4(r0, c3, vl), vm_temp_0, vl);
                acc_3 = vmv_x_s_i32m1_i32(acc_3_temp);
            }

            int32_t out_temp[4];
            int32_t in_temp[4] = {acc_0, acc_1, acc_2, acc_3};
            vint32m1_t res = vle32_v_i32m1(in_temp, 4);

            if (bias)
            {
                res = vadd_vx_i32m1(res, bias[i_out_ch], 4);
            }

            res = rvv_requantize(res, vl, output_mult[i_out_ch], output_shift[i_out_ch]);
            res = vadd_vx_i32m1(res, out_offset, 4);

            res = vmax_vx_i32m1(res, activation_min, 4);
            res = vmin_vx_i32m1(res, activation_max, 4);

            vse32_v_i32m1(out_temp, res, 4);

            out[i_out_ch] = (q7_t)out_temp[0];
            out[i_out_ch + output_ch] = (q7_t)out_temp[1];
            out[i_out_ch + output_ch * 2] = (q7_t)out_temp[2];
            out[i_out_ch + output_ch * 3] = (q7_t)out_temp[3];
        }
        out += 4 * output_ch;
    }
    else
    {
        for (int i_col_batch = (col_batches & ~0x3); i_col_batch < (col_batches & 0x3); i_col_batch++)
        {
            for (int i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
            {
                int32_t row_len_tmp = row_len;

                const int8_t *ip_r0 = input_row + (i_out_ch * row_len);
                const int8_t *ip_c0 = input_col + (i_col_batch * row_len);
                int32_t acc_0 = 0;
                vint32m1_t vm_temp_0;

                while (row_len_tmp > 0)
                {
                    vl = vsetvl_e8m1(row_len_tmp);
                    vm_temp_0 = vmv_v_x_i32m1(0, vl);
                    vint32m4_t offset = vmv_v_x_i32m4(col_offset, vl);
                    row_len_tmp -= vl;

                    vint32m4_t c0 = vsext_vf4(vle8_v_i8m1(ip_c0, vl), vl);
                    ip_c0 += vl;
                    c0 = vadd_vv_i32m4(c0, offset, vl);

                    vint32m4_t r0 = vsext_vf4(vle8_v_i8m1(ip_r0, vl), vl);
                    ip_r0 += vl;

                    vint32m1_t acc_0_temp = vredsum_vs_i32m4_i32m1(vm_temp_0, vmul_vv_i32m4(r0, c0, vl), vm_temp_0, vl);
                    acc_0 = vmv_x_s_i32m1_i32(acc_0_temp);
                }

                if (bias)
                {
                    acc_0 += bias[i_out_ch];
                }
                acc_0 = nn_requantize(acc_0, output_mult[i_out_ch], output_shift[i_out_ch]);
                acc_0 += out_offset;
                acc_0 = MAX(acc_0, activation_min);
                acc_0 = MIN(acc_0, activation_max);
                out[i_out_ch] = (q7_t)acc_0;
            }
            out += output_ch;
        }
    }
    return out;
}
#endif

int32_t rvv_convolve_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims)
{
    return (2 * input_dims->c * filter_dims->w * filter_dims->h) * (int32_t)sizeof(int16_t);
}

int rvv_convolve_s8(const cmsis_nn_context *ctx,
                    const cmsis_nn_conv_params *conv_params,
                    const cmsis_nn_per_channel_quant_params *quant_params,
                    const cmsis_nn_dims *input_dims,
                    const q7_t *input_data,
                    const cmsis_nn_dims *filter_dims,
                    const q7_t *filter_data,
                    const cmsis_nn_dims *bias_dims,
                    const int32_t *bias_data,
                    const cmsis_nn_dims *output_dims,
                    q7_t *output_data)
{
    (void)bias_dims;

    if (ctx->buf == NULL && rvv_convolve_s8_get_buffer_size(input_dims, filter_dims) > 0)
        return -1;

    q15_t *buffer_a = (q15_t *)ctx->buf;

    const int32_t input_batches = input_dims->n;
    const uint16_t input_x = input_dims->w;
    const uint16_t input_y = input_dims->h;
    const uint16_t input_ch = input_dims->c;
    const uint16_t kernel_x = filter_dims->w;
    const uint16_t kernel_y = filter_dims->h;
    const uint16_t output_x = output_dims->w;
    const uint16_t output_y = output_dims->h;
    const uint16_t output_ch = output_dims->c;

    const uint16_t pad_x = conv_params->padding.w;
    const uint16_t pad_y = conv_params->padding.h;
    const uint16_t stride_x = conv_params->stride.w;
    const uint16_t stride_y = conv_params->stride.h;

    const int32_t input_offset = conv_params->input_offset;
    const int32_t out_offset = conv_params->output_offset;
    const int32_t out_activation_min = conv_params->activation.min;
    const int32_t out_activation_max = conv_params->activation.max;
    int32_t *output_mult = quant_params->multiplier;
    int32_t *output_shift = quant_params->shift;

    int i_batch;
    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
#if defined(RVV)
        /* Generate upto four columns from the input tensor a GEMM computation */
        q7_t *im2col_buf = (q7_t *)buffer_a;
        q7_t *out = output_data;
        int32_t buffer_fill_cnt = 0;
        int32_t padded = 0;
        const int32_t num_elem = kernel_x * kernel_y * input_ch;
        const int32_t dilation_x = conv_params->dilation.w;
        const int32_t dilation_y = conv_params->dilation.h;

        /* This part implements the im2col function */
        for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                const int32_t base_idx_x = stride_x * i_out_x - pad_x;
                const int32_t base_idx_y = stride_y * i_out_y - pad_y;

                for (int32_t i_ker_y = 0; i_ker_y < kernel_y; i_ker_y++)
                {
                    for (int32_t i_ker_x = 0; i_ker_x < kernel_x; i_ker_x++)
                    {
                        const int32_t k_y = base_idx_y + dilation_y * i_ker_y;
                        const int32_t k_x = base_idx_x + dilation_x * i_ker_x;

                        if (k_y < 0 || k_y >= input_y || k_x < 0 || k_x >= input_x)
                        {
                            memset(im2col_buf, (int8_t)-input_offset, sizeof(q7_t) * input_ch);
                            padded = 1;
                        }
                        else
                        {
                            copy_q7(im2col_buf, input_data + (k_y * input_x + k_x) * input_ch, input_ch);
                        }
                        im2col_buf += input_ch;
                    }
                }

                buffer_fill_cnt++;

                if (buffer_fill_cnt == 4)
                {
                    buffer_fill_cnt = 0;
                    out = rvv_nn_mat_mult_s8(filter_data,
                                             (q7_t *)buffer_a,
                                             output_ch,
                                             4,
                                             output_shift,
                                             output_mult,
                                             out_offset,
                                             input_offset,
                                             0,
                                             out_activation_min,
                                             out_activation_max,
                                             num_elem,
                                             bias_data,
                                             out);

                    im2col_buf = (q7_t *)buffer_a;
                    padded = 0;
                }
            }
        }
        /* Handle left over columns */
        if (buffer_fill_cnt != 0)
        {
            out = rvv_nn_mat_mult_s8(filter_data,
                                     (q7_t *)buffer_a,
                                     output_ch,
                                     buffer_fill_cnt,
                                     output_shift,
                                     output_mult,
                                     out_offset,
                                     input_offset,
                                     0,
                                     out_activation_min,
                                     out_activation_max,
                                     num_elem,
                                     bias_data,
                                     out);
        }
#else 
    const uint16_t dilation_x = conv_params->dilation.w;
    const uint16_t dilation_y = conv_params->dilation.h;

    int32_t i_out_y, i_out_x, i_ker_y, i_ker_x;

    /* Generate two columns from the input tensor a GEMM computation */
    q15_t *two_column_buf = buffer_a;
    q7_t *out = output_data;

    /* This part implements the im2col function */
    for (i_out_y = 0; i_out_y < output_y; i_out_y++)
    {
        for (i_out_x = 0; i_out_x < output_x; i_out_x++)
        {
            const int32_t base_idx_y = stride_y * i_out_y - pad_y;
            const int32_t base_idx_x = stride_x * i_out_x - pad_x;

            for (i_ker_y = 0; i_ker_y < kernel_y; i_ker_y++)
            {
                for (i_ker_x = 0; i_ker_x < kernel_x; i_ker_x++)
                {
                    const int32_t k_y = base_idx_y + dilation_y * i_ker_y;
                    const int32_t k_x = base_idx_x + dilation_x * i_ker_x;

                    if (k_y < 0 || k_y >= input_y || k_x < 0 || k_x >= input_x)
                    {
                        /* Filling 0 for out-of-bound paddings */
                        memset(two_column_buf, 0, sizeof(q15_t) * input_ch);
                    }
                    else
                    {
                        /* Copying the pixel data to column */
                        q7_to_q15_with_offset(
                            input_data + (k_y * input_x + k_x) * input_ch, two_column_buf, input_ch, input_offset);
                    }
                    two_column_buf += input_ch;
                }
            }

            /* Computation is filed for every 2 columns */
            if (two_column_buf == buffer_a + 2 * input_ch * kernel_y * kernel_x)
            {
                out = nn_mat_mult_kernel_s8_s16(filter_data,
                                                buffer_a,
                                                output_ch,
                                                output_shift,
                                                output_mult,
                                                out_offset,
                                                out_activation_min,
                                                out_activation_max,
                                                input_ch * kernel_y * kernel_x,
                                                bias_data,
                                                out);

                /* counter reset */
                two_column_buf = buffer_a;
            }
        }
    }

    /* left-over because odd number of output pixels */
    if (two_column_buf != buffer_a)
    {
        const q7_t *ker_a = filter_data;
        int i;

        for (i = 0; i < output_ch; i++)
        {
            /* Load the accumulator with bias first */
            q31_t sum = 0;
            if (bias_data)
            {
                sum = bias_data[i];
            }

            /* Point to the beginning of the im2col buffer where the input is available as a rearranged column */
            const q15_t *ip_as_col = buffer_a;
            uint16_t col_count = input_ch * kernel_y * kernel_x;
            while (col_count)
                {
                    q7_t ker_a1 = *ker_a++;
                    q15_t ip_b1 = *ip_as_col++;
                    sum += ker_a1 * ip_b1;
                    col_count--;
                }

                sum = nn_requantize(sum, output_mult[i], output_shift[i]);
                sum += out_offset;
                sum = MAX(sum, out_activation_min);
                sum = MIN(sum, out_activation_max);
                *out++ = (q7_t)sum;
            }
        }
#endif
        /* Advance to the next batch */
        input_data += (input_x * input_y * input_ch);
        output_data += (output_x * output_y * output_ch);
    }

    /* Return to application */
    return 0;
}

int main(void)
{
    q7_t output[BASIC_DST_SIZE] = {0};

    cmsis_nn_context ctx;
    cmsis_nn_conv_params conv_params;
    cmsis_nn_per_channel_quant_params quant_params;
    cmsis_nn_dims input_dims;
    cmsis_nn_dims filter_dims;
    cmsis_nn_dims bias_dims;
    cmsis_nn_dims output_dims;

    const q31_t *bias_data = basic_biases;
    const q7_t *kernel_data = basic_weights;
    const q7_t *input_data = basic_input;
    const q7_t *output_ref = basic_output_ref;
    const int32_t output_ref_size = BASIC_DST_SIZE;

    input_dims.n = BASIC_INPUT_BATCHES;
    input_dims.w = BASIC_INPUT_W;
    input_dims.h = BASIC_INPUT_H;
    input_dims.c = BASIC_IN_CH;
    filter_dims.w = BASIC_FILTER_X;
    filter_dims.h = BASIC_FILTER_Y;
    output_dims.w = BASIC_OUTPUT_W;
    output_dims.h = BASIC_OUTPUT_H;
    output_dims.c = BASIC_OUT_CH;

    conv_params.padding.w = BASIC_PAD_X;
    conv_params.padding.h = BASIC_PAD_Y;
    conv_params.stride.w = BASIC_STRIDE_X;
    conv_params.stride.h = BASIC_STRIDE_Y;
    conv_params.dilation.w = BASIC_DILATION_X;
    conv_params.dilation.h = BASIC_DILATION_Y;

    conv_params.input_offset = BASIC_INPUT_OFFSET;
    conv_params.output_offset = BASIC_OUTPUT_OFFSET;
    conv_params.activation.min = BASIC_OUT_ACTIVATION_MIN;
    conv_params.activation.max = BASIC_OUT_ACTIVATION_MAX;
    quant_params.multiplier = (int32_t *)basic_output_mult;
    quant_params.shift = (int32_t *)basic_output_shift;

    int32_t buf_size = rvv_convolve_s8_get_buffer_size(&input_dims, &filter_dims);
    ctx.buf = malloc(buf_size);
    ctx.size = 0;

    int result = rvv_convolve_s8(&ctx,
                                &conv_params,
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

    for (size_t i = 0; i < BASIC_DST_SIZE; ++i)
        printf(" %d ", output[i]);
}