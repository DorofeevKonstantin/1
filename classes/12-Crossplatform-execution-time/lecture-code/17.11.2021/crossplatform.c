#include <stdio.h>
#include "crossplatform.h"

void WindowsFunction();
void LinuxFunction();

void WindowsFunction()
{
	printf_s("Hello, we are in Windows!\n");
}
void LinuxFunction()
{
	printf("Hello, we are in Linux!\n");
}