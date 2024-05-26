#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

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