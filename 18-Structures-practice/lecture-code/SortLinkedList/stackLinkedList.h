#pragma once

#include <stdio.h>

#include "..\..\..\16-Stack\lecture-code\Stack\stack.h"

struct stackNode
{
	stack* value;
	struct stackNode* next;
};

typedef struct stackNode stackNode;

struct stackLinkedList
{
	stackNode* head;
	stackNode* tail;
	size_t size;
};

typedef struct stackLinkedList stackLinkedList;

stackLinkedList* createStackList();
void pushBackStackList(stackLinkedList*, stack*);
void addNumberToStackList(stackLinkedList*, int);
stackNode* findNodeWithMinTop(stackLinkedList*);
const size_t getSizeStackList(stackLinkedList*);
void destroyStackList(stackLinkedList*);