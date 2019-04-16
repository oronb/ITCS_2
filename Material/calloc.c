#include <stdio.h>
#include <stdlib.h>

void prn_arr(int arr[], int size)
{
	int i;
	
	for (i = 0; i < size; i++)
		printf("%d\t", arr[i]);
	printf("\n");
}

int main() {
	int stat_arr[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	int arr_sz = sizeof(stat_arr) / sizeof(stat_arr[0]);
	int *dyn_arr;		// Dynamic array
	int *pi, i;

	dyn_arr = (int *)calloc(arr_sz, sizeof(int));
	if (dyn_arr == NULL) {
		printf("Error in allocating memory\n");
		return -1;
	}
		
	prn_arr(dyn_arr, arr_sz);	// Print the dynamic array before init

	// Copy the static array stat_arr into the dynamic array dyn_arr
	pi = dyn_arr;
	for (i = 0; i < arr_sz; i++)
		*(pi++) = stat_arr[i];	// access dyn_arr by pointer computation

	prn_arr(dyn_arr, arr_sz);	// Print the dynamic array after init
	
	free(dyn_arr);

	system("pause");
	return(0);
}