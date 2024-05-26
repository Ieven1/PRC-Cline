#include"student.h"
#ifndef stackh
#define stackh

void* insertNode(void* arg);
void* displayStudentList(void* arg);
void* sortStudentsByMathGrade(void* arg);

struct Node {
    struct Student data;
    struct Node* next;
    void* (*displayStudentList)(void*);
    void* (*insertNode)(void*);
    void* (*sortStudentsByMathGrade)(void* arg);
};


struct InsertArgs {
    struct Node** head;
    struct Student* student;
};

struct SortArgs {
    struct Node** head;
};

struct Node* initNode();

#endif 