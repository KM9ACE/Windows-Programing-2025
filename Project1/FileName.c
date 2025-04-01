#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main() 
{
	printf("***************\n");
	printf("* 뭐하는 게임 *\n");
	printf("***************\n\n");
	
	printf("1. 게임 시작\n");
	printf("2. 게임 종료\n\n");

	printf("입력 : ");

	char A; //게임 시작 여부 변수

	A = _getch();
	putchar(A);
 
	if (A == '1')
	{
		printf("\n게임을 시작합니다");
		system("cls");

		printf("___________0___________");

		char B; //좌우 이동용 키보드 변수 자판 A, D 사용

		while (1)
		{
			B = _getch();

			if (B == 'A')
			{
				system("cls");
				printf("__________0____________");
			}
			else if (B == 'D')
			{
				system("cls");
				printf("____________0__________");
			}
			else
			{
				printf("\n\n잘못눌렀잖아");
			}
		}
		
	}
	else if (A == '2')
	{
		printf("\n\n게임을 종료합니다");
	}
	else
	{
		printf("\n\n잘못눌렀잖아");
	}

	return 0;
}