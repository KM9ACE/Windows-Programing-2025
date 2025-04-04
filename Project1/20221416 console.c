#include <stdio.h>
#include <windows.h>

// 아스키 코드로 배경 색상 설정
void setBackgroundColor(int color) {
    printf("\033[48;5;%dm", color);
}

// 색상 초기화
resetColor() {
    printf("\033[0m");
}

// 커서 위치 조정
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// 바탕화면 채우는 함수
void fillBackground(int color) {
    system("cls");
    setBackgroundColor(color);

    int i, j;
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 120; j++) {
            printf(" ");
        }
    }
}

// 윈도우 구조체
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    char text[20];
    int backgroundColor; // 배경 색상 (테두리 색상과 동일)
};

// 윈도우를 그리는 함수
void drawWindow(struct Window w) 
{
    // 윈도우 배경 색상 설정
    setBackgroundColor(w.backgroundColor);

    int i, j;

    for (i = 0; i < w.width; i++) // 상단 테두리
    {
        gotoxy(w.x + i, w.y);
        printf("-");
    }
    printf("\n");

    for (i = 1; i < w.height - 1; i++)  // 내부 및 좌우 테두리
    {
        gotoxy(w.x, w.y + i);
        printf("|");

        for (j = 1; j < w.width - 1; j++) 
        {
            gotoxy(w.x + j, w.y + i);
            printf(" ");
        }
        gotoxy(w.x + w.width - 1, w.y + i);
        printf("|\n");
    }
  
    for (i = 0; i < w.width; i++)   // 하단 테두리
    {
        gotoxy(w.x + i, w.y + w.height - 1);
        printf("-");
    }

    if (strlen(w.text) > 0) // 문자열 길이가 0보다 큰 경우에만 출력
    { 
        gotoxy(w.x + 2, w.y + w.height / 2); // 글자 출력 위치 설정
        printf("%s", w.text);
    }

    printf("\n\n\n");

    resetColor(); // 색상 초기화
}

int main() {
    // 배경을 녹색으로 채우기
    fillBackground(22); // 초록색(22)

    // 첫 번째 윈도우
	struct Window window1_1 = { 20, 3, 10, 3, "A", 45 }; // 첫 번째 윈도우 제목 창
    struct Window window1_2 = { 20, 5, 10, 5, "", 45}; // 첫 번째 윈도우 본문

    // 두 번째 윈도우
    struct Window window2_1 = { 20, 3, 15, 5, "B", 226 }; // 두 번째 윈도우 제목
    struct Window window2_2 = { 20, 5, 15, 7, "", 226}; // 두 번째 윈도우 본문

    // 첫 번째 윈도우 그리기
    drawWindow(window1_1);
    drawWindow(window1_2);

    // 두 번째 윈도우 그리기
    drawWindow(window2_1);
    drawWindow(window2_2);

    return 0;
}