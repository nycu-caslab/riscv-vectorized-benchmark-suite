#include "riscv_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int test4() {
    uint8_t vlen = 128;
    uint8_t lmul = 4;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;
    uint8_t tvl = vl - 2;

    
    uint8_t* a = malloc(sizeof(uint8_t) * vl);
    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t  x = 32;


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl-1;i++) golden[i] = a[i+1];
    golden[tvl-1] = 32;
    //* set the vl and sew
    size_t nvl = vsetvl_e8m4(tvl);


    //* load to vector register
    vuint8m4_t vec = vle8_v_u8m4(a, tvl);
    vuint8m4_t vec2 = vslide1down_vx_u8m4(vec, x, tvl);


    vse8_v_u8m4(a, vec2, tvl);


    //* check
    for(int i=0;i<tvl;i++) {
        if(a[i] != golden[i]){
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
            return -1;
        } else {
            printf("%d \n", a[i]);
        }
    }
    
    return 0;
}

int test3() {
    uint8_t vlen = 128;
    uint8_t lmul = 4;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    
    uint8_t* a = malloc(sizeof(uint8_t) * vl);
    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t  x = 32;


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl-1;i++) golden[i] = a[i+1];
    golden[vl-1] = 32;
    //* set the vl and sew
    size_t nvl = vsetvl_e8m4(vl);


    //* load to vector register
    vuint8m4_t vec = vle8_v_u8m4(a, vl);
    vuint8m4_t vec2 = vslide1down_vx_u8m4(vec, x, vl);


    vse8_v_u8m4(a, vec2, vl);


    //* check
    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]){
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
            return -1;
        }
        printf("%d \n", a[i]);
    }
    
    return 0;
}


int test2() {
    uint8_t vlen = 128;
    uint8_t lmul = 2;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    
    uint8_t* a = malloc(sizeof(uint8_t) * vl);
    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t  x = 32;


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl-1;i++) golden[i] = a[i+1];
    golden[vl-1] = 32;
    //* set the vl and sew
    size_t nvl = vsetvl_e8m2(vl);


    //* load to vector register
    vuint8m2_t vec = vle8_v_u8m2(a, vl);
    vuint8m2_t vec2 = vslide1down_vx_u8m2(vec, x, vl);


    vse8_v_u8m2(a, vec2, vl);


    //* check
    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]){
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
            return -1;
        }
        printf("%d \n", a[i]);
    }
    
    return 0;
}


int test1() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    
    uint8_t* a = malloc(sizeof(uint8_t) * vl);
    uint8_t* golden = malloc(sizeof(uint8_t) * vl);
    uint8_t  x = 32;


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl-1;i++) golden[i] = a[i+1];
    golden[vl-1] = 32;
    //* set the vl and sew
    size_t nvl = vsetvl_e8m1(vl);


    //* load to vector register
    vuint8m1_t vec = vle8_v_u8m1(a, vl);
    vuint8m1_t vec2 = vslide1down_vx_u8m1(vec, x, vl);


    vse8_v_u8m1(a, vec2, vl);


    //* check
    for(int i=0;i<vl;i++) {
        if(a[i] != golden[i]){
            printf("a[%d] != golden[%d], (%d, %d)\n", i, i, a[i], golden[i]);
            // return -1;
        } else {
            printf("%d \n", a[i]);
        }
    }
    
    return 0;
}

int main(void) {


    //* test the vle8 correctness

    int ok = 0;

    ok = ok | test1(); 
    ok = ok | test2();
    ok = ok | test3();
    ok = ok | test4();

    return 0;

}
