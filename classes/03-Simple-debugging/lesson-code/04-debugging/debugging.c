#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned int number;
    printf_s("Enter a positive integer: ");
    scanf_s("%d", &number);

    // задача: посчитать сумму чисел в промежутке [0, number]
    int sum = 0;
    for (; number >= 0; --number) {
        sum += number;
    }
    printf_s("Sum = %d\n", sum);

    system("pause");
    return 0;
}