#include <stdio.h>
#include <stdlib.h>

#define NUMBERS_COUNT 10

int main(void) {
    int arr[NUMBERS_COUNT];

    // читаем числа из консоли и сохраняем в массиве
    printf_s("Enter %d integer numbers: ", NUMBERS_COUNT);
    for (int i = 0; i < NUMBERS_COUNT; ++i) {
        scanf_s("%d", &arr[i]);
    }
    // выводим элементы массива в консоль при условии
    for (int i = 0; i < NUMBERS_COUNT; ++i) {
        if (arr[i] > 0) { // выводим только положительные элементы
            printf_s("%d ", arr[i]);
        }
    }
    printf_s("\n");

    system("pause");
    return 0;
}