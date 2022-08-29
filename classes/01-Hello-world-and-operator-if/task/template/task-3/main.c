#include <stdio.h>
#include <locale.h>
#include <Windows.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU");

    // ввод числа
    int number = 0;
    printf_s("Enter an integer: ");
    if (!scanf_s("%d", &number)) {
        printf_s("ERROR: wrong input, exit with code 1");
        return 1;
    }

    // ...

    system("pause");
    return 0;
}
