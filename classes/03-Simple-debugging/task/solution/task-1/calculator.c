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
        // ОШИБКА: пропущен амперсанд перед firstOperand:
        if (scanf_s("%d%c%c%d", firstOperand, &operation, 1, &operation, 1, &secondOperand) != 4) {
            printf_s("ERROR: WRONG INPUT\nEXIT WITH ERROR CODE 1\n");
            return 1;
        }
        // не тратьте время на следующую строку пока не выполнили основное задание
        if (firstOperand == I_AM_READY_NOW) tenThousandsYears();
    }

    switch (operation) {
    case '+':
        // ОШИБКА: результат выражения никуда не сохраняется:
        firstOperand + secondOperand;
        break;
    case '-':
        // ОШИБКА: результат выполнения операции записывается в firstOperand вместо result:
        firstOperand -= secondOperand;
        break;
    case '*':
        result = firstOperand * secondOperand;
        break;
    case '/':
        // ОШИБКА: firstOperand и secondOperand перепутаны местами:
        result = secondOperand / firstOperand;
        break;
    case '%':
        result = firstOperand % secondOperand;
        break;
    case '^':
        // ОШИБКА: значение result = 0 и поэтому останется 0 после цикла
        // необходимо присвоить ему значение 1 перед выполнением цикла:
        for (int i = 0; i < secondOperand; ++i) {
            result *= firstOperand;
        }
        break;
    default:
        printf_s("ERROR: UNKNOWN OPERATION\nEXIT WITH ERROR CODE 1\n");
    }

    // ОШИБКА: result переменная типа int, используется модификатор %f вместо %d:
    printf_s("%f\n", result);

    if (argc != 4) {
        system("pause");
    }
    return EXIT_SUCCESS;
}
