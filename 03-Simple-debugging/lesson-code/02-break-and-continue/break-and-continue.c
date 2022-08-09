#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 20 // далее в коде при компиляции вместо 'MAX_NUMBER' будет подставляться указанное число

int main(void) {
    int degree, number, root;
    printf_s("Enter a number and degree: ");
    scanf_s("%d%d", &number, &degree);

    // выведем все нечетные числа в промежутке [1, number] используя оператор continue
    for (int i = 1; i <= number; ++i) {
        if (i % 2 == 0) // если в if лишь одна инструкция -- можно не ставить фигурные скобки
            continue;   // то же самое работает и с циклами (рекомендуется не злоупотреблять этим)
        printf_s("%d ", i);
    }
    printf_s("\n");


    // теперь наша задача: найти корень степени degree из числа number
    // ищем число, которое в степени degree даёт number
    root = 1;
    // сначала проверяем находится ли искомое число в промежутке [0, MAX_NUMBER]
    for (int i = 0; i < degree; ++i) {
        root *= MAX_NUMBER;
    }
    if (root >= number) {
        // перебираем числа от 0 до MAX_NUMBER
        for (root = 0; root <= MAX_NUMBER; ++root) {
            int tmp = 1;
            // считаем root в степени degree
            for (int i = 0; i < degree; ++i) {
                tmp *= root;
            }
            // если нашли число, которое даёт в степени нужный результат -- завершаем поиск
            if (tmp == number)
                break;         
        }
        if (root > MAX_NUMBER) {
            printf_s("There is not integer root\n");
        }
        else {
            printf_s("The root is %d\n", root);
        }
    }
    else {
        printf_s("ERROR: Root is not in range [0, %d]!\nExit with error code 1\n", MAX_NUMBER);
        return 1;
    }

    system("pause");
    return 0;
}