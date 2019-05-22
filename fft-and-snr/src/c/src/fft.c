#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "common.h"

int is_two_n(int num)
{
    /* ex: num = 8, 8-1 = 7
     *   
     * 8:　    1000
     * 7:　　& 0111
     *      -------
     *        0000
     */ 
	if ((num & (num - 1)) == 0)
		return 1;
	return 0;
}

// bit-reversal permutation
void bit_reverse(struct fft_info *fft_info)
{
    int N = fft_info->len;
    int bits;

    if (!is_two_n(N)) {
        bits = log2(N) + 1;
        N = pow(2, bits);
    } else {
        bits = log2(N);
    }

    double *reverse = calloc(N, sizeof(float));
    int reverse_index;

    // Nlog(N)
    for (int i = 0; i < N; i++) {
        reverse_index = 0;
        for (int j = 0; j < bits; j++) { 
            if ((i >> j) & 1) {
                reverse_index |= (1 << (bits - j - 1));
            }
        }
        reverse[i] = fft_info->input[reverse_index];
    }

    fft_info->input = reverse;
    fft_info->len = N;
}

/* Cooley-Tukey Fast Fourier Transform(FFT) Algorithm
 *
 * 1. radix-2 decimation-in-time (DIT) FFT
 *    -> O(NlogN)
 */
void FFT(struct fft_info *fft_info)
{   
    clock_t start, end;
    start = clock();

    // bit-reversal permutation */
    bit_reverse(fft_info);
    //print_array(fft_info->input, fft_info->len);

    int N = fft_info->len;
    double *x = fft_info->input;
    complex *y = calloc(N, sizeof(complex));

    complex Wn, G, H;

    // dynamic programming
    for (int k = 2; k <= N; k<<=1) {
        memset(&Wn, 0.0, sizeof(complex));
        memset(&G, 0.0, sizeof(complex));
        memset(&H, 0.0, sizeof(complex));

        Wn.real = cos(2*pi*k/N);
        Wn.imag = (-1) * sin(2*pi*k/N);

        for (int i = 0; i < N; i+=k) {
            for (int j=i; j<i+k/2; j++) {
                printf("k: %d, i:%d, j:%d, j+k/2: %d\n", k, i, j, j+(k/2));
            }
        }
        //for (int r = 0; r < N; r+=k) {
        //    G.real += x[2*r] * cos(2*pi*2*r*k / N);
        //    G.imag += x[2*r] * (-1) * sin(2*pi*2*r*k / N);
        //    H.real += x[2*r+1] * cos(2*pi*2*r*k / N);
        //    H.imag += x[2*r+1] * (-1) * sin(2*pi*2*r*k / N);
        //}

        //y[k].real = G.real + Wn.real * H.real - Wn.imag * H.imag;
        //y[k].imag = G.imag + Wn.real * H.imag + Wn.imag * H.real;
        //y[k+N/2].real = G.real - Wn.real * H.real + Wn.imag * H.imag;
        //y[k+N/2].imag = G.imag - Wn.real * H.imag - Wn.imag * H.real;
    }

    fft_info->output = y;

    end = clock();
    printf("FFT, %lf secs:\n", (end-start) / (double)(CLOCKS_PER_SEC));
}

int main(int argc, char **argv)
{       
    struct fft_info fft_info;

    /* Sampling information */
    int fs = 4;
    double Ts = 1.0 / fs;
    double t = 1.0;
    int N = fs * t;
    
    /* signal information */
    int f = 1;
    double *x = arange(0, t, Ts);
    //printf("time:\n");
    //print_array(x, N);

    // y = cos(2*pi*f*x)
    double y[N]; 
    for (int i = 0; i < N; i++) {
        y[i] = cos(2 * pi * f * x[i]);
    }

    fft_info.len = N;
    fft_info.input = y;

    /* Fast Fourier Tranform (FFT) */
    FFT(&fft_info);
    print_complex_array(fft_info.output, fft_info.len);
    
    return 0;
}
