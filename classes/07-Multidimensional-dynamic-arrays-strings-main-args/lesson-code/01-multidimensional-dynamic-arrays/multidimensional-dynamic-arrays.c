#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\nEXIT WITH ERROR CODE 1\n"

int** alloc2DArray(int height, int width);
void free2DArray(int** arr, int height);

double*** alloc3DArray(int firstDim, int secondDim, int thirdDim);
void free3DArray(double*** arr, int firstDim, int secondDim);

void print2DArray(int** arr, int height, int width);
void printComplexMatrix(double***, int, int);

int main(void) {
    srand((unsigned)time(NULL));

    int height, width;
    printf_s("Enter size (HxW): ");
    scanf_s("%dx%d", &height, &width);
    // динамический двумерный массив представляет собой массив указателей:
    int** array2D = alloc2DArray(height, width);
    // заполним этот массив таблицей умножения
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            array2D[i][j] = (i + 1) * (j + 1);
        }
    }
    printf_s("Dynamic array:\n");
    print2DArray(array2D, height, width);
    // освободим память:
    free2DArray(array2D, height);


    // МАТРИЦА КОМПЛЕКСНЫХ ЧИСЕЛ

    // создадим двумерный массив комплексных чисел, которые будут
    // организованы как массивы из двух вещественных чисел
    // т.е. это будет трехмерный массив
    double*** complexMatrix = alloc3DArray(height, width, 2);
    // память аллоцирована, теперь нагенерируем числа
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 2; ++k) {
                complexMatrix[i][j][k] = (double)rand() / RAND_MAX * 100;
            }
        }
    }
    // выведем
    printf_s("Complex matrix:\n");
    printComplexMatrix(complexMatrix, height, width);
    // освободим память
    free3DArray(complexMatrix, height, width);

    system("pause");
    return 0;
}

int** alloc2DArray(int height, int width) {
    int** arr = malloc(height * sizeof(int*));
    if (!arr) {
        printf_s(ERR_ALLOC_MEM);
        exit(1);
    }
    // теперь нужно выделить память для каждого подмассива
    for (int i = 0; i < height; ++i) {
        // в случае неудачи нужно освободить память,
        // которую мы уже выделили
        if (!(arr[i] = malloc(width * sizeof(int)))) {
            for (int j = 0; j < i; ++j) {
                free(arr[j]);
            }
            free(arr);
            printf_s(ERR_ALLOC_MEM);
            exit(1);
        }
    }
    return arr;
}

void free2DArray(int** arr, int height) {
    // освобождать память дин. массива нужно изнутри наружу
    // поэтому сначала освободим вложенные подмассивы, а затем
    // внешний массив указателей
    for (int i = 0; i < height; ++i) {
        free(arr[i]);
    }
    free(arr);
}

double*** alloc3DArray(int firstDim, int secondDim, int thirdDim) {
    double*** arr = malloc(firstDim * sizeof(double**));
    if (!arr) {
        printf_s(ERR_ALLOC_MEM);
        exit(1);
    }
    for (int i = 0; i < firstDim; ++i) {
        if (!(arr[i] = malloc(secondDim * sizeof(double*)))) {
            for (int j = 0; j < i; ++j) {
                free(arr[j]);
            }
            free(arr);
            printf_s(ERR_ALLOC_MEM);
            exit(1);
        }
    }
    for (int i = 0; i < firstDim; ++i) {
        for (int j = 0; j < secondDim; ++j) {
            if (!(arr[i][j] = malloc(2 * sizeof(double)))) {
                // освобождаем предыдущие строки
                for (int n = 0; n < i; ++n) {
                    for (int m = 0; m < secondDim; ++m) {
                        free(arr[n][m]);
                    }
                    free(arr[n]);
                }
                // освобождаем текущую строку
                for (int n = 0; n < j; ++n) {
                    free(arr[i][n]);
                }
                free(arr[i]);
                // освобождаем внешний массив
                free(arr);
                printf_s(ERR_ALLOC_MEM);
                exit(1);
            }
        }
    }
    return arr;
}

void free3DArray(double*** arr, int firstDim, int secondDim) {
    for (int i = 0; i < firstDim; ++i) {
        for (int j = 0; j < secondDim; ++j) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}

void print2DArray(int** arr, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf_s("%d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

void printComplexMatrix(double*** arr, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf_s("(%.2lf, %.2lf)\t", arr[i][j][0], arr[i][j][1]);
        }
        printf_s("\n");
    }
}
