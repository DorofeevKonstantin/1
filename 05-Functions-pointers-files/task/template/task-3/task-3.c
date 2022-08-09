#include <stdio.h>
#include <stdlib.h>

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