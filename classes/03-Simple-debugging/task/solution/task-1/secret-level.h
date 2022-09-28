#pragma once
#include <stdio.h>
#include <stdlib.h>

#define I_AM_READY_NOW 0x666

void tenThousandsYears(void) {
    int firstOperand = 0, secondOperand = 0;
    char operation = 0;
    printf_s("Welcome to the secret level!\nNow try to calculate '5 + 7':\n");
    scanf_s("%d%c%c%d", &firstOperand, &operation, 1, &operation, 1, &secondOperand);
    switch (operation) {
    case '+':
        printf_s("%d\n", firstOperand + secondOperand);
        if (firstOperand + secondOperand == 5 + 7) break;
    default:
        printf_s("=_=\n");
        exit(EXIT_SUCCESS);
    }
    printf_s("Very well, and the last challenge '7 + 7':\n");
    scanf_s("%d%с%c%d", &firstOperand, &operation, 1, &operation, 1, &secondOperand);
    printf_s("Great! Congratulations, show this output to your teacher!\nGood bye\n");
    system("pause");
    exit(EXIT_SUCCESS);
}