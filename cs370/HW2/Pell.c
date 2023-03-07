#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv){
    int num = atoi(argv[1]);
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
    return c;
}
