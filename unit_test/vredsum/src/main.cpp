#include "riscv_vector.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "unit_test.hh"


using namespace unittest;


int test_vredxor() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);
    

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (r << 10) ^ (r << 5) ^ (r >> 3);
    for(int i=0;i<vl;i++) b[i] = r;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t val = b[0];
    for(int i=0;i<vl;i++) {
        val = val ^ a[i];
    }
    golden[0] = val;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredxor_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}


int test_vredor() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);
    

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (r << 10) ^ (r << 5) ^ (r >> 3);
    for(int i=0;i<vl;i++) b[i] = r;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t val = b[0];
    for(int i=0;i<vl;i++) {
        val = val | a[i];
    }
    golden[0] = val;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredor_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;



}


int test_vredand() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);
    

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (r << 10) ^ (r << 5) ^ (r >> 3);
    for(int i=0;i<vl;i++) b[i] = r;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t val = b[0];
    for(int i=0;i<vl;i++) {
        val = val & a[i];
    }
    golden[0] = val;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredand_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;



}


int test_vredmin() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);


    for(int i=0;i<vl;i++) a[i] = (-i-1);
    for(int i=0;i<vl;i++) b[i] = 0;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t min = b[0];
    for(int i=0;i<vl;i++) {
        min = std::min(min, a[i]);
    }
    golden[0] = min;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredmin_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}


int test_vredminu() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t* b = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl;i++) b[i] = 0;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    uint8_t min = b[0];
    for(int i=0;i<vl;i++) {
        min = std::min(min, a[i]);
    }
    golden[0] = min;

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);
    vuint8m1_t vec_b = vle8_v_u8m1(b, vl);
    vuint8m1_t dst;
    vuint8m1_t vec2 = vredminu_vs_u8m1_u8m1(dst, vec_a, vec_b, vl);

    vse8_v_u8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}

int test_vredmax() {
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);


    for(int i=0;i<vl;i++) a[i] = (-i-1);
    for(int i=0;i<vl;i++) b[i] = 0;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    int8_t max = b[0];
    for(int i=0;i<vl;i++) {
        max = std::max(max, a[i]);
    }
    golden[0] = max;


    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);
    vint8m1_t dst;
    vint8m1_t vec2 = vredmax_vs_i8m1_i8m1(dst, vec_a, vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}



int test_vredmaxu() {

    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t* b = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);


    for(int i=0;i<vl;i++) a[i] = (i+1);
    for(int i=0;i<vl;i++) b[i] = 0;
    for(int i=0;i<vl;i++) golden[i] = a[i];

    uint8_t max = b[0];
    for(int i=0;i<vl;i++) {
        max = std::max(max, a[i]);
    }
    golden[0] = max;

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);
    vuint8m1_t vec_b = vle8_v_u8m1(b, vl);
    vuint8m1_t dst;
    vuint8m1_t vec2 = vredmaxu_vs_u8m1_u8m1(dst, vec_a, vec_b, vl);

    vse8_v_u8m1(a, vec2, vl);

    if(a[0] != golden[0]) {
        printf("a(%d) != golden(%d)\n", a[0], golden[0]);
        return 1;
    }
    printf("a(%d) == golden(%d)\n", a[0], golden[0]);
    return 0;
}

int test_vredsum() {

    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);


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


    TestSpec ts("vreduction");


    ts.test(test_vredsum, "test_vredsum");
    ts.test(test_vredmaxu, "test_vredmaxu");
    ts.test(test_vredmax, "test+vredmax");
    ts.test(test_vredminu, "test_vredminu");
    ts.test(test_vredmin, "test_vredmin");
    ts.test(test_vredand, "test_vredand");
    ts.test(test_vredor, "test_vredor");
    ts.test(test_vredxor, "test_vredxor");
    ts.run();

    // ok = ok | test_vredsum();
    // ok = ok | test_vredmaxu();


    // if(ok != 0) {
    //     printf("Failed\n");
    // } else {
    //     printf("Pass\n");
    // }

    return 0;
}


