/*
Задача: написать программу, которая определяет состояние клавиш клавиатуры после
её использования. Для каждой из клавиш известно количество нажатий, которое она
может выдержать, а также известна последовательность клавиш, которые нажимает пользователь.
В файле new-keyboard.txt в первой строке записано число n из диапазона
[1, 100] -- количество клавиш на клавиатуре. В следующей строке записано
n чисел -- запас прочности для каждой из клавиш соответственно (клавиши нумеруются
от 1 до n). В третьей строке записано неизвестное количество чисел из
диапазона [1, n] -- последовательность нажатий пользователем клавиш с соответствующими номерами.

Выведите в консоли число клавиш, которые были сломаны в процессе эксплуатации клавиатуры.
Код должен быть логично разбит на функции по вашему усмотрению.
*/
#include <stdio.h>
#include <stdlib.h>

#define ERR_OPEN_FILE "ERROR:couldn't open file '%s'\nEXIT WITH ERROR CODE 1\n"

#define FILE_NAME "new-keyboard.txt"
#define MAX_KEYS 101 // на один больше, чтобы можно было
                     //спокойно обращаться к индексам от 1 до 100

// заполняет массив с прочностями клавиш и
// возвращает количество клавиш в новой клавиатуре
int getNewKeyboard(FILE*,int[MAX_KEYS]);

// моделирует процесс использования клавиатуры и
// возвращает количество сломанных в процессе клавиш
int useKeyboard(FILE*, int[MAX_KEYS],int);

int main(void) {
    FILE* file;
    if (fopen_s(&file, FILE_NAME, "r")) {
        printf_s(ERR_OPEN_FILE, FILE_NAME);
        system("pause");
        exit(1);
    }
    
    int keyboard[MAX_KEYS], keysCount;
    keysCount = getNewKeyboard(file, keyboard);
    printf_s("Broken keys: %d\n", useKeyboard(file, keyboard, keysCount));
    fclose(file);

    system("pause");
    return 0;
}

int getNewKeyboard(FILE* file, int keyboard[MAX_KEYS]) {
    int keysCount = 0;
    // читаем количество клавиш
    fscanf_s(file, "%d", &keysCount);
    // читаем исходные прочности клавиш (для удобства начинаем с индекса 1)
    for (int i = 1; i <= keysCount; ++i) {
        fscanf_s(file, "%d", &keyboard[i]);
    }
    return keysCount;
}

int useKeyboard(FILE* file, int keyboard[MAX_KEYS], int keysCount) {
    int pressedKey = 0, brokenKeys = 0;
    // т.к. клавиши в массиве имеют точно индексы равные их номерам в задаче ([1, keysCount])
    // просто считываем число из файла и уменьшаем запас прочности клавиши
    // с соответствующим номером
    while (fscanf_s(file, "%d", &pressedKey) != EOF) {
        // если клавиша уже сломана - нет смысла дальше подсчитывать её прочность
        // такая проверка предотвратит переполнение типа в случае, если было сделано
        // огромное количество нажатий клавиши:
        if (keyboard[pressedKey] > -1) {
            --keyboard[pressedKey];
        }
    }
    // когда значения в файле закончились --  подсчитываем сломанные клавиши
    for (int i = 1; i <= keysCount; ++i) {
        brokenKeys += (keyboard[i] < 0);
    }

    return brokenKeys;
}
