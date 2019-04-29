
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
void insertDataToEndList(LIST* lst, int num);
LNODE* createNewListNode(int num, LNODE* next);
void insertNodeToEndList(LIST* lst, LNODE * newTail);
int isEmptyList(const LIST* lst);
void freeList(const LIST* lst);
void checkAlloc(void* val);

void main()
{

}

//Implement functions
LIST_OF_LISTS splitToPosNegZero(LIST lst)
{
    //Declare variables
    LIST_OF_LISTS res;
    LIST pos;
    LIST neg;
    LIST zero;
    LNODE* currListNode=lst->head;
    LIST_OF_LISTS_NODE* currLolNode=res->head;
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
            insertDataToEndList(pos,num);
        }
        if (currListNode->data < 0)
        {
            insertDataToEndList(neg,num);
        }
        if (currListNode->data == 0)
        {
            insertDataToEndList(zero,num);
        }
        currListNode=currListNode->next;
    }

    //Insert the positive, negative and zero lists to the response list
    insertDataToEndListOfLists(pos);
    insertDataToEndListOfLists(neg);
    insertDataToEndListOfLists(zero);
}

//Makes empty ynodes list
void makeEmptyList(LIST* lst)
{
	lst->head = lst->tail = NULL;
}

void makeEmptyListsOfLists(LIST_OF_LISTS* lol)
{
    lst->head = lst->tail = NULL;
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
    LIST* listInLolNode;
    res = (LIST_OF_LISTS_NODE*)malloc(sizeof(LIST_OF_LISTS_NODE));
    checkAlloc(res);
    listInLolNode=(LIST*)malloc(sizeof(LIST));
    *listInLolNode=lst
    checkAlloc(res);
    res->data = *listInLolNode;
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

void insertNodeToEndListOfLists(LIST_OF_LISTS* lol, LNODE * newTail) 
{
	if (isEmptyList(lol))
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
        free(tempNode->data);
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