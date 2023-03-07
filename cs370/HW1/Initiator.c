#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Enter 1 number to set the seed\n");
        return 0;
    }
    int test = atoi(argv[1]);
    printf("[Initiator]: With seed: %d\n", test);
    srand(test);
    
    float running_ratio = get_running_ratio();
    printf("[Initiator]: Running ratio: %.6f\n", running_ratio);
}
