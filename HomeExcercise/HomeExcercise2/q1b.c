//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//Define functions
void pointerSort(int* arr, unsigned int size, int ascend_flag, int*** pointers);
void printPointers(int** pointers, unsigned int size);
void setIntPointersArray(int* source, int size, int** dest);
void copyPointersArr(int** dest_arr, int** src_arr, int from, int len);
void mergeSortPointersArray(int** arr, int left, int right, int ascend_flag);
void mergePointersArray(int** arr, int left, int mid, int right, int ascend_flag);
void freeArrayMemory(int** arr, int size);
void checkAlloc(void* val );

//Define constants
#define SIZE 100


void main()
{
	unsigned int size, i;
	int arr[SIZE];
	int ** pointers;
	int ascend_flag;

	printf("Please enter the number of items:\n");
	scanf("%u", &size);

	for (i = 0; i<size; i++)
		scanf("%d", &arr[i]);

	scanf("%d", &ascend_flag);
	pointerSort(arr, size, ascend_flag, &pointers);
	printf("The sorted array:\n"); //Print the sorted array
	printPointers(pointers, size);
	free(pointers);
}

void printPointers(int** pointers, unsigned int size)
{
    int i;
    for(i = 0; i < size; i++)
        printf("%d ", **(pointers + i));
}

void setIntPointersArray(int* source, int size, int** dest)
{
    int i;
    for( i = 0; i < size; i++)
    {
        dest[i] = source + i;
    }
} 

void copyPointersArr(int** dest_arr, int** src_arr, int from, int len)
{
/* 
    Function to copy "len" elemnts from the given "src_arr" sub_array from index "from"
    into the given "dest_arr" array
*/
    int i;

    for(i = 0; i < len; i++)
        dest_arr[i] = src_arr[i + from];
}

void mergeSortPointersArray(int** arr, int left, int right, int ascend_flag)
{
/*
	Function to sort the given array using the Mergesort algorithm
*/
    int mid;

    if(left >= right)
        return; //nothing to sort

    mid = (left + right) / 2;
    mergeSortPointersArray(arr, left, mid, ascend_flag);        //sort left half of the array
    mergeSortPointersArray(arr, mid + 1, right, ascend_flag);   //sort right half of the array 
    mergePointersArray(arr, left, mid, right, ascend_flag);		//merge the sorted left half with the sorted right half
 
}
void mergePointersArray(int** arr, int left, int mid, int right, int ascend_flag)
{
/*
    Function to merge two sub-arrays of the given array arr.
    The first sub-array is between index left and mid.
    The second sub-array is between index mid+1 and right.
*/ 
    // Set Variables
    int i, j, k, left_len, right_len;
    int **left_arr, **right_arr;

    // Copy data to temp arrays left_arr and right_arr
    left_len = mid - left + 1;
	right_len = right - mid;
    left_arr = (int**)malloc(left_len * sizeof(int*)); // Allocate memory for the left temp arrays
    checkAlloc(left_arr);
    right_arr = (int**)malloc(right_len * sizeof(int*)); // Allocate memory for the right temp arrays
    checkAlloc(right_arr);
	copyPointersArr(left_arr, arr, left, left_len);
	copyPointersArr(right_arr, arr, mid + 1, right_len);
    
    // Merge the temp arrays back into arr
	i = 0;		// Initial index of left subarray
	j = 0;		// Initial index of right subarray
	k = left;	// Initial index of merged subarray

        while (i < left_len && j < right_len)
        {
            if(ascend_flag == 1)
            {
                if(*(left_arr[i]) <= *(right_arr[j]))
                {
                    arr[k] = left_arr[i];
                    i++;
                }
                else
                {
                    arr[k] = right_arr[j];
					j++;
                }
            }
            else if(ascend_flag == 0)
            {
                if(*(left_arr[i]) >= *(right_arr[j]))
                {
                    arr[k] = left_arr[i];
                    i++;
                }
                else
                {
                    arr[k] = right_arr[j];
					j++;
                }                
            }
            k++;
        }

    // Copy the remaining elemnts of left_arr, if there are any
    while(i < left_len)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    // Copy the remaining elemnts of right_arr, if there are any
    while(i < right_len)
    {
        arr[k] =right_arr[i];
        i++;
        k++;
    }    

    //Free the temp arrays memory
    free(left_arr); // Free the memory of the left temp array
    free(right_arr); // Free the memory of the right temp array
}    

void pointerSort(int* arr, unsigned int size, int ascend_flag, int*** pointers)
{
/*
    The function creates a pointers array.
    Than, the function checks if the ascend_flag value is 0 or 1.
    If the value is 1, the function sorts the pointers array to point to the array that was sent to the function from minimum to maximum 
    If the value is 0, the function sorts the pointers array to point to the array that was sent to the function from maximum to minimum 
*/

    *pointers = (int**)malloc(size * sizeof(int*));  //Allocate memory for the pointers array
    checkAlloc(*pointers);
    setIntPointersArray(arr, size, *pointers);       //Set the pointers in pointer array to points to the cells in the array

    //Check whether the value of ascend_flag is 1 or 0
    if (ascend_flag == 1)
    {
        mergeSortPointersArray(*pointers, 0, size - 1, ascend_flag);
    }
    else if (ascend_flag == 0)
    {
        mergeSortPointersArray(*pointers, 0, size - 1, ascend_flag);
    } 
}

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}
