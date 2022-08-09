#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stackLinkedList.h"

stackLinkedList* createStackList()
{
	stackLinkedList* l = (stackLinkedList*)malloc(sizeof(stackLinkedList));
	if (l)
	{
		l->size = 0;
		l->head = 0;
		l->tail = 0;
	}
	else
		printf_s("error : can't allocate memory in createList.\n");
	return l;
}
void pushBackStackList(stackLinkedList* l, stack* newValue)
{
	stackNode* newElem = (stackNode*)malloc(sizeof(stackNode));
	if (newElem)
	{
		newElem->value = newValue;
		newElem->next = 0;

		if (l->tail != 0)
			l->tail->next = newElem;
		l->tail = newElem;

		if (l->head == 0)
			l->head = newElem;

		l->size++;
	}
}
void addNumberToStackList(stackLinkedList* l, int number)
{
	stackNode* current = l->head;
	while (current != 0 && top(current->value) < number)
		current = current->next;
	if (current != 0)
		push(current->value, number);
	else
	{
		stack* newStack = createStack();
		push(newStack, number);
		pushBackStackList(l, newStack);
	}
}
stackNode* findNodeWithMinTop(stackLinkedList* l)
{
	stackNode* result = 0, * current = l->head;
	int minNumber = INT_MAX;
	while (current)
	{
		if (!empty(current->value))
		{
			int topValue = top(current->value);
			if (topValue < minNumber)
			{
				minNumber = topValue;
				result = current;
			}
		}
		current = current->next;
	}
	return result;
}
const size_t getSizeStackList(stackLinkedList* l)
{
	return l->size;
}
void destroyStackList(stackLinkedList* l)
{
	stackNode* current = l->head;
	stackNode* tmp;
	while (current != 0)
	{
		tmp = current->next;
		destroyStack(current->value);
		free(current);
		current = tmp;
	}
	free(l);
}