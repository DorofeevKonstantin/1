/*
Создайте двумерный статический массив произвольных размеров(каких хотите)
и заполните случайными числами.Выведите его в консоль.
Пользователь вводит целое положительное число N. Создайте массив размера N
и заполните случайными значениями из диапазона [-N, N]. Выведите массив в консоль.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATIC_ARRAY_WIDTH 7
#define STATIC_ARRAY_HEIGHT 12

void printStaticArray(int arr[STATIC_ARRAY_HEIGHT][STATIC_ARRAY_WIDTH]);
void generateStaticArr(int arr[STATIC_ARRAY_HEIGHT][STATIC_ARRAY_WIDTH]);
void printDynamicArray(int* arr, int size);
void generateDynamicArr(int* arr, int size, int minValue, int maxValue);

int main(void) {
    srand((unsigned)time(NULL));

    int staticArray[STATIC_ARRAY_HEIGHT][STATIC_ARRAY_WIDTH];
    generateStaticArr(staticArray);
    printStaticArray(staticArray);
    printf_s("\n");

    int N;
    printf_s("Enter N value: ");
    scanf_s("%d", &N);
    int* dynamicArray = malloc(sizeof(int) * N);
    if (!dynamicArray) exit(-1);
    generateDynamicArr(dynamicArray, N, -N, N);
    printDynamicArray(dynamicArray, N);
    printf_s("\n");

    system("pause");
    return 0;
}

void printStaticArray(int arr[STATIC_ARRAY_HEIGHT][STATIC_ARRAY_WIDTH]) {
    for (int i = 0; i < STATIC_ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < STATIC_ARRAY_WIDTH; ++j) {
            printf_s("%d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

void generateStaticArr(int arr[STATIC_ARRAY_HEIGHT][STATIC_ARRAY_WIDTH]) {
    for (int i = 0; i < STATIC_ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < STATIC_ARRAY_WIDTH; ++j) {
            arr[i][j] = rand() - (RAND_MAX / 2);
        }
    }
}

void printDynamicArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf_s("%d ", arr[i]);
    }
}

void generateDynamicArr(int* arr, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
}
