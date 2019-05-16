#include <stdio.h>

typedef unsigned char BYTE;

struct myFloat {
    union {
        float f;
        BYTE data[sizeof(float)];
    };
};

int main()
{
    myFloat f;
    char tmp[128];

    f.f = 17.625f;

    sprintf(tmp, "%x %x %x %x", f.data[0], f.data[1],
        f.data[2], f.data[3]);
    printf("%s\n", tmp);

    return 0;
}