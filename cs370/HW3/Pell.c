#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char** argv){
    char* pellName = "Shared_mem_pell";
    int shm_fd;
    //open pipe to share memory
    shm_fd = shm_open(pellName, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1){
        printf("Pipe Failed\n");
        exit(-1);
    }
    int *ptr = mmap(0, 32, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED){//check if map failed
        printf("Map Failed\n");
        exit(-1);
    }
    int num = atoi(argv[2]);
    printf("Pell[%d] : Number of terms in Pell series is %d.\n", getpid(), num);
    printf("Pell[%d] : The first %d numbers of the Pell sequence are:\n", getpid(), num);
    int a=1, b=0, c=0;
    printf("%d, ",c);
    for(int i = 1; i < num; i++) {
        c = a + (2*b);
        printf("%d, ",c);
        a = b;
        b = c;
    }
    printf("\n");
    
    //print and return when done
    //sprintf(ptr, "%d", c);
    *ptr = c;
    return 0;
}
