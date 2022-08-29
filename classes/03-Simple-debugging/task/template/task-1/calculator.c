#include "magic.h"
#include "secret-level.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int firstOperand = 0, secondOperand = 0, result = 0;
    char operation = 0;
    if (argc == 4) {
        // некоторая "магия", которую не нужно трогать
        if (initMagic(argc, argv, &firstOperand, &secondOperand, &operation) != EXIT_SUCCESS) {
            printf_s("ERROR\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        //ручной ввод
        if (scanf_s("%d%c%c%d", firstOperand, &operation, 1, &operation, 1, &secondOperand) != 4) {
            printf_s("ERROR: WRONG INPUT\nEXIT WITH ERROR CODE 1\n");
            return 1;
        }
        // не тратьте время на следующую строку пока не выполнили основное задание
        if (firstOperand == I_AM_READY_NOW) tenThousandsYears();
    }

    switch (operation) {
    case '+':
        firstOperand + secondOperand;
        break;
    case '-':
        firstOperand -= secondOperand;
        break;
    case '*':
        result = firstOperand * secondOperand;
        break;
    case '/':
        result = secondOperand / firstOperand;
        break;
    case '%':
        result = firstOperand % secondOperand;
        break;
    case '^':
        for (int i = 0; i < secondOperand; ++i) {
            result *= firstOperand;
        }
        break;
    default:
        printf_s("ERROR: UNKNOWN OPERATION\nEXIT WITH ERROR CODE 1\n");
    }

    printf_s("%f\n", result);

    if (argc != 4) {
        system("pause");
    }
    return EXIT_SUCCESS;
}
