#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* StudentInfo(void *student) {
    struct Student *stud = student;
    printf("Фамилия: %s\n", stud->lastName);
    printf("Имя: %s\n", stud->firstName);
    printf("Пол: %s\n", stud->gender);
    printf("Возраст: %d\n", stud->age);
    printf("Группа: %s\n", stud->group);
    printf("Оценка по математике: %.1f\n", stud->mathGrade);
    printf("Оценка по физике: %.1f\n", stud->physicsGrade);
    printf("Оценка по химии: %.1f\n", stud->chemistryGrade);
    return NULL;
}

void* Student_init(void *student, const char *lastName, const char *firstName, const char *gender, int age, const char *group, float mathGrade, float physicsGrade, float chemistryGrade) {
    struct Student *stud = student;
    stud->lastName = strdup(lastName);
    stud->firstName = strdup(firstName);
    stud->gender = strdup(gender);
    stud->age = age;
    strcpy(stud->group, group);
    stud->mathGrade = mathGrade;
    stud->physicsGrade = physicsGrade;
    stud->chemistryGrade = chemistryGrade;
    stud->StudentInfo = StudentInfo;

    return stud;
}

struct Node* createNode(void *student) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        exit(EXIT_FAILURE);
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

void LiberationStudentList(void *head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = temp->next;
        free(temp->data.lastName);
        free(temp->data.firstName);
        free(temp->data.gender);
        free(temp);
    }
}

void save_students_to_file(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Не удалось открыть файл %s для записи\n", filename);
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        size_t lastNameLength = strlen(current->data.lastName) + 1;
        size_t firstNameLength = strlen(current->data.firstName) + 1;
        size_t genderLength = strlen(current->data.gender) + 1;

        fwrite(&lastNameLength, sizeof(size_t), 1, file);
        fwrite(current->data.lastName, sizeof(char), lastNameLength, file);
        fwrite(&firstNameLength, sizeof(size_t), 1, file);
        fwrite(current->data.firstName, sizeof(char), firstNameLength, file);
        fwrite(&genderLength, sizeof(size_t), 1, file);
        fwrite(current->data.gender, sizeof(char), genderLength, file);
        fwrite(&(current->data.age), sizeof(int), 1, file);
        fwrite(current->data.group, sizeof(char), 20, file);
        fwrite(&(current->data.mathGrade), sizeof(float), 1, file);
        fwrite(&(current->data.physicsGrade), sizeof(float), 1, file);
        fwrite(&(current->data.chemistryGrade), sizeof(float), 1, file);

        current = current->next;
    }

    fclose(file);
    printf("Файл %s успешно сохранен.\n", filename);
}

struct Node* load_students_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Не удалось открыть файл %s для чтения\n", filename);
        return NULL;
    }

    struct Node* head = NULL;
    struct Student student;

    while (1) {
        size_t lastNameLength;
        size_t firstNameLength;
        size_t genderLength;

        if (fread(&lastNameLength, sizeof(size_t), 1, file) != 1) break;
        student.lastName = malloc(lastNameLength);
        if (student.lastName == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(EXIT_FAILURE);
        }
        fread(student.lastName, sizeof(char), lastNameLength, file);

        if (fread(&firstNameLength, sizeof(size_t), 1, file) != 1) break;
        student.firstName = malloc(firstNameLength);
        if (student.firstName == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(EXIT_FAILURE);
        }
        fread(student.firstName, sizeof(char), firstNameLength, file);

        if (fread(&genderLength, sizeof(size_t), 1, file) != 1) break;
        student.gender = malloc(genderLength);
        if (student.gender == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(EXIT_FAILURE);
        }
        fread(student.gender, sizeof(char), genderLength, file);

        fread(&(student.age), sizeof(int), 1, file);
        fread(student.group, sizeof(char), 20, file);
        fread(&(student.mathGrade), sizeof(float), 1, file);
        fread(&(student.physicsGrade), sizeof(float), 1, file);
        fread(&(student.chemistryGrade), sizeof(float), 1, file);

        struct tmp data = { &head, &student };
        insertNode(&data);
    }

    fclose(file);
    return head;
}
