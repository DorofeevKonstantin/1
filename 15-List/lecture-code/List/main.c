#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

// https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/manipulating-activeprocesslinks-to-unlink-processes-in-userland

void test1()
{
	const size_t size = 20;
	printf_s("test1 : \n");
	list* l = createList();
	fillRandom(l, size);
	printList(l);

	printf_s("after swap(position 1, position 2) : \n");
	swap(l, getNode(l, 1), getNode(l, 2));
	printList(l);

	swap(l, getNode(l, size - 1), getNode(l, size));
	printf_s("after swap(position %lu, position %lu) : \n", size - 1, size);
	printList(l);

	sort(l, 1);
	printf_s("after sort : \n");
	printList(l);
	printReverseList(l);

	destroyList(l);

	l = createList();
	fillRandom(l, size);
	printList(l);
	sort(l, 1);
	printf_s("after sort : \n");
	printList(l);
	destroyList(l);
	printf_s("\n");
}
void test2(int direction)
{
	printf_s("test2 : \nEnter list size : \n");
	size_t size;
	scanf_s("%lu", &size);
	if (size > 0 && size < 1'000'000)
	{
		list* l = createList();
		if (direction == 1)
			fillDescending(l, size);
		else
			fillAscending(l, size);
		shuffle(l);
		printList(l);
		sort(l, direction);
		printf_s("after sort : \n");
		printList(l);
		destroyList(l);
		printf_s("\n");
	}
	else
		printf_s("error : wrong size\n");
}

int main()
{
	srand((unsigned int)time(0));
	test1();
	test2(1);
	test2(2);
	return 0;
}