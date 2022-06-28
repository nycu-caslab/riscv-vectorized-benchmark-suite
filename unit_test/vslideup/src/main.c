#include "riscv_vector.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int test4() {


    printf("Test 4\n");
    uint32_t vlen = 128;
    uint8_t lmul = 4;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;
    

    uint8_t* a = malloc(sizeof(uint8_t) * vl);

    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t shift = 5;

    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=shift;i<vl;i++) {
        golden[i] = a[i - shift];
    }
    for(int i=0;i<shift;i++) {
        golden[i] = 0;
    }

    //* load to vector register

    vuint8m4_t vec = vle8_v_u8m4(a, vl);
    vuint8m4_t dst;
    vuint8m4_t vec2 = vslideup_vx_u8m4(dst, vec, shift, vl);

    vse8_v_u8m4(a, vec2, vl);

    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]) {
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
        } else {
            printf("%d\n", a[i]);
        }
    }

    return 0;

}



int test3() {


    printf("Test 3\n");
    uint32_t vlen = 128;
    uint8_t lmul = 4;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;


    uint8_t* a = malloc(sizeof(uint8_t) * vl);

    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t shift = 5;

    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=shift;i<vl;i++) {
        golden[i] = a[i - shift];
    }
    for(int i=0;i<shift;i++) {
        golden[i] = 0;
    }

    //* load to vector register

    vuint8m4_t vec = vle8_v_u8m4(a, vl);
    vuint8m4_t dst;
    vuint8m4_t vec2 = vslideup_vx_u8m4(dst, vec, shift, vl);

    vse8_v_u8m4(a, vec2, vl);

    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]) {
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
        } else {
            printf("%d\n", a[i]);
        }
    }

    return 0;

}



int test2() {

    printf("Test 2\n");
    uint8_t vlen = 128;
    uint8_t lmul = 2;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;


    uint8_t* a = malloc(sizeof(uint8_t) * vl);

    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t shift = 5;

    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=shift;i<vl;i++) {
        golden[i] = a[i - shift];
    }
    for(int i=0;i<shift;i++) {
        golden[i] = 0;
    }

    //* load to vector register

    vuint8m2_t vec = vle8_v_u8m2(a, vl);
    vuint8m2_t dst;
    vuint8m2_t vec2 = vslideup_vx_u8m2(dst, vec, shift, vl);

    vse8_v_u8m2(a, vec2, vl);

    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]) {
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
        } else {
            printf("%d\n", a[i]);
        }
    }

    return 0;

}


int test1() {

    printf("Test 1\n");
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;


    uint8_t* a = malloc(sizeof(uint8_t) * vl);
    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t shift = 5;

    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=shift;i<vl;i++) golden[i] = a[i - shift];

    //* load to vector register

    vuint8m1_t vec = vle8_v_u8m1(a, vl);
    vuint8m1_t dst;
    vuint8m1_t vec2 = vslideup_vx_u8m1(dst, vec, shift, vl);

    vse8_v_u8m1(a, vec2, vl);

    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]) {
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
        } else {
            printf("%d\n", a[i]);
        }
    }

    return 0;

}

int main(void) {

    int ok = 0;

    ok = ok | test1();
    ok = ok | test2();
    ok = ok | test3();

    return ok;

}

