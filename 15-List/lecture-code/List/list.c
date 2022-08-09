#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list* createList()
{
	printf_s("createList\n");
	list* l = (list*)malloc(sizeof(list));
	if (l)
	{
		l->head = 0;
		l->tail = 0;
		l->size = 0;
	}
	return l;
}
void pushBack(list* l, int newValue)
{
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode)
	{
		newNode->value = newValue;
		newNode->next = 0;
		newNode->prev = 0;

		if (l->head == 0) // empty list
			l->head = newNode;
		else if (l->tail == 0) // 1 element in list
		{
			l->tail = newNode;
			l->tail->prev = l->head;
			l->head->next = l->tail;
		}
		else // n elements in list
		{
			l->tail->next = newNode;
			newNode->prev = l->tail;
			l->tail = newNode;
		}
		l->size++;
	}
}
void fillRandom(list* l, size_t size)
{
	for (size_t i = 0; i < size; i++)
		pushBack(l, rand() % size);
}
void fillAscending(list* l, size_t size)
{
	for (size_t i = 0; i < size; i++)
		pushBack(l, i);
}
void fillDescending(list* l, size_t size)
{
	for (size_t i = 0; i < size; i++)
		pushBack(l, size - i);
}
void printList(list* l)
{
	printf_s("printList : \n");
	node* current = l->head;
	while (current != 0)
	{
		printf_s("%d ", current->value);
		current = current->next;
	}
	printf_s("\n");
}
void printReverseList(list* l)
{
	printf_s("printReverseList : \n");
	node* current = l->tail;
	while (current != 0)
	{
		printf_s("%d ", current->value);
		current = current->prev;
	}
	printf_s("\n");
}
void destroyList(list* l)
{
	printf_s("destroyList\n");
	node* current = l->tail;
	node* prev = 0;
	while (current != 0)
	{
		prev = current->prev;
		free(current);
		current = prev;
	}
	free(l);
}
node* find(list* l, int interestedValue)
{
	node* current = 0;
	if (l->head != 0)
		current = l->head;
	while (current != 0)
	{
		if (current->value == interestedValue)
			break;
		current = current->next;
	}
	return current;
}
int isNullNode(node* n)
{
	if (n == 0)
		return 1;
	else
		return 0;
}
void swapValues(list* l, node* left, node* right)
{
	if (isNullNode(left) || isNullNode(right))
		return;
	int tmp = left->value;
	left->value = right->value;
	right->value = tmp;
}
void swapLeftBeforeRight(list* l, node* left, node* right)
{
	node* lPrev = left->prev;
	node* rNext = right->next;

	if (lPrev != 0)
		lPrev->next = right;
	if (rNext != 0)
		rNext->prev = left;

	right->prev = lPrev;
	right->next = left;

	left->prev = right;
	left->next = rNext;
}
void swap(list* l, node* left, node* right)
{
	if (isNullNode(left) || isNullNode(right))
	{
		printf_s("warning : can't swap null nodes\n");
		return;
	}
	if (left == right)
		printf_s("warning : wouldn't swap node with itself\n");

	if (left->next == right)
		swapLeftBeforeRight(l, left, right);
	else if (right->next == left)
		swapLeftBeforeRight(l, right, left);
	else
	{
		node* lPrev = left->prev;
		node* lNext = left->next;
		node* rPrev = right->prev;
		node* rNext = right->next;

		if (lPrev != 0)
			lPrev->next = right;
		right->prev = lPrev;
		right->next = lNext;
		if (lNext != 0)
			lNext->prev = right;

		if (rPrev != 0)
			rPrev->next = left;
		left->next = rNext;
		left->prev = rPrev;
		if (rNext != 0)
			rNext->prev = left;
	}

	if (l->head == left)
		l->head = right;
	else if (l->head == right)
		l->head = left;

	if (l->tail == left)
		l->tail = right;
	else if (l->tail == right)
		l->tail = left;
}
node* getNode(list* l, size_t position)
{
	node* current = 0;
	if (position <= l->size)
	{
		current = l->head;
		while ((current->next != 0) && (--position))
			current = current->next;
	}
	return current;
}
void shuffle(list* l)
{
	for (size_t i = 0; i < l->size / 2; i++)
		swap(l, find(l, rand() % l->size), find(l, rand() % l->size));
}
// bubble algorithm realization
void sort(list* l, int direction)
{
	for (size_t i = 0; i < l->size; ++i)
	{
		for (node* current = l->head; current != 0; )
		{
			if (current->next != 0)
			{
				if (direction == 1)
				{
					if (current->value > current->next->value)
					{
						//swapValues(l, current, current->next);
						swap(l, current, current->next);
					}
					else
						current = current->next;
				}
				else
				{
					if (current->value < current->next->value)
					{
						//swapValues(l, current, current->next);
						swap(l, current, current->next);
					}
					else
						current = current->next;
				}
			}
			else
				break;
		}
	}
}