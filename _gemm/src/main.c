#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void) {



    int m, n, k;
    m = 32;
    n = 32;
    k = 32;


    unsigned char* a = malloc(sizeof(unsigned char) * m * k);
    unsigned char* b = malloc(sizeof(unsigned char) * k * n);
    unsigned char* c = malloc(sizeof(unsigned char) * m * n);

    // printf("Initialize the data\n");

    for(int i=0;i<m*k;i++) a[i] = 1;
    for(int i=0;i<k*n;i++) b[i] = 1;
    for(int i=0;i<m*n;i++) c[i] = 1;


    sgemm_nn(n, m, k, a, 32, b, 32, c, 32);

    // int err = 0;
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++)
            printf("%u ",c[i*32+j]);
        printf("\n");
    }



    // exit(-1);
    return 0;
}





