/*
В шаблоне task-3 напишите функцию swap, которая обменивает значениями
две переменных (т.е. если a = 0, b = 1, то после вызова этой функции
должно быть a = 1, b = 0).
Нельзя как-либо редактировать код функции main.
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int*, int*);

int main(void) {
    int a, b;
    printf_s("Enter two values: ");
    scanf_s("%d %d", &a, &b);
    printf_s("Now a = %d and b = %d\nEXEC: swap(a,b)\n", a, b);
    swap(&a, &b);
    printf_s("Now a = %d and b = %d\n", a, b);

    system("pause");
    return 0;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
