/*
Напишите программу-калькулятор для матриц.

Требования:
Матрицы считываются из файлов

Пример матрицы в файле:

1 2 3
4 5 6
7 8 9
Размер матрицы в файле определяется программой автоматически, он не указывается
пользователем и не записывается в самом файле с матрицей

Поддерживаемые операции и баллы за них:
сложение двух матриц (0.1)
вычитание одной матрицы из другой (0.1)
перемножение двух матриц (0.2)
транспонирование матрицы (0.2)
нахождение определителя матрицы (0.4)
Должен быть реализован интуитивно понятный пользователю текстовый либо
псевдографический интерфейс в командной строке.
Программа должна корректно завершать своё исполнение при любом сценарии использования.

Примем следующее соглашение: файл с матрицей должен содержать исключительно
цифры и пробельные символы. Допускается и игнорируется наличие последовательностей
пробельных символо, в том числе пустых строк и строк состоящих исключительно из пробельных
символов.
*/
#include "Matix.h"

#include "myErrors.h"

#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define FILENAME_BUF_LENGTH 100
#define FILENAME_BUF_SIZE (FILENAME_BUF_LENGTH + 1)

#define MAIN_MENU "MENU\n\
1. Load matrices\n\
2. Get sum\n\
3. Get subtract\n\
4. Get multiplication\n\
5. Get transposed matrices\n\
6. Get determinants\n\
0. Exit\n"

bool checkFile(char* fileName, size_t* height, size_t* width);
void readMatrixFromFile(char* fileName, MatrixPtr matrix);

void printMatrix(MatrixPtr matrix);

int main(int argc, char* argv[]) {
    errno_t error = 0;
    char action = 0;
    MatrixPtr first = NULL, second = NULL, result1, result2;
    int det1, det2;
    size_t height, width;
    bool matricesLoaded = false;
    char filenameBuf[FILENAME_BUF_SIZE];
    do {
        system("cls");
        char op = 0;
        result1 = result2 = NULL;
        printf_s(MAIN_MENU);

        action = _getch();
        system("cls");
        if (action != '1' && action != '0' && !matricesLoaded) {
            printf_s("Matrices aren't loaded, you should load them before other actions!\n");
            system("pause");
            continue;
        }

        switch (action) {
        case '1':
            if (first != NULL) {
                deleteMatrix(first);
                first = NULL;
            }
            if (second != NULL) {
                deleteMatrix(second);
                second = NULL;
            }
            matricesLoaded = false;

            printf_s("Enter a file name for the first matrix:\n");
            gets_s(filenameBuf, FILENAME_BUF_SIZE);
            if (!checkFile(filenameBuf, &height, &width)) {
                printf_s("Some problems occurred on reading this file\n");
                break;
            }
            checkError(newMatrix(&first, NULL, height, width));
            readMatrixFromFile(filenameBuf, first);
            printMatrix(first);

            printf_s("Enter a file name for the second matrix:\n");
            gets_s(filenameBuf, FILENAME_BUF_SIZE);
            if (!checkFile(filenameBuf, &height, &width)) {
                printf_s("Some problems occurred on reading this file\n");
                break;
            }
            checkError(newMatrix(&second, NULL, height, width));
            readMatrixFromFile(filenameBuf, second);
            printMatrix(second);
            matricesLoaded = true;
            break;
        case '2':
            op = '+';
            checkError(sumMatrix(&result1, first, second));
            checkError(sumMatrix(&result2, second, first));
            break;
        case '3':
            op = '-';
            checkError(subMatrix(&result1, first, second));
            checkError(subMatrix(&result2, second, first));
            break;
        case '4':
            op = '*';
            checkError(multMatrix(&result1, first, second));
            checkError(multMatrix(&result2, second, first));
            break;
        case '5':
            checkError(transposeMatrix(&result1, first));
            checkError(transposeMatrix(&result2, second));
            break;
        case '6':
            checkError(determinantMatrix(first, &det1));
            checkError(determinantMatrix(second, &det2));
            printf_s("det(first) = %d\ndet(second) = %d\n", det1, det2);
            break;
        }

        if (result1 != NULL) {
            if (op != 0) printf_s("matrix1 %c matrix2:\n", op);
            printMatrix(result1);
            printf_s("\n\n\n");
        }
        if (result2 != NULL) {
            if (op != 0) printf_s("matrix2 %c matrix1:\n", op);
            printMatrix(result2);
            printf_s("\n\n\n");
        }
        deleteMatrix(result1);
        deleteMatrix(result2);
        system("pause");
    } while (action != '0');

    return 0;
}

// проверяет соответствуют ли данные в файле соглашению
// и вычисляет размер матрицы в файле
bool checkFile(char* fileName, size_t* height, size_t* width) {
    FILE* file;
    errno_t error = fopen_s(&file, fileName, "r");
    if (error != 0) return false;
    *height = *width = 0;
    unsigned char ch;
    size_t strLength = 0, maxStrLength = 0;
    // проверяем наличие нецифровых символов в файле
    // параллельно с этим считаем максимульную длину строки в файле
    while ((ch = fgetc(file)) != EOF) {
        if (!isdigit(ch) && !isspace(ch)) {
            fclose(file);
            return false;
        }
        ++strLength;
        if (ch == '\n') {
            if (maxStrLength < strLength) maxStrLength = strLength;
            strLength = 0;
        }
    }
    // далее выясним размер матрицы
    rewind(file);
    size_t bufCount = maxStrLength + 1;
    char* buf = (char*)malloc(sizeof(char) * bufCount);
    if (buf == NULL) {
        fclose(file);
        checkError(errno);
        return false;
    }
    while (fgets(buf, (int)bufCount, file)) {
        size_t currentWidth = 0;
        size_t index = 1;
        while (buf[index] != '\0') {
            // каждая пара символов вида: непробельный + пробельный
            // это конец числа, таким образом их считаем
            if (isspace(buf[index]) && !isspace(buf[index - 1]))
                ++currentWidth;
            ++index;
        }
        // может быть ситуация, что в конце строки нет пробельного символа,
        // тогда последнее число не посчитается, поправим это
        if (!isspace(buf[index - 1])) ++currentWidth;
        if (currentWidth == 0) continue;    // пустые строки пропускаем
        // начальное значение width = 0, а после чтения любой строки с числами
        // оно изменится, поэтому следующей строкой определим значение width
        // по первой строке, в которой имеются числа
        if (*width == 0) *width = currentWidth;
        // количество чисел в строках должно строго совпадать по соглашению
        if (*width != currentWidth) {
            fclose(file);
            return false;
        }
        // не забываем считать строки
        ++*height;
    }
    fclose(file);
    return true;
}

void readMatrixFromFile(char* fileName, MatrixPtr matrix) {
    FILE* file;
    if (fopen_s(&file, fileName, "r")) {
        perror("");
        return;
    }

    int value;
    for (size_t i = 0; i < matrix->height; ++i) {
        for (size_t j = 0; j < matrix->width; ++j) {
            fscanf_s(file, "%d", &value);
            checkError(errno);
            setValueMatrix(matrix, i, j, value);
        }
    }
    fclose(file);
}

void printMatrix(MatrixPtr matrix) {
    for (size_t i = 0; i < matrix->height; ++i) {
        for (size_t j = 0; j < matrix->width; ++j) {
            printf_s("%5d ", getValueMatrix(matrix, i, j));
        }
        printf_s("\n");
    }
}