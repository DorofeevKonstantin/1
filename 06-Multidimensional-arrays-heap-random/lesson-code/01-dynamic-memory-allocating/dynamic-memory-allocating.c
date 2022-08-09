/*
malloc(N) -- выделяет N байт памяти
calloc(N, S) -- выделяет N * S байт памяти

realloc(ptr, N) -- выделяет N байт памяти,
перемещает туда данные из участка памяти, на который
указывает ptr, освобождает ptr

все функции выше в случае успеха возвращают указатель на выделенную память
а в случае неудачи 0 (NULL)

free(ptr) -- освобождает ранее выделенную память
не забывайте освобождать память, если она вам далее не нужна
общее правило: сколько раз у вас были вызваны функции
malloc и calloc столько раз должна быть вызвана функция free

в коде приведено правильное использование этих функций
*/
#include <stdio.h>
#include <stdlib.h>

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\nEXIT WITH ERROR CODE 1\n"

#define CHAR_ARRAY 0
#define INT_ARRAY 1
#define FLOAT_ARRAY 2
#define DOUBLE_ARRAY 3

void swapInt(int*, int*);
void printIntArray(int*, int);
void reverseIntArray(int*, int); // инвертирует порядок элементов в массиве

int main(void) {
    int* iPtr = malloc(sizeof(int)); // выделили 4 байта памяти для хранения числа
    if (iPtr == NULL) { // при попытке выделить память всегда делаем проверку
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    *iPtr = 6;
    printf_s("iPtr: %p\n*iPtr: %d\n", iPtr, *iPtr);
    // больше использоваться эту переменную не будем,
    // поэтому освобождаем память
    free(iPtr);

    // теперь создадим динамический массив, задаваемый с консоли
    int size;
    printf_s("Enter an array size: ");
    scanf_s("%d", &size);
    int* iArray = calloc(size, sizeof(int));
    if (!iArray) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    printf_s("Enter values: ");
    for (int i = 0; i < size; ++i) {
        scanf_s("%d", &iArray[i]);
        // аналогично через арифметику указателей:
        // scanf_s("%d", iArray + i);
    }
    // перевернем массив:
    reverseIntArray(iArray, size);
    printf_s("Reversed iArray:\n");
    printIntArray(iArray, size);
    printf_s("\n");
    // увеличим размер массива в 1.5 раза и запросим ввод недостающих значений
    // при использовании realloc заводим временным указатель
    int* tmp;
    int newSize = size * 3 / 2;
    tmp = realloc(iArray, newSize * sizeof(int));
    if (tmp) iArray = tmp;
    else {
        printf_s(ERR_ALLOC_MEM);
        free(iArray); // в случае неудачи не забываем очистить память
        return 1;
    }
    printf_s("Enter %d extra values: ", newSize - size);
    for (int i = size; i < newSize; ++i) {
        scanf_s("%d", &iArray[i]);
    }
    // перевернем массив ещё раз
    reverseIntArray(iArray, newSize);
    printIntArray(iArray, newSize);
    printf_s("\n");
    free(iArray);

    system("pause");
    return 0;
}

void swapInt(int* first, int* second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
}

void printIntArray(int* arr, int size) {
    const int* end = arr + size;
    while (arr < end) {
        printf_s("%d ", *(arr++));
    }
}

void reverseIntArray(int* arr, int size) {
    for (int i = 0; i < size / 2; ++i) {
        swapInt(&arr[i], &arr[size - 1 - i]);
    }
}
