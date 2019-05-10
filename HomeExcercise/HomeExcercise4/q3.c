#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define SIZE 100
#define LEFT  0
#define RIGHT 1
#define FALSE 0
#define TRUE 1

typedef int BOOL;

typedef struct listNode  {
	int data;
	struct listNode* next;
} ListNode;

typedef struct list  {
	ListNode* head;
	ListNode* tail;
} List;

typedef struct  treeNode {
	int data;
	struct treeNode* parent;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree{
    TreeNode* root;
    List leafList;   /*רשימה מקושרת של כל העלים בעץ*/ 
} Tree;

//Declare functions
void makeEmptyList(List* lst);
void insertNodeToEndList(List* lst, ListNode * newTail);
void insertNodeToList(List* lst, ListNode * prevNode, ListNode * newNode) ;
void insertDataToEndList(List* lst, int num);
void insertDataToList(List* lst, int num, ListNode* prevNode);
int isEmptyList(const List* lst);
void checkAlloc(void* val );
Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data);
void AddLeafRec(TreeNode* currTreeNode, TreeNode *p, int* leafListCounter, int branchSelect, int data, BOOL* foundParent, List* leafList, ListNode** prevParentListNode);
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);
void BuildTreeFromArrayWithLeafListRec(int *arr, TreeNode* parentCurr,TreeNode **curr, int size, List *leafList);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
void findParentRec(TreeNode* curr, TreeNode** parentNode, int parentData, int branchSelect, BOOL *foundParent);
void printTreeInOrder(Tree t); //Copy from Keren's presentation
void printTreeInOrderRec(TreeNode *t);
void printLeafList(Tree tree); 
TreeNode* createNewTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right);
ListNode* createNewListNode(int num, ListNode* next);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);

void main()

{
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode * p;
    int parentData, data, branchSelect;

    printf("Please enter the number of items: ");
    scanf("%d", &size);

    for(i=0; i<size; i++)
    {
        printf("Enter item in array\n");
        scanf("%d", &arr[i]);
    }    
    printf("Enter parentData, data and branchSelect\n");
    scanf("%d%d%d", &parentData, &data, &branchSelect);

    tr = BuildTreeFromArrayWithLeafList(arr, size);//the array is given as described in question 1
    //scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in branchSelect
    p = findParent(tr, parentData, branchSelect);
    printf("The parent is: %d\n", p->data);
    tr = AddLeaf(tr, p, branchSelect, data);
    printf("print Tree\n");
    printTreeInOrder(tr); //Print the tree in-order (LDR)
    printf("Print leaf list\n");
    printLeafList(tr); //Print the leaves from left to right

    freeTree(tr);

}

Tree BuildTreeFromArrayWithLeafList( int  *arr, int  size)
{
    Tree tree;
    tree.root=NULL;

    makeEmptyList(&tree.leafList);
    if(size != 0)
    {
        BuildTreeFromArrayWithLeafListRec(arr, NULL, &tree.root, size, &tree.leafList);
    }
    return tree;
}

void BuildTreeFromArrayWithLeafListRec(int *arr, TreeNode* parentCurr,TreeNode **curr, int size, List *leafList)
{
    int leftSize=size/2, rightSize=size/2, midPlace=size/2;
    TreeNode *leftTNode=NULL, *rightTNode=NULL;
    int midValue=arr[midPlace];
    if(midValue == -1 || size == 0)
    {
        return;
    }
    else if(size==1)
    {
        insertDataToEndList(leafList,arr[0]);
        *curr=createNewTreeNode(midValue,parentCurr,NULL,NULL); //create root
    }
    else
    {
        *curr=createNewTreeNode(midValue,parentCurr,NULL,NULL); //create root
        BuildTreeFromArrayWithLeafListRec(arr, *curr, &leftTNode,leftSize, leafList); // Build left branch  
        BuildTreeFromArrayWithLeafListRec(arr+leftSize+1, *curr, &rightTNode,rightSize, leafList); // Build right branch
        (*curr)->left=leftTNode;
        (*curr)->right=rightTNode;
    }

}

TreeNode* createNewTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right)
{
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));

	res->data = data;
    res->parent = parent;
	res->left = left;
	res->right = right;

	return res;
}

//FreeTreeRec() function recursively free all tree nodes.
void freeTreeRec(TreeNode *root)
{
	if (root != NULL)
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root);
	}
}

void printTreeInOrder(Tree t)
{
    printTreeInOrderRec(t.root);
}

