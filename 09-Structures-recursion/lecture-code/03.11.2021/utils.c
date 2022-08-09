#include <stdio.h>

#include "utils.h"

void function_that_uses_hello()
{
	hello_world(5);
}

// definition of function
void hello_world(int a)
{
	printf_s("hello world! %d\n",a);
}