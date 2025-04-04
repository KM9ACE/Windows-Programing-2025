#include <stdio.h>
#include <windows.h>

// �ƽ�Ű �ڵ�� ��� ���� ����
void setBackgroundColor(int color) 
{
    printf("\033[48;5;%dm", color);
}

// ���� �ʱ�ȭ
resetColor() 
{
    printf("\033[0m");
}

//Ŀ�� ��ġ ����
void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// ����ȭ�� ä��� �Լ�
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

// ������ ����
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    int name;
    int backgroundColor;  // ��� ���� (�׵θ� ����� ����)
};

// �����츦 �׸��� �Լ�
void drawWindow(struct Window w) 
{
    // ������ ��� ���� ����
    setBackgroundColor(w.backgroundColor);

	int i = 0;
	int j = 0;

    // ������ �׵θ��� ���θ� �׸���
    for (i = 0; i < w.width; i++) 
    {
        gotoxy(w.x + i, w.y);  // ���
        printf("-");
    }

    for (i = 0; i < w.height; i++) 
    {
        gotoxy(w.x, w.y + i);  // ����
        printf("|");

        gotoxy(w.x + w.width - 1, w.y + i);  // ������
        printf("|");
    }

    for (i = 0; i < w.width; i++)
	{
        gotoxy(w.x + i, w.y + w.height - 1);  // �ϴ�
        printf("-");
    }

    // ������ ���θ� ��� �������� ä���
    for (i = 1; i < w.height - 1; i++) 
    {
        for (j = 1; j < w.width - 1; j++) 
        {
            gotoxy(w.x + j, w.y + i);
            printf(" ");
        }
    }
	printf("\n\n\n");
    resetColor();  // ���� �ʱ�ȭ
}

int main() {
    // ����� ������� ä���
    fillBackground(22); // �ʷϻ�(22)

    // ù ��° ������ (�ϴû� ���)
    struct Window window1 = { 20, 7, 10, 3, 'A', 45}; // �ϴû�(45)
    // �� ��° ������ (����� ���)
    struct Window window2 = { 20, 7, 15, 5, 'B', 226}; // �����(226)

    // ù ��° ������ �׸���
    drawWindow(window1);

    // �� ��° ������ �׸���
    drawWindow(window2);

    return 0;
}