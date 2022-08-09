#include "Matix.h"

#include <malloc.h>

// в этой функции выделяем память для хранения матрицы согласно переданным размерам
// и если передан массив со значениями - копируем их в матрицу
// если же вместо массива передан NULL, то оставляем матрицу заполненной нулями
// также уславливаемся, что height и width обязаны быть ненулевыми
errno_t newMatrix(MatrixPtr* matrix, value_t** values, size_t height, size_t width) {
    if (height == 0 || width == 0) return ERR_WRONG_FUNC_ARGS;
    *matrix = (MatrixPtr)malloc(sizeof(Matrix));
    if (*matrix == NULL) return errno;
    (*matrix)->values = (value_t**)malloc(sizeof(value_t*) * height);
    if ((*matrix)->values == NULL) {
        free(*matrix);
        *matrix = NULL;
        return errno;
    }
    for (size_t i = 0; i < height; ++i) {
        (*matrix)->values[i] = (value_t*)calloc(width, sizeof(value_t));

        if ((*matrix)->values[i] == NULL) {
            for (size_t j = 0; j < i; ++j) free((*matrix)->values[j]);
            free((*matrix)->values);
            free(*matrix);
            *matrix = NULL;
            return errno;
        }
    }

    if (values != NULL) {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                (*matrix)->values[i][j] = values[i][j];
            }
        }
    }

    (*matrix)->height = height;
    (*matrix)->width = width;
    // т.к. матрица только что была создана, помечаем, что определитель у неё
    // ещё не известен
    (*matrix)->detIsKnown = false;

    return ERR_SUCCESS;
}

// освобождаем всю память, которую выделяли
errno_t deleteMatrix(MatrixPtr matrix) {
    if (matrix == NULL) return ERR_WRONG_FUNC_ARGS;
    for (size_t i = 0; i < matrix->height; ++i) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
    return ERR_SUCCESS;
}

value_t getValueMatrix(MatrixPtr matrix, size_t i, size_t j) {
    return matrix->values[i][j];
}

errno_t setValueMatrix(MatrixPtr matrix, size_t i, size_t j, value_t value) {
    if (i >= matrix->height || j >= matrix->width) return ERR_WRONG_FUNC_ARGS;
    matrix->values[i][j] = value;
    // т.к. изменились хранимые значения в матрице определитель будет
    // необходимо пересчитать
    matrix->detIsKnown = false;
    return ERR_SUCCESS;
}

errno_t transposeMatrix(MatrixPtr* dest, MatrixPtr matrix) {
    errno_t error = newMatrix(dest, NULL, matrix->width, matrix->height);
    if (error != ERR_SUCCESS) return error;
    for (size_t i = 0; i < matrix->height; ++i) {
        for (size_t j = 0; j < matrix->width; ++j) {
            (*dest)->values[j][i] = matrix->values[i][j];
        }
    }

    return ERR_SUCCESS;
}

// вспомогательная функция, выделяющая в матрице подматрицу без i-ой строки и 
// j-ого столбца
errno_t getSubmatrix(MatrixPtr* dest, MatrixPtr matrix, size_t i, size_t j) {
    errno_t error = newMatrix(dest, NULL, matrix->height - 1, matrix->width - 1);
    size_t lineShift = 0, columnShift = 0;
    for (size_t m = 0; m < matrix->height; ++m) {
        // пропускаем i-ую строку и устанавливаем сдвиг по строкам в 1
        if (m == i) {
            lineShift = 1;
            continue;
        }
        // с началом каждой строки сдвиг по столбцам обнуляется
        columnShift = 0;
        for (size_t n = 0; n < matrix->width; ++n) {
            // пропускаем j столбец, устанавливаем сдвиг по столбцам в 1
            if (n == j) {
                columnShift = 1;
                continue;
            }
            // вычитаем сдвиги по строкам и столбцам для корректировки
            // индексов в результирующей матрице
            (*dest)->values[m - lineShift][n - columnShift] = matrix->values[m][n];
        }
    }

    return ERR_SUCCESS;
}

