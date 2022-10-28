/*
#На стандартный ввод подаются числа N и M, после чего следуют N строк длины,
не превышающей M (строки не содержат пробельных символов).

Программа должна записать строки в память и вывести их в консоль вместе с
фактическими длинами.include <stdio.h>
*/
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define ERROR "ERROR\nEXIT WITH ERROR CODE 1"
#define ERR_MEM_ALLOC ERROR

char** alloc2DCharArray(int height, int width);
void free2DCharArray(char** arr, int height);

int main(void) {
    int N = 0, M = 0;
    printf_s("Enter N and M values: ");
    scanf_s("%d %d", &N, &M);
    const int maxLength = M + 1; // +1 для завершающего нуля
    // выделяем память под строки
    char** strings = alloc2DCharArray(N, maxLength);
    if (!strings) {
        printf_s(ERR_MEM_ALLOC);
        exit(1);
    }
    // читаем строки из консоли
    for (int i = 0; i < N; ++i) {
        scanf_s("%s", strings[i], maxLength);
    }
    // выводим строки:
    for (int i = 0; i < N; ++i) {
        size_t length = strnlen_s(strings[i], maxLength);
        printf_s("%s (len = %lld)\n", strings[i], length);
    }
    // освобождаем память
    free2DCharArray(strings, N);

    system("pause");
    return 0;
}

char** alloc2DCharArray(int height, int width) {
    char** arr = (char**)malloc(sizeof(char*) * height);
    if (!arr) {
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        if (!(arr[i] = (char*)malloc(sizeof(char) * width))) {
            for (int j = 0; j < i; ++j) free(arr[j]);
            free(arr);
            return NULL;
        }
    }
    return arr;
}

void free2DCharArray(char** arr, int height) {
    for (int i = 0; i < height; ++i) free(arr[i]);
    free(arr);
}
