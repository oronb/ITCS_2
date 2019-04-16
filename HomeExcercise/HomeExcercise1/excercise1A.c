#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printMultTable(int maxMult);

//Get input from user
void main()
{
    int maxMult=10;
    printMultTable(maxMult);
}

void printMultTable(int maxMult)
{
    int row, col, num, spaces, spacesc=0;
    for( row = 1, num = 1; (row <= maxMult) && (num <= maxMult); row++, num++ )
    {
        for( col = 1; col <= maxMult; col++)
        {
            spaces=col*maxMult;
            spacesc=0;
            while(spaces != 0)
             {
                spaces /= 10;
                spacesc++;
            }
            printf("%*d", spacesc, num);
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