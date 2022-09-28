#include <stdio.h>
#include <Windows.h>

int main(void) {
    int number;
    printf_s("Enter a number: ");
    scanf_s("%d", &number);
    printf_s("You entered %d\n", number);

    system("pause");
    return 0;
}