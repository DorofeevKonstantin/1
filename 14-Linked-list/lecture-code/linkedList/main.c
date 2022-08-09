#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedList.h"

void test1()
{
	linkedList* l1 = createList();
	popBack(l1);
	addRandom(l1, 10);
	printList(l1);
	printReverseList(l1);
	reverseList(l1);
	printf_s("After reverse :\b");
	printList(l1);
	printReverseList(l1);

	popBack(l1);
	popBack(l1);
	printf_s("After two popBack size = %lu\n", l1->size);
	printList(l1);
	destroyList(l1);

	l1 = createList();
	addRandom(l1, 5);
	printList(l1);
	printf_s("Middle value = %d\n", getMiddleElem(l1));
	destroyList(l1);
}

void test2()
{
	linkedList* l1 = createList();
	addRandom(l1, 20);
	printList(l1);
	removeAllValues(l1, 0);
	printf_s("after remove all 0 : \n");
	printList(l1);
	removeAllValues(l1, 1);
	printf_s("after remove all 1 : \n");
	printList(l1);
	printReverseList(l1);
	destroyList(l1);
}

void palindromeCheck()
{
	linkedList* l1 = createList();
	addRandom(l1, 4);
	printList(l1);
	if (isPalindrome(l1))
		printf_s("palindrome\n");
	else
		printf_s("not palindrome");
	destroyList(l1);
}

int main()
{
	srand((unsigned int)time(0));
	//test1();
	//test2();
	palindromeCheck();
	return 0;
}