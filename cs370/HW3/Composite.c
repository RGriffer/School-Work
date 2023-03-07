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
    int num = atoi(argv[2]);
    int i, j, limit=2100000, runningTotal=0;
    int composite = 0;
    int test;
    char* compositeName = "Shared_mem_composite";
    int shm_fd;
    //open pipe to share memory
    shm_fd =shm_open(compositeName, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1){
        printf("Pipe Failed\n");
        exit(-1);
    }
    int *ptr = mmap(0, 32, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED){//check if map failed
        printf("Map Failed\n");
        exit(-1);
    }
    printf("Composite[%d]: First %d composite numbers are:\n", getpid(), num);
    while(runningTotal < num) {
        for(i = 1;i < limit;i++){ 
            if(runningTotal == num) {
                i--;
                break;
            }
            composite = 0;
            for(j = i-1; j > 1 ; j--){
                if(i%j == 0)
                    composite = 1;
            }
        if(composite == 1) {
            test = i;
            runningTotal++;
            printf("%d, ", i);
        }
    }
    printf("\n");
    }
    
    *ptr = i;
    return 0;
}
