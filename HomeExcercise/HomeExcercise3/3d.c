
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
int searchValueInYList(YList lst, int num);
void makeEmptyList(List* lst);
void makeEmptyYList(YList* lst);
void insertDataToList(List* lst, int num, YList ylst, XListNode* prevXNode, XListNode* currXNode);
void insertDataToEndList(List* lst, int num, YList YListInXNode);
void insertDataToEndYList(YList* lst, int num);
void insertDataToYList(YList* lst,int y,YListNode* prevYNode,YListNode* currYNode);
XListNode* createNewListXNode(int num, YList ylst, XListNode* next, XListNode* prev);
YListNode* createNewYListNode(int num, YListNode* next);
void insertXNodeToEndList(List* lst, XListNode * newTail);
void insertXNodeToList(List* lst, XListNode * prevXNode, XListNode * newXNode, XListNode * nextXNode);
void insertNodeToEndYList(YList* lst, YListNode * newTail);
void insertNodeToYList(YList* list,YListNode* prevNode, YListNode* newNode, YListNode* nextNode);
int insertCoordinate(List *coord_list, int x, int y);
int isEmptyList(const List* lst);
int isEmptyYList(const YList* lst);
void printList(List lst);
void freeList(const List* lst);
void freeYList(const YList* lst);
void checkAlloc(void* val);

void main()
{
    List coordList;

    int x, y;
    int res;

    coordList = getCoordList();

    // get the (x,y) to insert
    scanf("%d%d", &x, &y);

    res = insertCoordinate(&coordList, x, y);

    if(res == 0)
        printf("The point (%d,%d) didn't appear\n",x,y);
    else
        printf("The point (%d,%d) already appeared\n",x,y);
    printList(coordList);
    freeList(&coordList);
}

int insertCoordinate(List *coord_list, int x, int y)
{
    XListNode* searchRes;
    YList* exitsYlist;
    YList newYList;
    int res;
    YListNode* currYNode;
    YListNode* prevYNode;
    XListNode* currXNode = coord_list->head;
    XListNode* prevXNode = NULL;

    if(searchValueInList(*coord_list,x,&searchRes))
    {
        exitsYlist=searchRes->YListInXNode;
        currYNode = exitsYlist->head;
        prevYNode = NULL;
        //Check if y exists in y list 
        if(searchValueInYList(*exitsYlist, y))
        {
            res=1;
        }
        else
        {
            res=0;
        }
        while(currYNode != NULL || currYNode->num >= y)
        {
            prevYNode=currYNode;
            currYNode=currYNode->next;
        }           
        insertDataToYList(exitsYlist,y,prevYNode,currYNode);
    }
    else
    {
        res=0;
        makeEmptyYList(&newYList);
        insertDataToEndYList(&newYList,y);
        while(currXNode != NULL || currXNode->num >= x)
        {
            prevXNode=currXNode;
            currXNode=currXNode->next;
        }
        insertDataToList(coord_list,x,newYList,prevXNode,currXNode);
    }
    return res;
}

List getCoordList()
{
    List CoordList;
    XListNode* searchRes;
    int size, x, y, i;
    YList* exitsYlist;
    YList newYList;

    makeEmptyList(&CoordList);

    printf("Please enter the number of points to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the dots:\n");
    for(i = 0; i < size; i++)
    {
        //Insert x
        printf("Insert x\n");
        scanf("%d", &x);
        printf("Insert y\n");
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

int searchValueInYList(YList lst, int num)
{
    YListNode* currLst1;
    currLst1=lst.head;
    while(currLst1 != NULL)
    {
        if(currLst1->num == num)
        {
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

//Insert Xnode to Xnode's list
void insertDataToList(List* lst, int num, YList ylst, XListNode* prevXNode, XListNode* currXNode) 
{
	XListNode* newXNode;

	newXNode = createNewListXNode(num, ylst, currXNode, prevXNode);
	insertXNodeToList(lst, prevXNode,newXNode,currXNode);
}

void insertNodeToYList( YList* list,YListNode* prevYNode, YListNode* newYNode, YListNode* nextYNode)
{
    if(prevYNode == NULL)
    {
        list->head=newYNode;
    }
    else
    {
        prevYNode->next = newYNode;
    }  
    if(nextYNode == NULL)
    {
        list->tail = newYNode;
    }
    newYNode->next=nextYNode;
}

void insertDataToYList(YList* lst,int y,YListNode* prevYNode,YListNode* currYNode)
{
    YListNode* newYNode;
    newYNode = createNewYListNode(y,currYNode);
    insertNodeToYList(lst,prevYNode,newYNode,currYNode);
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
//Inserts Xnode to Xnode's list

void insertXNodeToList(List* lst, XListNode * prevXNode, XListNode * newXNode, XListNode * nextXNode) 
{
    if(prevXNode == NULL)
    {
        lst->head=newXNode;
    }
    else
    {
        prevXNode->next = newXNode;
    }  
    if(nextXNode == NULL)
    {
        lst->tail = newXNode;
    }
    newXNode->prev=prevXNode;
    newXNode->next=nextXNode;
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

unsigned int getPairOccurrences(List coord_list, int x, int y)
{
    XListNode* currLst=coord_list.head;
    YListNode* currYLst;
    int count=0;

    while(currLst != NULL)
    {
        currYLst=currLst->YListInXNode->head;
        while(currYLst != NULL)
        {
            if((currLst->num == x) && (currYLst->num == y))
            {
                count++;
                printf("Found matched spot! ");
                printf("(%d,%d) \n",currLst->num,currYLst->num);
            }
            currYLst=currYLst->next;
        }
        currLst=currLst->next;
    }
    return count;
}

void printList(List lst)
{
    XListNode* currLst=lst.head;
    YListNode* currYLst;

    while(currLst != NULL)
    {
        currYLst=currLst->YListInXNode->head;
        printf("The list of %d:\n",currLst->num);
        while(currYLst != NULL)
        {
            printf("(%d,%d) ",currLst->num,currYLst->num);
            currYLst=currYLst->next;
        }
        printf("\n");
        currLst=currLst->next;
    }
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