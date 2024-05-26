#ifndef Praktika13_STUDENT_H
#define Praktika13_STUDENT_H

struct Student {
    char lastName[50];
    char firstName[50];
    char gender;
    int age;
    char group[20];
    float mathGrade;
    float physicsGrade;
    float chemistryGrade;
    void* (*StudentInfo)(void*);
};

void* StudentInfo(void*);

void* Student_init(void *student, const char *lastName, const char *firstName,
                   char gender, int age, const char *group, float mathGrade, float physicsGrade, float chemistryGrade);
void saveStudentToFile(const struct Student *student, const char *filename);
void readStudentFromFile(const char *filename);

struct Node {
    struct Student data;
    struct Node* next;
};


struct Node* createNode(void *student);
void insertNode(void *some_data);
void displayStudentList(void *head);
void sortStudentsByChemistryGrade(void **head);
void LiberationStudentList(void *head);
#endif

