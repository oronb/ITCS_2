
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct ArrayNode
{
    int **arr;
    int size;
    struct ArrayNode *next;
} ArrayNode;

typedef struct ArrayList
{
    ArrayNode* head;
    ArrayNode* tail;
} ArrayList;

//Declare functions
void DeleteValue(ArrayList *lst, int value);
void makeEmptyList(ArrayList* lst);
void deleteFromList(ArrayList *lst, ArrayNode* prevNode);
void deleteFromStartOfList(ArrayList* lst);
void deleteFromEndOfList(ArrayList* lst);
//LIST getlist();
void insertDataToEndList(ArrayList* lst, int **arr, int size);
ArrayNode* createNewListNode(int **arr, int size, ArrayNode* next);
void insertNodeToEndList(ArrayList* lst, ArrayNode * newTail);
int isEmptyList(const ArrayList* lst);
void freeList(const ArrayList* lst);
void checkAlloc(void* val);
int** getArr(unsigned int * arrSize);
ArrayList getList();
void printArr(int** arr, int size);
void printList(ArrayList lst);

void main()
{
    ArrayList lst;
    int num;
    lst=getList();
    printf("Enter the number you want to delete\n");
    scanf("%d",&num);
    DeleteValue(&lst,num);
    printList(lst);
}

void DeleteValue(ArrayList *lst, int value)
{
    ArrayNode* currListNode=lst->head;
    ArrayNode* prevNode=NULL;
    int **arr;
    int l,r;
    int size;
    int reduceSize=0;

    while(currListNode != NULL)
    {
        arr=currListNode->arr;
        size=currListNode->size;
        l=0;
        r=size-1;
        while (l <= r)
        {
            if(*arr[l] == value && *arr[r] != value)
            {
                free(arr[l]);
                arr[l]=arr[r];
                r--;
                l++;
                reduceSize++;
            }
            else if(*arr[l] != value && *arr[r] == value)
            {
                free(arr[r]);
                r--;
                l++;
                reduceSize++;
            }            
            else if(*arr[l] != value && *arr[r] != value)
            {
                l++;
            }
            else if(*arr[l] == value && *arr[r] == value)
            {
                free(arr[r]);
                r--;
                reduceSize++;
            }            
        }
        if(reduceSize != 0)
        {
            size=size-reduceSize;
            arr = (int**)realloc(arr, size * sizeof(int*));
            /*
                If the new size of the array is 0, delete the node that contains the arr, 
                and free the memory of the arr
            */ 
        }

        if(size == 0)
        {
            free(arr);
            deleteFromList(lst,prevNode);
        }

        prevNode=currListNode;
        currListNode=currListNode->next;
    }
}

void deleteFromList(ArrayList *lst, ArrayNode* prevNode)
{
    ArrayNode* tmp;
    if(!isEmptyList(lst))
    {
        if(prevNode==NULL)
        {
            deleteFromStartOfList(lst);
        }
        else if(prevNode->next->next==NULL)
        {
            deleteFromEndOfList(lst);
        }
        else
        {
            tmp=prevNode->next->next;
            free(prevNode->next);
            prevNode->next=tmp;
        }
    }     
}

void deleteFromStartOfList(ArrayList* lst)
{
    ArrayNode* tmp=lst->head;
    if(lst->head->next == NULL)
    {
        lst->head=NULL;
        lst->tail=NULL;
    }
    else
    {
        lst->head=lst->head->next;
    } 
    free(tmp);
}

void deleteFromEndOfList(ArrayList* lst)
{
    ArrayNode* currListNode = lst->head;
    while(currListNode->next != lst->tail)
    {
        currListNode=currListNode->next;
    }
    free(lst->tail);
    lst->tail=currListNode;
    lst->tail->next=NULL;
}

//Makes empty list
void makeEmptyList(ArrayList* lst)
{
	lst->head = lst->tail = NULL;
}

//Insert Ynode to the end of Ynode's list
void insertDataToEndList(ArrayList* lst, int **arr, int size)
{
	ArrayNode* newTail;

	newTail = createNewListNode(arr, size, NULL);
	insertNodeToEndList(lst, newTail);
}

ArrayNode* createNewListNode(int **arr, int size, ArrayNode* next)
{
	ArrayNode* res;

	res = (ArrayNode*)malloc(sizeof(ArrayNode));
    checkAlloc(res);
	res->arr = arr;
    res->size = size;
	res->next = next;

	return res;
}

void insertNodeToEndList(ArrayList* lst, ArrayNode * newTail)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

int isEmptyList(const ArrayList* lst)
{
    return lst->head == NULL;
}

void freeList(const ArrayList* lst)
{
    ArrayNode* tempNode;
    ArrayNode* currListNode = lst->head;

    while(currListNode != NULL)
    {
        tempNode=currListNode;
        currListNode=currListNode->next;
        free(tempNode);
    }
}

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}

ArrayList getList()
{
    ArrayList lst;
    int** arr;
    int lstSize;
    unsigned int arrSize,i;
    makeEmptyList(&lst);
    printf("Insert how many arrays you want\n");
    scanf("%d", &lstSize);
    for (i = 0; i < lstSize; i++)
    {
        arr=getArr(&arrSize);
        insertDataToEndList(&lst,arr,arrSize);
    }

    return lst;
}
int** getArr(unsigned int * arrSize)
{
    int phys_sz=1, logic_sz=0, num, flag=1;
    int* pNum;
    int** arr;
    arr = (int**)malloc(phys_sz * sizeof(int*));
    pNum = (int*)malloc(phys_sz * sizeof(int));
    checkAlloc(arr);
    printf("Insert element to array\n");
    scanf("%d", &num);
    printf("scanned\n");
    while(flag != 0)
    {
        printf("flag not 0\n");
        *pNum=num;
        arr[logic_sz] = pNum;
        logic_sz++;
        if (logic_sz == phys_sz) { // array is full; logical size reached physical size
            phys_sz *= 2;
            arr = (int**)realloc(arr, phys_sz * sizeof(int*)); // alloc twice the size
            checkAlloc(arr);
            //printf("Doubled the array size to %d\n", phys_sz);
        }  
        if (getchar()=='\n')
        {
            flag=0;
        }    
        else
        {
            printf("Insert element to array\n");
            scanf("%d", &num);
        } 
    }
    *arrSize=logic_sz;
    arr = (int**)realloc(arr, *arrSize * sizeof(int*)); // Allocate the array size by the physical size
    checkAlloc(arr);
    return arr;
}

void printArr(int** arr, int size)
{
    int i;
    for( i = 0; i < size; i++)
    {
        printf("%d ", *arr[i]);
    }
}
void printList(ArrayList lst)
{
    ArrayNode* currNode = lst.head;
    int listNum=0;
    while(currNode != NULL)
    {
        printf("Arr %d:\n", listNum);
        printArr(currNode->arr,currNode->size);
        printf("\n");
        listNum++;
        currNode=currNode->next;
    }
}