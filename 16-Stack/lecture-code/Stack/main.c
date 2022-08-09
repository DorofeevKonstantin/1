#include <stdio.h>

#include "stack.h"

void test1()
{
	stack* s = createStack();
	size_t count;
	printf_s("Enter elements count : \n");
	scanf_s("%lu", &count);
	for (size_t i = 0; i < count; i++)
	{
		push(s, i);
	}
	while (!empty(s))
	{
		printf_s("%d ", top(s));
		pop(s);
	}
	printf_s("\n");
	destroyStack(s);
}

void test2()
{
	stack* s = createStack();
	size_t value, base = 2;
	printf_s("Enter value to binarization : \n");
	scanf_s("%lu", &value);
	while (value)
	{
		push(s, value % base);
		value /= base;
	}
	while (!empty(s))
	{
		printf_s("%d", top(s));
		pop(s);
	}
	printf_s("\n");
	destroyStack(s);
}

int main()
{
	test1();
	test2();
	return 0;
}