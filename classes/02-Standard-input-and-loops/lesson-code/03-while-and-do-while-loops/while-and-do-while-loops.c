/*
Устройство цикла while:
while (A) {
    B
}
A -- проверочное логическое выражение
B -- тело цикла

инструкции "шага" цикла содержатся либо в теле цикла,
либо в проверочном выражении
*/
#include <stdio.h>
#include <stdlib.h> // можно использовать для system("pause") вместо Windows.h
#include <Windows.h>

int main(void) {
    float fValue;
    printf_s("Enter a float value: ");
    scanf_s("%f", &fValue);
    float fValueBackup = fValue;

    printf_s("while:\n");
    while (fValue > 0.5) {
        printf_s("%.5f\n", fValue);
        fValue /= 3;
    }
    
    fValue = fValueBackup;

    printf_s("do-while:\n");
    do { // цикл do-while всегда выполняет как минимум одну итерацию
        printf_s("%.5f\n", fValue);
        fValue /= 3;
        // Sleep() приостанавливает выполнение программы
        // принимает время в миллисекундах
        Sleep(1000); // (Windows.h)
    } while (fValue > 0.5);

    system("pause");
    return 0;
}
