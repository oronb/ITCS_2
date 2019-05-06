#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define SIZE 100

typedef struct treeNode
{
    unsigned int data;  
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{ 
       TreeNode *root;
}Tree;

//Declare Functions
Tree BuildTreeFromArray( int  *arr, int  size);
void BuildTreeFromArrayHelper(int *arr, TreeNode **curr, int size);
void printTreeInOrder(Tree t); //Copy from Keren's presentation
void printTreeInOrderRec(TreeNode *t);
void printLeafList(Tree tree); //Check if exists in Keren's presentation
TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right); //Create new tree node
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);

void main()
{
    int size, i;
    int arr[SIZE];
    Tree tr;

    printf("Please enter the number of items: ");
    scanf("%d", &size);

    for(i=0; i<size; i++)
        scanf("%d", &arr[i]);

    tr = BuildTreeFromArray(arr, size);

    printf("The tree in inorder (LDR) format:\n");

    printTreeInOrder(tr); //Print the tree in-order (LDR)

    freeTree(tr);

}

Tree BuildTreeFromArray( int  *arr, int  size)
{
    Tree tree;
    tree.root=NULL;
    if(size != 0)
    {
        BuildTreeFromArrayHelper(arr, &tree.root, size);
    }
    return tree;
}

void BuildTreeFromArrayHelper(int *arr, TreeNode **curr, int size)
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
        *curr=createNewTreeNode(midValue,NULL,NULL); //create root
        BuildTreeFromArrayHelper(arr+leftSize+1, &rightTNode,rightSize); // Build right branch
        BuildTreeFromArrayHelper(arr,&leftTNode,leftSize); // Build left branch  
        (*curr)->right=rightTNode;
        (*curr)->left=leftTNode;
    }
}

void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right)
{
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));

	res->data = data;
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