#include<stdio.h>
#include<Windows.h>

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, Cur);
}
void drawWindow(int x, int y, int width, int height)
{
    for (int i = 0; i < width; i++) 
    {
        gotoxy(x + i, y); // Top border
        printf("-");

        gotoxy(x + i, y + height - 1);
        printf("-");
    }
    for (int i = 0; i < height; i++) 
    {
        gotoxy(x, y + i); // Left border
        printf("|");

        gotoxy(x + width - 1, y + i); // Right border
        printf("|");
    }
}
int main()
{
    int x = 10, y = 5, width = 20, height = 10;

    drawWindow(x, y, width, height);

    return 0;
}