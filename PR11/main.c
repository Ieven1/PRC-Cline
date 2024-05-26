#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    char *lastName;
    char *firstName;
    char *gender;
    int age;
    char *group;
    float mathGrade;
    float physicsGrade;
    float chemistryGrade;
    void (*infoOutput )(struct Student* Student);
};

struct Tree {
    struct Student **data;
    struct Tree* left;
    struct Tree* right;
    int size;
    void (*addNode)(struct Tree *node, struct Student *data);
    void (*clear)(struct Tree *node);
    void (*TreeOutPut)(struct Tree* tree);
};

void addTreeNode(struct Tree *node, struct Student *data);
void treeClear(struct Tree *node);
void TreeOutPut(struct Tree*);

struct Tree *treeInit(struct Student *data) {
    struct Tree *result = malloc(sizeof(struct Tree));
    result->data = malloc(sizeof(struct Student*));
    result->size = 1;
    result->data[0] = data;
    result->left = NULL;
    result->right = NULL;
    result->clear = treeClear;
    result->addNode = addTreeNode;
    result->TreeOutPut = TreeOutPut;
    return result;
};

void TreeOutPut(struct Tree* node){
    if(node == NULL) {
        return;
    }

    for(int i = 0; i < node->size; i++) {
            node->data[i]->infoOutput(node->data[i]);
            }


    TreeOutPut(node->left);
    TreeOutPut(node->right);
}

void addTreeNode(struct Tree *node, struct Student *data) {
    if(node->data[0]->mathGrade < data->mathGrade){
        if(node->left == NULL) {
            node->left = treeInit(data);
            return;
        }
        node->left->addNode(node->left, data);
        return;
    } else if(node->data[0]->mathGrade > data->mathGrade) {
        if(node->right == NULL) {
            node->right = treeInit(data);
            return;
        }
        node->right->addNode(node->right, data);
        return;
    } else if(node->data[0]->mathGrade == data->mathGrade) {
        node->size++;
        node->data = realloc(node->data, node->size * sizeof(struct Student*));
        node->data[node->size - 1] = data;
        return;
    }
}

void treeClear(struct Tree* node) {
    if(node->left == NULL)
        free(node->left);
    if(node->right == NULL)
        free(node->right);

    for (int i = 0; i < node->size; i++) {
        free(node->data[i]);
    }
    free(node->data);
    free(node);
}


void infoOutput(struct Student *student) {
    printf("Фамилия: %s\n", student->lastName);
    printf("Имя: %s\n", student->firstName);
    printf("Пол: %s\n", student->gender);
    printf("Возраст: %d\n", student->age);
    printf("Группа: %s\n", student->group);
    printf("Отметка по математике: %f\n", student->mathGrade);
    printf("Отметка по физике: %f\n", student->physicsGrade);
    printf("Отметка по химии: %f\n", student->chemistryGrade);
    printf("\n");
}

struct Student* initStudent(char *lastName, char *firstName, char *gender, int age, char *group, float mathGrade, float physicsGrade, float chemistryGrade) {
    struct Student* result = malloc(sizeof(struct Student));
    result->lastName = lastName;
    result->firstName = firstName;
    result->gender = gender;
    result->age = age;
    result->group = group;
    result->mathGrade = mathGrade;
    result->physicsGrade = physicsGrade;
    result->chemistryGrade = chemistryGrade;
    result->infoOutput = infoOutput;
    return result;
};

int main() {
    system("chcp 65001");

    struct Student* student1 = initStudent( "Иванов", "Иван", "M", 16, "Группа1", 5.0f, 4.9f, 5.0f);
    struct Student* student2 = initStudent( "Петров", "Петр", "M", 17, "Группа2", 3.7f, 4.1f, 5.0f);
    struct Student* student3 = initStudent( "Сидорова", "Мария", "F", 17, "Группа1", 4.5f, 3.5f, 4.8f);

    struct Tree* students[25];
    students[0] = treeInit(student1);
    students[0]->addNode(students[0],student2);
    students[0]->addNode(students[0],student3);

    students[0]->TreeOutPut(students[0]);

    students[0]->clear(students[0]);

    return 0;
}