#include <stdio.h>

int PassOrFail() 
{
    int myPredictedScore = 40;

    if (myPredictedScore >= 50) 
    {
         return 1;
    }
    else 
    {
         return 0;
    }
}

int main() 
{
    int A = 0;

    A = PassOrFail();

    if ( A == 1) 
    {
        printf("����� �����ϴ�!\n");
    }
    else 
    {
        printf("�츮�� ���ߴ�... ������̴�...\n");
    }

    return 0;
}