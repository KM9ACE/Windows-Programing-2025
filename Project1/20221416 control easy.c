#include <conio.h>  // kbhit(), getch() 사용
#include <stdio.h>
#include<stdlib.h> // 터미널 사용

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
    int x = 10, y = 10;  // 'P'의 초기 위치
    char ch;

    while (1) 
    {
        system("cls");  // 화면 지우기 (Windows에서만 작동)

        setBackgroundColor(11);
        setTextColorBlack();

        int i = 0;
        // 'P'를 현재 위치에 출력
        for (i = 0; i < y; i++) printf("\n");
        for (i = 0; i < x; i++) printf(" ");

        printf("P\n");

        // 키 입력이 있을 경우
        if (_kbhit())// _kbhit <- 키 입력 없으면 0, 있으면 1
        {
            ch = _getch();  // 키 입력 받기

            if (ch == 'w') 
            {  // 위로 이동
                y--;
            }
            else if (ch == 's') 
            {  // 아래로 이동
                y++;
            }
            else if (ch == 'a') 
            {  // 왼쪽으로 이동
                x--;
            }
            else if (ch == 'd') 
            {  // 오른쪽으로 이동
                x++;
            }
            else if (ch == 'q') 
            {  // 'q'를 누르면 게임 종료
                printf("게임 종료\n");
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


