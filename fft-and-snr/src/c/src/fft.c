#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

void print_binary(unsigned int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    unsigned int x;
    for (int bit = 31; bit >= 0; bit--) {
        x = n >> bit;

        if (x & 1) printf("1");
        else printf("0");
    }
    printf("\n");
}

// bit-reversal permutation
void bit_reverse(double *input, int size)
{
    /* bit-reverse 
    * 
    * ex:
    *     3 bit -> max 7
    *     x[0], (000) -> (000), x[0]
    *     x[1], (001) -> (100), x[4]
    *     x[2], (010) -> (010), x[2]
    *     x[3], (011) -> (110), x[6]
    *     and so on. 
    * sol:
    *     011, 從最右邊開始取值,如果為1, 就加到最左邊依序遞減
    *     [i = 0]: 1 -> 000 | 100 (1 << index (N = 3 => index = N - i - 1))
    *     [i = 1]: 1 -> 100 | 010 (1 << index (N = 3 => index = N - i - 1))
    *     [i = 2]: 0 不做事情
    */
    int bits = log2(size);
    int *reverse = calloc(size, sizeof(int));

    // Nlog(N)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < bits; j++) { 
            if ((i >> j) & 1) {
                reverse[i] |= (1 << (bits - j - 1));
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("%d -> %d\n", i, reverse[i]);
    }
}

/* Cooley-Tukey Fast Fourier Transform(FFT) Algorithm
 *
 * 1. radix-2 decimation-in-time (DIT) FFT
 */
void FFT(double *x, int size)
{   
}

int main(int argc, char **argv)
{   
    /* Sampling information */
    int fs = 16;
    float Ts = 1.0 / fs;
    float t = 1;
    int N = fs * t;
    
    /* signal information */ 
    int f = 1;
    float *x = arange(0, t, Ts);
    double y[N]; // y = cos(2*pi*f*x)

    printf("[");
    for (int i = 0; i < N; i++) {
        y[i] = cos(2 * pi * f * x[i]);
        printf("%.2f%s", y[i], (i == N-1 ? "\0" : ", "));
    }
    printf("]\n");
    
    bit_reverse(y, N);

    return 0;
}

