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
        printf("재시험 없습니다!\n");
    }
    else 
    {
        printf("우리는 망했다... 재시험이다...\n");
    }

    return 0;
}