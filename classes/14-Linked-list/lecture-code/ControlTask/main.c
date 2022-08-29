#include <stdio.h>
#include <malloc.h>

// 1 < base <= 10
// f(127,2) == ?
size_t unknownFunction(size_t value, size_t base)
{
	if (value < base)
		return value;
	return value % base + unknownFunction(value / base, base);
}

void uknownFunction2(int** mass, int** mass2, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			mass2[i][j] = mass[size - 1 - j][i];
		}
	}
}

void outputMass(int** mass, size_t size, const char* name)
{
	printf("%s:\n", name);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			printf("%d ", mass[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void alloc(int*** mass, size_t size)
{
	*mass = (int**)malloc(size * sizeof(int*));
	for (size_t i = 0; i < size; i++)
		(*mass)[i] = (int*)malloc(size * sizeof(int));
}

void dealloc(int** mass, size_t size)
{
	for (size_t i = 0; i < size; i++)
		free(mass[i]);
	free(mass);
}

int main()
{
	size_t value = 127;
	printf_s("f(%lu,10) -> %lu\n", value, unknownFunction(value, 10));
	printf_s("f(%lu,8) -> %lu\n", value, unknownFunction(value, 8));
	printf_s("f(%lu,2) -> %lu\n\n", value, unknownFunction(value, 2));

	const size_t size = 3;
	int** mass, ** mass2;
	alloc(&mass, size);
	alloc(&mass2, size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
			mass[i][j] = i * size + j + 1;
	}
	outputMass(mass, size, "mass");
	uknownFunction2(mass, mass2, size);
	uknownFunction2(mass2, mass, size);
	uknownFunction2(mass, mass2, size);
	uknownFunction2(mass2, mass, size);
	outputMass(mass, size, "mass after 4 times rotation");
	dealloc(mass, size);
	dealloc(mass2, size);
	return 0;
}