#include <iostream>
using namespace std;

//Declare constants
#define ROWS 8
#define COLS 6
//Declare function
void printMat(int mat[][COLS], int rows, int cols);
int checkDiamond(int mat[][COLS], int rows, int cols);


int main()
{
	//Declare Variables
	int mat[ROWS][COLS], rows=8, cols=6;
	void printMat(int mat[][COLS], int rows,int cols);

}

//Implement functions

void printMat(int mat[][COLS], int rows, int cols)
{
	int i, j;

	for (i = 0; i < rows; i++) //lines
		for (j = 0; j < cols; j++) //cols
			cout << mat[i][j] << "\t";
		cout << endl;	
}

int checkDiamond(int mat[][COLS], int rows, int cols)
{
	int i,l,r;
	r=cols/2;
	if(rows % 2 == 0)
	{	
		l=(cols/2)-1;
	}
	else
	{
		l=cols/2;
	}
	for(i = 0; i < rows/2; i++)
	{
		if(mat[i][l] != 0 || mat[i][r] != 0)
			return(0);
		else
		{
			l--;
			r++;
		}			
	}
	if(rows % 2 == 0)
	{
		l++;
		r--;
	}
	for(i=rows/2;i<rows;i++)
	{
		if(mat[i][l] != 0 || mat[i][r] != 0)
			return(1);
		else
		{
			l++;
			r--;
		}			
	}	
	
}

