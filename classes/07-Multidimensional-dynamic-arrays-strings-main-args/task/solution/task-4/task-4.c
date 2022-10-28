/*
Существует файл, в котором записаны строки длиной не более 100. Строки
представлены в зашифрованном виде: каждое слово исходного текста было поделено
на две равные части (условимся, что все слова имеют чётную длину), и эти части в
слове переставлены местами.

Задача: получить имя файла как аргумент командной строки, считать строки из файла,
расшифровать их и вывести в лексикографическом порядке (сами строки, а не слова в
строках).

Задание выглядит большим и сложным, и может даже казаться вам непосильным, в таком случае
необходимо разбить его на более мелкие задания и разбираться по отдельности с каждым
из них, т.е. выполнить его декомпозицию. Давайте сделаем это.

Декомпозиция (выделим подзадачи и сразу определимся с их решением):

1. Посчитать количество строк в файле, чтобы сразу выделить под них память,
а не реаллоцировать её (необязательный пункт, можно реаллоцировать массив строк
по мере их чтения из файла, но в данном решении количество строк считается заранее).
Просто считаем количество символов переноса строки в файле.
Реализация в функции countStringsInFile.

2. Считать строки из файла
Функция readStringFromFile.

3. Выделить из строки отдельные слова
Ничего сложного: идём с начала слова до тех пор, пока не встретим пробельный символ
либо конец файла (начало слова - символ, следующий за пробельным символом).
Функция getWordEnd.

4. Расшифровать слово
Делим слово пополам и свапаем получившиеся половины.
Функция decryptWord.

5. Отсортировать строки в лексикографическом порядке.
Сортируем указатели на строки в массиве пузырьковой сортировкой.
Функция sortStrings.
Как сравнить 2 строки: ищем минимальный индекс i такой, что символы, расположенные
по этому индексу в сравниваемых строках, не равны (т.е. firstString[i] != secondString[i])
и, основываясь на этом неравенстве, сравниваем строки. Если такого i нет, значит строки
равны.
Функция stringCompare.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 100

#define ERROR "ERROR\nEXIT WITH ERROR CODE 1"
#define ERR_OPEN_FILE ERROR
#define ERR_ALLOC_MEM ERROR
#define ERR_READ_FILE ERROR

char** alloc2DCharArray(int height, int width);
int countStringsInFile(FILE* file);
void decryptString(char* string);
void decryptWord(char* begin, char* end);
void free2DCharArray(char** arr, int height);
char* getWordEnd(char* begin);
void printStrings(char** strings, int count);
int readStringFromFile(FILE* file, char* buf, int bufSize);
void sortStrings(char** strings, int count);
int stringCompare(char* first, char* second);
void swap(void* first, void* second, size_t size);

int main(int argc, char** argv) {
    FILE* file;
    if (!argv[1] || fopen_s(&file, argv[1], "r")) {
        printf_s(ERR_OPEN_FILE);
        exit(1);
    }
    int stringsCount = countStringsInFile(file);
    char** strings = alloc2DCharArray(stringsCount, MAX_STRING_LENGTH + 1);
    if (!strings) {
        printf_s(ERR_ALLOC_MEM);
        exit(1);
    }
    for (int i = 0; i < stringsCount; ++i) {
        if (readStringFromFile(file, strings[i], MAX_STRING_LENGTH + 1) == EXIT_FAILURE) {
            printf_s(ERR_READ_FILE);
            exit(1);
        }
        decryptString(strings[i]);
    }
    sortStrings(strings, stringsCount);
    printStrings(strings, stringsCount);

    free2DCharArray(strings, stringsCount);

    system("pause");
    return 0;
}

char** alloc2DCharArray(int height, int width) {
    char** arr = (char**)malloc(sizeof(char*) * height);
    if (!arr) {
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        if (!(arr[i] = (char*)malloc(sizeof(char) * width))) {
            for (int j = 0; j < i; ++j) free(arr[j]);
            free(arr);
            return NULL;
        }
    }
    return arr;
}

int countStringsInFile(FILE* file) {
    long currentPos = ftell(file);
    rewind(file);
    int counter = 0;
    char buf;
    while ((buf = fgetc(file)) != EOF)
        if (buf == '\n') ++counter;
    fseek(file, currentPos, SEEK_SET);
    return counter;
}

void decryptString(char* string) {
    char* begin = string;
    while (*begin) {
        while (isspace(*begin)) ++begin;
        char* end = getWordEnd(begin);
        decryptWord(begin, end);
        begin = end + 1;
    }
}

void decryptWord(char* begin, char* end) {
    int wordLength = (int)(end - begin + 1);
    end = begin + wordLength / 2;
    swap(begin, end, sizeof(char) * wordLength / 2);
    /*
    Решение для случая без ограничения на то, что длина строк всегда чётная:
    //int wordLength = (int)(end - begin + 1);
    //char copyWord[MAX_STRING_LENGTH];
    //memcpy_s(copyWord, MAX_STRING_LENGTH, begin, wordLength);
    //memcpy_s(begin, wordLength, copyWord + wordLength / 2, wordLength - wordLength / 2 + (wordLength % 2));
    //memcpy_s(begin + wordLength / 2 + (wordLength % 2), wordLength / 2, copyWord, wordLength / 2);
    */
}

void free2DCharArray(char** arr, int height) {
    for (int i = 0; i < height; ++i) free(arr[i]);
    free(arr);
}

char* getWordEnd(char* begin) {
    while (*begin && !isspace(*begin)) ++begin;
    return --begin;
}

void printStrings(char** strings, int count) {
    for (int i = 0; i < count; ++i){
        printf_s("%s\n", strings[i]);
    }
}

int readStringFromFile(FILE* file, char* buf, int bufSize) {
    if (fgets(buf, bufSize, file)) {
        size_t length = strnlen_s(buf, bufSize);
        buf[length - 1] = '\0';
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void sortStrings(char** strings, int count) {
    for (int i = 1; i < count; ++i)
        for (int j = 1; j < count; ++j)
            if (stringCompare(strings[j - 1], strings[j]) == 1)
                swap(strings + j, strings + j - 1, sizeof(char*));
}

int stringCompare(char* first, char* second) {
    while (*first == *second && *first && *second) ++first, ++second;
    if (!*first && !*second) return 0;
    if (*first < *second) return -1;
    return 1;
}

void swap(void* first, void* second, size_t size) {
    void* tmp = malloc(size);
    memcpy_s(tmp, size, first, size);
    memcpy_s(first, size, second, size);
    memcpy_s(second, size, tmp, size);
    free(tmp);
}
