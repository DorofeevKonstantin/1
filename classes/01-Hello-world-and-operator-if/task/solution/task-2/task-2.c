#include <stdio.h>
#include <Windows.h>

int main(void) {
    int a = 26;
    int b = 11;

    printf_s("%d + %d = %d\n", a, b, a + b);
    printf_s("%d - %d = %d\n", a, b, a - b);
    printf_s("%d * %d = %d\n", a, b, a * b);
    printf_s("%d / %d = %d\n", a, b, a / b);
    printf_s("%d %% %d = %d\n", a, b, a % b); // ����� � ��������� ������ % ������,
                                              // ����� �� ������������� ��� ������ %

    system("pause");
    return 0;
}