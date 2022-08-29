#pragma once
#include <stddef.h>
#include <stdbool.h>

struct IntegerSet {
    int* data;
    size_t size;
    size_t maxSize;
};

typedef struct IntegerSet Set;

// функции создания и удаления множества
Set* setNew(void);
void setDelete(Set* set);

// функции добавления и удаления элементов
errno_t setInsert(Set* set, int element);
errno_t setRemove(Set* set, int element);

// проверка наличия элемента в множестве
bool setContains(Set* set, int element);

// вывод множества в консоль
void setPrint(Set* set);
