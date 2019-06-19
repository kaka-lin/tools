#include <stdio.h>

typedef unsigned char BYTE;

struct myFloat {
    union {
        float f;
        BYTE data[sizeof(float)];
    };
};
typedef struct myFloat myFloat;

int main()
{
    myFloat float_data;
    char tmp[128];

    float_data.f = 17.625f;

    sprintf(tmp, "%x %x %x %x", float_data.data[0], float_data.data[1],
        float_data.data[2], float_data.data[3]);
    printf("%s\n", tmp);

    return 0;
}
