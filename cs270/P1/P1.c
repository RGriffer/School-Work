// P1 Assignment
// Author: Ryan Griffin
// Date:   1/24/2020
// Class:  CS270
// Email:  rgriffer@colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// example of a global array
int exampleGlobalArray[2];
double input[4];
double output[4];

// this function can be used as a guide for the funtions you will implement
void computeSphere(double radius, double *addressOfVolume)
{
    // Compute volume
    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);

    // Dereference pointer to return result
    *addressOfVolume = result;
}

void computeCircle(double radius, double *addressOfArea)
{
    double result = 3.141593 * radius * radius;

    *addressOfArea = result;
}

void computeTriangle(double side, double *addressOfArea)
{
    double result = 0.433013 * side * side;

    *addressOfArea = result;
}

void computeSquare(double side, double *addressOfArea) 
{
    double result = side * side;

    *addressOfArea = result;
}

void computePentagon(double side, double *addressOfArea)
{
    double result = 1.720477 * side * side;

    *addressOfArea = result;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 5) {
        printf("usage: ./P1 <double> <double> <double> <double>\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
    input[0] = atof(argv[1]);
    input[1] = atof(argv[2]);
    input[2] = atof(argv[3]);
    input[3] = atof(argv[4]);
    
    // Local variable
    //double area1;
    //double area2;
    //double area3;
    //double area4;

    // Call function
    //computeSphere(radius, &volume);
    computeCircle(input[0], &output[0]);
    computeTriangle(input[1], &output[1]);
    computeSquare(input[2], &output[2]);
    computePentagon(input[3], &output[3]);
    // Print volume
    printf("CIRCLE, radius = %.5f, area = %.5f.\n", input[0], output[0]);
    printf("TRIANGLE, length = %.5f, area = %.5f.\n", input[1], output[1]);
    printf("SQUARE, length = %.5f, area = %.5f.\n", input[2], output[2]);
    printf("PENTAGON, length = %.5f, area = %.5f.\n", input[3], output[3]);

    // Return success
    return EXIT_SUCCESS;
}

