#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;

	str = (char *)malloc(20);
	
	strcpy(str, "your name");
	printf("Str = %s,  Str address = %p\n\n", str, (void *)str);
	
	free(str);

	int size, *arr, i;

	printf("Please enter the number of elements of the array: ");
	scanf_s("%d", &size);
	arr = (int*)malloc(size * sizeof(int));

	if (!arr) {
		puts("Malloc error");
		system("pause");
		return -1;
	}

	for (i = 0; i < size; i++)		// Init array
		arr[i] = i;					// Access array elements by array index

	for (i = 0; i < size; i++)		// Print array
		printf("%d ", *(arr + i));	// Access array elements by computing addresses
	printf("\n");

	free(arr);

	// Dynamic allocation of a matrix

	int rows = 3;	// Given number of rows
	int cols = 4;	// Given number of columns
	int *mat;		// Pointer to the matrix
	int r, c;		// r is the row index, and c is the column index
	int count = 0;	// cell number

	mat = (int *)malloc(rows * cols * sizeof(int));		// skip test for NULL result

	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			*(mat + r * cols + c) = count++;	// Access mat[r][c]

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++)
			printf("%d\t", *(mat + r * cols + c));
		printf("\n");
	}

	free(mat);

	// Dynamic allocation of struct

	typedef struct employee { 
		long emp_id;  
		char rank;  
		int room;  
		double salary; 
	} EMPLOYEE;

	EMPLOYEE *emp;

	emp = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	
	(*emp).emp_id = 57496L;			// Using (*emp). to access the emp_id field
	(*emp).rank = 'a';
	emp->room = 337;				// Note the use of -> instead of (*emp).
	emp->salary = 70000.0;
		
	printf("emp id: %ld,", (*emp).emp_id);		// Note the "%ld" to print long
	printf(" rank: %c,", emp->rank);			// Note the use of -> instead of (*emp).
	printf(" room: %d,", emp->room);
	printf(" salary: %.2lf\n", emp->salary);	// Note the "%lf" to print double

	free(emp);

	// Dynamic allocation of an array of struct

	EMPLOYEE *emps[10];
	
	// Allocate memory for first 5 of the 10 entries of array emps
	for (i = 0; i < 5; i++)
		emps[i] = (EMPLOYEE *)malloc(sizeof(EMPLOYEE));

	// Mark the last 5 entries of array emps as empty, by setting the pointer to NULL
	for (i = 5; i < 10; i++)
		emps[i] = NULL;

	emps[0]->emp_id = 57496L;
	emps[0]->rank = 'a';
	emps[0]->room = 337;
	emps[0]->salary = 70000.0;

	puts("Array of Employees: first employee");
	printf("emp id: %ld,", emps[0]->emp_id);
	printf(" rank: %c,", emps[0]->rank);
	printf(" room: %d,", emps[0]->room);
	printf(" salary: %.2lf\n", emps[0]->salary);

	// Free  memory for all structs; for NULL entries, free does not take any action.
	for (i = 0; i < 10; i++)
		free(emps[i]);

	system("pause");
	return 0;
}