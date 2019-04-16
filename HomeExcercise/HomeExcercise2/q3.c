//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Define functions
char ** getStrArrayInput(unsigned int *str_array_size);
char ** setPtrToCharsArray(char **str_array);
void printArray(char **str_array, unsigned int str_array_size);
void freeArray(char **str_array, unsigned int str_array_size);
char ** setPtrToCharsArray(char **str_array);
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array);
void copyPointersArr(char** dest_arr, char** src_arr, int from, int len);
void mergeSortPointersArray(char** arr, int left, int right);
void mergePointersArray(char** arr, int left, int mid, int right);
void checkAlloc(void* val );

void main()
{
    char** str_array; // Array of the strings
    unsigned int str_array_size; // Size of the array of the strings
    char** ptr_to_chars_array; // Array of pointers to chars in strings
    unsigned int res;
    
    str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)
    ptr_to_chars_array = setPtrToCharsArray(str_array); // Set the pointer to chars array
    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array); //Remove the chars from the string array
    
    printArray(str_array, str_array_size - res);
    
    // Free memory
    freeArray(str_array, str_array_size - res);
    free(ptr_to_chars_array);
}

char ** setPtrToCharsArray(char **str_array)
{
    char** res;
    int size, i;
    int str_array_row, str_array_col;
    printf("How many pointers?\n");
    scanf("%d", &size); // Get number of ptrs
    res = (char**)malloc(sizeof(char*)*(size+1)); // Add 1 for NULL at the end
    checkAlloc(res);
    for (i = 0; i < size; i++)
    {
        printf("Enter row\n");
        scanf("%d", &str_array_row);
        printf("Enter column\n");
        scanf("%d", &str_array_col);
        res[i] = str_array[str_array_row] + str_array_col;
    }
    mergeSortPointersArray(res, 0, size-1); // Sort the res array
    res[size] = NULL; // Set the last one to NULL
    return res;
}

unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array){
    int i=0,j,count_empty_strings=0,st_len,left=0,right=str_array_size-1;
    char first_char_left, first_char_right;
    char *str_right;
    char *str_left;
    char *str;
    char *temp_str;
    
    while (ptr_to_chars_array[i] != NULL)
    {
        if (*(ptr_to_chars_array[i]) != '\0')
        {
            j=0;
            while(*(ptr_to_chars_array[i]+j+1) != '\0' )
            {
                *(ptr_to_chars_array[i]+j)=*(ptr_to_chars_array[i]+j+1);
                j++;
            }
            *(ptr_to_chars_array[i]+j) = '\0'; // Ending the string
        }
        i++;
    }
    
    for( i = 0, j = 0; i < str_array_size; i++,j=0)
    {
        str=(*str_array)[i]; //Set the string
        // Print string in strings array
        st_len=strlen(str)+1;
        str = (char*)realloc(str, st_len * sizeof(char)); // Allocate twice the size
        checkAlloc(str);
        
    }
    
    
    //Delete from str_array strings that are empty
    while (left <= right)
    {
        str_left=(*str_array)[left]; // String of the left index in the string array
        first_char_left=*str_left; // First char of the string of the left index in the string array
        str_right=(*str_array)[right]; // String of the right index in the string array
        first_char_right=*str_right; // First char of the string of the right index in the string array
        
        if (first_char_left == '\0' && first_char_right != '\0')
        {
            temp_str=(*str_array)[left]; //?????
            (*str_array)[left]=(*str_array)[right];
            (*str_array)[right]=temp_str;
            right--;
            left++;
            count_empty_strings++;
        }
        else if (first_char_left != '\0')
        {
            left++;
        }
        else if (first_char_right == '\0')
        {
            right--;
            count_empty_strings++;
        }
    }
    
    *str_array = (char**)realloc(*str_array, (str_array_size-count_empty_strings) * sizeof(char*)); // Allocate twice the size
    checkAlloc(*str_array);
    return count_empty_strings;
}

