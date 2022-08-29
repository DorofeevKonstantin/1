#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "list.h"

// https://github.com/Ginmaru-Gin/csu-lang-C/blob/main/14-Linked-list/task/task.md  task 14.4

void getNValues(list* l, size_t n)
{
	linkedList* result = createLinkedList();
	listNode* listPtr = l->tail;
	linkedListNode* linkedListPtr = listPtr->value->head;
	for (size_t i = 0; i < n; i++)
	{
		if (linkedListPtr == 0)
		{
			listPtr = listPtr->prev;
			linkedListPtr = listPtr->value->head;
		}
		insertLinkedList(result, linkedListPtr->value, linkedListPtr->position);
		//printLinkedList(result);
		linkedListPtr = linkedListPtr->next;
	}
	printf_s("\nresult:\n");
	printLinkedList(result);
	destroyLinkedList(result);
}

void task14_4(char* fileName)
{
	FILE* in;
	errno_t err = fopen_s(&in, fileName, "r");
	if (!err && in)
	{
		size_t n, position = 1;
		fscanf_s(in, "%lu", &n);
		printf_s("n == %lu\n", n);
		list* l = createList();
		char buffer[100];
		while (fscanf_s(in, "%s", buffer, _countof(buffer)) > 0)
		{
			printf_s("%s ", buffer);
			addStringToList(l, buffer, position);
			++position;
		}
		//printList(l);
		getNValues(l, n);
		destroyList(l);
	}
	else
		printf_s("Error : can't open file.\n");
}

void printHelp()
{
	printf_s("Usage example : 14.4.exe fileName.txt");
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printHelp();
		return -1;
	}
	task14_4(argv[1]);
	return 0;
}