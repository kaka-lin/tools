#include <stdio.h> 
#include <string.h> 
#include <sys/stat.h>  // FIFO
#include <sys/types.h> // FIFO
#include <assert.h>
#include <unistd.h>    // sleep, usleep
  
int main() 
{ 
    FILE *fp;
    int count = 0;
    const char *myfifo = "/tmp/myfifo";
  
    // Creating the named file (FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 

    while (1) {
        count += 1;
        fp = fopen(myfifo, "w"); 
        printf("Write: test%d\n", count);
        fprintf(fp, "test%d\n", count);
        fclose(fp);

        if (count == 10)
            break;

        sleep(1);
    }

    return 0; 
}
