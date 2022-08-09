#include <stdio.h>
#include <stdlib.h>

// https://docs.microsoft.com/en-us/cpp/c-language/arguments-to-main?view=msvc-160
int main(int argc, char* argv[], char* envp[])
{
	//printf_s("%d\n", (~(-9) >> 2) ^ 3);
	printf_s("argc == %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] == %s\n", i, argv[i]);
	}
	printf("\nENVP:\n");
	// envp, is an array of pointers to environment variables, envp array is terminated by a null pointer
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return 0;
}