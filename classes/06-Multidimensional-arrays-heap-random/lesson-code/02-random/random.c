#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time()

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\nEXIT WITH ERROR CODE 1\n"

void printIntArray(int*, int);
void printDoubleArray(double*, int);

int main(void) {
    srand((unsigned)time(NULL)); // этот вызов нужен, чтобы каждый раз
                       // при запуске программы генерируемые числа
                       // были разными
    int randNumb = rand(); // инициализируем переменную псевдослучайным значением
    printf_s("generated randNumb: %d\n", randNumb);
    printf_s("range of rand(): [0, %d]\n", RAND_MAX);

    // создадим массив случайного размера
    int size = rand() % 50; // т.к. берем получаемое значение по модулю 50,
                            // то числа будут из диапазона [0, 49]
    int* iArray = malloc(sizeof(int) * size);
    if (!iArray) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    printf_s("Array size: %d\n", size);
    // заполним массив случайными значениями в диапазоне [6, 37]
    for (int i = 0; i < size; ++i) {
        iArray[i] = rand() % 32 + 6;
    }
    printf_s("[6, 37]:\n");
    printIntArray(iArray, size);

    // [-10, 81]
    // обратите внимание, что распределение знаков в этом случае
    // будет смещено и положительные числа преобладают
    for (int i = 0; i < size; ++i) {
        iArray[i] = rand() % 92 - 10;
    }
    printf_s("[-10, 81]:\n");
    printIntArray(iArray, size);

    // далее используется тернарный оператор
    // простое пояснение к нему:
    // A ? B : C
    // A -- логическое выражение, если оно верно,
    // то на место тернарного оператора
    // подставляется выражение B, иначе -- выражение C
    // технически более точное описание найдите самостоятельно

    // предположим нужны числа случайного знака,
    // модули которых в диапазоне [5, 13]
    for (int i = 0; i < size; ++i) {
        // в таком случае знак получим отдельно от модуля числа
        // в данном случае положительные и отрицательные числа
        // будут распределены между собой более равномерно
        int sign = rand() % 2 ? 1 : -1;
        iArray[i] = rand() % 9 + 5;
        iArray[i] *= sign;
    }
    printf_s("+-[5, 13]:\n");
    printIntArray(iArray, size);

    // и, конечно, числа будут более равномерно распределены по знакам,
    // если взять диапазон [A, -A]
    for (int i = 0; i < size; ++i) {
        iArray[i] = rand() % 102 - 50; // подумайте какой здесь диапазон чисел
    }
    printf_s("last range:\n");
    printIntArray(iArray, size);
    free(iArray); // не забываем!

    // вещественные числа:
    double* dArray = malloc(size * sizeof(double));
    if (!dArray) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    // [12, 56]
    for (int i = 0; i < size; ++i) {
        dArray[i] = (double)rand() / RAND_MAX * 44 + 12;
    }
    printf_s("float values:\n");
    printDoubleArray(dArray, size);

    free(dArray);

    system("pause");
    return 0;
}

void printIntArray(int* arr, int size) {
    const int* end = arr + size;
    while (arr < end) printf_s("%d ", *(arr++));
    printf_s("\n");
}

void printDoubleArray(double* arr, int size) {
    const double* end = arr + size;
    while (arr < end) printf_s("%.2lf ", *(arr++));
    printf_s("\n");
}