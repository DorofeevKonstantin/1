#include <stdio.h>
#include <stdlib.h>
#include <string.h> // функции для работы со строками

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\n EXIT WITH ERROR CODE 1"
#define STACK_STRING_SIZE 10

void printStaticStr(char str[STACK_STRING_SIZE]);

int main(void) {

    // СТЕК

    // СТРОКИ -- МАССИВЫ СИМВОЛОВ
    // объявление строки в стеке
    char str[STACK_STRING_SIZE];
    // т.к. это массив - можем работать как с массивом:
    for (int i = 0; i < STACK_STRING_SIZE; ++i) {
        str[i] = 'a' + i; // пользуемся знанием об организации таблицы ASCII
    }
    // пусть в конце будет перенос строки
    str[STACK_STRING_SIZE - 1] = '\n';

    printf_s("Static string: ");
    printStaticStr(str);

    // СИ-СТРОКИ (нуль-терминированная строка)
    // по принятому соглашению си-строка
    // оканчивается нулевым символом
    // преобразуем наш массив символов в соответствии с этим соглашением:
    str[STACK_STRING_SIZE - 1] = '\0';

    // ввод строки из консоли
    printf_s("Enter string (max size = %d): ", STACK_STRING_SIZE - 1);
    if (scanf_s("%s", str, STACK_STRING_SIZE)) {
        // вывод строки в консоль
        printf_s("You entered: %s", str);
    }
    else printf_s("Wrong string length!");
    printf_s("\n");

    // символьный массив можно инициализировать строковым литералом
    // при этом будет создана нуль-терминированная строка
    char initializedStr[] = "Initialized char array";
    printf_s("%s\n", initializedStr);
//_____________________________________________________________________________

    // КУЧА

    int strSize = 0;
    printf_s("Enter a max string length: ");
    scanf_s("%d", &strSize);
    // выделяем памяти на 1 больше для записи нуль-символа
    strSize = (strSize + 1) * sizeof(char);
    char* heapStr = malloc(strSize);
    if (!heapStr) {
        printf_s(ERR_ALLOC_MEM);
        exit(1);
    }
    printf_s("Enter a string: ");
    if (scanf_s("%s", heapStr, strSize)) {
        printf_s("Your string: %s", heapStr);
    }
    else printf_s("Wrong string length!");
    printf_s("\n");

    // ФУНКЦИИ, НЕОБХОДИМЫЕ ПРИ ВЫПОЛНЕНИИ АУДИТОРНОЙ РАБОТЫ
    // длина строки:
    int strLength = (int)strnlen_s(heapStr, strSize);
    printf_s("string length: %d\n", strLength);
    // преобразование строки в число
    char* strNumber = "47";
    int number = atoi(strNumber);
    printf_s("strNumber = \"%s\"\nnumber = %d\n", strNumber, number);
    free(heapStr);

    // можно установить указатель на строковый литерал
    // как присваиванием так и инициализацией
    heapStr = "String literal";
    char* literalPtr = "One more string literal";
    printf_s("Literals:\n%s\n%s\n", heapStr, literalPtr);
    // освобождать вручную память с литералами нельзя


    system("pause");
    return 0;
}

void printStaticStr(char str[STACK_STRING_SIZE]) {
    for (int i = 0; i < STACK_STRING_SIZE; ++i) {
        printf_s("%c", str[i]);
    }
}