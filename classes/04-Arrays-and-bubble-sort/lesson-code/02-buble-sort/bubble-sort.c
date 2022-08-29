#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

void printArray(int [ARRAY_SIZE]);

int main(void) {
    int arr[ARRAY_SIZE];
    // заполнение массива случайными числами
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        // функция rand() возвращает
        // случайно сгенерированное число в диапазоне [0, RAND_MAX]
        // RAND_MAX = 32 767
        arr[i] = rand() % 100;
    }
    printf_s("Array:\n");
    printArray(arr); // вывод содержимого массива в консоль
    // сортировка пузырьком:
    for (int j = 0; j < ARRAY_SIZE; ++j) {
        for (int i = 1; i < ARRAY_SIZE; ++i) {
            if (arr[i] < arr[i - 1]) {
                // поменять элементы местами:
                int tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
            }
        }
    }
    printf_s("Sorted array:\n");
    printArray(arr);

    system("pause");
    return 0;
}

void printArray(int arr[ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf_s("%d ", arr[i]);
    }
    printf_s("\n");
}