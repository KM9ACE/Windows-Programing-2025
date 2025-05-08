#include <stdio.h>

int main() 
{
    int width = 80;
    int height = 25;
    int i = 0;

    for (i = 0; i < height; i++) 
    {
        int j = 0;

        for (j = 0; j < width; j++) 
        {
            if (i < 1 || i >= height - 1 || j < 2 || j >= width - 2) 
            {
                printf(" ");  // 여백 부분
            }
            else 
            {
                printf("\033[44m \033[0m");
            }
        }
        printf("\n");
    }

    return 0;
}