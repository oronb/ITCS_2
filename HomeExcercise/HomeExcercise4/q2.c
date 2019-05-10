#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


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
void buildExpressionTreeRec(char* str, int strSize, TreeNode** tr);
double calcExpression(Tree tr);
void calcExpressionRec(TreeNode* tr,double* num);
TreeNode* createNewTreeNode(char data, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
int checkIfOperation(char ch);
int checkIfCharIsDig(char ch);
void printTreeInOrder(Tree t); //Copy from Keren's presentation
void printTreeInOrderRec(TreeNode *t);

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
        printTreeInOrder(tr);
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
    {
        printf("The input expression is not valid\n");
        freeTree(tr);
    }
}   

BOOL buildExpressionTree(char* str, Tree* tr)
{
    int strSize, countLeftBrace=0, countRightBrace=0, operatorCount=0;
    int i=1;
    char ch, ch1;
    BOOL expressionOK=TRUE;
    strSize=strlen(str);

    //Check if the expression is OK
    if(strSize >= 5)
    {
        //Check if the first charcter is left bracet
        if(str[0] == '(')
            countLeftBrace++;
        else
            expressionOK=FALSE;

        while(str[i] != '\0' && expressionOK==TRUE)
        {
            ch=str[i], ch1=str[i+1]; 
            if(checkIfCharIsDig(str[i]))
            {
                //Check that the number is one digit only
                if(checkIfCharIsDig(str[i+1]))
                    expressionOK=FALSE;
                else if(str[i+1] == '(')   
                    expressionOK=FALSE; 
            }
            else if(checkIfOperation(str[i]))
            {
                operatorCount++;
                //Check that there is no ) after an operation
                if(str[i+1] == ')')
                    expressionOK=FALSE;
                else if(checkIfOperation(str[i+1]))   
                    expressionOK=FALSE; 
            }
            else if(str[i] == '(')
            {
                //Check that there is no right bracet after left bracet
                if(str[i+1] == ')')
                    expressionOK=FALSE;
                else if(checkIfOperation(str[i+1]))  
                    expressionOK=FALSE; 
                else
                    countLeftBrace++;                               
            }
            else if(str[i] == ')')
            {
                //Check that there is no left bracet after right bracet
                if(str[i+1] == '(')
                    expressionOK=FALSE;
                //Check that there is no digit after left bracet  
                else if(checkIfCharIsDig(str[i+1]))
                    expressionOK=FALSE;
                //Check there is left brace before right brace
                else if(countLeftBrace == 0)
                    expressionOK=FALSE;    
                else if(countRightBrace + 1 > countLeftBrace)
                    expressionOK=FALSE;
                else    
                    countRightBrace++;                  
            }
            //Check if the character in the expression is valid
            else
                expressionOK=FALSE;  
            i++;    
        }
        //Check if the last character in expression is right bracet
        if(str[i-1] != ')')
            expressionOK=FALSE;
        //Check if there is no operator or no left or right bracets. If so, returns error    
        else if(operatorCount == 0 || countLeftBrace == 0 || countRightBrace == 0)
            expressionOK=FALSE;
        //Check if the number of left and right bracers is equal to the number of operators and that the number of the left and right bracers is equal   
        else if(operatorCount != countLeftBrace || operatorCount != countRightBrace || countLeftBrace != countRightBrace )
            expressionOK=FALSE;
    }
    else
    {
        expressionOK=FALSE;
    }
    
    if(expressionOK)
        buildExpressionTreeRec(str, strSize, &tr->root); 
    else
    {
        tr->root=createNewTreeNode('a',NULL,NULL);
    }
        
    return expressionOK;
}

void buildExpressionTreeRec(char* str, int strSize, TreeNode** tr)
{
    int rightBrCount=0, leftBrCount=0, i=1, flag=TRUE;
    TreeNode *leftTNode=NULL, *rightTNode=NULL;
    if(strSize==1)
    {
        if(checkIfCharIsDig(str[0]))
        {
            *tr=createNewTreeNode(str[0], NULL, NULL);
        }
        return;       
    }
    else
    {
        if(str[0] == '(' && str[strSize-1] == ')')
        {
            while (str[i] != '\0' && flag)
            {
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%')
                {
                    if(rightBrCount==leftBrCount)
                    {
                        *tr=createNewTreeNode(str[i], NULL, NULL);
                        buildExpressionTreeRec(str+i+1,strSize-i-2,&rightTNode);
                        buildExpressionTreeRec(str+1,i-1,&leftTNode);
                        (*tr)->right=rightTNode;
                        (*tr)->left=leftTNode;
                        flag=FALSE;
                    }
                }
                else if(str[i] == '(')
                    leftBrCount++;
                else if(str[i] == ')')
                    rightBrCount++;                   
                i++;
            }
        }   
    }   
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
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
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

int checkIfCharIsDig(char ch)
{
    return(ch-'0' >= 0 && ch-'0' <= 9);
}

int checkIfOperation(char ch)
{
    return(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
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