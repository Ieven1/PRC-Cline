#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "stack.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))


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

    int a = 5, b = 10;
    int max_value = MAX(a, b);
    printf("Максимальное значение: %d\n", max_value);

    return 0;
}
