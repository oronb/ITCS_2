
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct lnode
{
    int data;
    struct lnode* next;
} LNODE;

typedef struct list
{
    LNODE* head;
    LNODE* tail;
} LIST;

typedef struct listOfListsNode
{
    LIST data;
    struct listOfListsNode* next;
} LIST_OF_LISTS_NODE;

typedef struct listOfLists
{
    LIST_OF_LISTS_NODE* head;
    LIST_OF_LISTS_NODE* tail;
}LIST_OF_LISTS;

//Declare functions
LIST_OF_LISTS splitToPosNegZero(LIST lst);
void makeEmptyList(LIST* lst);
void makeEmptyListsOfLists(LIST_OF_LISTS* lol);
LIST getlist();
void insertDataToEndList(LIST* lst, int num);
void insertDataToEndListOfLists(LIST_OF_LISTS* lol, LIST lst);
LNODE* createNewListNode(int num, LNODE* next);
LIST_OF_LISTS_NODE* createNewListOfListsNode(LIST lst, LIST_OF_LISTS_NODE* next);
void insertNodeToEndList(LIST* lst, LNODE * newTail);
void insertNodeToEndListOfLists(LIST_OF_LISTS* lst, LIST_OF_LISTS_NODE * newTail);
int isEmptyList(const LIST* lst);
int isEmptyListOfLists(const LIST_OF_LISTS* lol);
void freeListOfLists(const LIST_OF_LISTS* lol);
void freeList(const LIST* lst);
void checkAlloc(void* val);
void printLOL(LIST_OF_LISTS lol);
LIST_OF_LISTS createModuLusLists(LIST_OF_LISTS, int k);

void main()
{
    LIST lst;
    LIST_OF_LISTS lol;

    lst = getlist();
    lol=splitToPosNegZero(lst);
    printLOL(lol);
    freeList(&lst);
    freeListOfLists(&lol);
}

LIST_OF_LISTS createModuLusLists(LIST_OF_LISTS lst, int k)
{

    LNODE* currListNode;
    LIST_OF_LISTS_NODE* currLolNode;
    LIST* arr;
    LIST lstInArr;
    LIST_OF_LISTS res;

    /*
    create help array that it's indexes will repesents the modulu
    and every cell of the array will contain list of the modulu number from the lists of the listOfLists
    */
    arr=(int *)calloc(k, sizeof(LIST));
    while(currLolNode != NULL)
    {
        while(currListNode != NULL)
        {
            if(arr[currListNode->data / k] == 0)
            {
                makeEmptyList(&lstInArr);
                arr[currListNode->data / k]=lstInArr;
            }
            insertDataToEndList(arr[currListNode->data / k],currListNode->data);
        }
    }

    //Insert the lists of the array by their modulu
    for(int i = 1; i < k; i++)
    {
        if(arr[i] != 0)
            insertDataToEndListOfLists(res,arr[i]);
    }

    //Insert the last list
    if (arr[0] != 0)
    {
        insertDataToEndListOfLists(res,arr[0]);
    }

    free(arr);
    return res;
}
//Implement functions
LIST_OF_LISTS splitToPosNegZero(LIST lst)
{
    //Declare variables
    LIST_OF_LISTS res;
    LIST pos;
    LIST neg;
    LIST zero;
    LNODE* currListNode=lst.head;
    int num;

    //Create positive numbers list
    makeEmptyList(&pos);
    //Create negative numbers list
    makeEmptyList(&neg);
    //Create zero numbers list
    makeEmptyList(&zero);

    /*checking The numbers in the list
    If the number is zero, it's added to the zero list,
    If the number is positive, it's added to the positive list,
    and if the number is negative, it's added to the negative list
    */
    while (currListNode != NULL)
    {
        num=currListNode->data;

        if (num > 0)
        {
            insertDataToEndList(&pos,num);
        }
        if (currListNode->data < 0)
        {
            insertDataToEndList(&neg,num);
        }
        if (currListNode->data == 0)
        {
            insertDataToEndList(&zero,num);
        }
        currListNode=currListNode->next;
    }

    //Create list of lists
    makeEmptyListsOfLists(&res);

    //Insert the positive, negative and zero lists to the response list
    insertDataToEndListOfLists(&res,pos);
    insertDataToEndListOfLists(&res,neg);
    insertDataToEndListOfLists(&res,zero);

    return res;
}

