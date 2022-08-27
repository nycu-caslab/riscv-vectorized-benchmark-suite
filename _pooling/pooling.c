#include <riscv_vector.h>
#include <stdio.h>
#include <stdbool.h>

#include "arm_nn_types.h"
#include "test_data.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

static void copy_q7(q7_t *target, const q7_t *base, int32_t length)
{
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
}

static void compare_and_replace_if_larger_q7(q7_t *base, const q7_t *target, int32_t length)
{
    int32_t vl = 0;
    vint8m1_t op_1, op_2, max;
    
    while(length > 0)
    {
        vl = vsetvl_e8m1(length);
        op_1 = vle8_v_i8m1(base, vl);
        op_2 = vle8_v_i8m1(target, vl);
        max = vmax_vv_i8m1(op_1, op_2, vl);
        vse8_v_i8m1(base, max, vl);
        base += vl;
        target += vl;
        length -= vl;
    }
}

int arm_max_pool_s8(const cmsis_nn_context *ctx,
                                    const cmsis_nn_pool_params *pool_params,
                                    const cmsis_nn_dims *input_dims,
                                    const q7_t *src,
                                    const cmsis_nn_dims *filter_dims,
                                    const cmsis_nn_dims *output_dims,
                                    q7_t *dst)
{
    const int32_t input_y = input_dims->h;
    const int32_t input_x = input_dims->w;
    const int32_t output_y = output_dims->h;
    const int32_t output_x = output_dims->w;
    const int32_t stride_y = pool_params->stride.h;
    const int32_t stride_x = pool_params->stride.w;
    const int32_t kernel_y = filter_dims->h;
    const int32_t kernel_x = filter_dims->w;
    const int32_t pad_y = pool_params->padding.h;
    const int32_t pad_x = pool_params->padding.w;
    const int32_t act_min = pool_params->activation.min;
    const int32_t act_max = pool_params->activation.max;
    const int32_t channel_in = input_dims->c;
    (void)ctx;
    q7_t *dst_base = dst;

    for (int i_y = 0, base_idx_y = -pad_y; i_y < output_y; base_idx_y += stride_y, i_y++)
    {
        for (int i_x = 0, base_idx_x = -pad_x; i_x < output_x; base_idx_x += stride_x, i_x++)
        {
            const int32_t ker_y_start = MAX(0, -base_idx_y);
            const int32_t ker_x_start = MAX(0, -base_idx_x);

            const int32_t kernel_y_end = MIN(kernel_y, input_y - base_idx_y);
            const int32_t kernel_x_end = MIN(kernel_x, input_x - base_idx_x);

            int count = 0;

            for (int k_y = ker_y_start; k_y < kernel_y_end; k_y++)
            {
                for (int k_x = ker_x_start; k_x < kernel_x_end; k_x++)
                {
                    const q7_t *start = src + channel_in * (k_x + base_idx_x + (k_y + base_idx_y) * input_x);

                    if (count == 0)
                    {
                        copy_q7(dst, start, channel_in);
                        count++;
                    }
                    else
                    {
                        compare_and_replace_if_larger_q7(dst, start, channel_in);
                    }
                }
            }
            dst += channel_in;
        }
    }
    return 0;
}

int main(void)
{
    bool validate = true;
    q7_t output[MAXPOOLING_DST_SIZE] = {0};

    cmsis_nn_context ctx;
    cmsis_nn_pool_params pool_params;
    cmsis_nn_dims input_dims;
    cmsis_nn_dims filter_dims;
    cmsis_nn_dims output_dims;

    const q7_t *input_data = maxpooling_input;

    input_dims.n = MAXPOOLING_INPUT_BATCHES;
    input_dims.w = MAXPOOLING_INPUT_W;
    input_dims.h = MAXPOOLING_INPUT_H;
    input_dims.c = MAXPOOLING_IN_CH;
    filter_dims.w = MAXPOOLING_FILTER_X;
    filter_dims.h = MAXPOOLING_FILTER_Y;
    output_dims.w = MAXPOOLING_OUTPUT_W;
    output_dims.h = MAXPOOLING_OUTPUT_H;
    output_dims.c = MAXPOOLING_OUT_CH;

    pool_params.padding.w = MAXPOOLING_PAD_X;
    pool_params.padding.h = MAXPOOLING_PAD_Y;
    pool_params.stride.w = MAXPOOLING_STRIDE_X;
    pool_params.stride.h = MAXPOOLING_STRIDE_Y;

    pool_params.activation.min = MAXPOOLING_OUT_ACTIVATION_MIN;
    pool_params.activation.max = MAXPOOLING_OUT_ACTIVATION_MAX;

    arm_max_pool_s8(&ctx, &pool_params, &input_dims, input_data, &filter_dims, &output_dims, output);

    for (size_t i = 0; i < MAXPOOLING_DST_SIZE; ++i)
    {
        if (output[i] != maxpooling_output_ref[i])
        {
            validate = false;
            break;
        }
    }

    if (validate)
        printf("test passed \n");
    else
        printf("test failed \n");
}
