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

int main(int argc, char** argv) {
    int num = atoi(argv[2]);
    char* totalName = "Shared_mem_total";
    int shm_fd;
    //open pipe to share memory
    shm_fd =shm_open(totalName, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1){
        printf("Pipe Failed\n");
        exit(-1);
    }
    int *ptr = mmap(0, 32, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED){//check if map failed
        printf("Map Failed\n");
        exit(-1);
    }
    int sum = 0;
    for(int i = 1; i <= num; i++){
        sum += i;
    }
    printf("Total[%d] : Sum = %d\n", getpid(), sum);
    
    *ptr = sum;
    return 0;
}
