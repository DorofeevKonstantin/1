#include <stdio.h>
#include <stdlib.h>

// argc (argument count)- количество переданных аргументов командной строки (int)
// argv (argument vector)- аргументы командной строки (массив строк)
int main(int argc, char* argv[]) {
    // argv[0] -- по соглашению всегда имя вызываемой программы
    for (int i = 0; i < argc; ++i) {
        printf_s("arg[%d]: %s\n", i, argv[i]);
    }

    system("pause");
    return 0;
}