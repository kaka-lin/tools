#include <stdio.h>
#include <stdlib.h>

int file_size(FILE * file)
{
    if (fseek(file, 0, SEEK_END) < 0) {
        return -1;
    }
    long int file_size = ftell(file);
    if (fseek(file, 0, SEEK_SET) < 0) {
        return -1;
    }
    return file_size;
}

void hex_dump(void *data, int len) 
{
    unsigned char buff[17];
    unsigned char *_data = (unsigned char *)data;
    int i;

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }

    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).
        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf("  |  %s\n", buff);

            // Output the offset.
            printf("%06x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", _data[i]);

        // And store a printable ASCII character for later.
        if ((_data[i] < 0x20) || (_data[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = _data[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  |  %s\n", buff);
}

int main(int argc, char **argv)
{  
    long int size;
    void *data;

    FILE *fd = fopen("test.wav", "rb");
    if (fd == NULL) {
        printf("File is not exist!\n");
        return -1;
    }

    size = file_size(fd);

    data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "failed to allocate frames\n");
        fclose(fd);
        return 0;
    }

    fread(data, 1, size, fd);
    fclose(fd);

    hex_dump(data, size);

    return 0;
}
