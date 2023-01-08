#include "riscv_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "unit_test.hh"

using namespace unittest;

int vasub_vx(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t b;
    int8_t temp;

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    b = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((int)(a[i] - b) >> 1);
        temp = a[i] - b;
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);

    vint8m1_t vec2 = vasub_vx_i8m1(vec_a , b, vl);

    vse8_v_i8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}


int vasubu_vx(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t b ;
    uint8_t temp;

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    b = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((unsigned int)(a[i] - b) >> 1);
        temp = a[i] - b;
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);

    vuint8m1_t vec2 = vasubu_vx_u8m1(vec_a , b, vl);

    vse8_v_u8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}

int vaadd_vx(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t b;
    int8_t temp;

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    b = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((int)(a[i] + b) >> 1);
        temp = a[i] + b;
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);

    vint8m1_t vec2 = vaadd_vx_i8m1(vec_a , b, vl);

    vse8_v_i8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}

int vaaddu_vx(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t b;
    uint8_t temp;

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    b = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((unsigned int)(a[i] + b) >> 1);
        temp = a[i] + b;
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);

    vuint8m1_t vec2 = vaaddu_vx_u8m1(vec_a , b, vl);

    vse8_v_u8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}


int vasub_vv(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t temp;

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    for(int i=0;i<vl;i++) b[i] = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((int)(a[i] - b[i]) >> 1);
        temp = a[i] - b[i];
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);

    vint8m1_t vec2 = vasub_vv_i8m1(vec_a , vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}


int vasubu_vv(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t* b = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t temp;

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    for(int i=0;i<vl;i++) b[i] = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((unsigned int)(a[i] - b[i]) >> 1);
        temp = a[i] - b[i];
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);
    vuint8m1_t vec_b = vle8_v_u8m1(b, vl);

    vuint8m1_t vec2 = vasubu_vv_u8m1(vec_a , vec_b, vl);

    vse8_v_u8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}

int vaadd_vv(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    int8_t* a = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t* b = (int8_t*)malloc(sizeof(int8_t) * vl);
    int8_t temp;

    int8_t* golden = (int8_t*)malloc(sizeof(int8_t) * vl);

    int8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    for(int i=0;i<vl;i++) b[i] = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((int)(a[i] + b[i]) >> 1);
        temp = a[i] + b[i];
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vint8m1_t vec_a = vle8_v_i8m1(a, vl);
    vint8m1_t vec_b = vle8_v_i8m1(b, vl);

    vint8m1_t vec2 = vaadd_vv_i8m1(vec_a , vec_b, vl);

    vse8_v_i8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}

int vaaddu_vv(){

    // verify csr:vxrm = 0
    printf("csr: %d\n",vread_csr(RVV_VXRM));
    // vwrite_csr(RVV_VXRM, 1);
    // printf("csr: %d\n",vread_csr(RVV_VXRM));

    
    uint8_t vlen = 128;
    uint8_t lmul = 1;
    uint8_t sewb = 8;
    uint8_t vl = (vlen / sewb) * lmul;

    uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t* b = (uint8_t*)malloc(sizeof(uint8_t) * vl);
    uint8_t temp;

    uint8_t* golden = (uint8_t*)malloc(sizeof(uint8_t) * vl);

    uint8_t r = rand() % 100;

    for(int i=0;i<vl;i++) a[i] = (rand() % 124 / 2 );
    for(int i=0;i<vl;i++) b[i] = (rand() % 124);

    for(int i=0;i<vl;i++){
        golden[i] = ((unsigned int)(a[i] + b[i]) >> 1);
        temp = a[i] + b[i];
        temp = temp & 1;
        if(temp) golden[i]++;
    }

    size_t nvl = vsetvl_e8m1(vl);

    vuint8m1_t vec_a = vle8_v_u8m1(a, vl);
    vuint8m1_t vec_b = vle8_v_u8m1(b, vl);

    vuint8m1_t vec2 = vaaddu_vv_u8m1(vec_a , vec_b, vl);

    vse8_v_u8m1(a, vec2, vl);

    for(int i=0;i<vl;i++){
        if(a[i] != golden[i]){
            printf("a(%d) != golden(%d)\n", a[i], golden[i]);
            return 1;
        }
        printf("%d ", a[i]);

    }
    printf("\n");

    return 0;
}

int main(void){

    TestSpec ts("vectoraverage"); 
    ts.test(vaaddu_vv, "vaaddu_vv");
    ts.test(vaadd_vv, "vaadd_vv");
    ts.test(vasubu_vv, "vasubu_vv");
    ts.test(vasub_vv, "vasub_vv");
    ts.test(vaaddu_vx, "vaaddu_vx");
    ts.test(vaadd_vx, "vaadd_vx");
    ts.test(vasubu_vx, "vasubu_vx");
    ts.test(vasub_vx, "vasub_vx");



    ts.run();

    return 0;
}