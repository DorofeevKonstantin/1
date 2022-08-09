#include <stdio.h>
#include <stdlib.h>
#define INT_MASS_SIZE 10
#define STR_SIZE 20
int main()
{
	int int_value = 5;
	double double_value = 3.14;
	int* int_mass = (int*)malloc(INT_MASS_SIZE * sizeof(int));
	if (int_mass != NULL)
	{
		for (unsigned int i = 0; i < INT_MASS_SIZE; i++)
			int_mass[i] = i;
		free(int_mass);
	}
	char* str = (char*)malloc(STR_SIZE * sizeof(char));
	if (str != NULL)
	{
		for (unsigned int i = 0; i < STR_SIZE; i++)
			str[i] = 'a';
		free(str);
	}
	return 0;
}