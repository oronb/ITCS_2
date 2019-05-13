//tree.h

#pragma once

typedef int BOOL;

#define FALSE 0
#define TRUE 1
#define SIZE 100

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{
    TreeNode *root;
}Tree;

//Declare functions
BOOL buildExpressionTree(char* str, Tree* tr);
TreeNode* buildExpressionTreeRec(char* str, int strSize);
double calcExpression(Tree tr);
void calcExpressionRec(TreeNode* tr,double* num);
void freeTree(Tree tr);
TreeNode* createNewTreeNode(char data, TreeNode* left, TreeNode* right);
void freeTreeRec(TreeNode *root);
void printTreeInOrder(Tree t);
void printTreeInOrderRec(TreeNode *t);