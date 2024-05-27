void save_students_to_file(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Не удалось открыть файл для записи");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        if (fwrite(&(current->data), sizeof(struct Student), 1, file) != 1) {
            perror("Ошибка при записи в файл");
            fclose(file);
            return;
        }
        current = current->next;
    }

    if (fclose(file) != 0) {
        perror("Ошибка при закрытии файла после записи");
    } else {
        printf("Файл %s успешно сохранен.\n", filename);
    }
}

struct Node* load_students_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Не удалось открыть файл для чтения");
        return NULL;
    }

    struct Node* head = NULL;
    struct Student student;

    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        struct tmp data = { &head, &student };
        insertNode(&data);
    }

    if (ferror(file)) {
        perror("Ошибка при чтении из файла");
    }

    if (fclose(file) != 0) {
        perror("Ошибка при закрытии файла после чтения");
    }

    return head;
}
