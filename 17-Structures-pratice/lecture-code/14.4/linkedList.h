#pragma once

#include <stdio.h>

struct LinkedListNode
{
	char* value;
	size_t position;
	struct LinkedListNode* next;
};

typedef struct LinkedListNode linkedListNode;

struct LinkedList
{
	linkedListNode* head;
	linkedListNode* tail;
	size_t size;
};

typedef struct LinkedList linkedList;

linkedList* createLinkedList();
void pushBackLinkedList(linkedList*, char*, size_t);
void pushFront(linkedList*, char*, size_t);
void insertLinkedList(linkedList*, char*, size_t);
void printLinkedList(linkedList*);
void destroyLinkedList(linkedList*);