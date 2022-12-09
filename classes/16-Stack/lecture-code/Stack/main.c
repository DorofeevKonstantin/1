#include <stdio.h>

#include "stack.h"

void test1()
{
	stack* s = createStack();
	size_t count;
	printf_s("Enter elements count : \n");
	scanf_s("%zu", &count);
	for (size_t i = 0; i < count; i++)
	{
		push(s, (int)i);
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
	scanf_s("%zu", &value);
	while (value)
	{
		push(s, (int)(value % base));
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