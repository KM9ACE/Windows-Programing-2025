#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main() 
{
	printf("***************\n");
	printf("* ���ϴ� ���� *\n");
	printf("***************\n\n");
	
	printf("1. ���� ����\n");
	printf("2. ���� ����\n\n");

	printf("�Է� : ");

	char A; //���� ���� ���� ����

	A = _getch();
	putchar(A);
 
	if (A == '1')
	{
		printf("\n������ �����մϴ�");
		system("cls");

		printf("___________0___________");

		char B; //�¿� �̵��� Ű���� ���� ���� A, D ���

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
				printf("\n\n�߸������ݾ�");
			}
		}
		
	}
	else if (A == '2')
	{
		printf("\n\n������ �����մϴ�");
	}
	else
	{
		printf("\n\n�߸������ݾ�");
	}

	return 0;
}