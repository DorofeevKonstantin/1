#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "..\..\..\14-Linked-list\lecture-code\linkedList\linkedList.h"
#include "..\..\..\16-Stack\lecture-code\Stack\stack.h"
#include "..\..\..\12-Crossplatform-execution-time\lecture-code\17.11.2021\executionTime.h"
#include "stackLinkedList.h"

const size_t maxPrintSize = 20;

void generateNumbers(int** mass, linkedList** l, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		int newValue = rand() % size;
		pushBack(*l, newValue);
		(*mass)[i] = newValue;
	}
}
void compareResults(int* mass, linkedList* l, size_t size)
{
	node* current = l->head;
	for (size_t i = 0; i < size; i++)
	{
		if (mass[i] != current->value)
		{
			printf_s("not equal results!\n");
			return;
		}
		current = current->next;
	}
	printf_s("equal results with sortLinkedList and arraySort\n");
}
void printArray(int* mass, size_t size)
{
	if (size < maxPrintSize)
	{
		printf_s("printArray : ");
		for (size_t i = 0; i < size; i++)
			printf_s("%d ", mass[i]);
		printf_s("\n");
	}
}

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%A2%D0%B5%D1%80%D0%BF%D0%B5%D0%BB%D0%B8%D0%B2%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0
void sortLinkedListWithStacks(linkedList** l)
{
	size_t size = (*l)->size;
	stackLinkedList* sl = createStackList();
	node* current = (*l)->head;
	while (current)
	{
		addNumberToStackList(sl, current->value);
		current = current->next;
	}
	printf_s("stacks count : %d\n", sl->size);
	destroyList(*l);
	*l = createList();
	for (size_t i = 0; i < size; i++)
	{
		stack* stackWithMinTop = findNodeWithMinTop(sl)->value;
		int newValue = top(stackWithMinTop);
		pop(stackWithMinTop);
		pushBack(*l, newValue);
	}
	destroyStackList(sl);
}
void sortLinkedListExample(linkedList** l)
{
	if ((*l)->size < maxPrintSize)
		printList(*l);
	clock_t start = startTimeMeasure();
	sortLinkedListWithStacks(l);
	stopTimeMeasure(start);
	if ((*l)->size < maxPrintSize)
	{
		printList(*l);
	}
}

int simpleCompare(const void* lhs, const void* rhs)
{
	int arg1 = *(const int*)lhs;
	int arg2 = *(const int*)rhs;
	if (arg1 < arg2) return -1;
	if (arg1 > arg2) return 1;
	return 0;
}
void bubbleSortArray(int* mass, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size - 1; j++)
		{
			if (mass[j] > mass[j + 1])
			{
				int tmp = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = tmp;
			}
		}
	}
}
void arraySorts(int* mass, size_t size)
{
	printArray(mass, size);
	clock_t start = startTimeMeasure();
	qsort(mass, size, sizeof(int), simpleCompare);
	printf_s("qsort array\n");
	stopTimeMeasure(start);

	printArray(mass, size);
	start = startTimeMeasure();
	bubbleSortArray(mass, size);
	printf_s("bubble sort array\n");
	stopTimeMeasure(start);
	printArray(mass, size);
}

int main()
{
	srand((unsigned int)time(0));
	printf_s("enter size : \n");
	size_t size;
	scanf_s("%lu", &size);
	printf_s("\n");

	int* mass = (int*)malloc(size * sizeof(int));
	linkedList* l = createList();
	generateNumbers(&mass, &l, size);
	sortLinkedListExample(&l);
	arraySorts(mass, size);
	compareResults(mass, l, size);
	destroyList(l);
	free(mass);
	return 0;
}