#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

// объявления функций:
// тип-возвр-знач имя-функ(тип-арг1 имя-арг1, тип-арг2 имя-арг2, ...);
int sum(int first, int second);

void sumProc(int first, int second, int* result);

int mult(int, int); // имена аргументов в объявлении опциональны, типы - обязательны

void printArray(int[ARRAY_SIZE]); // передача в функцию статического массива

void printReversedArray(int*, unsigned); // передача в функцию массива (не обязательно статического)
                                         // указатель на начало и размер массива

// функция заполнения массива значениями
void fillInArray(int[ARRAY_SIZE]);

// функция вычисления суммы всех элементов массива
int arrSum(int [ARRAY_SIZE]);

// аналог arrSum, но для не обязательно статического массива
int arrnSum(int* , unsigned);


int main(void) {
    int a = 5, b = -7;
    int s = sum(a, b); // вызов функции sum и присваивание возвращаемого ею значения переменной s

    printf_s("Sum:\n%d + %d = %d\n", a, b, s);
    printf_s("Mult:\n%d * %d = %d\n", a, s, mult(a, s)); // можно не сохранять возвращаемое значение,
                                                         // а сразу выполнять над ним необходимые действия
    system("pause");

    // запишем в 'a' сумму 'b' и 's':
    sumProc(b, s, &a);
    printf_s("Executed sumProc(b, s, &a)\n");
    printf_s("Now b = %d, s = %d, a = %d\n", b, s, a);
    system("pause");

    int arr[ARRAY_SIZE];
    // заполним массив некоторым образом:
    fillInArray(arr);

    // выведем содержимое массива:
    printArray(arr);
    printf_s("\n");
    system("pause");
    // теперь в обратном порядке:
    printReversedArray(arr, ARRAY_SIZE);
    printf_s("\n");
    system("pause");

    // посчитаем и выведем сумму элементом массива:
    printf_s("Sum of array elements:\n");
    printf_s("arrSum(arr): %d\n", arrSum(arr));
    printf_s("arrnSum(arr, ARRAY_SIZE): %d\n", arrnSum(arr, ARRAY_SIZE));

    system("pause");
    return 0;
}


// определения функций
int sum(int first, int second) {
    //int s = first + second;
    //return s;
    return first + second; // return возвращает указанное значение в место вызова функции
}

void sumProc(int first, int second, int* result) {
    *result = first + second;
}

int mult(int first, int second) {
    return first * second;
}

void printArray(int arr[ARRAY_SIZE]) {
    for (unsigned i = 0; i < ARRAY_SIZE; ++i) {
        printf_s("%d ", arr[i]);
    }

    // нет оператора return, т.к. возвращаемый тип void
}

void printReversedArray(int* arr, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        printf_s("%d ", arr[size - 1 - i]);
    }
}

void fillInArray(int arr[ARRAY_SIZE]) {
    for (unsigned i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = i + 1;
        if (i % 2) {
            arr[i] *= 2;
        }
        if (i % 3) {
            arr[i] *= 3;
        }
        else {
            arr[i] += 5;
        }
    }
}

int arrSum(int mass[ARRAY_SIZE]) {
    int sum = 0;
    for (unsigned i = 0; i < ARRAY_SIZE; ++i) {
        sum += mass[i];
    }

    return sum;
}

int arrnSum(int* arr, unsigned size) {
    int s = 0;
    for (unsigned i = 0; i < size; ++i) {
        s += arr[i];
    }

    return s;
}
