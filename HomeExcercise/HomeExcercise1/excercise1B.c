#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printMultTable(int maxMult);

//Get input from user
void main()
{
    int maxMult;
    printf("Please enter number:\n");
    scanf("%d",&maxMult);
    printMultTable(maxMult);
}

void printMultTable(int maxMult)
{
    int row, col, num, spaces, spacesCount=0;
    for( row = 1, num = 1; (row <= maxMult) && (num <= maxMult); row++, num++ )
    {
        for( col = 1; col <= maxMult; col++)
        {
            spaces=col*maxMult;
            spacesCount=0;
            while(spaces != 0)
             {
                spaces /= 10;
                spacesCount++;
            }
            printf("%*d", spacesCount, num);
            if (col!=maxMult)
            {
                printf(" ");
            }
            num=num+row;
        }
        printf("\n");
        num=row;
    }  
}