#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define SIZE 100

typedef struct listNode  {
	int data;
	struct listNode* next;
} ListNode;

typedef struct list  {
	ListNode* head;
	ListNode* tail;
} List;

typedef struct  treeNode {
	int data;
	struct treeNode* parent;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree{
TreeNode* root;
List leafList;   /*רשימה מקושרת של כל העלים בעץ*/ 
} Tree;

//Declare functions
Tree BuildTreeFromArray( int  *arr, int  size);
Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data);
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
Tree AddLeaf(tr, p, branchSelect, data);
void printTreeInorder(tree); //Copy from Keren's presentation
void printLeafList(tree); //Check if exists in Keren's

void main()

{
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode * p;
    int parentData, data, branchSelect;

    printf("Please enter the number of items: ");
    scanf("%d", &size);

    for(i=0; i<size; i++)
        scanf("%d", &arr[i]);

    scanf("%d%d%d", &parentData, &data, &branchSelect);

    tr = BuildTreeFromArrayWithLeafList(arr, size);//the array is given as described in question 1
    //scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in branchSelect
    p = findParent(tr, parentData, branchSelect);
    tr = AddLeaf(tr, p, branchSelect, data);
    printTreeInorder(tr); //Print the tree in-order (LDR)
    printLeafList(tr); //Print the leaves from left to right

    freeTree(tr);

}