#include <stdio.h>
#include <windows.h>

// �ƽ�Ű �ڵ�� ��� ���� ����
void setBackgroundColor(int color) {
    printf("\033[48;5;%dm", color);
}

// ���� �ʱ�ȭ
resetColor() {
    printf("\033[0m");
}

// Ŀ�� ��ġ ����
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// ����ȭ�� ä��� �Լ�
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

// ������ ����ü
struct Window 
{
    int width;
    int height;
    int x;
    int y;
    char text[20];
    int backgroundColor; // ��� ���� (�׵θ� ����� ����)
};

// �����츦 �׸��� �Լ�
void drawWindow(struct Window w) 
{
    // ������ ��� ���� ����
    setBackgroundColor(w.backgroundColor);

    int i, j;

    for (i = 0; i < w.width; i++) // ��� �׵θ�
    {
        gotoxy(w.x + i, w.y);
        printf("-");
    }
    printf("\n");

    for (i = 1; i < w.height - 1; i++)  // ���� �� �¿� �׵θ�
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
  
    for (i = 0; i < w.width; i++)   // �ϴ� �׵θ�
    {
        gotoxy(w.x + i, w.y + w.height - 1);
        printf("-");
    }

    if (strlen(w.text) > 0) // ���ڿ� ���̰� 0���� ū ��쿡�� ���
    { 
        gotoxy(w.x + 2, w.y + w.height / 2); // ���� ��� ��ġ ����
        printf("%s", w.text);
    }

    printf("\n\n\n");

    resetColor(); // ���� �ʱ�ȭ
}

int main() {
    // ����� ������� ä���
    fillBackground(22); // �ʷϻ�(22)

    // ù ��° ������
	struct Window window1_1 = { 20, 3, 10, 3, "A", 45 }; // ù ��° ������ ���� â
    struct Window window1_2 = { 20, 5, 10, 5, "", 45}; // ù ��° ������ ����

    // �� ��° ������
    struct Window window2_1 = { 20, 3, 15, 5, "B", 226 }; // �� ��° ������ ����
    struct Window window2_2 = { 20, 5, 15, 7, "", 226}; // �� ��° ������ ����

    // ù ��° ������ �׸���
    drawWindow(window1_1);
    drawWindow(window1_2);

    // �� ��° ������ �׸���
    drawWindow(window2_1);
    drawWindow(window2_2);

    return 0;
}