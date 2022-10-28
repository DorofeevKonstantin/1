/*
Модифицировать #1 таким образом, чтобы числа N и M подавались не на стандартный
ввод, а в аргументах командной строки, а выводимые строки должны быть перевёрнуты
(строки должны переворачиваться в памяти, а не просто выводиться в таком виде).
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define ERROR "ERROR\nEXIT WITH ERROR CODE 1"
#define ERR_MEM_ALLOC ERROR ERROR

// универсальный свап для двух переменных одного типа
void swap(void* first, void* second, size_t size);
char** alloc2DCharArray(int height, int width);
// функция, "переворачивающая" строку
void reverseString(char* str, size_t length);
void free2DCharArray(char** arr, int height);

int main(int argc, char** argv) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
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
    // модифицируем и выводим строки:
    for (int i = 0; i < N; ++i) {
        size_t length = strnlen_s(strings[i], maxLength);
        reverseString(strings[i], length);
        printf_s("%s (len = %lld)\n", strings[i], length);
    }
    free2DCharArray(strings, N);

    system("pause");
    return 0;
}

void swap(void* first, void* second, size_t size) {
    void* tmp = malloc(size);
    memcpy_s(tmp, size, first, size);
    memcpy_s(first, size, second, size);
    memcpy_s(second, size, tmp, size);
    free(tmp);
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

void reverseString(char* str, size_t length) {
    char* begin = str;
    char* end = str + length - 1;
    while (begin < end) swap(begin++, end--, sizeof(char));
}

void free2DCharArray(char** arr, int height) {
    for (int i = 0; i < height; ++i) free(arr[i]);
    free(arr);
}