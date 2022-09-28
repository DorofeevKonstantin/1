#include <stdio.h>
#include <Windows.h>

#define EXIT_NUMBER 0

int main(void) {
    int number;
    do {
        printf_s("Enter an integer number: ");
        scanf_s("%d", &number);
        if (number != EXIT_NUMBER) {
            if (number % 2) {
                printf_s("Odd");
            }
            else {
                printf_s("Even");
            }
            printf_s("\n");
        }
    } while (number != EXIT_NUMBER);

    // теоретически можно (но не рекомендуемо)
    // написать следующее решение, которое будет работать
    /*
    do {
        printf_s("Enter an integer number: ");
        scanf_s("%d", &number);
    } while (number != EXIT_NUMBER && printf_s(number % 2 ? "Odd\n" : "Even\n"));
    */
    // подумайте почему и как оно работает (здесь используется "тернарный оператор")

    system("pause");
    return 0;
}