#include "riscv_vector.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "unit_test.hh"

using namespace unittest;




int test_vsextvf2() {

    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;


    uint8_t* a = (uint8_t*) malloc(sizeof(uint8_t) * vl);

    int16_t* golden = (int16_t*) malloc(sizeof(int16_t) * vl);
    int16_t* result = (int16_t*) malloc(sizeof(int16_t) * vl);

    for(int i=0;i<vl;i++) a[i] = (rand() % 128) + 128;

    for(int i=0;i<vl;i++) golden[i] = (int16_t)((int8_t)a[i]);



    size_t nvl = vsetvl_e8m1(vl);
    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);

    vint8m1_t vec_sa = vreinterpret_v_u8m1_i8m1(vec_a);

    vint16m2_t vec_ans = vsext_vf2_i16m2(vec_sa, vl);


    vse16_v_i16m2(result, vec_ans, vl);

    
    int err = 0;
    for(int i=0;i<vl;i++) {
        if(result[i] != golden[i]) {
            printf("result(%04x) != golden(%04x), original(%04x)\n", result[i], golden[i], a[i]);
            err += 1;
        } else {
            printf("result(%04x) == golden(%04x), original(%04x)\n", result[i], golden[i], a[i]);
        }
    }


    if(err) {
        return 1;
    }
    return 0;
}



int test_vzextvf2() {

    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;


    uint8_t* a = (uint8_t*) malloc(sizeof(uint8_t) * vl);

    uint16_t* golden = (uint16_t*) malloc(sizeof(uint16_t) * vl);
    uint16_t* result = (uint16_t*) malloc(sizeof(uint16_t) * vl);

    for(int i=0;i<vl;i++) a[i] = (rand() % 128) + 128;

    for(int i=0;i<vl;i++) golden[i] = (uint16_t)a[i];



    size_t nvl = vsetvl_e8m1(vl);
    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);

    vuint16m2_t vec_ans = vzext_vf2_u16m2(vec_a, vl);


    vse16_v_u16m2(result, vec_ans, vl);

    
    int err = 0;
    for(int i=0;i<vl;i++) {
        if(result[i] != golden[i]) {
            printf("result(%04x) != golden(%04x), original(%04x)\n", result[i], golden[i], a[i]);
            err += 1;
        } else {
            printf("result(%04x) == golden(%04x), original(%04x)\n", result[i], golden[i], a[i]);
        }
    }


    if(err) {
        return 1;
    }
    return 0;
}


int main(void) {

    TestSpec ts("vext");
    ts.test(test_vzextvf2, "test_vzextvf2");
    ts.test(test_vsextvf2, "test_vsextvf2");
    ts.run();

    return 0;
}







