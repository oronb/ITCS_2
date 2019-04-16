//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct monom{ 
    int coefficient;	//המקדם  
    int power;		// החזקה
} Monom;

//Declare functions
Monom * getPolynom(unsigned int * polynomSize);
void printPolyMul(Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size);
void printPolySum(Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size);
void merge_sort(Monom * polynom, int left, int right);
void merge(Monom * polynom, int left, int mid, int right);
void ar_copy(Monom * dest_ar, Monom * src_ar, int from, int len);
Monom * polynomReduction(Monom * polynom, unsigned int * polynomSize);
Monom * combineTwoPolySum (Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size, unsigned int *combinedPolySize);
Monom * combineTwoPolyMul (Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size, unsigned int *combinedPolySize);
void checkAlloc(void* val);

void main()

{
    Monom *polynom1, *polynom2;             // The input polynoms
    unsigned int polynom1Size,polynom2Size; // The size of each polynom
    
    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size);   // get polynom 1
    
    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size);   // get polynom 2
    
    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");
    
    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");
    
    free(polynom1); // releasing all memory allocations
    free(polynom2);
}

Monom * getPolynom(unsigned int * polynomSize)
{
    int phys_sz=1, logic_sz=0, coefficient, power, flag=1;
    Monom *arr;
    Monom *tempPolynom;
    arr = (Monom*)malloc(phys_sz * sizeof(Monom));
    checkAlloc(arr);
    scanf("%d %d", &coefficient, &power);
    while(flag != 0)
    {
        if(coefficient != 0)
        {
            arr[logic_sz].coefficient = coefficient;
            arr[logic_sz].power = power;
            logic_sz++;
            if (logic_sz == phys_sz) { // array is full; logical size reached physical size
                phys_sz *= 2;
                arr = (Monom *)realloc(arr, phys_sz * sizeof(Monom)); // alloc twice the size
                checkAlloc(arr);
                //printf("Doubled the array size to %d\n", phys_sz);
            }
        }   
        if (getchar()=='\n')
            flag=0;
        else
            scanf("%d %d", &coefficient, &power);
    }
    *polynomSize=logic_sz;
    arr = (Monom *)realloc(arr, *polynomSize * sizeof(Monom)); // Allocate the array size by the physical size
    checkAlloc(arr);
    merge_sort(arr, 0, (*polynomSize)-1); 
    tempPolynom=polynomReduction(arr, polynomSize);

    free(arr);
    arr=tempPolynom;
    return arr;
}

