#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

/*
Two-directional list
When Working with two direction list there is no need for temp when deleting node
*/

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

typedef struct dlistnode
{
    int data;
    struct dlistnode *prev;
    struct dlistnode *next;
} DLNODE;

typedef struct dlist
{
    DLNODE *head;
    DLNODE *tail;
} DLIST;

//Delete node from tree
void removeFromDList(DLNODE *curr)
{
    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;
    free(curr);
}