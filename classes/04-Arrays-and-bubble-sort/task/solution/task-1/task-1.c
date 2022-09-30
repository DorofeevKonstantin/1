#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // инициализируем массивы
    int iArr[] = { 2, 3, 5, 7, 11, 13, 17 };
    char chArr[] = { 'c', 'h', 'a', 'r' };

    // выводим в консоль
    for (int i = 0; i < sizeof(iArr) / sizeof(iArr[0]); ++i) {
        printf_s("%d ", iArr[i]);
    }
    printf_s("\n");

    for (int i = 0; i < sizeof(chArr); ++i) {
        printf_s("%c", chArr[i]);
    }
    printf_s("\n");

    system("pause");
    return 0;
}