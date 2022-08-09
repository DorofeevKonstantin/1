#include <stdio.h>
#include <limits.h> // INT_MIN, INT_MAX
#include <stdlib.h>

#define SIZE 11 // global scope macros

// make function from repeating code in main
void output_array(int* mass) // discuss "int*" later
{
	for (int i = 0; i < SIZE; ++i)
	{
		printf("%d ", mass[i]);
	}
	printf("\n");
}

int main()
{
	srand((unsigned int)time(0)); // discuss later
	// static one-dimensional array
	int mass[SIZE];
	int count_odd = 0, count_even = 0;
	int max = INT_MIN, min = INT_MAX;
	// set values
	for (int i = 0; i < SIZE; ++i)
	{
		mass[i] = rand() % 100; // 0...99
	}
	output_array(mass);
	for (int i = 0; i < SIZE; ++i)
	{
		if (mass[i] % 2 == 0)
			++count_even;
		else
			++count_odd;
	}
	printf("even = %d odd = %d\n", count_even, count_odd);
	// find max, min elements
	for (int i = 0; i < SIZE; ++i)
	{
		if (mass[i] < min)
			min = mass[i];
		if (mass[i] > max)
			max = mass[i];
	}
	printf("max = %d , min = %d\n", max, min);
	//int mass2[] = {1,2,3}; // initialization in code
	// reverse elements
	for (int i = 0; i < SIZE / 2; ++i)
	{
		// swap i, SIZE-1-i elements
		int tmp = mass[i];
		mass[i] = mass[SIZE - 1 - i];
		mass[SIZE - 1 - i] = tmp;
	}
	output_array(mass);
	// bubble sort
	for (int i = 0; i < SIZE; ++i) // SIZE times we will move the bubble up
	{
		for (int j = 0; j < SIZE - 1; ++j) // come bubble to the top
		{
			// swap
			if (mass[j] > mass[j + 1])
			{
				int tmp = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = tmp;
			}
		}
	}
	output_array(mass);
	// count duplicates
	int count_duplicates = 0;
	for (int i = 0; i < SIZE - 1; ++i)
	{
		if (mass[i] == mass[i + 1])
			++count_duplicates;
	}
	printf("count_duplicates = %d\n", count_duplicates);
	return 0;
}