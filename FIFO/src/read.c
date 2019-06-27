#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <assert.h>
#include <sys/select.h>

#define MAX_BUFFER 256
  
int main() 
{
    FILE *fp = NULL;
    int fd;
    char buff[MAX_BUFFER];
    const char *myfifo = "/tmp/myfifo";

    for (;;) {
        fd = open(myfifo, O_RDONLY | O_NONBLOCK);
        // fdopen(): transform fd into fp
        fp = fdopen(fd, "r");

        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        tv.tv_sec  = 2;
        tv.tv_usec = 0;

        // int select(int numfds, fd_set *readfds, 
        //            fd_set *writefds, fd_set *exceptfds, 
        //            struct timeval *timeout);
        ret = select(fd + 1, &fds, NULL, NULL, &tv);
        if (-1 == ret) {
            printf("continue\n");
            continue;
        }
        if (0 == ret) {
            printf("End!\n");
            break;
        }
        
        while(fgets(buff, MAX_BUFFER, fp) != NULL) 
            printf("Read: %s", buff);

        fclose(fp);
    }

    return 0; 
} 
