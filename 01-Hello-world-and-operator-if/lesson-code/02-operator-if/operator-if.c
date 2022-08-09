#include <stdio.h>
#include <Windows.h>

int main(void) {
    int var;
    printf_s("Enter an integer: ");
    scanf_s("%d", &var); // считываем с консоли целое число в переменную var

    if (var > 10) { 
        // инструкции в этом блоке будут выполнены если
        // логическое выражение истинно
        // иначе при наличии блока else будут выполнены инструкции в нём
        printf_s("This number exceed 10\n");
    }
    else {
        printf_s("This number not exceed 10\n");
    }

    // можно строить конструкцию else if следующим образом:
    if (var == 0) {
        printf_s("Entered value is 0\n");
    }
    else if (var % 2 == 0) {
        // выполнится в случае если введенное значение
        // не равно нулю и чётно
        printf_s("Entered value is even\n"); 
    }
    else {
        printf_s("Entered value is odd\n");
    }

    // то же самое можно реализовать использовав вложенный оператор if
    if (var != 0) {
        if (var % 2 == 0) {
            printf_s("Entered value is even\n"); 
        }
        else {
            printf_s("Entered value is odd\n");
        }
    }
    else {
        printf_s("Entered value is 0\n");
    }

    system("pause");
    return 0;
}