/*
Пользователь задаёт на плоскости прямую и точки. Необходимо установить
принадлежность точек этой прямой.

В аргументах командной строки задаются коэффициенты уравнения прямой
(уравнение прямой выглядит след. образом: `Ax + By + C = 0`) и имя
файла (длиной до 100 символов), в котором содержатся координаты точек.

Выводится количество точек, координаты каждой точки и сообщение о её
принадлежности прямой.
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR "ERROR\nEXIT WITH ERROR CODE 1"
#define ERR_OPEN_FILE ERROR

int isPointOnLine(int point[2], int line[3]);
int countPointsInFile(FILE* file);
int readPointFromFile(FILE* file, int point[2]);

int main(int argc, char** argv) {
    // линию представим массивом её коэффициентов { A, B, C }
    int line[3] = { atoi(argv[1]), atoi(argv[2]), atoi(argv[3]) };
    // точку представим как массив её координат: { x, y }
    int point[2];
    FILE* pointsFile;
    if (fopen_s(&pointsFile, argv[4], "r")) {
        printf_s(ERR_OPEN_FILE);
        exit(1);
    }
    int pointsCount = countPointsInFile(pointsFile);
    printf_s("%d points:\n", pointsCount);
    while (pointsCount--) {
        readPointFromFile(pointsFile, point);
        printf_s("%d %d: %s", point[0], point[1], (isPointOnLine(point, line) ? "YES" : "NO"));
        printf_s("\n");
    }
    fclose(pointsFile);

    system("pause");
    return 0;
}

int isPointOnLine(int point[2], int line[3]) {
    return (line[0] * point[0] + line[1] * point[1] + line[2]) == 0;
}

int countPointsInFile(FILE* file) {
    // сохраним позицию в файле перед работой
    // чтобы потом вернуть её в текущее состояние
    long currentPos = ftell(file);
    // сбросим позицию на начало файла
    rewind(file);
    int buf1, buf2, counter = 0;
    // каждая точка включает в себя две координаты, поэтому посчитаем пары чисел
    while (fscanf_s(file, "%d %d", &buf1, &buf2) == 2) counter++;
    // вернемся на позицию, которую сохранили ранее
    fseek(file, currentPos, SEEK_SET);
    return counter;
}

int readPointFromFile(FILE* file, int point[2]) {
    return fscanf_s(file, "%d %d", point, point + 1);
}