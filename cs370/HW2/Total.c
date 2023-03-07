#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    int num = atoi(argv[1]);
    int sum = 0;
    for(int i = 1; i <= num; i++){
        sum += i;
    }
    printf("Total[%d] : Sum = %d\n", getpid(), sum);
    return sum;
}
