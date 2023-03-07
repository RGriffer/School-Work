#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv){
    int num = atoi(argv[1]);
    int i, j, limit=2100000, runningTotal=0;
    int composite = 0;
    int test;
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
  return (test);
}
