#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
};

void displayStudentList(struct Node* head);
void sortStudentsByMathGrade(struct Node** head);
void initStudent(struct Student* student, const char* lastName, const char* firstName,
    char gender, int age, const char* group,
    float mathGrade, float physicsGrade, float chemistryGrade);

void insertNode(struct Node** head, struct Student student) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = student;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayStudentList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("Фамилия: %s\n", temp->data.lastName);
        printf("Имя: %s\n", temp->data.firstName);
        printf("Возраст: %d\n", temp->data.age);
        printf("Оценка по математике: %.1f\n", temp->data.mathGrade);
        printf("Оценка по физике: %.1f\n", temp->data.physicsGrade);
        printf("Оценка по химии: %.1f\n", temp->data.chemistryGrade);
        printf("\n");
        temp = temp->next;
    }
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

void sortStudentsByMathGrade(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node* sortedList = NULL;

    while (*head != NULL) {
        struct Node* current = *head;
        *head = (*head)->next;

        if (sortedList == NULL || current->data.mathGrade >= sortedList->data.mathGrade) {
            current->next = sortedList;
            sortedList = current;
        }
        else {
            struct Node* temp = sortedList;
            while (temp->next != NULL && temp->next->data.mathGrade > current->data.mathGrade) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    *head = sortedList;
}

int main() {

    system("chcp 65001"); //Кодировка !!ВАЖНО!!

    struct Node* head = NULL;

    struct Student student1, student2, student3;

    initStudent(&student1, "Иванов", "Иван", 'M', 16, "Группа1", 5.0f, 4.9f, 5.0f);
    initStudent(&student2, "Петров", "Петр", 'M', 17, "Группа2", 3.7f, 4.1f, 5.0f);
    initStudent(&student3, "Сидорова", "Мария", 'F', 17, "Группа1", 4.5f, 3.5f, 4.8f);


    insertNode(&head, student1);
    insertNode(&head, student2);
    insertNode(&head, student3);


    printf("Исходные данные:\n");
    displayStudentList(head);


    sortStudentsByMathGrade(&head);


    printf("\nОтсортировано по оценке по математике:\n");
    displayStudentList(head);



    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
