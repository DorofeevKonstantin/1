#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Структура - новый тип данных, описываемый программистом. Они используются,
когда необходимо работать с данными, которые не получается представить в удобном
виде, используя стандартные типы.

синтаксис описания структуры следующий:
struct StructName {
    type1 field1;
    type2 field2;
    ...
    typeN fieldN;
};
Где:
struct  - ключевое слово языка, используемое при работе со структурами
StructName - имя нашего нового типа данных
type1, type2, ..., typeN - типы данных, которыми представлены поля
field1, field2, ...,fieldN - имена полей

Обращение к полям структуры осуществляется оператором '.', либо '->', если
мы работаем с указателем на структуру.
*/

// опишем структуру "студент"
// будем хранить самое важное:
// имя, курс и количество его "хвостов"
// условимся, что имя не превосходит 15 символов
#define MAX_NAME_LENGTH 15
#define NAME_BUFER_SIZE MAX_NAME_LENGTH + 1
struct Student {
    char name[NAME_BUFER_SIZE];
    unsigned course;
    unsigned tails;
};
// замечание: для обращения к типу Student необходимо использовать 
// ключевое слово struct, т.е., например, объявление переменной данного типа
// будет выглядеть следующим образом:
// struct Student ivan;
// а не просто:
// Student ivan;

// функция для отображения информации о студенте в консоли
void printStudent(struct Student);

int main(void) {
    // создадим пару студентов
    struct Student alexandr, petr, student;
    // заполним поля структур
    // alexandr'a оставим незаполненым, посмотрим что в нём будет

    petr.tails = 4;
    petr.course = 2;
    // с именем всё немного сложнее, т.к. это массив символов и мы
    // не можем просто присвоить в него что-либо, нужно осуществить копирование
    // внимательно разберитесь со следующей строкой
    strcpy_s(petr.name, NAME_BUFER_SIZE, "Petr");

    // для student введём данные с клавиатуры
    printf_s("Enter a name for student (max length = %d): ", MAX_NAME_LENGTH);
    scanf_s("%s", student.name, NAME_BUFER_SIZE);
    printf_s("Enter his course: ");
    scanf_s("%u", &student.course);
    printf_s("Enter his tails number: ");
    scanf_s("%u", &student.tails);

    printf_s("There 3 students:\n");
    printStudent(alexandr);
    printStudent(petr);
    printStudent(student);

    system("pause");
    return 0;
}

void printStudent(struct Student student) {
    printf_s("Student:\nName: %s\tCourse: %u\tTails: %u\n", student.name, student.course, student.tails);
}