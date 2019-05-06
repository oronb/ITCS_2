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
void printTreeInorder(tree); //Copy from Keren's presentation
void printLeafList(tree); //Check if exists in Keren's presentation

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

    printTreeInorder(tr); //Print the tree in-order (LDR)

    freeTree(tr);

}