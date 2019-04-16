#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
void doReconstructCommand(char** strings, int size, int count, char* str);
void printStrings(char** strings, int size, int lineNum);
void addToStrings(char** strings, int size, int count, char* str);
void swap(char** pStr1, char** pStr2);
void freeStrings(char** strings, int size);


int main()
{
	char** strings;
	char* str;
	int size, count = 0;

	printf("Please enter the history storage size:\n");
	scanf("%d", &size);
	getchar();
	strings = (char**)malloc(sizeof(char*)*size);
	printf("The storage size was set to %d\n", size);
	str = getString();

	while (strcmp(str, "!quit") != 0)
	{
		if (str[0] == '!')
		{
			doReconstructCommand(strings, size, count, str);
		}
		else
		{
			addToStrings(strings, size, count, str);
			count++;
		}

		
		free(str);
		str = getString();
	}

	printf("Thanks for using the history application, bye bye\n");
	freeStrings(strings, size);
}

char* getString()
{
    char c;
    char* str; // the char array. Starts with physical size of 1, and grows
    int count, i=0;
    int phys_sz = 1; // physical size: number of elemnts actually allocated to array
    int logic_sz = 0; //logical size: number of elemnts in the array
    str = (char*)malloc(phys_sz * sizeof(char)); // allocate memory for 1 elemnt
    scanf("Please enter a string");
    while ( c != '\n') // Run until the user enters an enter
    {
        c = getchar();
        str[logic_sz++] = c;
        if (logic_sz == phys_sz) //array is full
        {

        }
        str = (char*)realloc(str,sizeof(char) * (i + 1));
        scanf("Please enter a string");
    } 
    	//strings = (char**)malloc(sizeof(char*)*size);

}