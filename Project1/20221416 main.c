#include<stdio.h> // #include <-- 컴파일 이전에 처리, 기본적인거
#include<conio.h> // 그 외에 여러가지 추가
#include<stdlib.h> // 터미널 사용

int main()
{
	printf("***************\n");
	printf("* 뭐하는 게임 *\n");
	printf("***************\n\n");

	printf("1. 게임 시작\n");
	printf("2. 게임 종료\n\n");

	printf("입력 : ");

	char A = 0; // 게임 시작 여부 변수
	char B = 0; // 좌우 이동용 변수 키보드 자판 A, D 사용
	int C = 11; // 0의 위치 변수 -> 23개 중에 11번째 가운데
	int i = 0; // ___________0___________ 크기 고정 변수

	A = _getch(); // A 입력 받기
	putchar(A); 

	if (A == '1')
	{
		system("cls"); // 화면 지우기

		printf("오른쪽 : D, 왼쪽 : A\n");
		printf("___________0___________");

		while (1) // 무한 반복
		{
			B = _getch(); // B 입력 받기 무한 반복
			system("cls"); // 화면 지우기 무한 반복

			if (B == 'A' || B == 'a')
			{
				if (C > 0) 
				{
					C--; // 자판 A 누르면 C값 줄어들면서 왼쪽으로 이동
				}
			}
			else if (B == 'D' || B == 'd')
			{
				if (C < 22)
				{
					C++; // 자판 B 누르면 C값 올라가면서 오른쪽으로 이동
				}
			}
			else
			{
				printf("\n\n잘못눌렀잖아");
			}
			for (i = 0; i < 23; i++) // ___________0___________ 크기 고정
			{
				if (i == C)
				{
					printf("0"); // i값과 C값이 같은 위치에는 0 출력
				}
				else
				{
					printf("_"); // i값과 C값이 다른 위치에는 _ 출력
				}
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