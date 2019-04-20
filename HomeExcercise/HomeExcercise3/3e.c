
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
int removeCoordinate(List *coord_list, int x, int y);
void removeXNodeFromList( List* list, XListNode* nodeToBeDeleted);
void removeYNodeFromList( YList* list,YListNode* prevNode, YListNode* nodeToBeDeleted);
int searchValueInList(List lst, int num, XListNode** res);
int countCoordinate(List *coord_list, int x, int y, int* xCount,XListNode** removeX, YListNode** removeY,YListNode** preRemoveY);
int countValueInList(List lst, int num, XListNode** removeX);
int countValueInYList(YList lst, int num, YListNode** removeY,YListNode** preRemoveY);
void makeEmptyList(List* lst);
void makeEmptyYList(YList* lst);
void insertDataToEndList(List* lst, int num, YList YListInXNode);
void insertDataToEndYList(YList* lst, int num);
XListNode* createNewListXNode(int num, YList ylst, XListNode* next, XListNode* prev);
YListNode* createNewYListNode(int num, YListNode* next);
void insertXNodeToEndList(List* lst, XListNode * newTail);
void insertNodeToEndYList(YList*  lst, YListNode * newTail);
int insertCoordinate(List *coord_list, int x, int y);
int isEmptyList(const List* lst);
int isEmptyYList(const YList* lst);
void printList(List lst);
void freeList(const List* lst);
void freeYList(const YList* lst);

void main()
{
    List coordList;

    int x, y;
    int res;

    coordList = getCoordList();

    // get the (x,y) to remove
    printf("Enter the point that you want to remove\n");
    scanf("%d%d", &x, &y);

    res = removeCoordinate(&coordList, x, y);

    if(res == 1)
        printf("The point (%d,%d) didn't appear\n",x,y);
    else if(res == 2)
        printf("The point (%d,%d) has another occurrence\n",x,y);
    else if(res == 3)
        printf("The point (%d,%d) was the only point with this x\n",x,y);
    else
        printf("Other\n");
    printList(coordList);
    freeList(&coordList);

}
// Remove coordinate from coordinate list
int removeCoordinate(List *coord_list, int x, int y)
{
    int coordCount;
    int xCount;
    XListNode* removeX;
    YListNode* removeY;
    YListNode* preRemoveY;

    coordCount=countCoordinate(coord_list,x,y,&xCount,&removeX,&removeY,&preRemoveY);

    if (coordCount == 0)
    {
        return 1;
    }
    else if (coordCount == 1)
    {
        removeYNodeFromList(removeX->YListInXNode,preRemoveY,removeY);
        if(xCount == 1)
        {
            removeXNodeFromList(coord_list,removeX);
            //Delete ylist's node(free), ylist* from Xnode(free) ,Xnode(free)
            return 3;
        }
        else if (xCount > 1)
        {
            removeYNodeFromList(removeX->YListInXNode,preRemoveY,removeY);
            //delete the value and free it
        }

    }
    else if (coordCount > 1)
    {
        removeYNodeFromList(removeX->YListInXNode,preRemoveY,removeY);
        //Delete one appearences(free) of the coordinate in the ylist* of Xnode
        return 2;
    }
    else
    {
        return 0;
    }
    return 0;
}

//Removes ylist that xnode points to and removes the xnode from coordinate list
void removeXNodeFromList( List* list, XListNode* nodeToBeDeleted)
{
    //Define variables
    YList* YListToRemove;
    XListNode * tempNode;

    //Set the node to be deleted into temp variables
    tempNode = nodeToBeDeleted;
    YListToRemove=nodeToBeDeleted->YListInXNode;

    //Set the prev node to point to the node after the node to be deleted
    if((list->head == nodeToBeDeleted) && (nodeToBeDeleted->prev == NULL))
    {
        list->head=nodeToBeDeleted->next;
        nodeToBeDeleted->next->prev=NULL;
    }
    else
    {
        nodeToBeDeleted->prev->next = nodeToBeDeleted->next;
        nodeToBeDeleted->next->prev = nodeToBeDeleted->prev;
    }
    
    if(list->tail == nodeToBeDeleted)
    {
        list->tail = nodeToBeDeleted->prev;
        nodeToBeDeleted->prev->next=NULL;
    }

    freeYList(YListToRemove);
    free(tempNode);
}

//Remove ynode from ynode's list
void removeYNodeFromList( YList* list,YListNode* prevNode, YListNode* nodeToBeDeleted)
{
    //Define variables
    YListNode * tempNode;

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
    }
    free(tempNode);
}

/*
Search for coordinate in cordinate list. 
Returns the number of the occurnces of the coordinate
*/
int countCoordinate(List *coord_list, int x, int y, int* xCount,XListNode** removeX, YListNode** removeY,YListNode** preRemoveY)
{
    int res=0;
    *xCount=countValueInList(*coord_list,x,removeX);
    if(*xCount > 0)
    {
        res=countValueInYList(*((*removeX)->YListInXNode),y,removeY,preRemoveY);
    }
    return res;
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

//Count the number of the appearnces of (x,*) in the coordinate list
int countValueInList(List lst, int num, XListNode** removeX)
{
    XListNode* currLst1;
    currLst1=lst.head;
    int count=0;
    while(currLst1 != NULL)
    {
        if(currLst1->num == num)
        {
            *removeX=currLst1;
            count++;
        }
        currLst1=currLst1->next;
    }
    return count;
}

//Counts the number appereances of the of (*,y) and returns it
int countValueInYList(YList lst, int num, YListNode** removeY,YListNode** preRemoveY)
{
    YListNode* currLst1;
    YListNode* preCurrLst1=NULL;
    currLst1=lst.head;
    int count=0;
    while(currLst1 != NULL)
    {
        if(currLst1==lst.head->next)
        {
            preCurrLst1=lst.head;
        }
        else
        {
            if(currLst1 != lst.head)
            {
                preCurrLst1=preCurrLst1->next;
            }
        }
        
        if(currLst1->num == num)
        {
            *preRemoveY=preCurrLst1;
            *removeY=currLst1;
            count++;
        }
        currLst1=currLst1->next;
    }
    return count;
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
    YListInXNode = ((YList*)malloc(sizeof(YList)));
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

//Check if coordinate list is empty
int isEmptyList(const List* lst)
{
    return lst->head == NULL;
}

//Check if Y list is empty
int isEmptyYList(const YList* lst)
{
    return lst->head == NULL;
}

//Print coordinate list
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

//Free cordinate list
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

//Free y list
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

//Input coordinate list
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
