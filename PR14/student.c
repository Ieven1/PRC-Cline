#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void initStudent(struct Student* student, const char* lastName, const char* firstName,
                 char gender, int age, const char* group,
                 float mathGrade, float physicsGrade, float chemistryGrade) {
    strcpy(student->lastName, lastName);
    strcpy(student->firstName, firstName);
    student->gender = gender;
    student->age = age;
    strcpy(student->group, group);
    student->mathGrade = mathGrade;
    student->physicsGrade = physicsGrade;
    student->chemistryGrade = chemistryGrade;
}