/*
Создайте двумерный массив размера NxM (N и M задаются в коде, должны легко и
быстро изменяться), заполните его случайными значениями из непрерывного диапазона
[A, B] (A и B задаются в коде, должны легко и быстро изменяться).
Выведите массив в консоль.
Отсортируйте массив следующим образом: элементы в строках сортируются по возрастанию,
а сами строки сортируются по убыванию минимального элемента.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h.>

#define N 10
#define M 10
#define A -10
#define B 10

void printArray(int arr[N][M]);
void fillInArray(int arr[N][M]);
// сортировка массива
void sortArray(int arr[N][M]);
// сортировка элементов в строке
void sortLine(int arr[M]);
// swap для двух строк
void swapLines(int first[M], int second[M]);
void swapIntValues(int* first, int* second);

int main(void) {
    srand((unsigned)time(NULL));

    int arr[N][M];
    fillInArray(arr);
    printf_s("Array:\n");
    printArray(arr);

    printf_s("Sorted array:\n");
    sortArray(arr);
    printArray(arr);

    system("pause");
    return 0;
}

void printArray(int arr[N][M]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf_s("%3d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

void fillInArray(int arr[N][M]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            arr[i][j] = rand() % (B - A + 1) + A;
        }
    }
}

void sortLine(int arr[M]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j < M - i; ++j) {
            if (arr[j] < arr[j - 1]) {
                swapIntValues(&arr[j], &arr[j - 1]);
            }
        }
    }
}

void sortArray(int arr[N][M]) {
    // сначала сортируем элементы в каждой строке
    for (int i = 0; i < N; ++i) {
        sortLine(arr[i]);
    }
    // далее идёт пузырьковая сортировка с изменениями в сравнении элементов,
    // раньше мы сравнивали два простых значения, теперь же для сравнения
    // двух массивов элементов будем идти по паре таких массивов с начала
    // и искать первую пару элементов с равными индексами, значения которых
    // будут не равны друг другу, после чего, основываясь на результате их
    // сравнения решаем нужно ли делать swap

    // swap двух массивов -- ни что иное как swap всех пар элементов из них
    // с одинаковыми индексами
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < N - i; ++j) {
            int k = 0;
            while (k < M && arr[j][k] == arr[j - 1][k]) ++k;
            if (k == M) continue;
            if (arr[j - 1][k] < arr[j][k]) swapLines(arr[j], arr[j - 1]);
        }
    }
}

void swapLines(int first[M], int second[M]) {
    for (int i = 0; i < M; ++i) {
        swapIntValues(first + i, second + i);
    }
}

void swapIntValues(int* first, int* second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
}
