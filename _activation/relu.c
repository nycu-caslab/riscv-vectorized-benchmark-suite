#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <riscv_vector.h>

#include "input_data.h"

void rvv_relu(int8_t *data, uint16_t size)
{
    int32_t vl = 0;
    vint8m1_t op_1, max;

    while(size > 0)
    {
        vl = vsetvl_e8m1(size);
        op_1 = vle8_v_i8m1(data, vl);
        max = vmax_vx_i8m1(op_1, 0, vl);
        vse8_v_i8m1(data, max, vl);
        data += vl;
        size -= vl;
    }
}

void base_relu(int8_t *data, uint16_t size)
{
    uint16_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] < 0)
            data[i] = 0;
    }
}

int main(void)
{
    int8_t data[2112];
    size_t size = sizeof(relu_input);
    memcpy(data, relu_input, size);

#ifdef RVV
    rvv_relu((int8_t *)data, size);
#else
    base_relu((int8_t *)data, size);
#endif
}