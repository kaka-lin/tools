#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "args.h"

#define MODULE_NAME "cp"

void init(fileDev *dev)
{
    dev->src = "";
    dev->dst = "";
}

int main(int argc, char **argv)
{
    fileDev dev;
    FILE *finput, *foutput;
    void *buffer;
    size_t size;
    size_t ret;

    // init
    init(&dev);

    ret = parse_args(&dev, argc, argv);
    if (ret) 
        return 0;

    if (*dev.src == '\0') {
        fprintf(stderr, "%s: missing file operand.\n", MODULE_NAME);
        return ENOENT;
        
    } else if (*dev.dst == '\0') {
        fprintf(stderr, "%s: missing destination file operand after %s.\n", MODULE_NAME, dev.src);
        return ENOENT;
    }
    
    // Open file -> read
    finput = fopen(dev.src, "rb+");
    if (finput == NULL) {
        fprintf(stderr, "Open file failed! %s (%d)\n",
            strerror(errno), errno);
        return ENOENT;
    }
    
    // obtain file size
    fseek(finput, 0, SEEK_END);
	size = ftell(finput);
	fseek(finput, 0, SEEK_SET); // equal rewind(finput)

    // allocate memory to contain the whole file
    buffer = calloc(size, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "(%s:%d) Out of memory.\n", __func__, __LINE__);
        return ENOMEM;
    }

    // copy the file into the buffer
    ret = fread(buffer, 1, size, finput);
    if (ret != size) {
        fprintf(stderr, "Reading error: only %lu bytes read instead of %lu\n",
            ret, size);
    }

    fclose(finput);

    // Open file -> write
    foutput = fopen(dev.dst, "wb+");
    if (finput == NULL) {
        fprintf(stderr, "Open file failed! %s (%d)\n",
            strerror(errno), errno);
        return ENOENT;
    }

    // write the buffer into the foutput
    ret = fwrite(buffer, 1, size, foutput);
    if (ret != size) {
        fprintf(stderr, "Writing error: only %lu bytes written instead of %lu\n",
            ret, size);
    }

    fclose(foutput);
    free(buffer);
    
    return 0;
}
