#include <stdio.h>
#include <stdlib.h>

void dynamic_arrays_example()
{
	printf_s("Input rows and columns count:\n");
	int rows, columns;
	scanf_s("%d", &rows);
	scanf_s("%d", &columns);
	int** matrix = (int**)malloc(rows * sizeof(int*));
	if (matrix != NULL)
	{
		for (int i = 0; i < rows; ++i)
			matrix[i] = (int*)malloc(columns * sizeof(int));
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				matrix[i][j] = rand() % 100; // == *(*(matrix+i) + j)
				printf_s("%d ", matrix[i][j]);
			}
			printf_s("\n");
		}
		for (int i = 0; i < rows; ++i)
			free(matrix[i]);
		free(matrix);
	}
}

int main()
{
	srand((unsigned int)time(0));
	dynamic_arrays_example();
	system("pause");
	return 0;
}