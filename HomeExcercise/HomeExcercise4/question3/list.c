#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct listNode  {
	int data;
	struct listNode* next;
} ListNode;

typedef struct list  {
	ListNode* head;
	ListNode* tail;
} List;

//Declare functions
void makeEmptyList(List* lst);
void insertNodeToEndList(List* lst, ListNode * newTail);
void insertDataToEndList(List* lst, int num);
int isEmptyList(const List* lst);
void checkAlloc(void* val );
ListNode* createNewListNode(int num, ListNode* next);

//Removes ylist that xnode points to and removes the xnode from coordinate list
void removeNodeFromLeafList( List* list, ListNode* prevNode, ListNode* nodeToBeDeleted)
{
    //Define variables
    ListNode * tempNode;

    //Set the node to be deleted into temp variables
    tempNode = nodeToBeDeleted;

    //Set the prev node to point to the node after the node to be deleted
    if((list->head == nodeToBeDeleted) && (prevNode == NULL))
    {
        list->head=nodeToBeDeleted->next;
    }
    else
    {
        prevNode->next = nodeToBeDeleted->next;
    }
    
    if(list->tail == nodeToBeDeleted)
    {
        list->tail = prevNode;
        prevNode->next=NULL;
    }
    free(tempNode);
}

ListNode* createNewListNode(int num, ListNode* next) {
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
    checkAlloc(res);
	res->data = (int*)malloc(sizeof(int));
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

int isEmptyList(const List* lst)
{
    return lst->head == NULL;
}

void makeEmptyList(List* lst)
{
	(*lst).head = (*lst).tail = NULL;
}

ListNode* createNewListNode(int num, ListNode* next) {
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
    checkAlloc(res);
	res->data = num;
	res->next = next;

	return res;
}