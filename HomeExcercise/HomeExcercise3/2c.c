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
List merge(List lst1, List lst2);
ListNode* createNewListNode(int num, ListNode * next);
void printList(List* lst);
int isEmptyList(const List* lst);
void recurseMerge(ListNode* currNodeLst1, ListNode* currNodeLst2,List* mergedList);


int main()
{

    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1,lst2);

    printf("Merged list:\n");
    printList(&mergedList);

	//Testing
	printf("print list1 \n");
	printList(&lst1);
	printf("print list2 \n");
	printList(&lst2);
	
    /*freeList(&lst1);
    freeList(&lst2);
    freeList(&mergedList);*/
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

void recurseMerge(ListNode* currNodeLst1, ListNode* currNodeLst2,List* mergedList)
{
    if(currNodeLst2==NULL)
    {
        while(currNodeLst1!=NULL)
        {
            insertDataToEndList(mergedList,*(currNodeLst1->dataPtr));
            currNodeLst1=currNodeLst1->next;  
        }
    }
    else if(currNodeLst1==NULL)
    {
        while(currNodeLst2!=NULL)
        {
            insertDataToEndList(mergedList,*(currNodeLst2->dataPtr)); 
            currNodeLst2=currNodeLst2->next;      
        }
    }    
    else if(*(currNodeLst2->dataPtr) >= *(currNodeLst1->dataPtr))
    {
        insertDataToEndList(mergedList,*(currNodeLst2->dataPtr));
        currNodeLst2=currNodeLst2->next;
        recurseMerge(currNodeLst1,currNodeLst2,mergedList);
    }  
    else if(*(currNodeLst1->dataPtr) > *(currNodeLst2->dataPtr))
    {
        insertDataToEndList(mergedList,*(currNodeLst1->dataPtr));
        currNodeLst1=currNodeLst1->next;
        recurseMerge(currNodeLst1,currNodeLst2,mergedList);
    }          
}
List merge(List lst1, List lst2) 
{
    List mergedList;
    makeEmptyList(&mergedList);
    ListNode* currNodeLst1 = lst1.head;
    ListNode* currNodeLst2 = lst2.head;
    recurseMerge(currNodeLst1,currNodeLst2,&mergedList);
    return mergedList;
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