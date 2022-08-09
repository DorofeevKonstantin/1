/*
Пользователь вводит в консоли имена двух файлов, обозначим их input-file и output-file.
В input-file записано число N, представленное в десятичной системе счисления.
Программа вычисляет сумму цифр числа N и двоичное представление этого числа в памяти
компьютера (условимся, что оно хранится как знаковое, 4-х байтовое).
Сумма цифр выводится в консоль, а двоичное представление -- в консоль и в output-file.
Программа должна корректно завершать работу при любых входных данных.
Программа должна исправно работать с именами файлов длиной до 100 символов.


Решение написано в общем виде, чтобы при желании его можно было адаптировать
к любому другому целочисленному типу (например long long), поэтому не используются
типы которые больше, чем тип, с которым мы работаем в данный момент (в нашем случае
это int)

В данном решении допускается и используется истинность следующих выражений:
[log(INT_MAX)] == [log(INT_MIN)]
A % B == -(-A % B)
*/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// ERRORS:
#define SUCCESS              0
#define WRONG_INPUT_DATA    -1
#define INT_TYPE_OVERFLOW   -2
#define ERR_ALLOC_MEM       -3
#define INTERNAL_ERROR      -4
#define TOO_LONG_STRING_IN_FILE -5
#define EMPTY_INPUT_FILE    -6
// ERRORS MESSAGES:
#define SUCCESS_MSG                     ""
#define WRONG_INPUT_DATA_MSG            "ERROR: wrong input data\n"
#define INT_TYPE_OVERFLOW_MSG           "ERROR: overflow int type\n"
#define ERR_ALLOC_MEM_MSG               "ERROR: an error has occured on memory allocating\n"
#define INTERNAL_ERROR_MSG              "ERROR: an internal error has occured\n"
#define TOO_LONG_STRING_IN_FILE_MSG     "ERROR: too long string in file\n"
#define EMPTY_INPUT_FILE_MSG            "ERROR: the input file is empty\n"
// создадим массив для сообщений об ошибках, чтобы можно было обращаться
// к ним по кодам ошибок (станет понятнее при просмотре функции fprintfMyExitError)
char* ERROR_MSGS[] = {
    SUCCESS_MSG,
    WRONG_INPUT_DATA_MSG,
    INT_TYPE_OVERFLOW_MSG,
    ERR_ALLOC_MEM_MSG,
    INTERNAL_ERROR_MSG,
    TOO_LONG_STRING_IN_FILE_MSG,
    EMPTY_INPUT_FILE_MSG
};

// некоторые константы, которыми будем пользоваться в ходе работы
#define MAX_FILE_NAME_LENGTH    100
#define FILE_NAME_BUF_SIZE      MAX_FILE_NAME_LENGTH + 1

#define BYTE_BIT    8
#define INT_BYTE    sizeof(int)
#define INT_BIT     (BYTE_BIT * INT_BYTE)

// typedef работает схожим образом с #define
// но предназначен для работы с типами
typedef char byte;

// вспомогательная функция
// возвращает длину десятичной записи числа INT_MAX
unsigned intMaxLength(void);
int isDigit(int ch);
int isSpace(int ch);

// ФУНКЦИИ ВЫВОДА
// вывод информации о своих ошибках и завершение работы
void fprintfMyExitError(FILE* file, errno_t error);
// вывод информации об ошибках, которые записываются в errno
// и завершение работы
errno_t exitErrMsg(char* msg);
// вывод бинарного представления одного байта
byte* fprintfBinaryByteRepresent(FILE* file, byte* binary);
// вывод бинарного представления числа типа int
errno_t fprintBinaryRepresent(FILE* file, byte* binary);

// чтение числа из файла
errno_t readNumberFromFile(FILE* file, int* number);
// получение двоичного представления числа
// использование единичной маски
errno_t getBinaryRepresent_1(int number, byte* binary);
// классический алгоритм
errno_t getBinaryRepresent_2(int number, byte* binary);
// получение суммы цифр десятичной записи числа
unsigned getDecimalDigitsSum(int number);

int main(void) {
    // читаем имя файла со стандартного ввода:
    errno_t error;
    char fileNameBuf[FILE_NAME_BUF_SIZE] = { 0 };
    printf_s("Enter input and output file name: ");
    scanf_s("%s", fileNameBuf, FILE_NAME_BUF_SIZE);
    // открываем файл с входными данными:
    FILE* file;
    if (fopen_s(&file, fileNameBuf, "r")) {
        exit(exitErrMsg("ERROR: couldn't open the input file"));
    }
    char tmp;
    while (isSpace(tmp = fgetc(file)));
    if (tmp == EOF) {
        fprintfMyExitError(stderr, EMPTY_INPUT_FILE);
        exit(EMPTY_INPUT_FILE);
    }
    ungetc(tmp, file);
    // читаем число из файла:
    int number;
    if ((error = readNumberFromFile(file, &number))) {
        fprintfMyExitError(stderr, error);
        exit(error);
    }
    fclose(file);
    // получаем двоичное представление числа:
    byte binary[INT_BIT];
    getBinaryRepresent_2(number, binary);
    // выводим результаты в консоль:
    printf_s("Sum of digits: %u\nBinary representation: ", getDecimalDigitsSum(number));
    fprintBinaryRepresent(stdout, binary);
    printf_s("\n");
    //открываем файл для выходных данных
    scanf_s("%s", fileNameBuf, FILE_NAME_BUF_SIZE);
    if (fopen_s(&file, fileNameBuf, "w")) {
        exit(exitErrMsg("ERROR: couldn't open the output file"));
    }
    // записываем в файл данные
    fprintBinaryRepresent(file, binary);

    fclose(file);

    system("pause");
    return 0;
}

