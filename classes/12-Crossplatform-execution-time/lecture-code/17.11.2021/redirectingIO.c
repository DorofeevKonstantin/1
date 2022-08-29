#include <stdio.h>
#include <stdlib.h>

#include "redirectingIO.h"

void redirectingExample()
{
	// run with cmd, "prog.exe <in.txt >out.txt"
	size_t size;
	scanf_s("%d", &size);
	int* mass = (int*)malloc(size * sizeof(int));
	for (size_t i = 0; i < size; i++)
		scanf_s("%d", &mass[i]);
	int maxValue = mass[0];
	for (size_t i = 1; i < size; i++)
	{
		if (mass[i] > maxValue)
			maxValue = mass[i];
	}
	printf_s("maxValue = %d\n", maxValue);
	free(mass);
}