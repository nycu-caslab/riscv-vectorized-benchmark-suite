#include "conv.h"
#include "string.h"
#include <stdio.h>


int main(void) {

    size_t m,n;
    m = 100;
    n = 100;
    uint8_t* a = malloc(sizeof(uint8_t) * (m+2) * (n+2));
    uint8_t* wei = malloc(sizeof(uint8_t) * 9);
    uint8_t* b = malloc(sizeof(uint8_t) * m * n);


    memset(a, 0, sizeof(uint8_t) * (m+2) * (n+2));
    memset(b, 0, sizeof(uint8_t) * m * n);

    for(int i=1;i<m+1;i++) {
        for(int j=1;j<n+1;j++) {
            a[i*(n+2)+j] = 1;
        }
    }

    for(int i=0;i<9;i++)
        wei[i] = 1;


    conv(b, a, wei, m+2, n+2);

    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            int32_t t = b[i*n + j];
            printf("%3d ", t);
        }
        printf("\n");
    }


    return 0;

}