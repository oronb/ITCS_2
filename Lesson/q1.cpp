#include <iostream>
using namespace std;

int chessBoard[8][8];
int main()
{
//calculate the diagonal only
    int sum=0, i=0;
    for(i=0;i<8;i++)
    	sum +=  chessBoard[i][i];
//calculate the opposite diagonal only
    for(i=0;i<8;i++)
	    sum += chessBoard[i][7-i];
}       