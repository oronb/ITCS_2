// mergsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

const int MAX_ELEM = 100;

void ar_copy(int dest_ar[], int src_ar[], int from, int len)
/*
	Function to copy "len" elements from the given "src_ar" sub-array from index "from"
	into the given "dest_ar" array.
*/
{
	int i;

	for (i = 0; i < len; i++)
		dest_ar[i] = src_ar[i + from];
}

void prn_array(int array[], int size)
/*
	Funtion to print the given array.
*/
{
	const int ELEM_LN = 20;
	int i;

	for (i = 0; i < size; i++) {
		cout << array[i] << " ";
		if (((i + 1) % ELEM_LN) == 0)
			cout << endl;
	}

	cout << endl;
}

void merge(int arr[], int left, int mid, int right)
/*
	Function to merge two sub-arrays of the given array arr. 
	The first sub-array is between index left and mid.
	The second sub-array is between index mid+1 and right.
*/
{
	int i, j, k, left_len, right_len;
	int left_ar[MAX_ELEM], right_ar[MAX_ELEM];	//temp arrays

	// Copy data to temp arrays left_ar[] and right_ar[]
	left_len = mid - left + 1;
	right_len = right - mid;
	ar_copy(left_ar, arr, left, left_len);
	ar_copy(right_ar, arr, mid + 1, right_len);

	// Merge the temp arrays back into arr
	i = 0;		// Initial index of left subarray
	j = 0;		// Initial index of right subarray
	k = left;	// Initial index of merged subarray

	while (i < left_len && j < right_len) {
		if (left_ar[i] <= right_ar[j]) {
			arr[k] = left_ar[i];
			i++;
		}
		else {
			arr[k] = right_ar[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of left_ar[], if there are any
	while (i < left_len) {
		arr[k] = left_ar[i];
		i++;
		k++;
	}

	// Copy the remaining elements of right_ar[], if there are any
	while (j < right_len) {
		arr[k] = right_ar[j];
		j++;
		k++;
	}
}

void merge_sort(int arr[], int left, int right)
/*
	Function to sort the given array using the Mergesort algorithm, which is a divide and conquer 
	algorithm developed by John von Neumann in 1945.
	Receives: the array, the range to be sorted between the given left index and the right index.
	Returns: the sorted array.
*/
{
	int mid;

	if (left >= right)
		return;		// nothing to sort

	mid = (left + right) / 2;
	merge_sort(arr, left, mid);			//sort left half of array
	merge_sort(arr, mid + 1, right);	//sort right half of array

	merge(arr, left, mid, right);		//merge the sorted left half with the sorted right half
}

int main()
{
	int i, elems, array[MAX_ELEM];

	while (true) {
		cout << "Please enter number of elements: ";
		cin >> elems;
		cout << "Please enter " << elems << " integers in any order:\n";

		for (i = 0; i < elems; i++)
			cin >> array[i];

		cout << "Sorting array:\n";
		prn_array(array, elems);

		merge_sort(array, 0, elems - 1);

		cout << "Sorted array:\n";
		prn_array(array, elems);
	}

	system("pause");
	return 0;
}

