#include <stdio.h>
#include <Windows.h>

int main(void) {
    double re1, re2, im1, im2, reResult, imResult;
    char operation;
    printf_s("Enter an expression: ");
    scanf_s("(%lf,%lf) %c (%lf,%lf)", &re1, &im1, &operation, 1, &re2, &im2);

    switch (operation) {
    case '+':
        reResult = re1 + re2;
        imResult = im1 + im2;
        break;
    case '-':
        reResult = re1 - re2;
        imResult = im1 - im2;
        break;
    case '*':
        reResult = re1 * re2 - im1 * im2;
        imResult = re1 * im2 + re2 * im1;
        break;
    default:
        printf_s("ERROR: unknown operation\nEXIT WITH ERROR CODE 1");
        return 1;
    }
    printf_s("(%g,%g)\n", reResult, imResult);

    system("pause");
    return 0;
}