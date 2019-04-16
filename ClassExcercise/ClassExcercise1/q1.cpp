#include <iostream>
using namespace std;

//Declare constants
const int N = 7;
const int M = 5;

//Declare function

int main()
{
	//Declare Variables
	//int mat[5][2] = { {1,2}, {3,4}, {5,6} };
	int mat[N][M];
	int i,j;
	int num = 1;

	for (j=0; j< M; j++) //cols
	{
		if (j % 2 == 0) //even col
		{
			for(i = 0; i < N; i++)
			{
				mat[i][j] == num++;
			}
		}
		else
		{
			for (i = N - 1; i >= 0; i--)//rows
			{
				mat[i][j] = num++;
			}
		}

	}
}

//Implement functions