// рекурсивное вычисление определителя разложением по первой строке
errno_t determinantMatrix(MatrixPtr matrix, value_t* determinant) {
    if (matrix->height != matrix->width) return ERR_WRONG_MATRIX_SIZE;
    // если определитель матрицы был посчитан ранее и до сих пор актуален
    // то не пересчитываем, а используем имеющееся значение
    if (matrix->detIsKnown && determinant != NULL) {
        *determinant = matrix->determinant;
        matrix->detIsKnown = true;
        return ERR_SUCCESS;
    }
    if (matrix->height == 1) {
        matrix->determinant = matrix->values[0][0];
        if (determinant != NULL) *determinant = matrix->determinant;
        matrix->detIsKnown = true;
        return ERR_SUCCESS;
    }
    if (matrix->height == 2) {
        matrix->determinant = matrix->values[0][0] * matrix->values[1][1] - matrix->values[0][1] * matrix->values[1][0];
        if (determinant != NULL) *determinant = matrix->determinant;
        matrix->detIsKnown = true;
        return ERR_SUCCESS;
    }
    // для большей оптимизации здесь можно было бы добавить частный случай
    // расчета по формуле для матрицы 3 ранга

    MatrixPtr submatrix;
    value_t minor = 0;

    matrix->determinant = 0;
    int sign = 1;
    // будем перебирать элементы в первой строке
    for (size_t j = 0; j < matrix->width; ++j) {
        // получаем подматрицу без первой строки и j-ого столбца
        errno_t error = getSubmatrix(&submatrix, matrix, 0, j);
        if (error != ERR_SUCCESS) {
            free(submatrix);
            return error;
        }
        // рекурсивно считаем дополнительный минор
        determinantMatrix(submatrix, &minor);
        // прибавляем алгебраическое 
        matrix->determinant += sign * minor * matrix->values[0][j];
        // не забываем о чередующемся знаке у алгебраических дополнений
        sign *= -1;
        // и не забываем удалять матрицы, чтобы не текла память
        deleteMatrix(submatrix);
    }
    // отметили, что теперь имеется сохраненное актуальное значение определителя
    matrix->detIsKnown = true;
    if (determinant != NULL) *determinant = matrix->determinant;

    return ERR_SUCCESS;
}

errno_t sumMatrix(MatrixPtr* dest, MatrixPtr first, MatrixPtr second) {
    if (first->height != second->height ||
        first->width != second->width)
        return ERR_WRONG_MATRIX_SIZE;

    errno_t error = newMatrix(dest, NULL, first->height, first->width);
    if (error != ERR_SUCCESS) return error;
    for (size_t i = 0; i < (*dest)->height; ++i) {
        for (size_t j = 0; j < (*dest)->width; ++j) {
            (*dest)->values[i][j] = first->values[i][j] + second->values[i][j];
        }
    }
    return ERR_SUCCESS;
}

errno_t subMatrix(MatrixPtr* dest, MatrixPtr first, MatrixPtr second) {
    if (first->height != second->height ||
        first->width != second->width)
        return ERR_WRONG_MATRIX_SIZE;

    errno_t error = newMatrix(dest, NULL, first->height, first->width);
    if (error != ERR_SUCCESS) return error;
    for (size_t i = 0; i < (*dest)->height; ++i) {
        for (size_t j = 0; j < (*dest)->width; ++j) {
            (*dest)->values[i][j] = first->values[i][j] - second->values[i][j];
        }
    }
    return ERR_SUCCESS;
}

errno_t multMatrix(MatrixPtr* dest, MatrixPtr left, MatrixPtr right) {
    if (left->width != right->height) return ERR_WRONG_MATRIX_SIZE;

    errno_t error = newMatrix(dest, NULL, left->height, right->width);
    if (error != ERR_SUCCESS) return error;
    for (size_t i = 0; i < (*dest)->height; ++i) {
        for (size_t j = 0; j < (*dest)->width; ++j) {
            for (size_t k = 0; k < left->width; ++k) {
                (*dest)->values[i][j] += left->values[i][k] * right->values[k][j];
            }
        }
    }

    return ERR_SUCCESS;
}
