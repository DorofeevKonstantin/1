#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void setconsolesize(int x, int y)
{
	HANDLE hCons;
	COORD crd;
	SMALL_RECT rct;
	crd.X = (short)x + 1;
	crd.Y = (short)y + 1;
	rct.Left = 0;
	rct.Top = 0;
	rct.Right = x;
	rct.Bottom = y;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hCons, crd);
	SetConsoleWindowInfo(hCons, 1, &rct);
}
void hidecursor()
{
	HANDLE hCons;
	CONSOLE_CURSOR_INFO cci;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	cci.dwSize = 1;
	cci.bVisible = 0;
	SetConsoleCursorInfo(hCons, &cci);
}
void clrscr()
{
	HANDLE hCons;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD crd;
	int len;
	DWORD bRet;
	short x, y;
	char space = 0x20;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hCons, &csbi);
	x = csbi.dwSize.X;
	y = csbi.dwSize.Y;
	len = (int)x*y;
	crd.X = 0;
	crd.Y = 0;
	FillConsoleOutputCharacter(hCons, space, len, crd, &bRet);
}
void gotoxy(int column, int row)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	//#ifdef MY_DEBUG
	//  if (hCons == INVALID_HANDLE_VALUE || hCons == 0) printf("\nERROR!!!\n");
	//#endif  	  
	crd.X = (short)column;
	crd.Y = (short)row;
	//#ifedf MY_DEBUG
	// if (SetConsoleCursorPosition(hCons,crd) == 0) printf("\nERROR2\n");
	//#else 
	SetConsoleCursorPosition(hCons, crd);
	//#endif
}
int GetFontSize(HANDLE windowHandle, COORD *size)
{
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	*size = font.dwFontSize;

	return 1;
}
int SetFontSize(HANDLE windowHandle, COORD size)
{
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	font.dwFontSize = size;

	if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	return 1;
}

int main()
{
	//setconsolesize(200, 200);
	//clrscr();
	hidecursor();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size;
	DWORD delay = 50;
	
	for (int i = 0; i < 50; i++)
	{
		gotoxy(i, 10);
		printf(".");
		Sleep(delay);
	}
	clrscr();
	for (int i = 5; i < 15; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			gotoxy(i, j);
			printf("x");
			Sleep(delay);
		}
	}
	gotoxy(0, 0);
	if (GetFontSize(h, &size))
	{
		size.X *= 2;
		size.Y *= 2;
		SetFontSize(h, size);
	}
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | BACKGROUND_GREEN);
	printf("Game over my friend!\n");
	getchar();
	return 0;
}