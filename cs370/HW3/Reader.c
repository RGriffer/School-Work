#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    //open pipe
    char dog[256];
    int fd = atoi(argv[2]);
    char* fn = argv[1];
    int running_total = 0;
    //open file
    FILE* myFile = fopen(fn, "r");

    char buf[256];                  //create a character buffer
    while(fgets(buf, sizeof(buf), myFile)) { //while lines to be read
        
        running_total += atoi(buf); //add to running total
    }
    sprintf(dog, "%d", running_total);
    //printf("%d\n %s\n", running_total, dog);
    write(fd, dog, strlen(dog)+1); //write to pipe
    close(fd);
    return 0;
}
