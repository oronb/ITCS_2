//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct listNode{
	int* dataPtr;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

//Declare functions
List getList();
void freeList(List* lst);
void makeEmptyList(List* lst);
void insertNodeToEndList(List* lst, ListNode * newTail);
void insertDataToEndList(List* lst, int num);
ListNode* createNewListNode(int num, ListNode * next);
void printList(List* lst);
int isEmptyList(const List* lst);
List merge(List lst1, List lst2);

void main()
{

List lst1, lst2, mergedList;

lst1 = getList();
lst2 = getList();

mergedList = merge(lst1,lst2);

printf("Merged list:\n");
printList(&mergedList);

freeList(&mergedList);
}


void printList(List* lst) {
	ListNode* currentNode=lst->head;
	while(currentNode != NULL){
		printf("%d ",*(currentNode->dataPtr));
		currentNode=currentNode->next;
	}
    printf("\n");
}

int isEmptyList(const List* lst)
{
    return lst->head == NULL;
}

List getList()
{
    List res;
    int size, num, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the numbers:\n");
    for(i = 0; i < size; i++)
    {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }
    return res;
}

void freeList(List* lst)
{

}

void makeEmptyList(List* lst)
{
	(*lst).head = (*lst).tail = NULL;
}

void insertDataToEndList(List* lst, int num) {
	ListNode* newTail;

	newTail = createNewListNode(num, NULL);
	insertNodeToEndList(lst, newTail);
}

ListNode* createNewListNode(int num, ListNode* next) {
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
	res->dataPtr = (int*)malloc(sizeof(int));
	*(res->dataPtr) = num;
	res->next = next;

	return res;
}

void insertNodeToEndList(List* lst, ListNode * newTail) {
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


List merge(List lst1, List lst2) 
{
    List mergedList;
    ListNode* currNodeLst1 = lst1.head;
    ListNode* currNodeLst2 = lst2.head;
    ListNode* next1;
    ListNode* next2;

    makeEmptyList(&mergedList);

    //Updates merged list's head if the current node of list 1 is the head of list 1
    if (*(currNodeLst1->dataPtr) >= *(currNodeLst2->dataPtr))
    {
        mergedList.head=currNodeLst1;
    }
    else
    {
        mergedList.head=currNodeLst2;
    }
    
    //Merges list1 and list2
    while((currNodeLst1 != NULL) && (currNodeLst2 != NULL))
    {
        if(*(currNodeLst1->dataPtr) >= *(currNodeLst2->dataPtr))
        {
            //Checks if the next node of list 1 bigger than the node in list 2
            if(currNodeLst1->next != NULL && *(currNodeLst1->next->dataPtr) >= *(currNodeLst2->dataPtr))
            {
                currNodeLst1=currNodeLst1->next;
            }
            else
            {                     
                next1=currNodeLst1->next;
                currNodeLst1->next=currNodeLst2;
                currNodeLst1=next1;
            }

        }
        else if(*(currNodeLst2->dataPtr) > *(currNodeLst1->dataPtr))
        {
            //Checks if the next node of list 2 bigger than the node in list 1
            if(currNodeLst2->next != NULL && *(currNodeLst2->next->dataPtr) >= *(currNodeLst1->dataPtr))
            {
                currNodeLst2=currNodeLst2->next;
            }
            else
            {               
            next2=currNodeLst2->next;
            currNodeLst2->next=currNodeLst1;
            currNodeLst2=next2;
            }
        }     
    }

    //Updates merged list's tail
    while(currNodeLst1 != NULL)
    {
        mergedList.tail=currNodeLst1;
        currNodeLst1=currNodeLst1->next;
    }
    while(currNodeLst2!= NULL)
    {
        mergedList.tail=currNodeLst2;
        currNodeLst2=currNodeLst2->next;
    }

    return mergedList;
}