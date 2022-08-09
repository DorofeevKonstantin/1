#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100
#define rows 2
#define columns 3

void palindrome_test()
{
	char str[MAX_SIZE];
	scanf_s("%99s", str, 100);
	int length = 0;
	while (str[length] != 0)
		++length;
	printf_s("str = %s\n", str);
	int is_palindrome = 1;
	for (int i = 0; i < length / 2; i++)
	{
		if (str[i] != str[length - 1 - i]) // why is C26451 ?
			is_palindrome = 0;
	}
	if (is_palindrome == 1)
		printf("str is palindrome.\n");
	else
		printf("str is not palindrome.\n");
}

void dynamic_array_example()
{
	FILE* in;
	int size;
	errno_t err;
	err = fopen_s(&in, "C:\\_main\\_univer\\Projects\\TESTS\\lecture-code\\input.txt", "r");
	if (err == 0 && in != 0)
	{
		fscanf_s(in, "%d", &size);
		int* mass = (int*)malloc(size * sizeof(int));
		if (mass != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				fscanf_s(in, "%d", &mass[i]); // == (mass+i)
			}
			for (int i = 0; i < size; i++)
			{
				printf_s("%d ", mass[i]);
			}
			printf_s("\n");
			free(mass);
		}
		fclose(in);
	}
	else
		printf("Can't open file\n");
}

void rand_example()
{
	srand((unsigned int)time(0));
	int value = rand() % 100; // [-200...200]  ==  rand()%401 - 200
	printf("value = %d %d\n", value, rand() % 100);
}

void static_two_dimensional_array_example()
{
	int matrix[rows][columns]; // rows*columns*? bytes
	printf("Input %d ints\n", rows * columns);
	// rows
	for (int i = 0; i < rows; i++)
	{
		// columns
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = i + j;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void find_max_elem_for_matrix_rows()
{
	srand((unsigned int)time(0));
	int matrix[rows][columns];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = rand() % 100;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < rows; i++)
	{
		// find max element in each (i) row
		int max_element = matrix[i][0];
		for (int j = 0; j < columns; j++)
		{
			if (matrix[i][j] > max_element)
				max_element = matrix[i][j];
		}
		printf("max_element in %d row == %d\n", i, max_element);
	}
}

int main()
{
	/*palindrome_test();
	dynamic_array_example();
	rand_example();
	static_two_dimensional_array_example();
	find_max_elem_for_matrix_rows();*/
	return 0;
}