char getDigit(char ch) {
    if (isDigit(ch)) return ch - '0';
    return 0;
}

void fprintfMyExitError(FILE* file, errno_t error) {
    // коды ошибок отрицательные, поэтому взятые со знаком минус
    // они дадут индексы соответствующих ошибок в массиве
    fprintf_s(stderr, ERROR_MSGS[-error]);
    fprintf_s(stderr, "EXIT WITH ERROR CODE %d", error);
}

int exitErrMsg(char* msg) {
    perror(msg);
    fprintf_s(stderr, "EXIT WITH ERROR CODE %d", errno);
    return errno;
}

errno_t readNumberFromFile(FILE* file, int* number) {
    // посчитаем максимальную длину десятичной записи модуля числа,
    // которое может храниться в типе int
    unsigned maxModuleLength = intMaxLength();

    // считаем строку соответствующей длины, поскольку если она будет
    // длинее, то даже если это число - оно будет выходить за пределы
    // диапазона хранимых типом int значений
    // делаем +2 т.к. +1 для '\0' и +1 для возможного знака '+' или '-'
    unsigned bufSize = maxModuleLength + 2;
    char* string = (char*)malloc(sizeof(char) * bufSize);
    if (!string) return ERR_ALLOC_MEM;
    if (fscanf_s(file, "%s", string, bufSize) != 1) {
        free(string);
        return TOO_LONG_STRING_IN_FILE;
    }

    // проверим, что в строке нет символов кроме знака числа и цифр
    char* ptr = string;
    if (*ptr == '-' || *ptr == '+') ++ptr;
    while (*ptr != '\0') {
        if (!isDigit(*(ptr++))) {
            free(string);
            return WRONG_INPUT_DATA;
        }
    }

    // функцией atoi преобразуем строку в число и обработаем ошибки
    // опираясь на информацию из документации по работе этой функции
    int tmp = atoi(string);
    free(string);
    switch (errno) {
    case ERANGE:
        return INT_TYPE_OVERFLOW;
        break;
    case EINVAL:
        return WRONG_INPUT_DATA;
    }

    *number = tmp;
    return SUCCESS;
}

errno_t getBinaryRepresent_1(int number, byte* binary) {
    // создадим битовую маску, в которой единичный младший бит,
    // а все остальные нулевые
    byte lastBitMask = 1;
    for (int i = INT_BIT - 1; i >= 0; --i) {
        // применяя побитовую конъюнкцию запишем младший бит
        // числа в наш массив для хранения двоичной записи
        binary[i] = number & lastBitMask;
        // побитово сдвинем число вправо, чтобы далее работать
        // со следующим его битом
        number >>= 1;
    }
    return SUCCESS;
}

errno_t getBinaryRepresent_2(int number, byte* binary) {
    // простую реализацию этого алгоритма знают все, поэтому  рассмотрим её
    // вариант, основанный на битовых операциях (много ли выгоды от этого
    // мы получим в конкретно этой задаче? - врядли, но работать с
    // этими операциями нужно научиться)

    //знак сохраним для будущего использования
    char sign = number < 0 ? -1 : 1;

    // хочется сделать деление на битовых сдвигах, поэтому нужно число
    // преобразовать в положительное, но модуль INT_MIN не влезет в int
    // поэтому вручную обработаем один бит числа, а дальше знаем точно, что
    // -(INT_MIN / 2) < INT_MAX
    binary[INT_BIT - 1] = number % 2 * sign;
    number = sign * (number / 2);
    for (int i = INT_BIT - 2; i >= 0; --i) {
        binary[i] = (number % 2);
        // деление на два побитовым сдвигом (это быстрее чем обычное деление):
        number >>= 1;
    }
    if (sign == -1) {
        // инвертируем нули и единицы по маске (используем XOR)
        for (unsigned i = 0; i < INT_BIT; ++i) binary[i] ^= 1;

        // прибавим единицу
        byte* ptr = binary + INT_BIT - 1;
        while (*ptr & 1) *(ptr--) = 0;
        *ptr = 1;
    }
    return SUCCESS;
}

byte* fprintfBinaryByteRepresent(FILE* file, byte* binary) {
    for (unsigned i = 0; i < 2; ++i) {
        for (unsigned j = 0; j < BYTE_BIT / 2; ++j) {
            fprintf_s(file, "%d", *binary);
            ++binary;
        }
        fprintf_s(file, " ");
    }
    return binary;
}

errno_t fprintBinaryRepresent(FILE* file, byte* binary) {
    for (unsigned i = 0; i < INT_BYTE; ++i) {
        binary = fprintfBinaryByteRepresent(file, binary);
    }
    return SUCCESS;
}

unsigned getDecimalDigitsSum(int number) {
    unsigned sum = 0;
    while (number) {
        sum += number % 10;
        number /= 10;
    }
    return abs(sum);
}

unsigned intMaxLength(void) {
    unsigned length = 1;
    int intMax = INT_MAX;
    while (intMax /= 10) ++length;
    return length;
}

int isDigit(int ch) {
    return isdigit((char)ch);
}

int isSpace(int ch) {
    return isspace((char)ch);
}
