#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "checkString.h"

//buildExpressionTree build tree from string of a Mathematical expression and returns if the expression is ok
BOOL buildExpressionTree(char* str, Tree* tr)
{
    int strSize; //String size
    BOOL expressionOK; //Check if expression is ok
    strSize=strlen(str);

    expressionOK=checkExpression(str,strSize);

    if(expressionOK)
        tr->root=buildExpressionTreeRec(str, strSize);
    else
    {
        tr->root=createNewTreeNode('a',NULL,NULL);
    }

    return expressionOK;
}

//buildExpressionTreeRec builds Tree from mathematical expression in recursion
TreeNode* buildExpressionTreeRec(char* str, int strSize)
{
    TreeNode* tr;
    int i; //index
    if(strSize==1)
    {
        if(checkIfCharIsDig(str[0]))
        {
            tr=createNewTreeNode(str[0], NULL, NULL);
        }
    }
    else
    {
        i=findMidOperatorInString(str, strSize);
        tr=createNewTreeNode(str[i], NULL, NULL);
        tr->right=buildExpressionTreeRec(str+i+1,strSize-i-2);
        tr->left=buildExpressionTreeRec(str+1,i-1);
    }
    return tr;
}

double calcExpression(Tree tr)
{
    double calc=0;
    calcExpressionRec(tr.root, &calc);
    return calc;
}

void calcExpressionRec(TreeNode* tr,double* num)
{
    char ch=tr->data;
    double rightCalc;
    double leftCalc;

    if(checkIfCharIsDig(ch))
    {
        *num=ch - '0';
        return;
    }
    else
    {
        if (checkIfOperator((ch)))
        {
            calcExpressionRec(tr->right,&rightCalc); //Calculate right branch
            calcExpressionRec(tr->left,&leftCalc); //Calculate left branch
            switch (ch)
            {
                case '+':
                    *num=leftCalc + rightCalc;
                    break;
                case '-':
                    *num=leftCalc - rightCalc;
                    break;
                case '*':
                    *num=leftCalc * rightCalc;
                    break;
                case '/':
                    *num=leftCalc / rightCalc;
                    break;
                case '%':
                    *num=(int)leftCalc % (int)rightCalc;
                    break;
            }
        }

    }

}

void freeTree(Tree tr)
{
    freeTreeRec(tr.root);
}

TreeNode* createNewTreeNode(char data, TreeNode* left, TreeNode* right)
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