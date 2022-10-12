/*
Дополнить #4 функцией, выполняющей следующее:
после количества сломанных клавиш, на следующей строке в консоль выводятся
номера клавиш в порядке убывания их оставшегося запаса прочности (сломанные
клавиши равносильны между собой, их порядок не важен)
*/
#include <stdio.h>
#include <stdlib.h>

#define ERR_OPEN_FILE "ERROR:couldn't open file '%s'\nEXIT WITH ERROR CODE 1\n"

#define FILE_NAME "new-keyboard.txt"
#define MAX_KEYS 101

int getNewKeyboard(FILE*,int[MAX_KEYS]);

int useKeyboard(FILE*, int[MAX_KEYS],int);

void printSortedKeyboardStatus(int[MAX_KEYS], int);

int main(void) {
    FILE* file;
    if (fopen_s(&file, FILE_NAME, "r")) {
        printf_s(ERR_OPEN_FILE, FILE_NAME);
        system("pause");
        return 1;
    }
    int keyboard[MAX_KEYS], keysCount;
    keysCount = getNewKeyboard(file, keyboard);
    printf_s("Broken keys: %d\n", useKeyboard(file, keyboard, keysCount));
    fclose(file);
    printSortedKeyboardStatus(keyboard, keysCount);
    printf_s("\n");

    system("pause");
    return 0;
}

int getNewKeyboard(FILE* file, int keyboard[MAX_KEYS]) {
    int keysCount = 0;
    fscanf_s(file, "%d", &keysCount);
    for (int i = 1; i <= keysCount; ++i) {
        fscanf_s(file, "%d", &keyboard[i]);
    }
    return keysCount;
}

int useKeyboard(FILE* file, int keyboard[MAX_KEYS], int keysCount) {
    int pressedKey = 0, brokenKeys = 0;
    while (fscanf_s(file, "%d", &pressedKey) != EOF) {
        if (keyboard[pressedKey] > -1) {
            --keyboard[pressedKey];
        }
    }
    for (int i = 1; i <= keysCount; ++i) {
        brokenKeys += (keyboard[i] < 0);
    }

    return brokenKeys;
}

void printSortedKeyboardStatus(int keyboard[MAX_KEYS], int keysCount) {
    // заведем массив где будем хранить текущий порядок
    // клавиш представленных в массиве keyboard
    int keysIndexes[MAX_KEYS];
    for (int i = 1; i <= keysCount; ++i) keysIndexes[i] = i;

    // параллельно сортируем эти два массива
    // начинаем со второго индекса, т.к. первый элемент по индексу 1
    // второй соответственно по индексу 2
    for (int i = 0; i < keysCount; ++i) {
        for (int j = 2; j <= keysCount - i; ++j) {
            if (keyboard[j] > keyboard[j - 1]) {
                int tmp = keyboard[j];
                keyboard[j] = keyboard[j - 1];
                keyboard[j - 1] = tmp;
                tmp = keysIndexes[j];
                keysIndexes[j] = keysIndexes[j - 1];
                keysIndexes[j - 1] = tmp;
            }
        }
    }

    // выводим отсортированный порядок клавиш
    for (int i = 1; i <= keysCount; ++i) {
        printf_s("%d ", keysIndexes[i]);
    }
}
