#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
        exit(EXIT_FAILURE);
    }
    return file;
}

void* Student_init(void *student, const char *lastName, const char *firstName, char gender, int age, const char *group, float mathGrade, float physicsGrade, float chemistryGrade) {
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
    if (newNode == NULL) {
        perror("Ошибка выделения памяти для нового узла");
        exit(EXIT_FAILURE);
    }
    if (student == NULL) {
        perror("Ошибка: передан NULL указатель в createNode");
        free(newNode);
        return NULL;
    }
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
        return;
    }

    struct Node* sortedList = NULL;
    struct Node* current = *((struct Node**)head);
    while (current != NULL) {
        struct Node* nextNode = current->next;
        if (sortedList == NULL || sortedList->data.chemistryGrade <= current->data.chemistryGrade) {
            current->next = sortedList;
            sortedList = current;
        } else {
            struct Node* temp = sortedList;
            while (temp->next != NULL && temp->next->data.chemistryGrade > current->data.chemistryGrade) {
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

void saveStudentToFile(const struct Student *student, const char *filename) {
    if (student == NULL || filename == NULL) {
        perror("Ошибка: передан NULL указатель в saveStudentToFile");
        return;
    }
    FILE *file = openFile(filename, "ab");
    if (fwrite(student, sizeof(struct Student), 1, file) != 1) {
        perror("Ошибка записи студента в файл");
    }
    fclose(file);
}

struct Student* readStudentsFromFile(const char *filename, int *numStudents) {
    if (filename == NULL || numStudents == NULL) {
        perror("Ошибка: передан NULL указатель в readStudentsFromFile");
        return NULL;
    }
    FILE *file = openFile(filename, "rb");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == -1) {
        perror("Ошибка получения размера файла");
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

    int studentCount = fileSize / sizeof(struct Student);
    struct Student *students = malloc(studentCount * sizeof(struct Student));
    if (students == NULL) {
        perror("Ошибка выделения памяти для студентов");
        fclose(file);
        return NULL;
    }

    if (fread(students, sizeof(struct Student), studentCount, file) != studentCount) {
        perror("Ошибка чтения студентов из файла");
        free(students);
        fclose(file);
        return NULL;
    }
    *numStudents = studentCount;

    fclose(file);
    return students;
}

void clearFile(const char *filename) {
    FILE *file = openFile(filename, "wb");
    fclose(file);
}