Monom * combineTwoPolySum (Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size, unsigned int *combinedPolySize)
{
    int i=0, j=0, k=0, power, coefficient;
    Monom *combinedPoly;
    Monom *tempCombinedPoly;
    // Define the combined polynom size
    *combinedPolySize=polynom1Size+polynom2Size;     
    combinedPoly = (Monom*)malloc(*combinedPolySize * sizeof(Monom)); // Allocate memory for the left temp arrays  
    checkAlloc(combinedPoly);
	while (i < polynom1Size && j < polynom2Size)
    {
		if (polynom1[i].power == polynom2[j].power) 
        {
            power=polynom1[i].power;
            coefficient=polynom1[i].coefficient+polynom2[j].coefficient;             
            i++;
            j++;
        }    
        else if(polynom1[i].power >= polynom2[j].power)
        {
            power=polynom1[i].power;
            coefficient=polynom1[i].coefficient;
            i++;
        } 
        else if(polynom2[j].power > polynom1[i].power)
        {
            power=polynom2[j].power;
            coefficient=polynom2[j].coefficient;
            j++;
        }
        combinedPoly[k].power=power;
        combinedPoly[k].coefficient=coefficient;
        k++;
    }
    // Copy the remaining elements of left_ar[], if there are any
	while (i < polynom1Size) {
        combinedPoly[k].power=polynom1[i].power;
        combinedPoly[k].coefficient=polynom1[i].coefficient;
        k++;   
        i++;
	}

	// Copy the remaining elements of right_ar[], if there are any
	while (j < polynom2Size) {
		combinedPoly[k].power=polynom2[j].power;
        combinedPoly[k].coefficient=polynom2[j].coefficient;
        k++;
        j++;
	}
    *combinedPolySize=k;
    combinedPoly = (Monom *)realloc(combinedPoly, *combinedPolySize * sizeof(Monom)); // alloc the size of the combioned polynom array by the logic size
    checkAlloc(combinedPoly);
    merge_sort(combinedPoly, 0, *combinedPolySize-1); 
    tempCombinedPoly=polynomReduction(combinedPoly, combinedPolySize);
    free(combinedPoly);
    combinedPoly=tempCombinedPoly;
    return combinedPoly;                     
}
Monom * combineTwoPolyMul (Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size, unsigned int *combinedPolySize)
{
    int i=0, j=0;
    int k=0;  
    Monom *tempCombinedPoly;
    Monom *combinedPoly;
    // Define the combined polynom size
    *combinedPolySize=polynom1Size*polynom2Size;
    combinedPoly = (Monom*)malloc(*combinedPolySize * sizeof(Monom)); // Allocate memory for the left temp arrays 
    checkAlloc(combinedPoly);
	for(i=0; i < polynom1Size; i++) {
	    for(j=0; j < polynom2Size; j++) {
            combinedPoly[k].coefficient=(polynom1[i].coefficient) * (polynom2[j].coefficient);
            combinedPoly[k].power=(polynom1[i].power) + (polynom2[j].power);
            k++;
        }
    }    
    *combinedPolySize=k;
    combinedPoly = (Monom *)realloc(combinedPoly, *combinedPolySize * sizeof(Monom)); // alloc the size of the combioned polynom array by the logic size
    checkAlloc(combinedPoly);
    merge_sort(combinedPoly, 0, *combinedPolySize-1); 
    tempCombinedPoly=polynomReduction(combinedPoly, combinedPolySize);
    free(combinedPoly);
    combinedPoly=tempCombinedPoly;
    return combinedPoly;                     
}
void printPolyMul(Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size)
{   
    int i=0;
    unsigned int combinedPolySize;
    Monom *combinedPoly;
    combinedPoly=combineTwoPolyMul(polynom1, polynom1Size, polynom2, polynom2Size, &combinedPolySize);
    //print the combined polynom
    for(i=0;i<combinedPolySize;i++)
    {
        if (combinedPoly[i].coefficient != 0) 
        {  
            if ((i != 0) && (combinedPoly[i].coefficient > 0))
                printf(" + ");
            else if (combinedPoly[i].coefficient < 0)
                printf(" - ");
            if (combinedPoly[i].power == 0)
                printf("%d",abs(combinedPoly[i].coefficient));
            else if (combinedPoly[i].power == 1 )
                printf("%dx",abs(combinedPoly[i].coefficient));
            else    
                printf("%dx^%d",abs(combinedPoly[i].coefficient),combinedPoly[i].power);

        } 
	}     
    printf("\n");          
    free(combinedPoly);
}

void printPolySum(Monom * polynom1,unsigned int polynom1Size, Monom * polynom2,unsigned int polynom2Size)
{
    int i=0;
    unsigned int combinedPolySize;
    Monom *combinedPoly;
    combinedPoly=combineTwoPolySum(polynom1, polynom1Size, polynom2, polynom2Size, &combinedPolySize);

    //print the combined polynom
    for(i=0;i<combinedPolySize;i++)
    {
        if (combinedPoly[i].coefficient != 0)  
        {  
            if ((i != 0) && (combinedPoly[i].coefficient > 0))
                printf(" + ");
            else if (combinedPoly[i].coefficient < 0)
                printf(" - ");
            if (combinedPoly[i].power == 0)
                printf("%d",abs(combinedPoly[i].coefficient));
            else if (combinedPoly[i].power == 1 )
                printf("%dx",abs(combinedPoly[i].coefficient));
            else    
                printf("%dx^%d",abs(combinedPoly[i].coefficient),combinedPoly[i].power);

        } 
	}     
    printf("\n");          
    free(combinedPoly);           
}


