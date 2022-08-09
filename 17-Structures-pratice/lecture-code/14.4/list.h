#pragma once

#include "linkedList.h"

struct ListNode
{
	struct ListNode* prev;
	linkedList* value;
	struct ListNode* next;
};

typedef struct ListNode listNode;

struct List
{
	listNode* head;
	listNode* tail;
	size_t size;
};

typedef struct List list;

list* createList();
void pushBackList(list*, linkedList*);
void addStringToList(list*, char*, size_t);
void printList(list*);
void destroyList(list*);