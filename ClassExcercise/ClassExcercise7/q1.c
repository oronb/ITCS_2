#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


#define ERROR -1
#define max(x, y) (((x) >= (y)) ? (x) : (y))

typedef struct TreeNode
{
	int data;
	struct TreeNode* right;
	struct TreeNode* left;
}TreeNode;

typedef struct Tree
{
	TreeNode* root;
}Tree;

int calcLeaves(Tree tr);
int calcLeavesRec(TreeNode* tr);
void printLeaves(Tree tr);
void printLeavesRec(TreeNode* tr);
int treeDiameter(Tree tr);
int treeDiameterRec(TreeNode* tr);
TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right);
Tree BuildTree();

void FreeTree(Tree tr);
void FreeTreeRec(TreeNode *root);

void main()
{
	Tree tr = BuildTree();

	printf("number of leaves in tree is: %d\n", calcLeaves(tr));
	printf("The leaves are:\n");
	printLeaves(tr);
	printf("\nTree diameter is: %d\n", treeDiameter(tr));

	FreeTree(tr);
}

int calcLeaves(Tree tr)
{
    int numOfLeaves;
    numOfLeaves=calcLeavesRec(tr.root);
    return numOfLeaves;
}

int calcLeavesRec(TreeNode* tr)
{
    int res=0;
    if(tr == NULL)
    {
        return 0;
    }
    else if(!tr->left && !tr->right)
    {
        return 1;
    }
    else
    {
        res+=calcLeavesRec(tr->left);
        res+=calcLeavesRec(tr->right);
        return res;
    }
    
}    
void printLeaves(Tree tr)
{
    printLeavesRec(tr.root);
}

void printLeavesRec(TreeNode* tr)
{
    if(tr == NULL)
    {
        return;
    }
    else
    {
        if(!tr->right && !tr->left)
        {
            printf("%d",tr->data);
            return;
        }    
        else
        {
            printLeavesRec(tr->left);
            printLeavesRec(tr->right);
        }     
    }
}

int treeDiameter(Tree tr)
{
    int maxRight=0;
    int maxLeft=0;
    int diameter=0;
    int leftDiameter=0;
    int rightDiameter=0;

    if(tr.root != NULL)
    {
        if(tr.root->right)
        {
            maxRight=treeDiameterRec(tr.root->right,&rightDiameter)+1;
            printf("max right is: %d", maxRight);
        } 
        if(tr.root->left)
        {
            maxLeft=treeDiameterRec(tr.root->left,&leftDiameter)+1;
            printf("max left is: %d", maxLeft);
        }
        if(maxRight+maxLeft > leftDiameter && maxRight+maxLeft > rightDiameter) 
            return maxRight+maxLeft;
        else
        {
            if leftDiameter >= rightDiameter)
                return leftDiameter;
            else
                return rightDiameter;              
        }
            
    } 

    
    return(diameter);   
}

int treeDiameterRec(TreeNode* tr, int* treeDiameter)
{
    int right, left ,treeDiameterMax;
    if(!tr->right && !tr->left)
    {
        return 0;
    }
    else
    {   
        if(tr->right)
            right=treeDiameterRec(tr->right)+1;
        else
        {
            right=0;
        }
        
        if(tr->left)
            left=treeDiameterRec(tr->left)+1;
        else
        {
            left=0;
        }
        treeDiameterMax=left+right;           
        return(max(left,right));
    }


}

TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right)
{
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));

	res->data = data;
	res->left = left;
	res->right = right;

	return res;
}

Tree BuildTree()
{
	Tree T;
	TreeNode *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;

	n1 = createNewTreeNode(3, NULL, NULL);
	n2 = createNewTreeNode(12, n1, NULL);
	n3 = createNewTreeNode(2, NULL, n2);
	n4 = createNewTreeNode(1, NULL, NULL);
	n5 = createNewTreeNode(8, NULL, n4);
	n6 = createNewTreeNode(15, NULL, n5);
	n7 = createNewTreeNode(4, n3, n6);
	n8 = createNewTreeNode(6, NULL, NULL);
	n9 = createNewTreeNode(10, n7, n8);

	T.root = n9;

	return T;
}

void FreeTree(Tree tr)
{
	FreeTreeRec(tr.root);
}

void FreeTreeRec(TreeNode *root)
{
	if (root != NULL)
	{
		FreeTreeRec(root->left);
		FreeTreeRec(root->right);
		free(root);
	}
}
/*
int maxNum(Tree tr)
{
    return maxNumRec(tr.root);
}

int maxNumRec(TreeNode *nodep)
{
    if(!nodep->left && !nodep->right)
    {
        return nodep->data;
    }
    if(!nodep->right)
    {
        return max(nodep->data,maxNumRec(nodep->left));
    }
    if(!nodep->left)
    {
       return max(nodep->data,max(maxNumRec(nodep->right)));
    }
}

//Returns how much special tzmatim there is
int numSnodes(Tree tr)
{
    int sumLeaves;
    return numSnodesRec(tr.root, &sumLeaves);
}

int numSnodesRec(TreeNode *nodep, int* sum)
{
    int sumLL,sumLR;
    int sumNodesL,sumNodesR;

    if(!nodep)
    {
        *sum=0;
        return 0;
    }
    if(!nodep->right && !nodep->left)
    {
        *sum=nodep->data;
        return 0;
    }
    sumNodesL=numSnodesRec(nodep->left,&sumLL);
    sumNodesR=numSnodesRec(nodep->right,&sumLR);
    *sum=sumLL+sumLR;
    if(*sum <= nodep->data)
        return sumNodesL+sumNodesR+1;
    else
    {
        return sumNodesL+sumNodesR;
    }
    
}
*/