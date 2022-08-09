#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "..\..\..\16-Stack\lecture-code\Stack\stack.h"

linkedList* createList()
{
	linkedList* l = (linkedList*)malloc(sizeof(linkedList));
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
linkedList* copyList(linkedList* src)
{
	linkedList* l = createList();
	if (l)
	{
		node* current = src->head;
		while (current != 0)
		{
			pushBack(l, current->value);
			current = current->next;
		}
	}
	else
		printf_s("error : can't allocate memory in copyList.\n");
	return l;
}
void destroyList(linkedList* l)
{
	node* current = l->head;
	node* tmp;
	while (current != 0)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(l);
}
void pushBack(linkedList* l, int newValue)
{
	node* newElem = (node*)malloc(sizeof(node));
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
void pushFront(linkedList* l, int newValue)
{
	node* newElem = (node*)malloc(sizeof(node));
	if (newElem)
	{
		newElem->value = newValue;
		newElem->next = l->head;

		if (l->tail == 0)
			l->tail = newElem;

		l->head = newElem;

		l->size++;
	}
}
// https://titanwolf.org/Network/Articles/Article?AID=76013240-79e8-4cb5-8f83-f49e97e4b646
void removeAllValues(linkedList* l, int removedValue)
{
	node** current = &(l->head);
	while (*current != 0)
	{
		node* entry = *current;
		if (entry->value == removedValue)
		{
			*current = entry->next;
			l->size--;
			free(entry);
		}
		else
			current = &(entry->next);
	}
}
void printList(linkedList* l)
{
	printf_s("linkedList : \n");
	node* current = l->head;
	while (current != 0)
	{
		printf_s("%d ", current->value);
		current = current->next;
	}
	printf_s("\n");
}
void addRandom(linkedList* l, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		pushBack(l, rand() % count);
	}
}
void printReverseNodes(node* n)
{
	if (n == 0)
		return;
	printReverseNodes(n->next);
	printf_s("%d ", n->value);
}
void printReverseList(linkedList* l)
{
	printf_s("printReverseList : \n");
	printReverseNodes(l->head);
	printf_s("\n");
}
void reverseList(linkedList* l)
{
	node* saveTail = l->tail;
	l->tail = l->head;
	node* previous = 0, * current = l->head, * following = l->head;
	l->head = saveTail;
	while (current != 0)
	{
		following = following->next;
		current->next = previous;
		previous = current;
		current = following;
	}
}
int popBack(linkedList* l)
{
	int result = 0;
	if (l->tail != 0)
	{
		result = l->tail->value;
		l->size--;
	}
	else
		printf_s("warning : empty linkedList popBack.\n");
	node* current = l->head;
	if (current != 0)
	{
		while (current->next != l->tail)
			current = current->next;
		free(current->next);
	}
	l->tail = current;
	if (l->tail != 0)
		l->tail->next = 0;
	return result;
}
// not ideal realization, need error handling mechanism
int popFront(linkedList* l)
{
	int value = 0;
	if (l && l->head)
	{
		value = l->head->value;
		node* tmp = l->head;
		l->head = l->head->next;
		free(tmp);
		l->size--;
	}
	else
		printf_s("warning : empty linkedList popFront.\n");
	return value;
}
int front(linkedList* l)
{
	int value = 0;
	if (l && l->head)
		value = l->head->value;
	else
		printf_s("warning : empty linkedList front.\n");
	return value;
}
int getMiddleElem(linkedList* l)
{
	node* slow = l->head;
	node* fast = l->head;
	node* predSlow = l->head;
	while (fast != 0 && fast != l->tail)
	{
		predSlow = slow;
		fast = fast->next->next;
		slow = slow->next;
	}
	if (fast == l->tail)
		return slow->value;
	else
		return predSlow->value;
}
const size_t getSize(linkedList* l)
{
	return l->size;
}
int recursivePalindromeCheck(node** left, node* right)
{
	if (right == 0)
		return 1;
	int recursiveResult = recursivePalindromeCheck(left, right->next);
	if ((*left)->value == right->value)
	{
		*left = (*left)->next;
		return recursiveResult && 1;
	}
	else
		return recursiveResult && 0;
}
int isPalindrome(linkedList* l)
{
	return recursivePalindromeCheck(&(l->head), l->head);
}