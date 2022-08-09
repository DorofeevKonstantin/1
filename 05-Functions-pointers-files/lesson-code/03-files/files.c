#include <stdio.h> // функции для работы с файлами 
#include <stdlib.h>
#include <time.h>

#define NUMBERS_COUNT 100
#define ERR_OPEN_FILE "ERROR: couldn't open a file\n"

void prepairInputFile();

int main(void) {
    prepairInputFile();

    FILE* input, * output;
    // fopen_s возвращает 0 при успешной работе
    // всегда проверяйте открылись ли файлы, с которыми вы собираетесь работать
    if (fopen_s(&input, "numbers.txt", "r") || fopen_s(&output, "odd.txt", "w")) { // показать режим append
        // если какой-то из файлов не открылся -- вывести сообщение об ошибке,
        // закрыть все файлы и завершить выполнение программы с кодом ошибки
        printf_s(ERR_OPEN_FILE);
        _fcloseall();
        exit(1);
    }
    // считаем числа из файла numbers.txt и сохраним нечётные в файл odd.txt
    int tmp;
    while (fscanf_s(input, "%d ", &tmp) != EOF) { // читаем пока не дойдем до конца файла
        if (!(tmp % 2)) {
            fprintf_s(output, "%d ", tmp); // если четное -- записываем в файл
        }
    }
    printf_s("DONE\n");

    // не забываем закрыть файлы когда закончили работу с ними
    fclose(input);
    fclose(output);
    system("pause");
    return 0;
}

void prepairInputFile() {
    static seed = 0;
    if (!seed) srand((unsigned)time(NULL));
    FILE* file;
    if (fopen_s(&file, "numbers.txt", "w")) {
        printf_s(ERR_OPEN_FILE);
        exit(1);
    }
    for (int i = 0; i < NUMBERS_COUNT; ++i) fprintf_s(file, "%d ", ((rand() % 2 ? 1 : -1) * rand() % 100));
    fclose(file);
}