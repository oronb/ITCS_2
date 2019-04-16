#include <stdio.h>
#include <stdlib.h>

int main() {
	char *str;

	str = (char *)malloc(20);

	strcpy(str, "your first name");
	printf("Str = %s   \t\t\t Str address = %p\n", str, (void *)str);

	/* Reallocating memory */
	str = (char *)realloc(str, 500);
	strcat(str, " and your last name");
	printf("Str = %s   \t Str address = %p\n", str, (void *)str);

	free(str);

	// Reallocating double the size of the memory each time more memory is needed

	int num, i;
	int *arr;			// array; starts with physical size of 1, and grows
	int phys_sz = 1;	// physical size: number elements actually allocated to array
	int logic_sz = 0;	// logical size: number of elements in the array
	
	arr = (int *)malloc(phys_sz * sizeof(int));		// allocate memory for 1 element
	printf("Please enter a series of numbers; enter -1 to stop the series: ");

	while (1) {
		scanf_s("%d", &num);
		if (num == -1)
			break;			// Reached the end of the series of numbers

		printf("Read number %d\n", num);
		arr[logic_sz++] = num;	// Store number read, and inc logical size

		if (logic_sz == phys_sz) {	// array is full; logical size reached physical size
			phys_sz *= 2;
			arr = (int *)realloc(arr, phys_sz * sizeof(int)); //alloc mem twice the size
			printf("Doubled the array size to %d\n", phys_sz);
		}
	}

	printf("The array has %d elements (phys_sz = %d):\n", logic_sz, phys_sz);
	for (i = 0; i < logic_sz; i++)
		printf("%d ", arr[i]);
	printf("\n");

	free(arr);

	system("pause");
	return(0);
}