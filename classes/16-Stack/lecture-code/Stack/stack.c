#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack* createStack()
{
	stack* s = (stack*)malloc(sizeof(stack));
	if (s)
		s->l = createList();
	return s;
}
void destroyStack(stack* s)
{
	destroyList(s->l);
	free(s);
}
void push(stack* s, int newValue)
{
	pushFront(s->l, newValue);
}
void pop(stack* s)
{
	popFront(s->l);
}
int top(stack* s)
{
	return front(s->l);
}
int empty(stack* s)
{
	int isEmpty = 0;
	if (getSize(s->l) == 0)
		isEmpty = 1;
	return isEmpty;
}