char ** getStrArrayInput(unsigned int *str_array_size){
    
    //Define variables
    int i, j;              // index
    char** str_array;      // string array
    char* str;             // String in the string array
    char c;                // Char of string
    int logic_size=0;      // Logical size of string
    int phys_sz=1;         // Physical size of string
    printf("Enter number of strings\n");
    scanf("%d",str_array_size); // Get number of strings
    getchar();  //clean the buffre from enter
    str_array = (char**)malloc(*str_array_size * sizeof(char*)); // allocate memory for the strings array
    checkAlloc(str_array);
    // Get strings from the user
    printf("Enter strings\n");
    for( i = 0, j = 0; i < *str_array_size; i++, j = 0)
    {
        logic_size = 1;                                // Logical size of the string
        phys_sz = 2;                                   // Physical size of the string
        str = (char*)malloc(phys_sz * sizeof(char));   // Allocate memory for the string
        checkAlloc(str);
        
        //Get string (Untils the user inserts an enter)
        c=getchar();
        while( c != '\n'){
            str[j]=c;                   // Insert char into string
            logic_size++;                // Increase logic_size by one
            if (logic_size == phys_sz) {  // Array is full; logical size reached physical size
                phys_sz *= 2;
                str = (char*)realloc(str, phys_sz * sizeof(char)); // Allocate twice the size
                checkAlloc(str);
            }
            c=getchar();  // Get character
            j++ ;         // Increase index of string by one
        }
        str = (char*)realloc(str, logic_size * sizeof(char)); // Reallocate the string's size according to the logic size
        checkAlloc(str);
        str[logic_size-1] = '\0';
        str_array[i]=str; // Sets the string array to point to the string that was entered by the user
    }
    return str_array; // Returns the string array from the function
}

void printArray(char **str_array, unsigned int str_array_size){
    
    int i,j; //index
    char* str; //string in string array
    
    //Print strings in strings array
    for( i = 0, j = 0; i < str_array_size; i++,j=0)
    {
        str=str_array[i]; //Set the string
        // Print string in strings array
        while(str[j] != '\0'){
            printf("%c", str[j]);
            j++;
        }
        printf("\n");
    }
    
}
void freeArray(char **str_array, unsigned int str_array_size){
    
    int i; //index
    char* str; //string in string array
    
    //Free strings memory in the strings array
    for( i = 0; i < str_array_size; i++)
    {
        str=str_array[i];  //Set the string
        free(str);         //Free the string memory
    }
    
    free(str_array);       //Free the string array memory
}


void copyPointersArr(char** dest_arr, char** src_arr, int from, int len);
void mergeSortPointersArray(char** arr, int left, int right);
void mergePointersArray(char** arr, int left, int mid, int right);

void copyPointersArr(char** dest_arr, char** src_arr, int from, int len)
{
    /*
     Function to copy "len" elemnts from the given "src_arr" sub_array from index "from"
     into the given "dest_arr" array
     */
    int i;
    
    for(i = 0; i < len; i++)
        dest_arr[i] = src_arr[i + from];
}

void mergeSortPointersArray(char** arr, int left, int right)
{
    /*
     Function to sort the given array using the Mergesort algorithm
     */
    int mid;
    
    if(left >= right)
        return; //nothing to sort
    
    mid = (left + right) / 2;
    mergeSortPointersArray(arr, left, mid);        //sort left half of the array
    mergeSortPointersArray(arr, mid + 1, right);   //sort right half of the array
    mergePointersArray(arr, left, mid, right);        //merge the sorted left half with the sorted right half
    
}
void mergePointersArray(char** arr, int left, int mid, int right)
{
    /*
     Function to merge two sub-arrays of the given array arr.
     The first sub-array is between index left and mid.
     The second sub-array is between index mid+1 and right.
     */
    // Set Variables
    int i, j, k, left_len, right_len;
    char **left_arr, **right_arr;
    
    // Copy data to temp arrays left_arr and right_arr
    left_len = mid - left + 1;
    right_len = right - mid;
    left_arr = (char**)malloc(left_len * sizeof(char*)); // Allocate memory for the left temp arrays
    checkAlloc(left_arr);
    right_arr = (char**)malloc(right_len * sizeof(char*)); // Allocate memory for the right temp arrays
    checkAlloc(right_arr);
    copyPointersArr(left_arr, arr, left, left_len);
    copyPointersArr(right_arr, arr, mid + 1, right_len);
    
    // Merge the temp arrays back into arr
    i = 0;        // Initial index of left subarray
    j = 0;        // Initial index of right subarray
    k = left;    // Initial index of merged subarray
    
    while (i < left_len && j < right_len)
    {
        if(left_arr[i] >= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
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

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}
