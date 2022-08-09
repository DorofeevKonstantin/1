#include <stdio.h>
#include <stdlib.h>
//#include <string.h> // you must be ready to do the same things in your code

void arithmetic_examples()
{
	// +,-,*,/,%,++,--,=
	int a = 3, b = 4;
	int result = a + b;
}

void logic_examples()
{
	// &&,||,!,==,!=,>,<,>=,<=,ternop
	int a = 3, b = 4;
	if ((a % 2 == 5) && ((b + 1) >= 2 || 0))
		printf_s("strange example");
}

void bits_examples()
{
	// &,|,~,^,>>,<<
	int a = 3, b = 4;
	int c = a & b; // c==?
	// 011 == a
	// 100 == b
	// 000 == c
	c = a | b; // c==?
	a = 6;
	// 110 ^ 100 == 010
	c = a ^ b; // c==?
	a = 1;
	c = ~a; // c==?
	c = 17;
	c = c >> 1; // c==?
	c = -3;
	c = c << 1; // c==?
}

void output_string_with_known_size(char* str, int size)
{
	for (int i = 0; i < size; ++i)
		printf_s("%c", str[i]);
	printf_s("\n");
}

void output_string(char* str)
{
	// '\0' in the end
	for (int i = 0; str[i] != '\0'; ++i)
		printf_s("%c", str[i]);
	printf_s("\n");
}

int my_strange_strlen(char* str)
{
	int length = 0;
	while (str[length] != '\0' && str[length] != '\n') // '\n' we want for file strings example
		++length;
	return length;
}

void string_examples()
{
	char* str = (char*)malloc(10 * sizeof(char));
	if (str != NULL)
	{
		str[0] = 'a';
		str[1] = 'b';
		str[2] = '\0';
		output_string_with_known_size(str, 10);
		output_string(str);
		free(str);
	}

	printf_s("\nLength of 123 == %d\n", my_strange_strlen("123"));
	output_string("123456");
}

void dynamic_arrays()
{
	printf_s("Input rows and columns count:\n");
	int rows, columns;
	scanf_s("%d", &rows);
	scanf_s("%d", &columns);
	// alloc memory
	int** matrix = (int**)malloc(rows * sizeof(int*));
	if (matrix != NULL)
	{
		for (int i = 0; i < rows; ++i)
		{
			matrix[i] = (int*)malloc(columns * sizeof(int));
		}
		// works
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				matrix[i][j] = i; // == *(*(matrix+i) + j)
				printf_s("%d ", matrix[i][j]);
			}
			printf_s("\n");
		}
		// dealloc
		for (int i = 0; i < rows; ++i)
			free(matrix[i]);
		free(matrix);
	}
}

void file_io_example()
{
	FILE* in;
	char** strings = NULL;
	int strings_count = 1; // we must calculate it
	if (fopen_s(&in, "C:\\_main\\_univer\\Projects\\TESTS\\lecture-code\\input.txt", "r") == 0)
	{
		fseek(in, 0, SEEK_END);
		long int bytes_in_file = ftell(in);
		fseek(in, 0, SEEK_SET);
		char* buffer = (char*)malloc(bytes_in_file + 1);
		char current_symbol;
		while (fscanf_s(in, "%c", &current_symbol, 1) != EOF)
		{
			if (current_symbol == '\n')
				++strings_count;
		}
		fseek(in, 0, SEEK_SET);
		strings = (char**)malloc(strings_count * sizeof(char*));
		if (strings != NULL)
		{
			for (int i = 0; i < strings_count; ++i)
			{
				fgets(buffer, bytes_in_file + 1, in);
				int length = my_strange_strlen(buffer) + 1;
				strings[i] = (char*)malloc(length * sizeof(char));
				for (int j = 0; j < length - 1; ++j)
				{
					strings[i][j] = buffer[j];
				}
				strings[i][length - 1] = '\0';
			}
		}
		fclose(in);
		free(buffer);
	}

	if (strings != NULL)
	{
		printf_s("\nSTRINGS:\n");
		for (int i = 0; i < strings_count; ++i)
		{
			if (strings[i] != NULL)
				printf_s("%s\n", strings[i]);
		}
	}

	for (int i = 0; i < strings_count; i++)
		free(strings[i]);
	free(strings);
}

int main()
{
	arithmetic_examples();
	logic_examples();
	bits_examples();
	string_examples();
	dynamic_arrays();
	file_io_example();
	system("pause");
	return 0;
}