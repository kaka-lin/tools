#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

void DFT(double *src, complex *dst, int size)
{
    for (int k = 0; k < size; k++) {
        double real = 0;
        double imag = 0;
        
        for (int n = 0; n < size; n++) {
            real += src[n] * cos(2 * pi *k * n / size);
            imag += src[n] * (-1) * sin(2 * pi *k * n / size);
        }

        dst[k].real = real;
        dst[k].imag = imag;
    }
}

int main(int argc, char **argv)
{   
    // Sampling information
    int fs = 80;
    float Ts = 1.0 / fs;
    float t = 1;
    int N = fs * t;
    
    // signal information
    int f = 20;
    float *x = arange(0, t, Ts);

    double y[N];
    complex yf[N];
    memset(yf, 0, sizeof yf);

    // Input signal
    printf("Input array: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\n\t ");
        }
        y[i] = cos(2 * pi * f * x[i]);
        printf("%.2f%s", y[i], (i == N-1 ? "\0" : ", "));
    }
    printf("]\n");

    // Discrete Fourier Tranform (DFT)
    // According to the DFT formula, 
    // time complexity: O(n^2)
    DFT(y, yf, N);

    printf("DFT: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\n\t ");
        }
        printf("%.2f%c%.2f%s", yf[i].real, (yf[i].imag >= 0 ? '+': '\0'), yf[i].imag, (i == N-1 ? "j" : "j, "));
    }
    printf("]\n");
   
    return 0;
}

