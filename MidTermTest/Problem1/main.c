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
        printf("재시험 없습니다!\n");
    }
    else 
    {
        printf("우리는 망했다... 재시험이다...\n");
    }

    return 0;
}