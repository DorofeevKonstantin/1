#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int main() {
    int arr[ARRAY_SIZE];
    // заполнение массива случайными целыми числами из промежутка (-100, 100):
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (rand() % 2 ? -1 : 1) * (rand() % 100);
    }

    // ...

    system("pause");
    return 0;
}