/*
Даны три отрезка с длинами a, b и c.Вы можете увеличивать отрезки, но не можете
их уменьшать, ваша задача : вычислить на сколько суммарно необходимо увеличить
длины отрезков, чтобы из них можно было построить треугольник.
Натуральные числа a, b и c записаны в файле input.txt, ответ нужно записать
в файл result.txt.
В коде должна быть написана и использована функция, которая принимает
длины отрезков и возвращает ответ.

Из трёх отрезков можно построить треугольник в случае, когда длина каждого
из них меньше суммы длин двух других.
Решение: найти отрезок наибольшей длины, вычислить разность длины этого наибольшего отрезка
и суммы длин двух других. Ответ 0 в случае, когда разность отрицательна,
в ином случае ответ (разность + 1).
*/
#include <stdio.h>
#include <stdlib.h>

#define ERR_OPEN_FILE "ERROR:couldn't open file '%s'\nEXIT WITH ERROR CODE 1\n"

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "result.txt"

int getAnswer(int triangle[3]);

int main(void) {
    FILE* input, *output;
    if (fopen_s(&input, INPUT_FILE_NAME, "r")) {
        printf_s(ERR_OPEN_FILE, INPUT_FILE_NAME);
        system("pause");
        return 1;
    }
    if (fopen_s(&output, OUTPUT_FILE_NAME, "w")) {
        fclose(input);
        printf_s(ERR_OPEN_FILE, OUTPUT_FILE_NAME);
        system("pause");
        return 1;
    }

    int triangle[3];
    fscanf_s(input, "%d %d %d", &triangle[0], &triangle[1], &triangle[2]);
    fclose(input);
    fprintf_s(output, "%d", getAnswer(triangle));
    fclose(output);
    printf_s("DONE!\n");

    system("pause");
    return 0;
}

int getAnswer(int triangle[3]) {
    // сортируем длины отрезков по возрастанию
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j < 3 - i; ++j) {
            if (triangle[j] < triangle[j - 1]) {
                int tmp = triangle[j];
                triangle[j] = triangle[j - 1];
                triangle[j - 1] = tmp;
            }
        }
    }
    //следуем алгоритму решения, описанному в начале
    int diff = triangle[2] - triangle[0] - triangle[1];
    return diff < 0 ? 0 : diff + 1;
}
