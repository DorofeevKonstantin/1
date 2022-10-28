/*
Создайте двумерный массив размера NxM(N и M задаются в коде и должны
легко и быстро изменяться при желании), заполните его таблицей умножения.
Выведите результат в консоль(столбцы должны разделяться табуляцией).
Нельзя использовать вложенные циклы.
*/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_HEIGHT 5
#define ARRAY_WIDTH 9

void printArray(int arr[ARRAY_HEIGHT][ARRAY_WIDTH]);
void fillInMultTable(int arr[ARRAY_HEIGHT][ARRAY_WIDTH]);

int main(void) {
    int arr[ARRAY_HEIGHT][ARRAY_WIDTH];
    fillInMultTable(arr);
    printArray(arr);

    system("pause");
    return 0;
}

void printArray(int arr[ARRAY_HEIGHT][ARRAY_WIDTH]) {
    for (int i = 0; i < ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < ARRAY_WIDTH; ++j) {
            printf_s("%d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

void fillInMultTable(int arr[ARRAY_HEIGHT][ARRAY_WIDTH]) {
    for (int i = 0; i < ARRAY_HEIGHT * ARRAY_WIDTH; ++i) {
        // индекс строки - частное деления текущей позиции на ширину строки
        int lineNumber = i / ARRAY_WIDTH + 1;
        // индекс столбца - остаток от предыдущего деления
        int columnNumber = i % ARRAY_WIDTH + 1;
        // сквозное индексирование, которое рассматривалось
        // в lesson-code
        *(*arr + i) = lineNumber * columnNumber;
    }
}
