#include <conio.h>  // kbhit(), getch() ���
#include <stdio.h>
#include<stdlib.h> // �͹̳� ���

void setBackgroundColor(int color) 
{
    printf("\033[48;5;%dm", color);
}

void setTextColorBlack() 
{
    printf("\033[30m");
}

void control() 
{
    int x = 10, y = 10;  // 'P'�� �ʱ� ��ġ
    char ch;

    while (1) 
    {
        system("cls");  // ȭ�� ����� (Windows������ �۵�)

        setBackgroundColor(11);
        setTextColorBlack();

        int i = 0;
        // 'P'�� ���� ��ġ�� ���
        for (i = 0; i < y; i++) printf("\n");
        for (i = 0; i < x; i++) printf(" ");

        printf("P\n");

        // Ű �Է��� ���� ���
        if (_kbhit())// _kbhit <- Ű �Է� ������ 0, ������ 1
        {
            ch = _getch();  // Ű �Է� �ޱ�

            if (ch == 'w') 
            {  // ���� �̵�
                y--;
            }
            else if (ch == 's') 
            {  // �Ʒ��� �̵�
                y++;
            }
            else if (ch == 'a') 
            {  // �������� �̵�
                x--;
            }
            else if (ch == 'd') 
            {  // ���������� �̵�
                x++;
            }
            else if (ch == 'q') 
            {  // 'q'�� ������ ���� ����
                printf("���� ����\n");
                break;
            }
        }
    }
}

int main() 
{
    control();

    return 0;
}


