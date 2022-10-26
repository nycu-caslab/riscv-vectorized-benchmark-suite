#include "riscv_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int test1() {

    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = malloc(sizeof(int8_t) * vl);
    int8_t* b = malloc(sizeof(int8_t) * vl);

    int8_t* golden = malloc(sizeof(int8_t) * vl);


    for(int i=0;i<vl;i++) a[i] = (1);
    for(int i=0;i<vl;i++) b[i] = 0;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t sum = b[0];
    for(int i=0;i<vl;i++) {
        sum += a[i];
    }
    golden[0] = sum;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredsum_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
     printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}


int main(void) {
    int ok = 0;
    ok = test1();

    if(ok != 0) {
        printf("Failed\n");
    } else {
        printf("Pass\n");
    }

    return 0;
}


