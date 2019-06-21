#include <string.h>

#define memzero(a)  memset(&a, 0, sizeof(a))

struct file_dev
{
    const char *src;
    const char *dst;
};
typedef struct file_dev fileDev;
