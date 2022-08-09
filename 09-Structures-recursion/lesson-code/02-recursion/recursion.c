// Рекурсивная функция - функция, которая вызывает сама себя.
// Любую рекурсию можно реализовать в итеративном виде, что будет
// эффективнее рекурсии, но сложнее в написании.
#include <stdio.h>
#include <stdlib.h>

#define STR_BUF_SIZE 100

// давайте напишем рекурсивную функцию вычисления факториала числа
// подумайте: в чем проблема этой функции и когда она будет
// выдавать некорректный результат?
unsigned long long factorial(unsigned number);

// пример рекурсивной функции вычисления длины строки 
size_t stringLength(char* string);

int main(void) {
    printf_s("Enter a number: ");
    char buf[STR_BUF_SIZE + 1];
    gets_s(buf, STR_BUF_SIZE + 1);
    printf_s("Factorial of %s is %llu\n", buf, factorial(atoi(buf)));

    printf_s("Enter a string (length <= %d): ", STR_BUF_SIZE);
    gets_s(buf, STR_BUF_SIZE + 1);
    printf_s("Your entered the string that's length equals %llu\n", stringLength(buf));
    system("pause");
    return 0;
}

unsigned long long factorial(unsigned number) {
    if (!number) return 1; // факториал нуля = 1
    // факториал числа N = (факториал числа N - 1) * N:
    else return number * factorial(number - 1);
}

size_t stringLength(char* string) {
    // если первый символ - конец строки -> длина 0
    if (*string == '\0') return 0;
    // длина строки = (длина подстроки начинающейся со второго символа) + 1
    return stringLength(string + 1) + 1;
}