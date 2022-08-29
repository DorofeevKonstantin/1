#pragma once

#include "myErrors.h"

#include <stdbool.h>
#include <stddef.h>

// для удобства зададим тип элементов матрицы через typedef
// если захотим в будущем его поменять - это будет просто сделать
typedef int value_t;

typedef struct {
    value_t** values;
    size_t height;
    size_t width;
    // определитель будем тоже хранить, чтобы не считать его каждый раз заново,
    // когда он уже был посчитан ранее
    bool detIsKnown;
    value_t determinant;
} Matrix;

typedef Matrix* MatrixPtr;

// при работе с матрицами создавать и удалять их будем исключительно специальными
// функциями
errno_t newMatrix(MatrixPtr* matrix, value_t** values, size_t height, size_t width);
errno_t deleteMatrix(MatrixPtr matrix);
// получение элементов матрицы
value_t getValueMatrix(MatrixPtr matrix, size_t i, size_t j);
// изменение элементов матрицы
errno_t setValueMatrix(MatrixPtr matrix, size_t i, size_t j, value_t value);

errno_t transposeMatrix(MatrixPtr* dest, MatrixPtr matrix);
errno_t determinantMatrix(MatrixPtr matrix, value_t* determinant);
errno_t sumMatrix(MatrixPtr* dest, MatrixPtr first, MatrixPtr second);
errno_t subMatrix(MatrixPtr* dest, MatrixPtr first, MatrixPtr second);
errno_t multMatrix(MatrixPtr* dest, MatrixPtr left, MatrixPtr right);
