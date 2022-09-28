#include <stdio.h>
#include <Windows.h>

int main(void) {
    int a = 26;
    int b = 11;

    printf_s("%d + %d = %d\n", a, b, a + b);
    printf_s("%d - %d = %d\n", a, b, a - b);
    printf_s("%d * %d = %d\n", a, b, a * b);
    printf_s("%d / %d = %d\n", a, b, a / b);
    printf_s("%d %% %d = %d\n", a, b, a % b); // пишем в форматной строке % дважды,
                                              // чтобы он воспринимался как символ %

    system("pause");
    return 0;
}