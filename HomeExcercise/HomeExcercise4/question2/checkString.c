#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "checkString.h"

BOOL checkIfOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}


int checkIfCharIsDig(char ch)
{
    return(ch-'0' >= 0 && ch-'0' <= 9);
}

BOOL checkExpression(char* str, int strSize)
{
    BOOL expressionOK=TRUE;
    int i=1;
    int countLeftBrace=0, countRightBrace=0, operatorCount=0;
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
            if(checkIfCharIsDig(str[i]))
            {
                //Check that the number is one digit only
                if(checkIfCharIsDig(str[i+1]))
                    expressionOK=FALSE;
                else if(str[i+1] == '(')
                    expressionOK=FALSE;
            }
            else if(checkIfOperator(str[i]))
            {
                operatorCount++;
                //Check that there is no ) after an operation
                if(str[i+1] == ')')
                    expressionOK=FALSE;
                else if(checkIfOperator(str[i+1]))
                    expressionOK=FALSE;
            }
            else if(str[i] == '(')
            {
                //Check that there is no right bracet after left bracet
                if(str[i+1] == ')')
                    expressionOK=FALSE;
                else if(checkIfOperator(str[i+1]))
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
    return expressionOK;
}

int findMidOperatorInString(char* str, int strSize)
{
    BOOL flag=TRUE;
    int rightBrCount=0,leftBrCount=0;
    int i=1;

    if(str[0] == '(' && str[strSize-1] == ')')
    {
        while (str[i] != '\0' && flag)
        {
            if (checkIfOperator(str[i]))
            {
                if(rightBrCount==leftBrCount)
                    flag=FALSE;
            }
            else if(str[i] == '(')
            {
                leftBrCount++;
            }
            else if(str[i] == ')')
            {
                rightBrCount++;

            }
            i++;
        }
    }
    return i-1;
}