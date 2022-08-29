#pragma once

#include "..\..\..\14-Linked-list\lecture-code\linkedList\linkedList.h"

struct Stack
{
	linkedList* l;
};

typedef struct Stack stack;

stack* createStack();
void destroyStack(stack*);
void push(stack*, int);
void pop(stack*);
int top(stack*);
int empty(stack*);