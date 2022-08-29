#include <stdio.h>
#include <stdlib.h>

void first_variant(int size)
{
	// as one dimension
	int* mass = (int*)malloc(size * size * sizeof(int));
	if (mass)
	{
		// mass[2][4] = 99;
		mass[2 * size + 4] = 99;
		free(mass);
	}
	// 1. uncomfortably!
	// 2. (size*size*sizeof(int) + sizeof(void*)) memory using
	// 3. malloc calls 1 time
}

void second_variant(int size)
{
	// classic way
	int** mass = (int**)malloc(size * sizeof(int*));
	if (mass)
	{
		for (int i = 0; i < size; i++)
			mass[i] = (int*)malloc(size * sizeof(int));

		mass[2][4] = 99;

		for (int i = 0; i < size; i++)
			free(mass[i]);
		free(mass);
	}
	// 1. comfortable
	// 2. (size*size*sizeof(int) + size*sizeof(void*) + sizeof(void*)) memory using
	// 3. malloc calls (size + 1) times
}

void third_variant(int size)
{
	// decrease malloc calls to 2 times
	int** mass = (int**)malloc(size * sizeof(int*));
	int* buffer = (int*)malloc(size * size * sizeof(int));
	for (int i = 0; i < size; i++)
		mass[i] = &buffer[size * i];

	mass[2][4] = 99;

	free(buffer);
	free(mass);
	// 1. comfortable
	// 2. (size*size*sizeof(int) + size*sizeof(void*) + 2*sizeof(void*)) memory using
	// 3. malloc calls (2) times
}

void fourth_variant(int size)
{
	// decrease malloc calls to 1 time
	int count = (size * size * sizeof(int) + size * sizeof(void*));
	int** mass = (int**)malloc(count);

	for (int i = 0; i < size; i++)
		mass[i] = (int*)(mass + size) + i * size; // mass[i] = mass+size+i*size WRONG!

	mass[size - 1][size - 1] = 99;

	// analyze pointers
	int* start = (int*)mass;
	int* end = &(mass[size - 1][size - 1]);
	// theoretical difference with size==5   end-start == 116 for x86 configuration, real difference 116
	// theoretical difference with size==5   end-start == 136 for x64 configuration, real difference 216!
	printf("start == %p\nend == %p\ndifference == %d", start, end, (end - start) * sizeof(int));

	free(mass);
	// 1. comfortable
	// 2. (size*size*sizeof(int) + size*sizeof(void*) + sizeof(void*)) memory using
	// 3. malloc calls (1) times
}


//4 variants for int** works
int main()
{
	first_variant(5);
	second_variant(5);
	third_variant(5);
	fourth_variant(5);
	return 0;
}