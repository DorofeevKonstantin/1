#pragma once

#include <stdio.h>

struct Node
{
	int value;
	struct Node* next;
};

typedef struct Node node;

struct LinkedList
{
	node* head;
	node* tail;
	size_t size;
};

typedef struct LinkedList linkedList;

linkedList* createList();
linkedList* copyList(linkedList* src);
void pushBack(linkedList*, int);
void pushFront(linkedList*, int);
void addRandom(linkedList*, size_t);
int popBack(linkedList*);
int popFront(linkedList*);
int front(linkedList*);
void removeAllValues(linkedList*, int);
void printList(linkedList*);
void reverseList(linkedList*);
void printReverseList(linkedList*);
int getMiddleElem(linkedList*);
const size_t getSize(linkedList*);
void destroyList(linkedList*);
int isPalindrome(linkedList*);