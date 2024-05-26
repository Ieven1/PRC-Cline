#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    wchar_t str[100];
    int i = 0;
    int toUpper = 1;

    wprintf(L"Введите текст: ");
    fgetws(str, sizeof(str) / sizeof(wchar_t), stdin);

    while (str[i] != L'\0') {
        if ((str[i] >= L'a' && str[i] <= L'z') || (str[i] >= L'A' && str[i] <= L'Z')) {
            if (toUpper) {
                if (str[i] >= L'a' && str[i] <= L'z')
                    str[i] -= 32;
            } else {
                if (str[i] >= L'A' && str[i] <= L'Z')
                    str[i] += 32;
            }
            toUpper = !toUpper;
        }
        i++;
    }

    wprintf(L"Текст с измененным регистром: %ls\n", str);

    FILE* file = fopen("output.txt", "w");
    if(file) {
        fwprintf(file, L"Тектс: %ls\n", str);
        fclose(file);
    }
    else {
        wprintf(L"NE VERNO\n");
        return 0;
    }

    return 0;
}