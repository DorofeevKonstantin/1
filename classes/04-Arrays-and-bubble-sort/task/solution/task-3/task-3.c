#include <stdio.h>
#include <stdlib.h>

#define NUMBERS_COUNT 10
#define MAX_COUNT 5

int main(void) {
    int arr[NUMBERS_COUNT], max[MAX_COUNT];
    // считаем числа из консоли в массив
    printf_s("Enter %d integer numbers :", NUMBERS_COUNT);
    for (int i = 0; i < NUMBERS_COUNT; ++i) {
        scanf_s("%d", &arr[i]);
    }

    // заполним максимумы первыми значениями и запомним индекс минимального среди них
    int minIndex = 0;
    for (int i = 0; i < MAX_COUNT; ++i) {
        max[i] = arr[i];
        if (max[i] < max[minIndex]) {
            minIndex = i;
        }
    }

    // теперь переберём оставшиеся значения в массиве
    // если текущее проверяемое значение превосходит минимальное среди максимумов,
    // то заменим минимальное значение текущим проверяемым и заново найдем минимальный
    // элемент среди максимумов
    for (int i = MAX_COUNT; i < NUMBERS_COUNT; ++i) {
        if (arr[i] > max[minIndex]) {
            max[minIndex] = arr[i];
        }
        for (int j = 0; j < MAX_COUNT; ++j) {
            if (max[j] < max[minIndex]) {
                minIndex = j;
            }
        }
    }
    // отсортируем
    for (int i = 0; i < MAX_COUNT; ++i) {
        for (int j = 1; j < MAX_COUNT - i; ++j) {
            if (max[j] < max[j - 1]) {
                int tmp = max[j];
                max[j] = max[j - 1];
                max[j - 1] = tmp;
            }
        }
    }
    // выведем
    for (int i = 0; i < MAX_COUNT; ++i) {
        printf_s("%d ", max[i]);
    }
    printf_s("\n");

    system("pause");
    return 0;
}