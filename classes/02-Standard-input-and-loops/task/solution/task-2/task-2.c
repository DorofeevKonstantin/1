#include <stdio.h>
#include <Windows.h>

int main(void) {
    int n;
    printf_s("Enter a number: ");
    scanf_s("%d", &n);
    if (n % 2) {
        for (int i = n; i > 0; i -= 1) {
            printf_s("%d ", i);
        }
    }
    else {
        for (int i = 1; i <= n; i += 1) {
            printf_s("%d ", i);
        }
    }
    printf_s("\n");

    system("pause");
    return 0;
}