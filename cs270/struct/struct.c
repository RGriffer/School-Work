/* CS270 
 *
 * Author: Your name here
 * Date:   2/12/2020
 */

#include "struct.h"
#include<stdio.h>
#include <stdlib.h>
/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
    Student* tempstudent = malloc(sizeof(Student));
    scanf("%s", tempstudent->firstName);
    scanf("%f", &(tempstudent->qualityPoint));
    scanf("%d", &(tempstudent->numCredits));
    *slot = tempstudent;
}

void displayStudent(Student s)
{
    float gpa = s.qualityPoint / s.numCredits;
    printf("%s, %.2f\n", s.firstName, gpa); 
}
