#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int dayNumber;
    do {
        printf_s("Enter a week day number (0 to exit): ");
        scanf_s("%d", &dayNumber);

        switch (dayNumber) { // осуществляет выбор исполняемых инструкций в соответствии со значением dayNumber
        case 0:
            break;
        case 1:
            printf_s("Monday!");
            break;
        case 2:
            printf_s("Tuesday!");
            break;
        case 3:
            printf_s("Wednesday!");
            break;
        case 4:
            printf_s("Thursday!");
            break;
        case 5:
            printf_s("Friday!");
            break;
        case 6:
            printf_s("Saturday!");
            break;
        case 7:
            printf_s("Sunday!");
            break;
        default: // все прочие значения
            printf_s("There are only 7 days in week!");
        }
        printf_s("\n");

        switch (dayNumber) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf_s("It's regular workday!\n");
            break;
        case 6:
        case 7:
            printf_s("He-hey, it's holiday!\n");
            break;
        // default не обязателен
        }
    } while (dayNumber);

    system("pause");
    return 0;
}