#include <stdio.h>

#define pi 3.14159

typedef struct complex {
    double real;
    double imag;
} complex;

// numpy.arange(strat, stop, step, dtype=None)
float *arange(float start, float stop, float step) 
{
    int N = (int)((1 / step) * stop);
    float *array = calloc(N, sizeof(float));

    for (int index = 0; index < N; index++) {
        array[index] = start + index * step;
        //printf("%f ", array[index]);
    }
    
    return array;
}
