#include <stdio.h>

int A = 0;

void PassOrFail() 
{
    int myPredictedScore = 0;

    if (myPredictedScore >= 50) 
    {
        A = 1;
    }
    else 
    {
        A = 0;
    }
}

int main() 
{
    PassOrFail();

    if (A == 1) 
    {
        printf("����� �����ϴ�!\n");
    }
    else 
    {
        printf("�츮�� ���ߴ�... ������̴�...\n");
    }

    return 0;
}