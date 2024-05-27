#ifndef PRAKTIKA13_STUDENT_H
#define PRAKTIKA13_STUDENT_H

struct Student {
    char *lastName;
    char *firstName;
    char *gender;
    int age;
    char group[20];
    float mathGrade;
    float physicsGrade;
    float chemistryGrade;
    void* (*StudentInfo)(void*);
};


void* StudentInfo(void* student);
void* Student_init(void *student, const char *lastName, const char *firstName, char gender, int age, const char *group, float mathGrade, float physicsGrade, float chemistryGrade);
void save_students_to_file(struct Node* head, const char* filename);
struct Node* load_students_from_file(const char* filename);

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