void printTreeInOrderRec(TreeNode *t)
{
    if (t == NULL)
        return;

    printTreeInOrderRec(t->left);
    printf ("%d ",t->data);
    printTreeInOrderRec(t->right);
}

void printLeafList(Tree tree)
{
    ListNode* curr=tree.leafList.head;
    while(curr != NULL)
    {
        printf("%d ",curr->data);
        curr=curr->next;
    }
}

TreeNode* findParent(Tree tr, int parentData, int branchSelect)
{
    TreeNode* parentNode;
    BOOL foundParent=FALSE;
    findParentRec(tr.root,&parentNode, parentData, branchSelect,&foundParent);
    return parentNode;
}


void findParentRec(TreeNode* curr, TreeNode** parentNode, int parentData, int branchSelect, BOOL *foundParent)
{
    //if(curr->left == NULL && curr->right == NULL)
    if(curr==NULL)
    {
        return;
    }
    else
    {
        findParentRec(curr->left,parentNode, parentData, branchSelect, foundParent); //Searching the parent data in the left branch
        if(*foundParent == TRUE)
            return;
        else
        {
            if(branchSelect == LEFT && curr->left==NULL && curr->data == parentData)
            {
                *parentNode=curr;
                *foundParent=TRUE;
                return;
            }    
            else if(branchSelect == RIGHT && curr->right==NULL && curr->data == parentData)
            {
                *parentNode=curr;
                *foundParent=TRUE;
                return;
            } 
        }          
        findParentRec(curr->right,parentNode, parentData, branchSelect, foundParent); //Searching the parent data in the right branch
    }
}

void makeEmptyList(List* lst)
{
	(*lst).head = (*lst).tail = NULL;
}

void insertDataToEndList(List* lst, int num) 
{
	ListNode* newTail;

	newTail = createNewListNode(num, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertDataToList(List* lst, int num, ListNode* prevNode) 
{
	ListNode* newNode;

	newNode = createNewListNode(num, prevNode->next);
	insertNodeToList(lst, prevNode,newNode);
}

void insertNodeToList(List* lst, ListNode * prevNode, ListNode * newNode) 
{
    if(prevNode == NULL)
    {
        lst->head=newNode;
    }
    else
    {
        prevNode->next = newNode;
    }  
    if(prevNode->next == NULL)
    {
        lst->tail = newNode;
    }
    newNode->next=prevNode->next;
}

ListNode* createNewListNode(int num, ListNode* next) {
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
    checkAlloc(res);
	res->data = num;
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

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}    

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

void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data)
{
    int leafListCounter;
    BOOL foundParent;
    foundParent=FALSE;
    leafListCounter=0;
    AddLeafRec(tr.root, p, &leafListCounter, branchSelect, data, &foundParent, &tr.leafList, NULL);
    return tr;
}

void AddLeafRec(TreeNode* currTreeNode, TreeNode *p, int* leafListCounter, int branchSelect, int data, BOOL* foundParent, List* leafList, ListNode** prevParentListNode)
{
    TreeNode* newTreeNode;

    if(currTreeNode == NULL)
        return;

    AddLeafRec(currTreeNode->left, p, leafListCounter, branchSelect, data, foundParent, leafList, prevParentListNode);
    if(currTreeNode == p)
    {
        if(currTreeNode->right == NULL && currTreeNode->left == NULL) 
        {
            if(*leafListCounter==0)
            {
                removeNodeFromLeafList(leafList,NULL,leafList->head);
            }
            else
            {
                removeNodeFromLeafList(leafList,*prevParentListNode,(*prevParentListNode)->next);
            }
        }
        if(prevParentListNode == NULL)
            insertDataToEndList(leafList,data); 
        else
        {
            insertDataToList(leafList,data,*prevParentListNode);
        }
        newTreeNode=createNewTreeNode(data,p,NULL,NULL); //Create the new tree node
        //Add new tree node to the relevent branch
        if(branchSelect == LEFT)
            currTreeNode->left=newTreeNode;
        else if(branchSelect == RIGHT)    
            currTreeNode->right=newTreeNode;                  
        *foundParent=TRUE;          
    }
    else
    {
        if(*foundParent==FALSE)
        {
            leafListCounter++;
            if(*leafListCounter==1)
            {
                *prevParentListNode=leafList->head;
            }
            else
            {
                if(prevParentListNode != NULL)
                    *prevParentListNode=(*prevParentListNode)->next;
            }
        }          
    }
    AddLeafRec(currTreeNode->right, p, leafListCounter, branchSelect, data, foundParent, leafList, prevParentListNode);
}
