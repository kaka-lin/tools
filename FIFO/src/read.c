#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <assert.h>
#include <sys/select.h>
  
int main() 
{
    int ret;
    FILE *fp;  
    char buff[255];
    const char *myfifo = "/tmp/myfifo";
    fd_set fds;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;

    while (1) {
        fp = fopen(myfifo, "r");
        FD_ZERO(&fds);
        FD_SET(fileno(fp), &fds);

        ret = select(fileno(fp) + 1, &fds, NULL, NULL, &tv);
        if (-1 == ret) {
            printf("continue\n");
            continue;
        }
        if (0 == ret) {
            printf("break\n");
            break;
        }
 
        if(fgets(buff, 255, fp) != NULL) 
            printf("Read: %s", buff);

        fclose(fp);

        if (!strncmp(buff, "test10", 6))
            break;
    }

    return 0; 
} 
