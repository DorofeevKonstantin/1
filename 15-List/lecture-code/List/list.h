#pragma once

struct Node
{
	struct Node* prev;
	int value;
	struct Node* next;
};

typedef struct Node node;

struct List
{
	node* head;
	node* tail;
	size_t size;
};

typedef struct List list;

list* createList();
void fillRandom(list*, size_t);
void fillAscending(list* l, size_t size);
void fillDescending(list*, size_t);
void pushBack(list*, int);
//void pushFront(list*, int);
//int popBack(list*);
//int popFront(list*);
void printList(list*);
void printReverseList(list*);
node* find(list*, int);
node* getNode(list*, size_t);
void swapValues(list*, node*, node*);
void swapLeftBeforeRight(list*, node*, node*);
void swap(list*, node*, node*);
void shuffle(list*);
void sort(list*, int);
void destroyList(list*);