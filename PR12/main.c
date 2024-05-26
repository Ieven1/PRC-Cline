#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* insertNode(void* arg);
void* displayStudentList(void* arg);
void* sortStudentsByMathGrade(void* arg);

struct Student {
    char lastName[50];
    char firstName[50];
    char gender;
    int age;
    char group[20];
    float mathGrade;
    float physicsGrade;
    float chemistryGrade;
};


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


void* insertNode(void* arg) {
    struct InsertArgs* args = (struct InsertArgs*)arg;

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = *(args->student);
    newNode->next = NULL;
    newNode->displayStudentList = &displayStudentList;

    if (*(args->head) == NULL) {
        *(args->head) = newNode;
    } else {
        struct Node* temp = *(args->head);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return NULL;
}


void* displayStudentList(void* arg) {
    struct Node* head = (struct Node*)arg;
    struct Node* temp = head;
    while (temp != NULL) {
        if (strlen(temp->data.lastName) > 0) {
            printf("Фамилия: %s\n", temp->data.lastName);
            printf("Имя: %s\n", temp->data.firstName);
            printf("Возраст: %d\n", temp->data.age);
            printf("Оценка по математике: %.1f\n", temp->data.mathGrade);
            printf("Оценка по физике: %.1f\n", temp->data.physicsGrade);
            printf("Оценка по химии: %.1f\n", temp->data.chemistryGrade);
            printf("\n");
        }
        temp = temp->next;
    }
    return NULL;
}



struct SortArgs {
    struct Node** head;
};


void* sortStudentsByMathGrade(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    struct Node** head = args->head;

    if (*head == NULL || (*head)->next == NULL) {
        return NULL;
    }

    struct Node* sortedList = NULL;

    while (*head != NULL) {
        struct Node* current = *head;
        *head = (*head)->next;

        if (sortedList == NULL || current->data.mathGrade >= sortedList->data.mathGrade) {
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
    }

    *head = sortedList;

    return NULL;
}


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


struct Node* initNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
    }
    struct Student student;
    initStudent(&student, "", "", ' ', 0, "", 0, 0, 0);

    newNode->data = student;
    newNode->next = NULL;
    newNode->displayStudentList = displayStudentList;
    newNode->sortStudentsByMathGrade = sortStudentsByMathGrade;
    newNode->insertNode = insertNode;
    return newNode;
}

int main() {
    struct Node* head = initNode();


    struct Student student1, student2, student3;
    initStudent(&student1, "Иванов", "Иван", 'M', 16, "Группа1", 5.0f, 4.9f, 5.0f);
    initStudent(&student2, "Петров", "Петр", 'M', 17, "Группа2", 3.7f, 4.1f, 5.0f);
    initStudent(&student3, "Сидорова", "Мария", 'F', 17, "Группа1", 4.5f, 3.5f, 4.8f);


    struct InsertArgs insertArgs1 = { &head, &student1 };
    head->insertNode(&insertArgs1);

    struct InsertArgs insertArgs2 = { &head, &student2 };
    head->insertNode(&insertArgs2);

    struct InsertArgs insertArgs3 = { &head, &student3 };
    head->insertNode(&insertArgs3);

    printf("Исходные данные:\n");
    head->displayStudentList(head);

    struct SortArgs sortArgs = { &head };
    sortStudentsByMathGrade(&sortArgs);

    printf("\nОтсортировано по оценке по математике:\n");
    head->displayStudentList(head);

    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
