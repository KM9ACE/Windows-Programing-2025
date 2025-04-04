#include <stdio.h>
#include <windows.h>

//아스키 코드로 색상 설정
void setTextColor(int color) 
{
    printf("\033[38;5;%dm", color); // 텍스트 색상 변경
}

void setBackgroundColor(int color) 
{
    printf("\033[48;5;%dm", color); // 배경 색상 변경
}

void resetColor() 
{
    printf("\033[0m"); // 색상 초기화
}

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// 바탕화면을 배경 색상으로 채우는 함수
void fillBackground(int color) 
{
    system("cls");  // 콘솔 창을 클리어
    setBackgroundColor(color);  // 배경 색상 설정
    for (int i = 0; i < 40; i++) 
    {  // 대략 40줄 출력
        for (int j = 0; j < 100; j++) 
        {  // 대략 100칸씩 출력
            printf(" ");
        }
        printf("\n");
    }
}

// 윈도우 구조체 정의
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    int backgroundColor;  // 배경 색상 (테두리 색상과 동일)
};

// 윈도우를 그리는 함수
void drawWindow(struct Window w) 
{
    // 윈도우 배경 색상 설정
    setBackgroundColor(w.backgroundColor);

    // 윈도우 테두리와 내부를 그리기
    for (int i = 0; i < w.width; i++) 
    {
        gotoxy(w.x + i, w.y);  // 상단
        printf("-");

        gotoxy(w.x + i, w.y + w.height - 1);  // 하단
        printf("-");
    }
    for (int i = 0; i < w.height; i++) 
    {
        gotoxy(w.x, w.y + i);  // 왼쪽
        printf("|");

        gotoxy(w.x + w.width - 1, w.y + i);  // 오른쪽
        printf("|");
    }

    // 윈도우 내부를 배경 색상으로 채우기
    for (int i = 1; i < w.height - 1; i++) 
    {
        for (int j = 1; j < w.width - 1; j++) 
        {
            gotoxy(w.x + j, w.y + i);
            printf(" ");
        }
    }

    resetColor();  // 색상 초기화
}

int main() 
{
    // 배경을 녹색으로 채우기
    fillBackground(22);  // 배경 색상은 초록색 (22)

    // 첫 번째 윈도우 (하늘색 배경)
    struct Window window1 = { 20, 7, 10, 3, 45 };  // 하늘색 배경 (테두리도 하늘색)
    // 두 번째 윈도우 (노란색 배경)
    struct Window window2 = { 20, 7, 15, 5, 226 };  // 노란색 배경 (테두리도 노란색)

    // 첫 번째 윈도우 그리기
    drawWindow(window1);

    // 두 번째 윈도우 그리기
    drawWindow(window2);

    return 0;
}