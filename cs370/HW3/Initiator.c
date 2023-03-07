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
#define READ 0
#define WRITE 1


int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r"); //open the file in read mode
    char buf[256];                  //create a character buffer
        int fd[2];
        char* fn;
        if(pipe(fd) == -1){
            fprintf(stderr, "Pipe Failed.\n");
            return 1;
        }
        
        int readerSTAT;
        pid_t pid = fork();
        if(pid == 0){
            char val[256];
            sprintf(val, "%d", fd[WRITE]);
            close(fd[READ]);
            execlp("./Reader", "Reader",  argv[1], val, NULL);
        } 
        wait(&readerSTAT);
        
        //get the information from reader!
        char fromReader[256];
        close(fd[WRITE]);
        read(fd[READ], fromReader, strlen(fromReader));
        close(fd[READ]);
        
        printf("Initiator[%d]: contents read from the read end pipe: %s\n", pid, fromReader);
        
        char* pellName = "Shared_mem_pell";
        char* compositeName = "Shared_mem_composite";
        char* totalName = "Shared_mem_total";
        
        //open the shared memory
        int shmPell = shm_open(pellName, O_CREAT | O_RDWR, 0666);
        int shmComposite = shm_open(compositeName, O_CREAT | O_RDWR, 0666);
        int shmTotal = shm_open(totalName, O_CREAT | O_RDWR, 0666);
        
        //truncate to 32 bytes
        ftruncate(shmPell, 32);
        ftruncate(shmComposite, 32);
        ftruncate(shmTotal, 32);
        
        //mmap pointers
        int *pellPtr = mmap(0, 32, PROT_READ, MAP_SHARED, shmPell, 0);
        int *compositePtr = mmap(0, 32, PROT_READ, MAP_SHARED, shmComposite, 0);
        int *totalPtr = mmap(0, 32, PROT_READ, MAP_SHARED, shmTotal, 0);
        
        printf("Initiator[%d] : Created Shared memory \"%s\" with FD: %d\n", pid, pellName, shmPell);
        printf("Initiator[%d] : Created Shared memory \"%s\" with FD: %d\n", pid, compositeName, shmComposite);
        printf("Initiator[%d] : Created Shared memory \"%s\" with FD: %d\n", pid, totalName, shmTotal);
        
        //command and names used to loop through programs
        char* names[3];
        names[0] = pellName;
        names[1] = compositeName;
        names[2] = totalName;
        
        char* command[3];
        command[0] = "./Pell";
        command[1] = "./Composite";
        command[2] = "./Total";
        pid_t* pids = (pid_t*)malloc(3 * sizeof(pid_t));  //store PID for later
        
        //run programs
        for(int i = 0; i < 3; i++) {
            pid_t pid = fork();
            if(pid < 0) {
                return -1;
            }
            if(pid == 0) {
                execlp(command[i], command[i], names[i], fromReader, NULL);
            }
            if(pid > 0) {
                pids[i] = pid;
            }
        }
        //wait for all to finish
        for(int i = 0; i < 3; i++) {
            int status;
            waitpid(pids[i], &status, 0);
        }
        free(pids);
        
        //retrieve values from shared memory
        int pellReturn = *pellPtr;
        int compositeReturn = *compositePtr;
        int totalReturn = *totalPtr;
        
        //print statements
        printf("Initiator[%d]: Pell last number: %d\n", pid, pellReturn);
        printf("Initiator[%d]: Composite last number: %d\n", pid, compositeReturn);
        printf("Initiator[%d]: Total last number: %d\n", pid, totalReturn);
        //Unlink memory
        if((shm_unlink(pellName) == -1) || (shm_unlink(compositeName) == -1) || (shm_unlink(totalName) == -1)){
            return -1;
        }
        
}

