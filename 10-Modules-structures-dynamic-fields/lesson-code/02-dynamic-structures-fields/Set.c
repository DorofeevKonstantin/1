#include "Set.h"

#include <malloc.h>
#include <stdio.h>

#define SUCCESS         0
#define ERR_ALLOC_MEM   1
#define ELEMENT_NOT_FOUND   2
#define ELEMENT_FOUND      3

#define START_SET_SIZE  10

// впомогательная функция
int* find(Set* set, int element) {
    for (size_t i = 0; i < set->size; ++i) {
        if (set->data[i] == element) return &set->data[i];
    }
    return NULL;
}

// вспомогательная функция
errno_t resizeSet(Set* set, size_t newSize) {
    int* reallocPtr = (int*)realloc(set->data, sizeof(int) * newSize);
    if (reallocPtr == NULL) return ERR_ALLOC_MEM;
    set->data = reallocPtr;
    return SUCCESS;
}

// функция для создания множества
Set* setNew(void) {
    Set* set = (Set*)malloc(sizeof(Set));
    set->data = (int*)malloc(sizeof(int) * START_SET_SIZE);
    set->maxSize = START_SET_SIZE;
    set->size = 0;
    return set;
}

// функция для удаления множества
void setDelete(Set* set) {
    // необходимо освободить динамическую память, используемую внутри структуры
    // прежде чем "освобождать" саму струтуру
    free(set->data);
    free(set);
}

errno_t setInsert(Set* set, int element) {
    if (setContains(set, element)) return ELEMENT_FOUND;
    if (set->maxSize == set->size) {
        size_t newSize = set->maxSize * 2;
        errno_t error = resizeSet(set, newSize);
        if (error != SUCCESS) return error;
    }
    set->data[set->size] = element;
    ++set->size;
    return SUCCESS;
}

errno_t setRemove(Set* set, int element) {
    int* ptr = find(set, element);
    if (ptr == NULL) return ELEMENT_NOT_FOUND;

    int* dataEndPtr = set->data + set->size;
    while (++ptr < dataEndPtr) *(ptr - 1) = *ptr;
    --set->size;

    if (set->size * 2 < set->maxSize) {
        size_t newSize = (size_t)(set->maxSize * 0.75);
        errno_t error = resizeSet(set, newSize);
        if (error != SUCCESS) return error;
    }

    return SUCCESS;
}

bool setContains(Set* set, int element) {
    return find(set, element) == NULL ? false : true;
}

void setPrint(Set* set) {
    for (size_t i = 0; i < set->size; ++i) printf_s("%d ", set->data[i]);
    printf_s("\n");
}