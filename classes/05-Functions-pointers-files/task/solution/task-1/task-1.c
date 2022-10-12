/*
в файле numbers записано не более 100 чисел, необходимо их считать из файла,
отсортировать по возрастанию и записать в файл sorted.
Сортировка должна быть реализована отдельной функцией.
*/
#include <stdio.h>
#include <stdlib.h>

#define ERR_OPEN_FILE "ERROR:couldn't open file '%s'\nEXIT WITH ERROR CODE 1\n"

#define MAX_ARRAY_SIZE 100
#define INPUT_FILE_NAME "numbers"
#define OUTPUT_FILE_NAME "sorted"

void sort(int[MAX_ARRAY_SIZE], int numbersCount);
// возвращает количество прочитанных чисел
int readNumbersFromFileToArray(FILE* file, int arr[MAX_ARRAY_SIZE]);
void printNumbersFromArrayToFile(FILE* file, int arr[MAX_ARRAY_SIZE], int numbersCount);

int main(void) {
    FILE* input, *output;
    int arr[MAX_ARRAY_SIZE];

    if (fopen_s(&input, INPUT_FILE_NAME, "r")) {
        printf_s(ERR_OPEN_FILE, INPUT_FILE_NAME);
        exit(1);
    }
    if (fopen_s(&output, OUTPUT_FILE_NAME, "w")) {
        fclose(input);
        printf_s(ERR_OPEN_FILE, OUTPUT_FILE_NAME);
        exit(1);
    }

    int numbersCount = readNumbersFromFileToArray(input, arr);
    fclose(input); // файл input больше не нужен
    sort(arr, numbersCount);
    printNumbersFromArrayToFile(output, arr, numbersCount);
    fclose(output);
    printf_s("DONE!\n");

    system("pause");
    return 0;
}

void sort(int arr[MAX_ARRAY_SIZE], int numbersCount) {
    for (int i = 0; i < numbersCount; ++i) {
        for (int j = 1; j < numbersCount - i; ++j) {
            if (arr[j] < arr[j - 1]) {
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
}

int readNumbersFromFileToArray(FILE* file, int arr[MAX_ARRAY_SIZE]) {
    int counter = 0;
    // обратите внимание на проверку counter < MAX_ARRAY_SIZE
    while (counter < MAX_ARRAY_SIZE && (fscanf_s(file, "%d", &arr[counter]) != EOF)) {
        ++counter;
    }

    return counter;
}

void printNumbersFromArrayToFile(FILE* file, int arr[MAX_ARRAY_SIZE], int numbersCount) {
    for (int i = 0; i < numbersCount; ++i) {
        fprintf_s(file, "%d ", arr[i]);
    }
}
