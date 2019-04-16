#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct letterEncrypt {
	char letter;
	int count;
}LetterEncrypt;

typedef struct listNode {
	LetterEncrypt* sequencePtr;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

List encode(char* str);
void deleteChar(List *lst, char c);
void deleteNodeFromList(List *lst, ListNode* curr, ListNode* prev);

void printList(List lst);
List makeEmptyList();
BOOL isEmptyList(List lst);
ListNode* createNewListNode(LetterEncrypt sequence, ListNode * next);
void insertNodeToEndListNode(List* lst, ListNode * tail);
void freeList(List lst);

void main()
{
	List lst1 = encode("aaaabbaaac");

	printList(lst1);
	deleteChar(&lst1, 'a');
	printList(lst1);
	freeList(lst1);

	/////////////////////////////////////////////////

	List lst2 = encode("aaaabbaaac");

	printList(lst2);
	deleteChar(&lst2, 'c');
	printList(lst2);
	freeList(lst2);

	/////////////////////////////////////////////////

	List lst3 = encode("daaaabbaaac");

	printList(lst3);
	deleteChar(&lst3, 'd');
	printList(lst3);
	freeList(lst3);
}

List encode(char* str)
{
	List lst;
	int i=0;
	while(str[i] != '/0')
	{



		i++;
	}
}

void deleteChar(List *lst, char c)
{

}

void deleteNodeFromList(List *lst, ListNode* curr, ListNode* prev)
{

}


void printList(List lst)
{
	ListNode *curr;

	curr = lst.head;

	while (curr != NULL)
	{
		printf("%c %d\n", curr->sequencePtr->letter, curr->sequencePtr->count);
		curr = curr->next;
	}

	printf("\n");
}

List makeEmptyList()
{
	List res;

	res.head = res.tail = NULL;

	return res;
}

BOOL isEmptyList(List lst)
{
	return (lst.head == NULL);
}

ListNode* createNewListNode(LetterEncrypt sequence, ListNode * next)
{
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
	res->sequencePtr = (LetterEncrypt*)malloc(sizeof(LetterEncrypt));
	*res->sequencePtr = sequence;
	res->next = next;

	return res;
}

void insertNodeToEndListNode(List* lst, ListNode * newTail)
{
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void freeList(List lst)
{
	ListNode* curr = lst.head, *saver;

	while (curr != NULL)
	{
		saver = curr->next;
		free(curr->sequencePtr);
		free(curr);
		curr = saver;
	}
}