// комментарий

/* многострочный
   комментарий*/

//msdn -- документация по языку (microsoft software developer network)
#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {

    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    printf_s("Hello world!"); // вывод строки в консоль
    printf_s("Привет мир!");
    printf_s("\n"); // управляющая последовательность символов, означающая перенос строки

    // Наиболее часто используемые базовые типы переменных:
    // int -- целочисленный
    // double, float -- вещественные (числа с плавающей точкой)
    // char -- целочисленный (обычно будем работать как с символом)
    // bool -- отсутствует, 0 считается как FALSE, ненулевые значения -- TRUE

    int var; // объявление переменной (definition)
    var = 2; // присваивание значения переменной
    int number = 156; // инициализация переменной (initialization)

    printf_s("%d\n", number); // вывод значения целочисленной переменной

    // Модификаторы printf_s() для вывода значений переменных:
    // int      %d
    // char     %c
    // float    %f
    // double   %lf

    // Инициализируем несколько переменных различных типов и выведем их:
    int iVar = 19;
    char chVar = 'R';
    float fVar = 12.95;
    double dVar = 4.000000000003;

    printf_s("iVar = %d\n", iVar);
    printf_s("chVar = %c\n", chVar);
    printf_s("fVar = %f\ndVar = %.12lf\n", fVar, dVar);

    system("pause");
    return 0;
}
