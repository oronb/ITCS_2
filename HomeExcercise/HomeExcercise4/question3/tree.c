#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <list.h>

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

typedef struct treeNode {
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
void checkAlloc(void* val );
Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data);
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);
void BuildTreeFromArrayWithLeafListRec(int *arr, TreeNode **curr, int size);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
void findParentRec(TreeNode* curr, TreeNode** parentNode, int parentData, int branchSelect, BOOL *foundParent);
Tree AddLeaf(tr, p, branchSelect, data);
void printTreeInOrder(Tree t); //Copy from Keren's presentation
void printTreeInOrderRec(TreeNode *t);
void printLeafList(Tree tree); 
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
void findParentRec(TreeNode* curr, TreeNode** parentNode, int parentData, int branchSelect, BOOL *foundParent);
Tree BuildTreeFromArrayWithLeafList( int  *arr, int  size);
{
    Tree tree;
    tree.root=NULL;
    if(size != 0)
    {
        BuildTreeFromArrayWithLeafListRec(arr, &tree.root, size);
    }
    return tree;
}

void BuildTreeFromArrayWithLeafListRec(int *arr, TreeNode **curr, int size)
{
    int leftSize=size/2, rightSize=size/2, midPlace=size/2;
    TreeNode *leftTNode=NULL, *rightTNode=NULL;
    int midValue=arr[midPlace];
    if(midValue == -1 || size == 0)
    {
        return;
    }
    else
    {
        *curr=createNewTreeNode(midValue,NULL,NULL,curr); //create root
        BuildTreeFromArrayWithLeafListRec(arr+leftSize+1, &rightTNode,rightSize); // Build right branch

        BuildTreeFromArrayWithLeafListRec(arr,&leftTNode,leftSize); // Build left branch  
        (*curr)->right=rightTNode;
        (*curr)->left=leftTNode;
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