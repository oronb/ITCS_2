#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

/*
Usually don't use return value, but with parameters that returns value
*/
#define ERROR -1;
 
typedef struct treenode
{
    int data;
    struct treenode* left;
    struct treenode* right;
} TNODE;

typedef struct tree
{
    TNODE* root;
} TREE;

//Declare Functions
int CountNode(TREE t);


int CountNode(TREE t)
{
    int res;
    res=CountNodeRec(t.root);
    return res;
}

void CountNodeRec(TNODE* t, int *count)
{
    if(t==NULL)
    {
        return 0;
    }
    else if(!t->left && !t->right)
    {
        *count++;
        return;
    }    
    else
    {
        if(t->left)
        {
            CountNodeRec(t->right,count);
        }
        if(t->right)
        {
            CountNodeRec(t->left,count);
        }
    }
    
}

int countNodes(TREE tr)
{
    return countNodesRec(tr.root);
}

int countNodesRec(TNODE* curr)
{
    int countLeft, countRight;
    if(curr==NULL)
        return 0;

    countLeft=countNodesRec(curr->left);
    countRight=countNodesRec(curr->right);
    return(countLeft + countRight + 1);
}

int countNodes2(TREE tr)
{
    int counter=0;
    countNodesRec2(tr.root,&counter);
    return counter;
}

void countNodesRec2(TNODE* curr, int *count)
{
    if(curr==NULL)
        return;
    (*count)++;
    countNodesRec2(curr->left,count);
    countNodesRec2(curr->right,count);
}


double calcAvgOfSmallOddLeaves(TREE t)
{
    if (t.root=NULL)
        return ERROR;
    int counter=0,sum=0;
    calcAvgOfSmallOddLeavesRec(t.root, &counter, &sum);
    return((double)sum/counter);
}

void calcAvgOfSmallOddLeavesRec(TNODE* curr, int* counter, int* sum)
{
    if(!curr)
        return;
    if (curr->data < 5)
    {
        (*counter)++;
        sum+=curr->data;   
    }
    calcAvgOfSmallOddLeavesRec(curr->left, counter, sum);
    calcAvgOfSmallOddLeavesRec(curr->right, counter, sum);
}

int* shto(TREE tr, int* size)
{
    int *res, i=0;
    *size=countNodes2(tr);
    if(*size==0)
    {
        return ERROR;
    }
    else
    {
        res=(int*)malloc(*size * sizeof(int));
        shtoRec(tr.root, res);
    }
}    

void shtoRec(TNODE *root, int* arr)
{
    if(root == NULL)
    {
        return;
    }
    shtoRec(root->left, arr+1);
    arr[0]=root->data;
    shtoRec(root->right, arr+1);
}

/*A:1.Counter tzmatim o(n)
    2.Allocate array o(1)
    3.Fill the array o(n)
    n+1+n => o(n)

B:1.Allocate 1
  2.Fill and when comes to logsize=physicalsize*2
  and realloc
  nlog(n)
*/

int bigDaddy(TREE t)
{
    int res, count=0, sum=0, val=0;
    if(!t.root)
    {
        return ERROR;
    }
    else
    {
        bigDaddyRec(t.root, &count, &sum, &val);
    }
}

void bigDaddyRec(TNODE* curr, int* count, int* sum, int* val)
{
    double avg=0;
    if(curr==NULL)
    {
        return;
    }
    else
    {
        (*count)++;
        (*sum)+=curr->data;
        bigDaddyRec(curr->right, &count, &sum, &val);
        bigDaddyRec(curr->left, &count, &sum, &val);
        avg=(*sum)/(*count);
    }
    
}