//Makes empty ynodes list
void makeEmptyList(LIST* lst)
{
	lst->head = lst->tail = NULL;
}

void makeEmptyListsOfLists(LIST_OF_LISTS* lol)
{
    lol->head = lol->tail = NULL;
}

LIST getlist()
{
    LIST lst;
    int num, size, i;

    makeEmptyList(&lst);

    //Add elements to list
    printf("Enter the number of elemnts you want to add to the list\n");
    scanf("%d", &size);

    for(i = 0; i < size; i++)
    {
        printf("Enter the elemnet\n");
        scanf("%d", &num);
        insertDataToEndList(&lst,num);
    }
    return lst;
}

//Insert Ynode to the end of Ynode's list
void insertDataToEndList(LIST* lst, int num) 
{
	LNODE* newTail;

	newTail = createNewListNode(num, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertDataToEndListOfLists(LIST_OF_LISTS* lol, LIST lst)
{
    LIST_OF_LISTS_NODE* newTail;

    newTail = createNewListOfListsNode(lst, NULL);
    insertNodeToEndListOfLists(lol, newTail);
}

LNODE* createNewListNode(int num, LNODE* next)
{
	LNODE* res;

	res = (LNODE*)malloc(sizeof(LNODE));
    checkAlloc(res);
	res->data = num;
	res->next = next;

	return res;
}

LIST_OF_LISTS_NODE* createNewListOfListsNode(LIST lst, LIST_OF_LISTS_NODE* next)
{
    LIST_OF_LISTS_NODE* res;
    res = (LIST_OF_LISTS_NODE*)malloc(sizeof(LIST_OF_LISTS_NODE));
    checkAlloc(res);
    res->data = lst;
    res->next = next;

    return res;
} 

void insertNodeToEndList(LIST* lst, LNODE * newTail) 
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

void insertNodeToEndListOfLists(LIST_OF_LISTS* lol, LIST_OF_LISTS_NODE * newTail) 
{
	if (isEmptyListOfLists(lol))
	{
		lol->head = lol->tail = newTail;
	}
	else
	{
		lol->tail->next = newTail;
		lol->tail = newTail;
	}
}

int isEmptyList(const LIST* lst)
{
    return lst->head == NULL;
}

int isEmptyListOfLists(const LIST_OF_LISTS* lol)
{
    return lol->head == NULL;
}

void freeListOfLists(const LIST_OF_LISTS* lol)
{
    LIST_OF_LISTS_NODE* tempNode;
    LIST_OF_LISTS_NODE* currLolNode = lol->head;

    while(currLolNode != NULL)
    {
        tempNode=currLolNode;
        currLolNode=currLolNode->next;
        freeList(&(tempNode->data));
        free(tempNode);
    }
}

void freeList(const LIST* lst)
{
    LNODE* tempNode;
    LNODE* currListNode = lst->head;

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

void printLOL(LIST_OF_LISTS lol)
{
    LIST_OF_LISTS_NODE* currLolNode = lol.head;
    LNODE* currListNode;
    int listNum=1;
    while(currLolNode != NULL)
    {
        currListNode=currLolNode->data.head;
        printf("List%d:\n", listNum);
        while(currListNode != NULL)
        {
            printf("%d ", currListNode->data);
            currListNode=currListNode->next;
        }
        printf("\n");
        listNum++;
        currLolNode=currLolNode->next;
    }
}