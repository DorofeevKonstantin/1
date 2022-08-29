#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list* createList()
{
	list* l = (list*)malloc(sizeof(list));
	if (l)
	{
		l->head = 0;
		l->tail = 0;
		l->size = 0;
	}
	return l;
}
void pushBackList(list* l, linkedList* newValue)
{
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
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
void addStringToList(list* l, char* str, size_t position)
{
	listNode* current = l->head;
	int addBefore = 0;
	while (current != 0)
	{
		if (current->value != 0 && current->value->head != 0)
		{
			size_t currentStrLength = strlen(current->value->head->value);
			if (currentStrLength == strlen(str))
				break;
			else if (currentStrLength < strlen(str))
				current = current->next;
			else if (currentStrLength > strlen(str))
			{
				addBefore = 1;
				break;
			}
		}
	}
	if (current != 0 && addBefore)
	{
		linkedList* newElem = createLinkedList();
		pushBackLinkedList(newElem, str, position);
		listNode* newNode = (listNode*)malloc(sizeof(listNode));
		newNode->value = newElem;

		listNode* currentPrev = current->prev;
		current->prev = newNode;
		newNode->next = current;
		newNode->prev = currentPrev;
		if (currentPrev != 0)
			currentPrev->next = newNode;
		if (l->tail == 0)
			l->tail = l->head;
		if (current == l->head)
			l->head = newNode;
		l->size++;
	}
	else if (current != 0)
	{
		pushBackLinkedList(current->value, str, position);
	}
	else
	{
		linkedList* newElem = createLinkedList();
		pushBackLinkedList(newElem, str, position);
		pushBackList(l, newElem);
	}
}
void printList(list* l)
{
	listNode* current = l->head;
	while (current != 0)
	{
		printLinkedList(current->value);
		current = current->next;
	}
	printf_s("\n");
}
void destroyList(list* l)
{
	listNode* current = l->tail;
	listNode* prev = 0;
	while (current != 0)
	{
		prev = current->prev;
		destroyLinkedList(current->value);
		free(current);
		current = prev;
	}
	free(l);
}