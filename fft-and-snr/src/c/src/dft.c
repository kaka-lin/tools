#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

complex *DFT(double *x, int size)
{   
    complex *y = calloc(size, sizeof(complex));

    for (int k = 0; k < size; k++) {
        double real = 0.0;
        double imag = 0.0;
        
        for (int n = 0; n < size; n++) {
            real += x[n] * cos(2 * pi *k * n / size);
            imag += ((-1) * x[n] * sin(2 * pi * k * n / size));
        }

        y[k].real = real;
        y[k].imag = imag;
    }

    return y;
}

complex *IDFT(complex *x, int size)
{ 
    complex *y = calloc(size, sizeof(complex));

    for (int n = 0; n < size; n++) {
        double real = 0.0;
        double imag = 0.0;

        for (int k = 0; k < size; k++) {
            real += x[k].real * cos(2 * pi * k * n / size) - x[k].imag * sin(2 * pi * k * n / size);
            imag += x[k].real * sin(2 * pi * k * n / size) + x[k].imag * cos(2 * pi * k * n / size);
        }

        y[n].real = real / size;
        y[n].imag = imag / size;
    }

    return y;
}

int main(int argc, char **argv)
{   
    /* Sampling information */
    int fs = 80;
    float Ts = 1.0 / fs;
    float t = 1;
    int N = fs * t;
    
    /* signal information */ 
    int f = 20;
    float *x = arange(0, t, Ts);
    double y[N]; // y = cos(2*pi*f*x)

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
    complex *yf = DFT(y, N);

    printf("DFT: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\n\t ");
        }
        printf("%.2f%c%.2f%s", yf[i].real, (yf[i].imag >= 0 ? '+': '\0'), yf[i].imag, (i == N-1 ? "j" : "j, "));
    }
    printf("]\n");


    complex *yif = IDFT(yf, N);

    printf("IDFT: \n\t[");
    for (int i = 0; i < N; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\n\t ");
        }
        printf("%.2f%c%.2f%s", yif[i].real, (yif[i].imag >= 0 ? '+': '\0'), yif[i].imag, (i == N-1 ? "j" : "j, "));
    }
    printf("]\n");
   
    return 0;
}

