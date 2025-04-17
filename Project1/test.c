#include <stdio.h>
#include <windows.h>

// �ܼ� ���� ���� (ANSI �̽������� �ڵ� ���)
void setConsoleColor(int color) {
    // 30: ����, 31: ����, 32: �ʷ�, 33: ���, 34: �Ķ�, 35: ����Ÿ, 36: �þ�, 37: ���
    // 40~47�� ����
    printf("\033[%dm", 30 + (color & 0x07)); // ����� ����
    if (color & 0x08) {
        printf("\033[1m"); // ���
    }
    else {
        printf("\033[0m"); // �⺻
    }
}

// �ܼ� ��� ���� ���� (ANSI �̽������� �ڵ� ���)
void setConsoleBackgroundColor(int color) {
    // 40: ����, 41: ����, 42: �ʷ�, 43: ���, 44: �Ķ�, 45: ����Ÿ, 46: �þ�, 47: ���
    printf("\033[%dm", 40 + (color & 0x07));
}

// �ܼ� ũ�� ��� �Լ� (���� �ڵ�� ����)
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

// Ŀ�� �̵� �Լ� (ANSI �̽������� �ڵ� ���)
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

        // ĥ�� ���� ���
        int fill_start_row = top_margin;
        int fill_start_col = left_margin;
        int fill_end_row = height - 1 - bottom_margin;
        int fill_end_col = width - 1 - right_margin;

        // �Ķ��� ������� ���� ĥ�ϱ� (�Ķ��� ��� ANSI �ڵ�: 44)
        setConsoleBackgroundColor(4); // �Ķ��� ��� ����
        for (int i = fill_start_row; i <= fill_end_row; ++i) {
            move_cursor(i, fill_start_col);
            for (int j = fill_start_col; j <= fill_end_col; ++j) {
                printf(" ");
            }
        }

        // ���� �ʱ�ȭ
        printf("\033[0m"); // ��� �Ӽ� �ʱ�ȭ

        // Ŀ���� ������ �ٷ� �̵� (���� ����)
        move_cursor(height, 1);
    }


    return 0;
}