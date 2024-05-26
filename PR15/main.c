#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int main() {
    system("chcp 65001");

    void* head = NULL;

    struct Student student1, student2, student3, student4;
    Student_init(&student1, "Иванов", "Иван", 'M', 16, "Группа1", 5.0, 4.9, 1.4);
    Student_init(&student2, "Петров", "Петр", 'M', 17, "Группа2", 3.7, 4.1, 3.2);
    Student_init(&student3, "Сидорова", "Мария", 'F', 17, "Группа1", 4.5, 3.5, 4.3);
    Student_init(&student4, "Алексеева", "Соня", 'F', 23, "Группа1", 4.2, 4.6, 5.0);

    struct tmp {
        void** head;
        void *student;
    };

    struct tmp temp1 = { &head, &student1 };
    struct tmp temp2 = { &head, &student2 };
    struct tmp temp3 = { &head, &student3 };
    struct tmp temp4 = { &head, &student4 };

    insertNode(&temp1);
    insertNode(&temp2);
    insertNode(&temp3);
    insertNode(&temp4);

    printf("Исходные данные:\n");
    displayStudentList(head);

    const char *filename = "D:\\Ci\\df.txt";
    clearFile(filename);

    saveStudentToFile(&student1, filename);
    saveStudentToFile(&student2, filename);
    saveStudentToFile(&student3, filename);
    saveStudentToFile(&student4, filename);

    sortStudentsByChemistryGrade(&head);

    printf("\nОтсортировано по оценке по математике:\n");
    displayStudentList(head);

    LiberationStudentList(head);

    int numStudents = 0;
    struct Student* students = readStudentsFromFile(filename, &numStudents);

    printf("Содержимое файла:\n");
    for (int i = 0; i < numStudents; i++) {
        StudentInfo(&students[i]);
        printf("\n");
    }

    free(students);

    return 0;
}
