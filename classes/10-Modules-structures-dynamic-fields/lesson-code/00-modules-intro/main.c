#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

int main(void) {
    printf_s("Enter two numbers: ");
    int firstOperand, secondOperand;
    scanf_s("%d %d", &firstOperand, &secondOperand);
    printf_s("%d + %d = %d\n"
        "%d - %d = %d\n"
        "%d * %d = %d\n"
        "%d / %d = %d\n",
        firstOperand, secondOperand, intSum(firstOperand, secondOperand),
        firstOperand, secondOperand, intSub(firstOperand, secondOperand),
        firstOperand, secondOperand, intMult(firstOperand, secondOperand),
        firstOperand, secondOperand, intDiv(firstOperand, secondOperand)
        );

    system("pause");
    return 0;
}