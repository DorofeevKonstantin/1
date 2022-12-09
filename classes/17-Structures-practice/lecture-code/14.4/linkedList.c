#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

linkedList* createLinkedList()
{
	linkedList* l = (linkedList*)malloc(sizeof(linkedList));
	if (l)
	{
		l->size = 0;
		l->head = 0;
		l->tail = 0;
	}
	return l;
}
void strcpyForElem(linkedListNode* newElem, char* str)
{
	size_t strLength = strlen(str);
	newElem->value = (char*)malloc(strLength + 1);
	newElem->value[strLength] = '\0';
	strcpy_s(newElem->value, strLength + 1, str);
}
void pushBackLinkedList(linkedList* l, char* newValue, size_t _position)
{
	linkedListNode* newElem = (linkedListNode*)malloc(sizeof(linkedListNode));
	if (newElem)
	{
		strcpyForElem(newElem, newValue);
		newElem->position = _position;
		newElem->next = 0;

		if (l->tail != 0)
			l->tail->next = newElem;
		l->tail = newElem;

		if (l->head == 0)
			l->head = newElem;

		l->size++;
	}
}
void pushFront(linkedList* l, char* newValue, size_t _position)
{
	linkedListNode* newElem = (linkedListNode*)malloc(sizeof(linkedListNode));
	if (newElem)
	{
		strcpyForElem(newElem, newValue);
		newElem->position = _position;
		newElem->next = l->head;

		if (l->head == 0)
			l->tail = newElem;

		l->head = newElem;

		l->size++;
	}
}
void insertLinkedList(linkedList* l, char* newValue, size_t _position)
{
	if (l->head == 0 || l->head->position > _position)
	{
		pushFront(l, newValue, _position);
		return;
	}
	linkedListNode* current = l->head;
	while (current)
	{
		if (current->next != 0 && current->next->position > _position)
			break;
		current = current->next;
	}
	if (current == 0)
		pushBackLinkedList(l, newValue, _position);
	else
	{
		linkedListNode* newElem = (linkedListNode*)malloc(sizeof(linkedListNode));
		if (newElem)
		{
			strcpyForElem(newElem, newValue);
			newElem->position = _position;
			newElem->next = current->next;
			current->next = newElem;
			l->size++;
		}
	}
}
void printLinkedList(linkedList* l)
{
	linkedListNode* current = l->head;
	while (current != 0)
	{
		//printf_s("%s,%lu ", current->value, current->position);
		printf_s("%s ", current->value);
		current = current->next;
	}
	printf_s("\n");
}
void destroyLinkedList(linkedList* l)
{
	linkedListNode* current = l->head;
	linkedListNode* tmp;
	while (current != 0)
	{
		tmp = current->next;
		free(current->value);
		free(current);
		current = tmp;
	}
	free(l);
}