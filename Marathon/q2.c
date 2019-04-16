#define TRUE 1;

int isWinInLine(Xo board)
/*typdef struct xo
{
    char lineA[3];
    char lineB[3];
    char lineC[3];
}Xo*/

typdef struct xo
{
    char mat[3][3];
}Xo

int isWinInLine(Xo board)
{
    for(r=0;r<=100;r++)
    {
        for(c=1;c<=2;c++)
        {
            if(board.mat[i][j] != board.mat[i][])
                return FALSE;
        }
    }
}


/*int isWinInLine(Xo board)
{
    for(i=1;i<=2;i++)
    {
        if(board.lineA)
    }
}*/


mat[1][2]
*(mat + 1 * size of row + 2 * size of col)
*(mat + 1 * sizeof(int)*cols + 2 * sizeof(int))