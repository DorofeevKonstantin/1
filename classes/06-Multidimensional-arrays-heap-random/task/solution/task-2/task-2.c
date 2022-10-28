/*
Пользователь вводит числа A, B (B < A). Создайте массив размера A и заполните его
случайными числами, модули которых из диапазона [10, 30].
Создайте массив размера B и заполните его случайно выбранными элементами из
первого массива (каждый элемент должен быть выбран не более, чем 1 раз).
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int* arr, int size);
void generateArrayA(int* arr, int size);
void fillInArrayB(int* arrayA, int sizeA, int* arrayB, int sizeB);

int main(void) {
    srand((unsigned)time(NULL));

    int A, B;
    printf_s("Enter A and B values: ");
    scanf_s("%d %d", &A, &B);

    int* arrayA = malloc(sizeof(int) * A);
    if (!arrayA) exit(-1);
    int* arrayB = malloc(sizeof(int) * B);
    if (!arrayB) {
        free(arrayA);
        exit(-1);
    }
    generateArrayA(arrayA, A);
    fillInArrayB(arrayA, A, arrayB, B);

    printArray(arrayA, A);
    printf_s("\n");
    printArray(arrayB, B);
    printf_s("\n");

    system("pause");
    return 0;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++ i) {
        printf_s("%d ", arr[i]);
    }
}

void generateArrayA(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 21 + 10;
    }
}

void fillInArrayB(int* arrayA, int sizeA, int* arrayB, int sizeB) {
    // заведем массив, в котором будем для каждого индекса
    // отмечать был ли уже элемент исходного массива с
    // соответствующим индексом добавлен во второй массив
    char* usingFlags = calloc(sizeA, sizeof(char));
    if (!usingFlags) {
        free(arrayA);
        free(arrayB);
        exit(-1);
    }
    int usedCount = 0;
    while (usedCount < sizeB) {
        int index = rand() % sizeA;
        // если элемент ещё не был "использован"
        // записываем его во второй массив
        // и отмечаем "использованным"
        if (!usingFlags[index]) {
            arrayB[usedCount] = arrayA[index];
            ++usedCount;
            usingFlags[index] = 1;
        }
    }
}