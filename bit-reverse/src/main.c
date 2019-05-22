#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "args.h"

// bit-reversal permutation
void bit_reverse(int N)
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
    int length = pow(2, N);
    int *reverse = calloc(length, sizeof(int));

    // Nlog(N)
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < N; j++) { 
            if ((i >> j) & 1) {
                reverse[i] |= (1 << (N - j - 1));
            }
        }
    }

    for (int i = 0; i < length; i++) {
        printf("%d -> %d\n", i, reverse[i]);
    }
}

int main(int argc, char **argv)
{   
    int ret;
    int N;

    ret = parse_args(&N, argc, argv);

    bit_reverse(N);

    return 0;
}
