/*
Name: Lital Doron
I.D : 209633429
Date: 30.3.19
//This program get a pointer to an adress which point to strings array, get a set of pointers to the characters in the strings,
deletes the characters that the pointers point on, updates the strings, and updates the array of strings if there are some empty strings
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** getStrArrayInput(unsigned int *str_array_size);
char** setPtrToCharsArray(char** str_array);
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char ** ptr_to_chars_array);
void printArray(char ** str_array, unsigned int size);
void freeArray(char** str_array, unsigned int str_array_size);

void mergeDown(char **arr, char **l, int sizel, char **r, int sizer);
void mergeSort(char **arr, int size);
void swap(char **first, char **last);


int main()
{
	char** str_array;
	unsigned int str_array_size;
	char** ptr_to_chars_array;
	unsigned int res;

	str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)

	ptr_to_chars_array = setPtrToCharsArray(str_array); //������� ����� 

	res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array); // ��� ����� int ? 

	printArray(str_array, str_array_size - res);

	// Free memory
	freeArray(str_array, str_array_size - res);
	free(ptr_to_chars_array);
}

char ** getStrArrayInput(unsigned int *str_array_size) // function to get the strings and put its first adress into the arr of strings
{
	printf("please enter the numbers of strings\n");
	scanf("%d", str_array_size); 
	getchar();// for the first '\n'
	unsigned int i;
	char ch;
	char *str;

	char **arrOfStr;
	arrOfStr = (char**)malloc(sizeof(char*)*(*str_array_size));
	if (!arrOfStr)
	{
		printf("memmory alocation is failed\n");
		exit(1);
	}
	for (i = 0; i < *str_array_size; i++) // get strings 
	{
		printf("Enter string");
		unsigned int logSize = 1, phySize = 2;
		// get char function
		str = (char*)malloc(sizeof(char)* phySize);
		if (!str)
		{
			printf("memmory alocation is failed\n");
			exit(1);
		}
		ch = getchar();
		while (ch != '\n')
		{
			if (logSize == phySize)
			{
				phySize *= 2;
				str = (char*)realloc(str, sizeof(char)*phySize);
			}
			str[logSize-1] = ch;
			logSize++;
			ch = getchar();
		}
		str = (char*)realloc(str, sizeof(char)*logSize);
		str[logSize-1] = '\0'; // put in the last index the '\0;

		arrOfStr[i] = str;
	}

	return arrOfStr;
}

char** setPtrToCharsArray(char** str_array)
{
	char** res;
	int size, i;
	int str_array_row, str_array_col;
	printf("Enter number of ptr\n");
	scanf("%d", &size); // Get number of ptrs
	getchar();
	res = (char**)malloc(sizeof(char*)*(size + 1)); // Add 1 for NULL at the end

	for (i = 0; i < size; i++)
	{
		printf("enter row\n");
		scanf("%d", &str_array_row);
		printf("Enter column\n");
		scanf("%d", &str_array_col);
		res[i] = str_array[str_array_row] + str_array_col;
	}

	res[size] = NULL; // Set the last one to NULL
	mergeSort(res, size-1); // (-1) for the null . sorted the adress from the highest one to the low one
	return res;
}


unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char ** ptr_to_chars_array)
{
	int i; // index for ptr array
	int j; // index for stings

	int length = 0; // define for the length of strings
	unsigned int res = 0;

	
	for (i = 0; *(ptr_to_chars_array + i) != NULL; i++) // delete by the pointers array the charcter in the string and than arrange the new string
	{
		for (j = 0; *(*(ptr_to_chars_array + i) + j) != '\0'; j++)
		{
			*(*(ptr_to_chars_array + i) + j) = *(*(ptr_to_chars_array + i) + j + 1);
		}
	}


	for (i = 0; i < str_array_size; i++) // realloc the string after delete the charcter ptr point on
	{
		char *old_string = *((*str_array) + i); // create a new string for readable code
		length = strlen(old_string); // check length of string
		char *new_string = (char*)malloc(sizeof(char)* (length + 1));
		if (!new_string)
		{
			printf("memmory alocation is failed\n");
			exit(1);
		}

		strcpy(new_string, old_string); // copy the arrange string to the new one
		free(old_string);
		
		*((*str_array) + i) = new_string; // put into the original strings array the new arrange string with the update length 
	}

	unsigned int first = 0;
	unsigned int last= str_array_size -1;

		while (first <= last) // check if there an empty string and delete it from the str_array
		{
			if (*(*((*str_array) + first)) == '\0' && *(*((*str_array) + last)) != '\0') // check the first charcter in the first string is '\0' and the first charctr in the last string is not '\0'
			{
				swap(*(str_array) + first, *(str_array) + last); // swap aderss strings
				first++; // advance them adress next first string
				last--; // back the adress  last string
				res++; // count how many strings were empty
			}
			else if (*(*((*str_array) + first)) != '\0')
			{
				first++;
			}
			else
			{
				last--;
				res++;
			}
		} // while
		str_array = (char***)realloc(str_array, sizeof(char**)*(str_array_size - res)); // update the new length of array of str ????
		return res;
}

void swap(char **first, char **last) // function swap
{
	char* temp = *first;
	*first=*last;
	*last= temp;
}

void printArray(char ** str_array, unsigned int size) // function print
{
	int i,j;
	for (i = 0; i < size ; i++) // run over array of str
	{
		for(j=0; *(*(str_array+i)+j)!= '\0'; j++) // run over charcter of each str
		{
			printf("%c", *(*(str_array + i) + j));
		}
		printf("\n"); /// ???
	}
}

void freeArray(char** str_array, unsigned int str_array_size) // function free memory
{
	int i;
	for (i = 0; i <str_array_size; i++) // free strings memory
	{
		free( *(str_array+i) ); // ???
	}
	free(str_array); // free array of strings
}

void mergeDown(char **arr, char **l, int sizel, char **r, int sizer) // sorted the pointers array from the highest number adress to the low one 
{
	int i = 0;
	int j = 0;
	while (i < sizel && j < sizer)
	{
		if (l[i] > r[j])
		{
			arr[i + j] = l[i];
			i++;
		}
		else
		{
			arr[i + j] = r[j];
			j++;
		}
	}
	while (i < sizel)
	{
		arr[i + j] = l[i];
		i++;
	}
	while (j < sizer)
	{
		arr[i + j] = r[j];
		j++;
	}
}

void mergeSort(char **arr, int size)
{
	int i;
	char **ptr;
	if (size <= 1) // there is no resun to sort the pointer array
		return;

	mergeSort(arr, (size / 2)); // sort for the left side of the pointer array
	mergeSort(arr + size / 2, size - (size / 2)); // sort for the right side of the pointer array
	ptr = (char**)malloc(size * sizeof(char *)); // create new pointer array for dividing the original pointer array for two left and right new pointers array
	if (!ptr)
	{
		printf("memmory alocation is failed\n");
		exit(1);
	}

	mergeDown(ptr, arr, size / 2, arr + (size / 2), size - (size / 2));

	for (i = 0; i < size; i++) // put into the original pointers array the sorted new array
	{
		arr[i] = ptr[i];
	}
	free(ptr); // free memory
}

