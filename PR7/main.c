#include <stdio.h>

int main() {
    char str[100];
    int i = 0;
    int toUpper = 1;

    printf("Введите текст: ");
    fgets(str, sizeof(str), stdin);

    while (str[i] != '\0') {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            if (toUpper) {
                if (str[i] >= 'a' && str[i] <= 'z')
                    str[i] -= 32;
            } else {
                if (str[i] >= 'A' && str[i] <= 'Z')
                    str[i] += 32;
            }
            toUpper = !toUpper;
        }
        i++;
    }

    printf("Текст с измененным регистром: %s\n", str);

    return 0;
}
