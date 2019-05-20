#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

#define N 10

void DFT(double *src, complex *dst) {
    for (int k = 0; k < N; k++) {
        double real = 0;
        double imag = 0;
        
        for (int n = 0; n < N; n++) {
            real += src[n] * cos(2 * pi *k * n / N);
            imag += src[n] * (-1) * sin(2 * pi *k * n / N);
        }

        dst[k].real = real;
        dst[k].imag = imag;
    }
}

int main(int argc, char **argv)
{   
    double input[N];
    complex y[N];
    memset(y, 0, sizeof y);

    float *x = arange(0, 1, 1/10.0);

    // Input signal
    printf("Input array: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 5 == 0) {
            printf("\n\t ");
        }
        input[i] = cos(2 * pi * 10 * x[i]);
        printf("%.2f%s", input[i], (i == N-1 ? "\0" : ", "));
    }
    printf("]\n");

    // Discrete Fourier Tranform (DFT)
    // According to the DFT formula, 
    // time complexity: O(n^2)
    DFT(input, y);

    printf("DFT: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 5 == 0) {
            printf("\n\t ");
        }
        printf("%.2f%c%.2f%s", y[i].real, (y[i].imag >= 0 ? '+': '\0'), y[i].imag, (i == N-1 ? "j" : "j, "));
    }
    printf("]\n");
    
   
    return 0;
}

