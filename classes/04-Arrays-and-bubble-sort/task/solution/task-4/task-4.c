#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int main() {
    int arr[ARRAY_SIZE];
    // заполнение массива случайными целыми числами из промежутка (-100, 100):
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (rand() % 2 ? -1 : 1) * (rand() % 100);
    }

    int number;
    int arr1[ARRAY_SIZE], arr2[ARRAY_SIZE], arrResult[ARRAY_SIZE];
    int count1 = 0, count2 = 0;
    printf_s("Enter an integer: ");
    scanf_s("%d", &number);

    // разделим числа на два массива:
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (arr[i] % number) {
            arr1[count1++] = arr[i];
        }
        else {
            arr2[count2++] = arr[i];
        }
    }

    // отсортируем оба
    for (int i = count1; i >= 1; --i) {
        for (int j = 1; j < i; ++j) {
            if (arr1[j] > arr1[j - 1]) {
                int tmp = arr1[j];
                arr1[j] = arr1[j - 1];
                arr1[j - 1] = tmp;
            }
        }
    }
    for (int i = count2; i >= 1; --i) {
        for (int j = 1; j < i; ++j) {
            if (arr2[j] > arr2[j - 1]) {
                int tmp = arr2[j];
                arr2[j] = arr2[j - 1];
                arr2[j - 1] = tmp;
            }
        }
    }
    for (int i = 0; i < count1; ++i) {
        printf_s("%d ", arr1[i]);
    }
    printf("\n");
    for (int i = 0; i < count2; ++i) {
        printf_s("%d ", arr2[i]);
    }
    printf("\n");

    // объединение массивов:
    // алгоритм:
    // будем индексироваться по двум массивам, начиная с нулевых
    // сравниваем два элемента, больший записываем в итоговый массив
    // и увеличиваем индекс на 1 для массива, в котором был больший элемент
    // повторяем эти действия пока не дойдем до конца одного из массивов
    int i = 0, j = 0;
    while (i < count1 && j < count2) {
        if (arr2[j] < arr1[i]) {
            arrResult[i + j] = arr1[i];
            ++i;
        }
        else {
            arrResult[i + j] = arr2[j];
            ++j;
        }
    }
    //  когда один из массивов закончился
    //  нужно скопировать оставшиеся в другом массиве
    //  элементы в конец итогового массива
    while (i < count1) {
	    arrResult[i + j] = arr1[i];
	    ++i;
    }
    while (j < count2) {
	    arrResult[i + j] = arr2[j];
	    ++j;
    }
    // вывод в консоль
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf_s("%d ", arrResult[i]);
    }
    printf_s("\n");

    system("pause");
    return 0;
}
