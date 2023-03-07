#include <stdlib.h>
#include <stdio.h>
#include "Worker.h"

float get_running_ratio() {
    int maxDivisibleElements = 0;
    int maxCountIteration = 0;
    float running_total = 0;
    int iterationNumber = random_in_range(50, 100); 
    printf("[Worker]: Number of iterations is: %d\n", iterationNumber); 
    for(int i = 1; i <= iterationNumber; i++) {                                          
        int size = random_in_range(100, 150);
        int *myArray = (int *)malloc(sizeof(int)*size);                  
        
        for (int j = 0; j < size; j++) {
            myArray[j] = random_in_range(1, 100);
        }
        
        int divisor = random_in_range(5,15);
        int temp = get_divisibility_count(myArray, size, divisor);
        running_total += ratio(temp, size);
        if(temp > maxDivisibleElements) { maxDivisibleElements = temp; maxCountIteration = i; }
        //FREE MEMORY ON LINE BELOW THIS!!!!!!
        free(myArray);                                                                                 
    }
    printf("[Worker]: Iteration with maximum fully divisible elements is %d\n", maxCountIteration);
    return (float)running_total / iterationNumber;
}

int random_in_range(int lower_bound, int upper_bound) {
    int num = (rand() % (upper_bound - lower_bound)) + lower_bound;
    return num;
}

int get_divisibility_count(int *array, int arraySize, int randomDividend) {
    int total = 0;
    for(int i = 0; i < arraySize; i++) {
        if(array[i] % randomDividend == 0) {
            total++;
        }
    }
    return total;
}

float ratio (float a, float b){
  return a/(b-a);
}
