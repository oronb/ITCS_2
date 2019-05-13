//checkString.h
#pragma once

typedef int BOOL;

#define FALSE 0
#define TRUE 1

//Declare functions
int checkIfOperator(char ch);
int checkIfCharIsDig(char ch);
BOOL checkExpression(char* str, int strSize);
int findMidOperatorInString(char* str, int strSize);