// # Copyright Hung Yan Tai
// # Licensed under the Solderpad Hardware License v2.1, see LICENSE.txt for details
// # SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

#include "conv.h"
#include <stdio.h>
#include <string.h>
#include <riscv_vector.h>


#define PVECTOR(x, vl, DEC) do {    \
    printf(DEC);                    \
    char a[32];                     \
    memset(a, '\0', 32);            \
    vse8_v_u8m1(a, x, vl);          \
    puint8_t(a, vl);                \
} while(0); 




void conv(const uint8_t* dst, const uint8_t* src, const uint8_t* wei, size_t m, size_t n) {



    register uint8_t w0, w1, w2, w3, w4, w5, w6, w7, w8;
    w0 = wei[0];
    w1 = wei[1];
    w2 = wei[2];
    w3 = wei[3];
    w4 = wei[4];
    w5 = wei[5];
    w6 = wei[6];
    w7 = wei[7];
    w8 = wei[8];


    uint8_t vlenb       = 128;
    uint8_t vsew_bits   = 8;
    uint8_t lmul        = 1;
    uint8_t vlmax       = (vlenb / vsew_bits) * lmul;

    size_t citer = n - 2;
    size_t riter = m - 2;
    size_t cur_vl = 0;
    
    register uint8_t* src_ = src;
    register uint8_t* src_np = src_;
    register uint8_t* dst_ = dst;
    register uint8_t* dst_np = dst_;
    register uint8_t t0, t1;

    register vuint8m1_t v0, v1, v2, v3, v4, v5, v6, v7, v8;
    register vuint8m1_t v9, v10, v11;
    // vuint8m1_t tmp;

    if(citer <= vlmax) {
        vsetvl_e8m1(citer);
        cur_vl = citer;
    } else {
        vsetvl_e8m1(vlmax);
        cur_vl = vlmax;
    }

    while(citer > 0) { 

        riter = m - 2;
        src_np = src_;
        dst_np = dst_;


        // puint8_t(src_np, cur_vl);
        v0 = vle8_v_u8m1(src_np, cur_vl);
        //PVECTOR(v0, cur_vl, "v0");
        t0 = *(src_np + cur_vl);
        t1 = *(src_np + cur_vl + 1);
        // printf("t0, %u\n", t0);
        // printf("t1, %u\n", t1);

        v1 = vslide1down_vx_u8m1(v0, t0, cur_vl);
        v2 = vslide1down_vx_u8m1(v1, t1, cur_vl);
        //PVECTOR(v1, cur_vl, "v1");
        //PVECTOR(v2, cur_vl, "v2");

        src_np = src_np + n;
        //puint8_t(src_np, cur_vl);
        v3 = vle8_v_u8m1(src_np, cur_vl);
        //PVECTOR(v3, cur_vl, "v3");
        t0 = *(src_np + cur_vl);
        t1 = *(src_np + cur_vl + 1);
        // printf("t0, %u\n", t0);
        // printf("t1, %u\n", t1);
        v4 = vslide1down_vx_u8m1(v3, t0, cur_vl);
        v5 = vslide1down_vx_u8m1(v4, t1, cur_vl);
        //PVECTOR(v4, cur_vl, "v4");
        //PVECTOR(v5, cur_vl, "v5");


        src_np = src_np + n;
        ////puint8_t(src_np, cur_vl);
        v6 = vle8_v_u8m1(src_np, cur_vl);
        //PVECTOR(v6, cur_vl, "v6");
        t0 = *(src_np + cur_vl);
        t1 = *(src_np + cur_vl + 1);
        // printf("t0, %u\n", t0);
        // printf("t1, %u\n", t1);
        v7 = vslide1down_vx_u8m1(v6, t0, cur_vl);
        v8 = vslide1down_vx_u8m1(v7, t1, cur_vl);
        //PVECTOR(v7, cur_vl, "v7");
        //PVECTOR(v8, cur_vl, "v8");

        while(riter > 0) {
            // printf("Iter %d\n", riter);
            if(citer <= vlmax) {
                vsetvl_e8m1(citer);
                cur_vl = citer;
            } else {
                vsetvl_e8m1(vlmax);
                cur_vl = vlmax;
            }

            // printf("cur_vl %d\n", cur_vl);

            //puint8_t(dst_np, cur_vl);

            v9 = vle8_v_u8m1(dst_np, cur_vl);
            //PVECTOR(v9, cur_vl, "v9");

            v9 = vmacc_vx_u8m1(v9, w0, v0, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w1, v1, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w2, v2, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w3, v3, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w4, v4, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w5, v5, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w6, v6, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w7, v7, cur_vl);
            v9 = vmacc_vx_u8m1(v9, w8, v8, cur_vl);
            //PVECTOR(v9, cur_vl, "v9");
            vse8_v_u8m1(dst_np, v9, cur_vl);

            // printf("V9 store: "); puint8_t(dst_np, cur_vl);

            dst_np += (n-2);

            riter -= 1;
            if(riter == 0)
                break;


            v10 = vle8_v_u8m1(dst_np, cur_vl);
            //PVECTOR(v10, cur_vl, "v10");
            
            src_np = src_np + n;
            v0 = vle8_v_u8m1(src_np, cur_vl);

            t0 = *(src_np + cur_vl);
            t1 = *(src_np + cur_vl + 1);
            v1 = vslide1down_vx_u8m1(v0, t0, cur_vl);
            v2 = vslide1down_vx_u8m1(v1, t1, cur_vl);
            //PVECTOR(v0, cur_vl, "v0");
            //PVECTOR(v1, cur_vl, "v1");
            //PVECTOR(v2, cur_vl, "v2");

            v10 = vmacc_vx_u8m1(v10, w0, v3, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w1, v4, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w2, v5, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w3, v6, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w4, v7, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w5, v8, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w6, v0, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w7, v1, cur_vl);
            v10 = vmacc_vx_u8m1(v10, w8, v2, cur_vl);

            //PVECTOR(v10, cur_vl, "v10");
            vse8_v_u8m1(dst_np, v10, cur_vl);
            // printf("V10 store: "); puint8_t(dst_np, cur_vl);
            dst_np += (n-2);

            riter -= 1;
            if(riter == 0)
                break;


            v11 = vle8_v_u8m1(dst_np, cur_vl);
            //PVECTOR(v11, cur_vl, "v11");

            src_np = src_np + n;
            v3 = vle8_v_u8m1(src_np, cur_vl);
            t0 = *(src_np + cur_vl);
            t1 = *(src_np + cur_vl + 1);
            v4 = vslide1down_vx_u8m1(v3, t0, cur_vl);
            v5 = vslide1down_vx_u8m1(v4, t1, cur_vl);
            //PVECTOR(v3, cur_vl, "v3");
            //PVECTOR(v4, cur_vl, "v4");
            //PVECTOR(v5, cur_vl, "v5");

            v11 = vmacc_vx_u8m1(v11, w0, v6, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w1, v7, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w2, v8, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w3, v0, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w4, v1, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w5, v2, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w6, v3, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w7, v4, cur_vl);
            v11 = vmacc_vx_u8m1(v11, w8, v5, cur_vl);
            //PVECTOR(v11, cur_vl, "v11");

            vse8_v_u8m1(dst_np, v11, cur_vl);
            // printf("V11 store: "); puint8_t(dst_np, cur_vl);
            dst_np += (n-2);

            riter -= 1;
            if(riter == 0)
                break;

            src_np = src_np + n;
            v6 = vle8_v_u8m1(src_np, cur_vl);
            t0 = *(src_np + cur_vl);
            t1 = *(src_np + cur_vl + 1);
            v7 = vslide1down_vx_u8m1(v6, t0, cur_vl);
            v8 = vslide1down_vx_u8m1(v7, t1, cur_vl);
            //PVECTOR(v6, cur_vl, "v6");
            //PVECTOR(v7, cur_vl, "v7");
            //PVECTOR(v8, cur_vl, "v8");
        }

        citer -= cur_vl;
        src_ += cur_vl;
        dst_ += cur_vl;
    }

    return;

}



void puint8_t(const uint8_t* src, size_t len) {
    for(size_t i=0;i<len;i++) {
        printf("%3u ", src[i]);
    }
    printf("\n");
}












