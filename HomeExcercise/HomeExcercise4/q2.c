#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


typedef int BOOL;

#define FALSE 0
#define TRUE 1
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

//Declare functions
BOOL buildExpressionTree(char* str, Tree* tr);
double calcExpression(tr);
void freeTree(tr);

void main()
{
    char str[SIZE];
    Tree tr;
    double res;
    BOOL expressionOK;

    printf("Please enter the expression: ");

    gets(str);

    expressionOK = buildExpressionTree(str, &tr);

    if(expressionOK == TRUE)
    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
    {
        printf("The input expression is not valid\n");
        freeTree(tr);
    }
}   