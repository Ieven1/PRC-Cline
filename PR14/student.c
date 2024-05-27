#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void* StudentInfo(void *student) {
    struct Student *stud = student;
    printf("Фамилия: %s\n", stud->lastName);
    printf("Имя: %s\n", stud->firstName);
    printf("Пол: %c\n", stud->gender);
    printf("Возраст: %d\n", stud->age);
    printf("Группа: %s\n", stud->group);
    printf("Оценка по математике: %.1f\n", stud->mathGrade);
    printf("Оценка по физике: %.1f\n", stud->physicsGrade);
    printf("Оценка по химии: %.1f\n", stud->chemistryGrade);
    return NULL;
}
FILE* openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        exit(1);
    }
    return file;
}

void* Student_init(void *student, const char *lastName, const char *firstName,
                   char gender, int age, const char *group, float mathGrade, float physicsGrade, float chemistryGrade) {
    struct Student *stud = student;
    strcpy(stud->lastName, lastName);
    strcpy(stud->firstName, firstName);
    stud->gender = gender;
    stud->age = age;
    strcpy(stud->group, group);
    stud->mathGrade = mathGrade;
    stud->physicsGrade = physicsGrade;
    stud->chemistryGrade = chemistryGrade;
    stud->StudentInfo = StudentInfo;

    return NULL;
}

struct Node* createNode(void *student) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = *((struct Student*)student);
    newNode->next = NULL;
    return newNode;
}

void insertNode(void *some_data) {
    struct tmp {
        void** head;
        void *student;
    };
    struct tmp* my_data = some_data;
    void** head = my_data->head;
    void* student = my_data->student;
    struct Node* newNode = createNode(student);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *((struct Node**)head);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayStudentList(void *head) {
    struct Node* temp = head;
    while (temp != NULL) {
        temp->data.StudentInfo(&temp->data);
        printf("\n");
        temp = temp->next;
    }
}

void sortStudentsByChemistryGrade(void **head) {
    if (*head == NULL || (*((struct Node**)head))->next == NULL) {
        return ;
    }

    struct Node* sortedList = NULL;
    struct Node* current = *((struct Node**)head);
    while (current != NULL) {
        struct Node* nextNode = current->next;
        if (sortedList == NULL || sortedList->data.mathGrade <= current->data.mathGrade) {
            current->next = sortedList;
            sortedList = current;
        } else {
            struct Node* temp = sortedList;
            while (temp->next != NULL && temp->next->data.mathGrade > current->data.mathGrade) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }
    *head = sortedList;
}

void LiberationStudentList(void *head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = temp->next;
        free(temp);
    }
}
void save_students_to_file(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file %s for writing\n", filename);
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        struct Student* student = &(current->data);
        fprintf(file, "%s %s %c %d %s %.1f %.1f %.1f\n",
                student->lastName,
                student->firstName,
                student->gender,
                student->age,
                student->group,
                student->mathGrade,
                student->physicsGrade,
                student->chemistryGrade);
        current = current->next;
    }

    fclose(file);
    printf("File %s saved successfully.\n", filename);
}

struct Node* load_students_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s for reading\n", filename);
        return NULL;
    }

    struct Node* head = NULL;
    struct Student student;

    while (fscanf(file, "%s %s %c %d %s %f %f %f",
                  student.lastName,
                  student.firstName,
                  &student.gender,
                  &student.age,
                  student.group,
                  &student.mathGrade,
                  &student.physicsGrade,
                  &student.chemistryGrade) == 8) {
        struct tmp data = { &head, &student };
        insertNode(&data);
    }

    fclose(file);
    return head;
}
