#include <stdio.h>
#include <Windows.h>

int main(void) {
    int number;
    printf_s("Enter a number: ");
    scanf_s("%d", &number);
    while (number) {
        int sum = 0;
        int i = 1;
        // ключевой момент алгоритма решения: проверка суммы на шаг вперед
        // т.е. !прежде! чем вывести число A нужно проверить
        // не превышает ли сумма 1 + 2 + ... + A число number
        // можно использовать вложенный while, но while требуемый по заданию уже имеется,
        // поэтому здесь показан for, решающий данную задачу:
        for (int i = 1, sum = 1; sum <= number; i += 1, sum += i) {
            printf_s("%d ", i);
            Sleep(50);
        }
        printf_s("\n");
        Sleep(1000);
        number /= 2;
    }

    system("pause");
    return 0;
}