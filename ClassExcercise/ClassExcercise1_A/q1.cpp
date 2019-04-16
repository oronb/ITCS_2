#include <iostream>
using namespace std;

//Declare constants
#define ROWS 8
#define COLS 6
//Declare function
void updateMat(int mat[][COLS], int rows, int cols);
void printMat(int mat[][COLS], int rows, int cols);

int main()
{
	//Declare Variables
	int mat[ROWS][COLS], rows=8, cols=6;
	void updateMat(int mat[][COLS],int rows,int cols);
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

void updateMat(int mat[][COLS], int rows, int cols)
{
	int i,j,val=1;
	for(i=0;i<cols;i++)
	{
		if(i % 2 == 0)
		{
			for(j=0;j<rows;j++)
			{
				mat[i][j]=val++;
			}
		}
		else 
		{
			for(j=rows-1;j>=0;j--)
			{
				mat[i][j]=val++;
			}
		}
	}
}