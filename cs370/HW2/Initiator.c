#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 
 * List of Current things to do:
 *      -Find out why not returning correct number for exit status/why return same number for all
 *      -Fill out the Read me
 *      -Add Meaningful comments
 */

int pell(char* buf){                //create pell sequence thread here
        pid_t pid = fork();         //fork it baby
        int status;                 
        int exitStat = 0;
        if(pid == 0) {              //check that pid is the child
           execlp("./Pell", "./Pell", buf, NULL); 
        }
        if(pid > 0) {               //check that pid is the parent
            printf("Initiator[%d]: Forked process with ID %d.\n", getpid(), pid);
            printf("Initiator[%d]: Waiting for Process [%d].\n", getpid(), pid);
            wait(&status);          //wait! no!
            exitStat = WEXITSTATUS(status);
            printf("Initiator: Child process %d returned %d.\n", pid, exitStat);
            return exitStat;
        }
}
//this is pretty much just the above function but copy and pasted with the executable changed. 
int composite(char* buf){
        pid_t pid = fork();
        int status;
        int exitStat = 0;
        if(pid == 0) {
           execlp("./Composite", "./Composite", buf, NULL); 
        }
        if(pid > 0) {
            printf("Initiator[%d]: Forked process with ID %d.\n", getpid(), pid);
            printf("Initiator[%d]: Waiting for Process [%d].\n", getpid(), pid);
            wait(&status);
            exitStat = WEXITSTATUS(status);
            printf("Initiator: Child process %d returned %d.\n", pid, exitStat);
            return exitStat;
        }
}
//this is pretty much just the first function but copy and pasted with the executable changed. 
int total(char* buf){
        pid_t pid = fork();
        int status;
        int exitStat = 0;
        if(pid == 0) {
           execlp("./Total", "./Total", buf, NULL); 
        }
        if(pid > 0) {
            printf("Initiator[%d]: Forked process with ID %d.\n", getpid(), pid);
            printf("Initiator[%d]: Waiting for Process [%d].\n", getpid(), pid);
            wait(&status);
            exitStat = WEXITSTATUS(status);
            printf("Initiator: Child process %d returned %d.\n", pid, exitStat);
            return exitStat;
        }
        
}


int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r"); //open the file in read mode
    char buf[256];                  //create a character buffer
    while(fgets(buf, sizeof(buf), fp)) { //while there are lines to be read
        //DO PELL THREAD HERE
        int p = pell(buf);
        
        //DO COMPOSITE THREAD HERE
        int c = composite(buf);
        
        //DO TOTAL THREAD HERE
        int t = total(buf);
        
        //Final print statements
        printf("Initiator: Pell: %d\n", p);
        printf("Initiator: Composite: %d\n", c);
        printf("Initiator: total Count: %d\n", t); 
    }
}

