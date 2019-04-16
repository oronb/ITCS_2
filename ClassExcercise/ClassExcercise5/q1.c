#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode{
	int data;
	struct listNode* next;
}ListNode;

typedef struct list {
	ListNode* head;
	ListNode* tail;
}List;

List buildList();
int* createEvenArr(List lst, int* pSize);
void printArr(int* arr, int size);

List buildList1();
List buildList2();
void mergeListsAlternately(List lst1, List lst2);
void printList(List lst);

List makeEmptyList();
int isEmptyList(List lst);
ListNode* createNode(int data, ListNode* next);
void insertNodeToTail(List* lst, ListNode* newTail);
void freeList(List lst);

void main()
{
	int *arr, size;
	List lst = buildList();

	arr = createEvenArr(lst, &size);

	printArr(arr, size);
	free(arr);
	freeList(lst);

	////////////////////////////////////////////////////

	List lst1 = buildList1();
	List lst2 = buildList2();

	mergeListsAlternately(lst1, lst2);

	printList(lst1);
	freeList(lst1);
}

List buildList()
{
	List lst = makeEmptyList();

	insertNodeToTail(&lst, createNode(12, NULL));
	insertNodeToTail(&lst, createNode(-7, NULL));
	insertNodeToTail(&lst, createNode(9, NULL));
	insertNodeToTail(&lst, createNode(4, NULL));
	insertNodeToTail(&lst, createNode(-10, NULL));
	insertNodeToTail(&lst, createNode(13, NULL));
	insertNodeToTail(&lst, createNode(22, NULL));

	return lst;
}

int* createEvenArr(List lst, int* pSize)
{
    ListNode *nodep = lst.head;
    int *arr, phys_sz=1, logic_sz =0;
    arr = (int*)malloc(phys_sz * sizeof(int));

    while(nodep != NULL)
    {
        if (nodep->data % 2 == 0)
            arr[logic_sz++]=nodep->data;
        if (logic_sz == phys_sz) { // array is full; logical size reached physical size
            phys_sz *= 2;
            arr = (int *)realloc(arr, phys_sz * sizeof(int)); // alloc twice the size
        }    
        nodep = nodep -> next;
    }
    //Set pSize
    *pSize=logic_sz;
    return arr;
}

void printArr(int* arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
        printf("%d \t", arr[i]);
}


List buildList1()
{
	List lst = makeEmptyList();

	insertNodeToTail(&lst, createNode(1, NULL));
	insertNodeToTail(&lst, createNode(3, NULL));
	insertNodeToTail(&lst, createNode(5, NULL));

	return lst;
}

List buildList2()
{
	List lst = makeEmptyList();

	insertNodeToTail(&lst, createNode(2, NULL));
	insertNodeToTail(&lst, createNode(4, NULL));
	insertNodeToTail(&lst, createNode(6, NULL));
	insertNodeToTail(&lst, createNode(7, NULL));

	return lst;
}

void mergeListsAlternately(List lst1, List lst2)
{
    ListNode *nodep1 = lst1.head;
    ListNode *nodep2 = lst2.head;

    nodep1 -> next = nodep2;
    nodep1 = nodep1 -> next;
    nodep2 -> next = nodep1;

}

void printList(List lst)
{
	ListNode *curr;

	curr = lst.head;

	while (curr != NULL)
	{
		printf("%d ", curr->data);
		curr = curr->next;
	}

	printf("\n");
}



List makeEmptyList()
{
	List result;

	result.head = result.tail = NULL;
	return result;
}

int isEmpty(List lst) 
{
	return (lst.head == NULL);
}

ListNode* createNode(int data, ListNode* next)
{
	ListNode *result;

	result = (ListNode *)malloc(sizeof(ListNode));

	result->data = data;
	result->next = next;

	return result;
}

void insertNodeToTail(List* lst, ListNode* newTail)
{
	newTail->next = NULL;

	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void freeList(List lst)
{
	ListNode* curr = lst.head, *next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

int isEmptyList(List lst)
{
    return(lst.head == NULL);
}