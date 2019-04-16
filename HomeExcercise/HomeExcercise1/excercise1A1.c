#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printMultTable(int MaxMult);

//Get input from user
void main()
{
    int maxMult=10;
    printMultTable(maxMult);
}

void printMultTable(int MaxMult)
{
    int row, col, num, spaces, spacesCount=0;
    for( row = 1, num = 1; (row <= MaxMult) && (num <= MaxMult); row++, num++ )
    {
        for( col = 1; col <= MaxMult; col++)
        {
            spaces=col*MaxMult;
            spacesCount=0;
            while(spaces != 0)
             {
                spaces /= 10;
                spacesCount++;
            }
            printf("%*d ", spacesCount, num);
            num=num+row;
        }
        printf("\n");
        num=row;
    }  
}