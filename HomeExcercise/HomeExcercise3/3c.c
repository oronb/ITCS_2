
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//Declare definitions

typedef struct YlistNode{
    int num;
    struct YlistNode* next;
} YListNode;

typedef struct Ylist
{
    YListNode* head;
    YListNode* tail;
} YList;

typedef struct XlistNode{
    YList* YListInXNode; //Pointer or the list itself?
    int num;
    struct XlistNode* next;
    struct XlistNode* prev;
} XListNode;

typedef struct list
{
	XListNode* head;
	XListNode* tail;
}List;

//Declare functions
List getCoordList();
int searchValueInList(List lst, int num, XListNode** res);
void makeEmptyList(List* lst);
void makeEmptyYList(YList* lst);
void insertDataToEndList(List* lst, int num, YList YListInXNode);
void insertDataToEndYList(YList* lst, int num);
XListNode* createNewListXNode(int num, YList ylst, XListNode* next, XListNode* prev);
YListNode* createNewYListNode(int num, YListNode* next);
void insertXNodeToEndList(List* lst, XListNode * newTail);
void insertNodeToEndYList(YList* lst, YListNode * newTail);
unsigned int getXOccurrences(List coord_list, int x);
int isEmptyList(const List* lst);
int isEmptyYList(const YList* lst);
void freeList(const List* lst);
void freeYList(const YList* lst);
void checkAlloc(void* val);

void main()
{

    List coordList;
    int x;
    unsigned int res;

    coordList = getCoordList();

    // get the (x,*) to look for
    scanf("%d", &x);
    res = getXOccurrences(coordList, x);

    printf("The point (%d,*) appears %u times\n", x, res);

    freeList(&coordList);
}

unsigned int getYOccurrences(List coord_list, int y)
{
    XListNode* currLst=coord_list.head;
    YListNode* currYLst;
    int count=0;

    while(currLst != NULL)
    {
        currYLst=currLst->YListInXNode->head;
        while(currYLst != NULL)
        {
            if(currYLst->num == y)
            {
                count++;
            }
            currYLst=currYLst->next;
        }
        currLst=currLst->next;
    }
    return count;   
}

List getCoordList()
{
    List CoordList;
    XListNode* searchRes;
    int size, x, y, i;
    YList* exitsYlist;
    YList newYList;

    makeEmptyList(&CoordList);

    scanf("%d", &size);

    for(i = 0; i < size; i++)
    {
        scanf("%d", &x);
        scanf("%d", &y);
        if(searchValueInList(CoordList,x,&searchRes))
        {
            exitsYlist=searchRes->YListInXNode;
            insertDataToEndYList(exitsYlist,y);          
            //Inserts new y node to the end of ylist that xnode with x value points to
        }
        else
        {
            makeEmptyYList(&newYList);
            insertDataToEndYList(&newYList,y);
            insertDataToEndList(&CoordList,x,newYList);
            //Inserts new x node to the end of xlist and create new ylist with ynode (includes y) that x node points to
        }

    }
    return CoordList;
}

//Search for a number in x nodes list
int searchValueInList(List lst, int num, XListNode** res)
{
    XListNode* currLst1;
    currLst1=lst.head;
    while(currLst1 != NULL)
    {
        if(currLst1->num == num)
        {
            *res=currLst1;
            return 1;
        }
        currLst1=currLst1->next;
    }
    return 0;
}
//Makes empty xnodes list
void makeEmptyList(List* lst)
{
	lst->head = lst->tail = NULL;
}
//Makes empty ynodes list
void makeEmptyYList(YList* lst)
{
	lst->head = lst->tail = NULL;
}

//Insert Xnode to the end of Xnode's list
void insertDataToEndList(List* lst, int num, YList ylst) 
{
	XListNode* newTail;

	newTail = createNewListXNode(num, ylst, NULL, lst->tail);
	insertXNodeToEndList(lst, newTail);
}

//Insert Ynode to the end of Ynode's list
void insertDataToEndYList(YList* lst, int num) 
{
	YListNode* newTail;

	newTail = createNewYListNode(num, NULL);
	insertNodeToEndYList(lst, newTail);
}

//Create Xnode
XListNode* createNewListXNode(int num, YList ylst, XListNode* next, XListNode* prev)
{
	XListNode* res;
    YList* YListInXNode;

	res = (XListNode*)malloc(sizeof(XListNode));
    checkAlloc(res);
    YListInXNode = ((YList*)malloc(sizeof(YList)));
    checkAlloc(YListInXNode);
    *YListInXNode=ylst;
	res->num = num;
    res->YListInXNode=YListInXNode;
	res->next = next;
    res->prev = prev;

	return res;
}

//Create Ynode
YListNode* createNewYListNode(int num, YListNode* next)
{
	YListNode* res;

	res = (YListNode*)malloc(sizeof(YListNode));
    checkAlloc(res);
	res->num = num;
	res->next = next;

	return res;
}

//Inserts Xnode to the end of Xnode's list
void insertXNodeToEndList(List* lst, XListNode * newTail) 
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

//Inserts Ynode to the end of Ynode's list
void insertNodeToEndYList(YList* lst, YListNode * newTail) 
{
	if (isEmptyYList(lst))
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

int isEmptyYList(const YList* lst)
{
    return lst->head == NULL;
}

unsigned int getXOccurrences(List coord_list, int x)
{
    XListNode* currLst=coord_list.head;
    YListNode* currYLst;
    int count=0;

    while(currLst != NULL)
    {
        currYLst=currLst->YListInXNode->head;
        while(currYLst != NULL)
        {
            if(currLst->num == x)
            {
                count++;
            }
            currYLst=currYLst->next;
        }
        currLst=currLst->next;
    }
    return count;
}

void freeList(const List* lst)
{
    XListNode* tempNode;
    XListNode* currXNodeList = lst->head;

    while(currXNodeList != NULL)
    {
        tempNode=currXNodeList;
        freeYList(currXNodeList->YListInXNode);
        free(currXNodeList->YListInXNode);
        currXNodeList=currXNodeList->next;
        free(tempNode);
    }
}

void freeYList(const YList* lst)
{
    YListNode* tempNode;
    YListNode* currYNodeList = lst->head;

    while(currYNodeList != NULL)
    {
        tempNode=currYNodeList;
        currYNodeList=currYNodeList->next;
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