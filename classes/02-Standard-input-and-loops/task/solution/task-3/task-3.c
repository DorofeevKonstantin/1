#include <stdio.h>
#include <Windows.h>

int main(void) {
    int lines, columns;
    char character;
    printf_s("Enter a character, height and width: ");
    scanf_s("%c %d %d", &character, 1, &lines, &columns);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf_s("%c ", character);
        }
        printf_s("\n");
    }

    system("pause");
    return 0;
}