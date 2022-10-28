/*
Модифицировать #4 таким образом, чтобы при сортировке строк каждая
строка копировалась на новое место ровно один раз.

Решение:
Заведем массив, в который запишем индексы наших строк.
Теперь просто отсортируем этот массив, но сравнивать мы будем не сами индексы,
а строки, соответствующие этим индексам, а swap выполнять для индексов.
Таким образом в итоге массив индексов будет показывать в каком порядке должны
находиться наши строки, а нам нужно будет лишь записать их на новые позиции.

Для большей простоты кода запись строк на их конечные позиции выполняется
с помощью копии всего массива, которую мы заранее создаем (иначе, при записи строки
на новую позицию, та строка, что находилась на этой позиции ранее, будет потеряна).

Это можно сделать без создания копии массива, но алгоритм будет значительно сложнее.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 10
#define A -10
#define B 10

void printArray(int arr[N][M]);
void fillInArray(int arr[N][M]);
void sortArray(int arr[N][M]);
void sortLine(int arr[M]);
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
    for (int i = 0; i < N; ++i) {
        sortLine(arr[i]);
    }
    int lineIndexes[N];
    for (int i = 0; i < N; ++i) {
        lineIndexes[i] = i;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < N - i; ++j) {
            int k = 0;
            while (k < M && arr[lineIndexes[j]][k] == arr[lineIndexes[j - 1]][k]) ++k;
            if (k == M) continue;
            if (arr[lineIndexes[j - 1]][k] < arr[lineIndexes[j]][k]) swapIntValues(&lineIndexes[j], &lineIndexes[j - 1]);
        }
    }

    int arrayCopy[N][M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            arrayCopy[i][j] = arr[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            arr[i][j] = arrayCopy[lineIndexes[i]][j];
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