void merge(Monom * polynom, int left, int mid, int right)
/*
	Function to merge two sub-arrays of the given array arr. 
	The first sub-array is between index left and mid.
	The second sub-array is between index mid+1 and right.
*/
{
	int i, j, k, left_len, right_len;
    Monom *right_ar;
    Monom *left_ar;

    // Copy data to temp arrays left_arr and right_arr
    left_len = mid - left + 1;
	right_len = right - mid;
    left_ar = (Monom*)malloc(left_len * sizeof(Monom)); // Allocate memory for the left temp arrays
    checkAlloc(left_ar);
    right_ar = (Monom*)malloc(right_len * sizeof(Monom)); // Allocate memory for the right temp arrays
    checkAlloc(right_ar);
	ar_copy(left_ar, polynom, left, left_len);
	ar_copy(right_ar, polynom, mid + 1, right_len);

	// Merge the temp arrays back into arr
	i = 0;		// Initial index of left subarray
	j = 0;		// Initial index of right subarray
	k = left;	// Initial index of merged subarray

	while (i < left_len && j < right_len) {
		if (left_ar[i].power >= right_ar[j].power) {
			polynom[k] = left_ar[i];
			i++;
		}
		else {
			polynom[k] = right_ar[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of left_ar[], if there are any
	while (i < left_len) {
		polynom[k] = left_ar[i];
		i++;
		k++;
	}

	// Copy the remaining elements of right_ar[], if there are any
	while (j < right_len) {
		polynom[k] = right_ar[j];
		j++;
		k++;
	}
    free(left_ar);
    free(right_ar);
}

void merge_sort(Monom * polynom, int left, int right)
/*
	Function to sort the given array using the Mergesort algorithm, which is a divide and conquer 
	algorithm developed by John von Neumann in 1945.
	Receives: the array, the range to be sorted between the given left index and the right index.
	Returns: the sorted array.
*/
{
    //printf("merge_sort: left: %d right: %d\n", left, right);
	int mid;
	if (left >= right)
		return;		// nothing to sort
	mid = (left + right) / 2;
	merge_sort(polynom, left, mid);		//sort left half of array	
    //printf("merge_sort of left: left: %d right: %d\n", left, right);
	merge_sort(polynom, mid + 1, right);	//sort right half of array
    //printf("merge_sortof right: left: %d right: %d\n", left, right);

	merge(polynom, left, mid, right);		//merge the sorted left half with the sorted right half
}

void ar_copy(Monom * dest_ar, Monom * src_ar, int from, int len)
/*
	Function to copy "len" elements from the given "src_ar" sub-array from index "from"
	into the given "dest_ar" array.
*/
{
	int i;

	for (i = 0; i < len; i++)
		dest_ar[i] = src_ar[i + from];
}

Monom * polynomReduction(Monom * polynom, unsigned int * polynomSize)
{
    Monom *tempPolinom;
    int i, j=0, coefficient=0, power=0;
    tempPolinom = (Monom*)malloc(*polynomSize * sizeof(Monom)); // Allocate memory for the left temp arrays
    checkAlloc(tempPolinom);
    power=polynom[0].power;
    coefficient=polynom[0].coefficient;
    tempPolinom[0].power=polynom[0].power;
    tempPolinom[0].coefficient=polynom[0].coefficient;
    if(*polynomSize > 1)
    {
        for(i = 1;i < *polynomSize; i++)
        {
            if (polynom[i].power == power)
            {   
                coefficient=coefficient+polynom[i].coefficient;
            }
            else
            {
                power=polynom[i].power;
                coefficient=polynom[i].coefficient;
                j++;
            }  
            tempPolinom[j].coefficient=coefficient;
            tempPolinom[j].power=power;                 
        }
        *polynomSize=j+1;
        tempPolinom = (Monom *)realloc(tempPolinom, *polynomSize * sizeof(Monom)); // alloc twice the size
        checkAlloc(tempPolinom);
    }
    return tempPolinom;
}

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}