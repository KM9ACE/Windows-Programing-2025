#include <windows.h>
#include <stdio.h>

void setBackgroundColor(int color)
{
    printf("\033[48;5;%dm", color);
}

void setTextColorBlack()
{
    printf("\033[30m");
}

int main()
{
    // 'P'�� �ʱ� ��ġ
    int x = 60;
    int y = 15;  
    char ch;

    while (1)
    {
        system("cls");

        setBackgroundColor(11);
        setTextColorBlack();

        // 'P'�� ���� ��ġ�� ���
        int i = 0;

        for (i = 0; i < y; i++) 
        { 
            printf("\n"); 
        }
        for (i = 0; i < x; i++)
        {
            printf(" ");
        }

        printf("P\n");

        if (GetAsyncKeyState(0x57) & 0x8000) // w
        {
            y--;
        }

        if (GetAsyncKeyState(0x53) & 0x8000) // s
        {
            y++;
        }

        if (GetAsyncKeyState(0x41) & 0x8000) // a
        {
            x--;
        }

        if (GetAsyncKeyState(0x44) & 0x8000) // d
        {
            x++;
        }

        // ���α׷� ���� ����
        if (GetAsyncKeyState(0x51) & 0x8000) // q
        {
            printf("���� ����\n");
            break;  // Q Ű�� ������ ����
        }
        // ��� ��� (CPU ��� ����ȭ)
        Sleep(10);
    }

    return 0;
}