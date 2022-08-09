#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pow(int a, int b)
{
	int result = 1;
	for (int i = 0; i < b; ++i)
	{
		result = result * a;
	}
	return result;
}

void increment(int a) // bad idea! will discuss later
{
	++a;
}

void file_io_example()
{
	FILE* in_f;
	errno_t err;
	int value;
	err = fopen_s(&in_f, "C:\\_main\\_univer\\Projects\\TESTS\\C\\input.txt", "r+");
	if (err == 0)
	{
		fscanf_s(in_f, "%d", &value);
		fprintf_s(in_f, " %d", 100);
		printf_s("value = %d\n", value);
		fclose(in_f);
	}
	else
		printf("Error in opening file : %d\n", err);
}

int main()
{
	// functions examples
	int b = 2;
	increment(b);
	int result = pow(2, 3);

	// pointers examples
	int a = 3; // 4 bytes?
	printf_s("%d\n", a);
	scanf_s("%d", &a);
	int* ptr = &a; // ? bytes?
	printf("%p\n", ptr);
	printf("%d\n", *ptr); // dereferencing a pointer
	*ptr = 10;
	printf("%d\n", a);
	printf("%d\n", *ptr);

	file_io_example();
	return 0;
}