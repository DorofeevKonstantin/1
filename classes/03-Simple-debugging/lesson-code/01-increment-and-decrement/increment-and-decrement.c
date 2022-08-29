#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a;
    printf_s("Enter an integer \"a\": "); // экранирование символов в строке выполняется с помощью обратного слеша '\'
    scanf_s("%d", &a);
    printf_s("a = %d\n", a);
    system("pause");

    // постфиксная инкрементация/декрементация выполняется после вычисления значения выражения
    int b = a++; // значение 'a' запишется в 'b', после чего увеличится на 1
    printf_s("execute: int b = a++;\n");
    printf_s("Now b = %d, but a = %d\n", b, a);
    system("pause");

    // префиксная инкрементация/декрементация выполняется перед вычислением значения выражения
    int c = ++b; // значение 'b' увеличится на 1, после чего запишется в 'c'
    printf_s("execute: int c = ++b;\n");
    printf_s("Now c = %d and b = %d\n", c, b);
    system("pause");

    // примеры использования
    printf_s("From 'c' to '0' (postfix):\n");
    while (c) {
        printf_s("%d ", c--);
    }
    printf_s("\n");
    system("pause");

    printf_s("From 'b' to '0' (prefix):\n");
    while (b) {
        printf_s("%d ", --b);
    }
    printf_s("\n");

    system("pause");
    return 0;
}