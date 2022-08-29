#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct flags
{
	unsigned char is_read : 1;
	unsigned char is_write : 1;
	unsigned char is_binary : 1;
};

union symbol
{
	int iValue;
	char cValue;
};

enum day
{
	monday = 1,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
};

typedef struct flags FLAGS;
typedef union symbol SYMBOL;
typedef enum day DAY;

struct field
{
	unsigned char cells : 8; // need to implement operations for work with bits
};
typedef struct field FIELD;

void flagsExample()
{
	FLAGS inputFileInfo;
	inputFileInfo.is_binary = 1;
	inputFileInfo.is_read = 1;
	inputFileInfo.is_write = 0;
	printf_s("sizeof(inputFileInfo) = %lu\n", sizeof(inputFileInfo));
}

void symbolExample()
{
	SYMBOL s;
	s.cValue = 'F';
	printf_s("sizeof (union) = %lu , value = %c\n", sizeof(s), s.cValue);
	s.iValue = 55;
	printf_s("sizeof (union) = %lu , value = %d\n", sizeof(s), s.iValue);
}

void dayExample()
{
	DAY day = friday;
	printf_s("Now is day : %d\n", day);
	printf_s("Enter day number:\n");
	scanf_s("%d", &day);
	if (day >= monday && day <= friday)
		printf_s("It is workday.\n");
	else if (day >= saturday && day <= sunday)
		printf_s("It is holiday.\n");
	else
		printf_s("Wrong input.\n");
}

void fieldsExample()
{
	// implement field 80x80 (6400 cells) on stack memory
	printf_s("sizeof (struct FIELD) = %lu\n", sizeof(FIELD));
	FIELD gameFieldStack[800]; // 8 cells in each
	char simpleFieldStack[80][80];
	printf_s("sizeof (gameFieldStack) = %lu b\nsizeof (simpleFieldStack) = %lu kb \n", sizeof(gameFieldStack), sizeof(simpleFieldStack) / 1024);

	// implement field 1000x1000 (1'000'000 cells) on heap memory
	unsigned int dynamicFieldSize = 1000;
	FIELD* gameFieldHeap = (FIELD*)malloc(((dynamicFieldSize * dynamicFieldSize) / 8 + 1) * sizeof(FIELD));
	unsigned int memoryUsed = sizeof(void*) + ((dynamicFieldSize * dynamicFieldSize) / 8 + 1) * sizeof(FIELD);
	printf_s("sizeof (gameFieldHeap) = %lu kb\n", memoryUsed / 1024);
	char** simpleFieldHeap = (char**)malloc(dynamicFieldSize * sizeof(char*));
	memoryUsed = sizeof(void*) + dynamicFieldSize * sizeof(char*);
	for (int i = 0; i < dynamicFieldSize; ++i)
	{
		simpleFieldHeap[i] = (char*)malloc(dynamicFieldSize * sizeof(char));
		memoryUsed += dynamicFieldSize * sizeof(char);
	}
	printf_s("sizeof (simpleFieldHeap) = %lu kb\n", memoryUsed / 1024);

	for (int i = 0; i < dynamicFieldSize; ++i)
		free(simpleFieldHeap[i]);
	free(simpleFieldHeap);
	free(gameFieldHeap);
}

int main()
{
	flagsExample();
	symbolExample();
	dayExample();
	fieldsExample();
	system("pause");
	return 0;
}