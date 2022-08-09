#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ullong;

size_t digitsSum(size_t value, size_t base)
{
	if (value < base)
		return value;
	return value % base + digitsSum(value / base, base);
}
void digitsSumExample()
{
	size_t value = 127;
	printf_s("f(%lu,10) -> %lu\n", value, digitsSum(value, 10));
	printf_s("f(%lu,8) -> %lu\n", value, digitsSum(value, 8));
	printf_s("f(%lu,2) -> %lu\n\n", value, digitsSum(value, 2));
}

int binarySearch(int* mass, int l, int r, int value)
{
	int pos = -1;
	while (l < r)
	{
		int midPos = (l + r) / 2;
		int midValue = mass[midPos];
		if (value < midValue)
			r = midPos - 1;
		else if (value > midValue)
			l = midPos + 1;
		else
		{
			pos = midPos;
			break;
		}
	}
	return pos;
}
void binarySearchExample()
{
	int mass[] = { 1,2,3,4,5,6,7,8,9 };
	int value = 7;
	int pos = binarySearch(mass, 0, 8, value);
	if (pos > 0)
		printf("Position of %d : %d.\n", value, pos);
	else
		printf("%d value not finded.\n", value);
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
void rotate90(int** mass, int** mass2, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			mass2[i][j] = mass[size - 1 - j][i];
		}
	}
}
void rotate90Example()
{
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
	rotate90(mass, mass2, size);
	rotate90(mass2, mass, size);
	rotate90(mass, mass2, size);
	rotate90(mass2, mass, size);
	outputMass(mass, size, "mass after 4 times rotation");
	dealloc(mass, size);
	dealloc(mass2, size);
}

//int getMiddleElem(linkedList* l)
//{
//	node* slow = l->head;
//	node* fast = l->head;
//	node* predSlow = l->head;
//	while (fast != 0 && fast != l->tail)
//	{
//		predSlow = slow;
//		fast = fast->next->next;
//		slow = slow->next;
//	}
//	if (fast == l->tail)
//		return slow->value;
//	else
//		return predSlow->value;
//}

ullong fastPower(ullong base, ullong pow)
{
	ullong result = 1;
	while (pow)
	{
		if ((pow % 2) == 0)
		{
			base *= base;
			pow /= 2;
		}
		else
		{
			result *= base;
			--pow;
		}
	}
	return result;
}
void fastPowerExample()
{
	ullong base = 6, pow = 11;
	printf_s("%llu ^ %llu = %llu\n", base, pow, fastPower(base, pow));
}

ullong gcdRecursive(ullong lhs, ullong rhs)
{
	return rhs ? gcdRecursive(rhs, lhs % rhs) : lhs;
}
void swap(ullong* lhs, ullong* rhs)
{
	*lhs = *lhs ^ *rhs;
	*rhs = *lhs ^ *rhs;
	*lhs = *lhs ^ *rhs;
}
ullong gcd(ullong a, ullong b)
{
	while (b)
	{
		a %= b;
		swap(&a, &b);
	}
	return a;
}
void gcdExample()
{
	ullong lhs = 8, rhs = 18;
	printf_s("nod(%llu,%llu) == %llu\n", lhs, rhs, gcdRecursive(lhs, rhs));
	printf_s("nod(%llu,%llu) == %llu\n", lhs, rhs, gcd(lhs, rhs));
}


int main()
{
	//digitsSumExample();
	//binarySearchExample();
	//rotate90Example();
	////getMiddleElem();
	//fastPowerExample();
	gcdExample();
	return 0;
}