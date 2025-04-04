#include <stdio.h>
#include <windows.h>

// 아스키 코드로 배경 색상 설정
void setBackgroundColor(int color) 
{
    printf("\033[48;5;%dm", color);
}

// 색상 초기화
resetColor() 
{
    printf("\033[0m");
}

//커서 위치 조정
void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// 바탕화면 채우는 함수
void fillBackground(int color) 
{
    system("cls");
    setBackgroundColor(color);

    int i = 0;
	int j = 0;

    for (i = 0; i < 15; i++) 
    {
        for (j = 0; j < 120; j++) 
        {
            printf(" ");
        }
    }
}

// 윈도우 구조
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    int name;
    int backgroundColor;  // 배경 색상 (테두리 색상과 동일)
};

// 윈도우를 그리는 함수
void drawWindow(struct Window w) 
{
    // 윈도우 배경 색상 설정
    setBackgroundColor(w.backgroundColor);

	int i = 0;
	int j = 0;

    // 윈도우 테두리와 내부를 그리기
    for (i = 0; i < w.width; i++) 
    {
        gotoxy(w.x + i, w.y);  // 상단
        printf("-");
    }

    for (i = 0; i < w.height; i++) 
    {
        gotoxy(w.x, w.y + i);  // 왼쪽
        printf("|");

        gotoxy(w.x + w.width - 1, w.y + i);  // 오른쪽
        printf("|");
    }

    for (i = 0; i < w.width; i++)
	{
        gotoxy(w.x + i, w.y + w.height - 1);  // 하단
        printf("-");
    }

    // 윈도우 내부를 배경 색상으로 채우기
    for (i = 1; i < w.height - 1; i++) 
    {
        for (j = 1; j < w.width - 1; j++) 
        {
            gotoxy(w.x + j, w.y + i);
            printf(" ");
        }
    }
	printf("\n\n\n");
    resetColor();  // 색상 초기화
}

int main() {
    // 배경을 녹색으로 채우기
    fillBackground(22); // 초록색(22)

    // 첫 번째 윈도우 (하늘색 배경)
    struct Window window1 = { 20, 7, 10, 3, 'A', 45}; // 하늘색(45)
    // 두 번째 윈도우 (노란색 배경)
    struct Window window2 = { 20, 7, 15, 5, 'B', 226}; // 노란색(226)

    // 첫 번째 윈도우 그리기
    drawWindow(window1);

    // 두 번째 윈도우 그리기
    drawWindow(window2);

    return 0;
}