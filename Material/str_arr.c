#include <stdio.h>

#define	MAX_ROWS	4
#define MAX_STR_LEN	120

char *get_line()
/*
To read a line, allocate memory for a string to hold the line, copy the line into that
string, and return a pointer to that string, or NULL in case of failure.
*/
{
	char line[MAX_STR_LEN];
	char *str;

	printf("> ");				// Prompt the user to enter text
	if (gets(line) == NULL)		// Read the line
		return NULL;

	str = (char *)malloc(strlen(line) + 1);
	if (str != NULL)
		strcpy(str, line);

	return str;
}

void swap_str(char **str1, char **str2)
/*
To swap the value of the two given pointers so that the first pointer points at the 
string pointed at by the second pointer, and the second pointer points at the string
pointed at by the first pointer.
Receives: a pointer to the first string in str1 and a pointer to the second string in str2
Returns: str1 points at the string previously pointed at by str2 and str2 points at the
	     string pointed at by str1.
*/
{
	char *tmp_str;

	tmp_str = *str1;	// tmp_str points at the string pointed at by str1
	*str1 = *str2;		// str1 changes value to point at the string pointed at by str2
	*str2 = tmp_str;	// str2 changes value to point at the string pointed at by str1
}

void short_fst(char *page[], int page_sz)
/*
Have the shortest string in the given page as the first string in page.
*/
{
	int i;
	int min_i = 0;		// min is set to be the first string
	char *tmp;

	// scan the array and find the index with the shortest string
	for (i = 1; i < page_sz; i++)
		if (strlen(page[i]) < strlen(page[min_i]))
			min_i = i;

	/* 
	swap the pointers of the first index with the pointer of the min index
	tmp = page[0];
	page[0] = page[min_i];
	page[min_i] = tmp;
	*/
	swap_str(&(page[0]), &(page[min_i]));
}

void fill_page(char *page[], int page_sz)
{
	int i;

	for (i = 0; i < page_sz; i++)
		page[i] = get_line();
}

void prn_page(char *page[], int page_sz)
{
	int i;

	for (i = 0; i < page_sz; i++)
		printf("%s\n", page[i]);
}

void free_page(char *page[], int page_sz)
{
	int i;

	for (i = 0; i < page_sz; i++)
		free(page[i]);
}

int main()
{
	char *page[MAX_ROWS];	// Array of pointers to a string
	char *ptr;
	char ch;
	
	fill_page(page, MAX_ROWS);
	prn_page(page, MAX_ROWS);

	ptr = page[0];		// ptr points at the first string
	printf("First string = %s \t\t\t", ptr);
	ptr = *page;		// ptr points again at the first string
	printf("First string = %s\n", ptr);
	ch = *ptr;			// ch = the first char of the first string
	printf("First char of the first string = %c \t", ch);
	ch = *(*page);		// ch = the first char of the first string
	printf("First char of the first string = %c\n", ch);

	ptr = page[MAX_ROWS - 1];		// ptr points at the last string
	printf("Last string = %s \t\t\t", ptr);
	ptr = *(page + MAX_ROWS - 1);	// ptr points again at the last string
	printf("Last string = %s\n", ptr);
	ch = *(ptr + strlen(ptr) - 1);	// ch = the last char of the last string
	printf("Last char of the last string = %c\n", ch);

	short_fst(page, MAX_ROWS);
	prn_page(page, MAX_ROWS);

	free_page(page, MAX_ROWS);

	system("pause");
	return 0;
}