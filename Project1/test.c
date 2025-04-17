#include <stdio.h>
#include <windows.h>

// 콘솔 색상 설정 (ANSI 이스케이프 코드 사용)
void setConsoleColor(int color) {
    // 30: 검정, 31: 빨강, 32: 초록, 33: 노랑, 34: 파랑, 35: 마젠타, 36: 시안, 37: 흰색
    // 40~47은 배경색
    printf("\033[%dm", 30 + (color & 0x07)); // 전경색 설정
    if (color & 0x08) {
        printf("\033[1m"); // 밝게
    }
    else {
        printf("\033[0m"); // 기본
    }
}

// 콘솔 배경 색상 설정 (ANSI 이스케이프 코드 사용)
void setConsoleBackgroundColor(int color) {
    // 40: 검정, 41: 빨강, 42: 초록, 43: 노랑, 44: 파랑, 45: 마젠타, 46: 시안, 47: 흰색
    printf("\033[%dm", 40 + (color & 0x07));
}

// 콘솔 크기 얻기 함수 (이전 코드와 동일)
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;
}

// 커서 이동 함수 (ANSI 이스케이프 코드 사용)
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

int main() {
    int width = getConsoleWidth();
    int height = getConsoleHeight();

    if (width != -1 && height != -1) {
        int left_margin = 5;
        int right_margin = 5;
        int top_margin = 2;
        int bottom_margin = 3;

        // 칠할 영역 계산
        int fill_start_row = top_margin;
        int fill_start_col = left_margin;
        int fill_end_row = height - 1 - bottom_margin;
        int fill_end_col = width - 1 - right_margin;

        // 파란색 배경으로 영역 칠하기 (파란색 배경 ANSI 코드: 44)
        setConsoleBackgroundColor(4); // 파란색 배경 설정
        for (int i = fill_start_row; i <= fill_end_row; ++i) {
            move_cursor(i, fill_start_col);
            for (int j = fill_start_col; j <= fill_end_col; ++j) {
                printf(" ");
            }
        }

        // 색상 초기화
        printf("\033[0m"); // 모든 속성 초기화

        // 커서를 마지막 줄로 이동 (선택 사항)
        move_cursor(height, 1);
    }


    return 0;
}