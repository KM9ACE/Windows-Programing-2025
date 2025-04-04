#include <stdio.h>
#include <windows.h>

//�ƽ�Ű �ڵ�� ���� ����
void setTextColor(int color) 
{
    printf("\033[38;5;%dm", color); // �ؽ�Ʈ ���� ����
}

void setBackgroundColor(int color) 
{
    printf("\033[48;5;%dm", color); // ��� ���� ����
}

void resetColor() 
{
    printf("\033[0m"); // ���� �ʱ�ȭ
}

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// ����ȭ���� ��� �������� ä��� �Լ�
void fillBackground(int color) 
{
    system("cls");  // �ܼ� â�� Ŭ����
    setBackgroundColor(color);  // ��� ���� ����
    for (int i = 0; i < 40; i++) 
    {  // �뷫 40�� ���
        for (int j = 0; j < 100; j++) 
        {  // �뷫 100ĭ�� ���
            printf(" ");
        }
        printf("\n");
    }
}

// ������ ����ü ����
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    int backgroundColor;  // ��� ���� (�׵θ� ����� ����)
};

// �����츦 �׸��� �Լ�
void drawWindow(struct Window w) 
{
    // ������ ��� ���� ����
    setBackgroundColor(w.backgroundColor);

    // ������ �׵θ��� ���θ� �׸���
    for (int i = 0; i < w.width; i++) 
    {
        gotoxy(w.x + i, w.y);  // ���
        printf("-");

        gotoxy(w.x + i, w.y + w.height - 1);  // �ϴ�
        printf("-");
    }
    for (int i = 0; i < w.height; i++) 
    {
        gotoxy(w.x, w.y + i);  // ����
        printf("|");

        gotoxy(w.x + w.width - 1, w.y + i);  // ������
        printf("|");
    }

    // ������ ���θ� ��� �������� ä���
    for (int i = 1; i < w.height - 1; i++) 
    {
        for (int j = 1; j < w.width - 1; j++) 
        {
            gotoxy(w.x + j, w.y + i);
            printf(" ");
        }
    }

    resetColor();  // ���� �ʱ�ȭ
}

int main() 
{
    // ����� ������� ä���
    fillBackground(22);  // ��� ������ �ʷϻ� (22)

    // ù ��° ������ (�ϴû� ���)
    struct Window window1 = { 20, 7, 10, 3, 45 };  // �ϴû� ��� (�׵θ��� �ϴû�)
    // �� ��° ������ (����� ���)
    struct Window window2 = { 20, 7, 15, 5, 226 };  // ����� ��� (�׵θ��� �����)

    // ù ��° ������ �׸���
    drawWindow(window1);

    // �� ��° ������ �׸���
    drawWindow(window2);

    return 0;
}