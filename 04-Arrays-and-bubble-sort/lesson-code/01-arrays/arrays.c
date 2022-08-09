#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int arr[5]; // объявление массива
    arr[0] = 3; // запись значения в первую ячейку массива (индекс 0)

    // всегда следите, чтобы не происходило обращений к элементам за пределами массива
    // в данном случае индексы должны быть в промежутке [0, 4], т.к. в массиве 5 элементов
    // иначе вы получите ошибку типа "index out of range"
    for (int i = 1; i < 5; ++i) {
        // заполнение массива такими элементами,
        // что каждый следующий в два раза превосходит предыдущий
        arr[i] = arr[i - 1] * 2; // arr[0] уже задан, начинаем с arr[1]
    }

    // вывод содержимого массива в консоль:
    printf_s("arr:\n");
    for (int i = 0; i < 5; ++i) {
        printf_s("%d ", arr[i]);
    }
    printf_s("\n\n");
    // можно инициализировать значения массива при его объявлении
    // если при этом не указать размер массива,
    // то он автоматически установится равным количеству элементов
    char chArray[] = { 'a', 'r', 'r', 'a', 'y'}; // эквивалентно: char chArray[5] = { 'a', 'r', 'r', 'a', 'y'};
    printf_s("chArray:\n");
    for (int i = 0; i < sizeof(chArray); ++i) {
        printf_s("%c ", chArray[i]);
    }
    printf_s("\n\n");

    // неинициализированный массив будет заполнен "мусором":
    int uninitializedArray[5];
    printf_s("uninitializedArray:\n");
    // sizeof() применительно к переменной (либо типу) возвращает её размер в байтах
    // применительно к массиву возвращает, соответственно, общий размер массива
    for (int i = 0; i < sizeof(uninitializedArray) / sizeof(int); ++i) {
        printf_s("%d ", uninitializedArray[i]);
    }
    printf_s("\n\n");

    // заполнение массива с клавиатуры
    printf_s("Enter a %d numbers: ", sizeof(uninitializedArray) / sizeof(int));
    for (int i = 0; i < sizeof(uninitializedArray) / sizeof(int); ++i) {
	scanf_s("%d", &uninitializedArray[i]);
    }
    printf_s("Now uninitializedArray:\n");
    for (int i = 0; i < sizeof(uninitializedArray) / sizeof(int); ++i) {
        printf_s("%d ", uninitializedArray[i]);
    }
    printf_s("\n\n");

    // если в инициализирующем выражении значений меньше, чем размер массива,
    // то оставшимся элементам будет присвоено значение 0
    int partlyInitializedArray[10] = { 8, 4, 9, 11 };
    printf_s("partlyInitializedArray:\n");
    for (int i = 0; i < 10; ++i) {
        printf_s("%d ", partlyInitializedArray[i]);
    }
    printf_s("\n\n");

    // если нужен массив нулей:
    int zeroArray[7] = { 0 };
    printf_s("zeroArray:\n");
    for (int i = 0; i < 5; ++i) {
        printf_s("%d ", zeroArray[i]);
    }
    printf_s("\n\n");


    system("pause");
    return 0;
}
