#include<Windows.h>
#include<stdio.h>

void gotoxy(int x, int y) 
{
	COORD Cur;
	Cur. X = x;
	Cur. Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int i = 0;
int c = 0;

int main()
{

	for (i = 0; i < c; i++)
	{
		printf("-");
	}
	
	printf("");
	
	return 0;
}