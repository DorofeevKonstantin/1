#include <stdio.h>

//int mass[] = { 9,8,7,6,5,4,3,2,1 };
//int value = 7;
//int pos = unknownFunction(mass, 0, 8, value);
int unknownFunction(int* mass, int l, int r, int value)
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

int main()
{
	int mass[] = { 9,8,7,6,5,4,3,2,1 };
	int value = 7;
	int pos = unknownFunction(mass, 0, 8, value);
	if (pos > 0)
		printf("Position of %d : %d.\n", value, pos);
	else
		printf("%d value not finded.\n", value);
	return 0;
}