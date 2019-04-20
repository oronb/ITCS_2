//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list_node
{
	char*  dataPtr;
	struct list_node*  next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

typedef struct student
{
	List first;
	int grade;  
} Student;


//Declare functions
void freeList(List* lst);
void makeEmptyList(List* lst);
void insertNodeToEndList(List* lst, ListNode * newTail);
void insertDataToEndList(List* lst, char ch);
ListNode* createNewListNode(char ch, ListNode * next);
int isEmptyList(const List* lst);
Student unScramble (List  lst);
void printList(List* lst);
void printStudent(Student* student);
void deleteNodeFromList( List* list,ListNode* prevNode, ListNode* nodeToBeDeleted);
void checkAlloc(void* val);

void main()
{
    List lst;
    Student student;
    char ch;

    makeEmptyList(&lst);

    printf("Please enter the scrambled student:\n");

    ch = (char)getchar();
    while(ch != '\n')
    { 
        insertDataToEndList(&lst, ch);
        ch = (char)getchar();
    }
    student = unScramble(lst);
    printStudent(&student);
    
    freeList(&student.first);
}

Student unScramble (List lst)
{
    //Define variables
    Student student; //The student
    ListNode* currNode = lst.head; //Previous node
    ListNode* prevNode = lst.head; //Current node
    char charCheckCurr; //Contains the char that dataPtr points to in the current node
    char charCheckPrev; //Contains the char that dataPtr points to in the previous node
    int grade=0; //grade of the student
    int dig; //The dig that dataPtr points to (After converting it from char to int)
    int digPlace=1; //The digit place in the grade

    while(currNode != NULL)
    {
        charCheckCurr=*(currNode->dataPtr); 
        charCheckPrev=*(prevNode->dataPtr);

        //Checks if the current node's dataPtr points to a digit or a letter
        if (charCheckCurr - '0' >= 0 && charCheckCurr - '0' <= 9)
        {
            //Insert digit to the grade
            dig=charCheckCurr - '0';
            grade=grade * digPlace + dig;
            digPlace*=10;

            //Remove node from list
            deleteNodeFromList(&lst, prevNode, currNode);
        }
        else if (charCheckCurr >= 'a' && charCheckCurr <= 'z')
        {
            prevNode=currNode;
        }
        
        //Checks if the previous node is a digit. If so,
        if (charCheckPrev - '0' >= 0 && charCheckPrev - '0' <= 9)
        {
            prevNode=prevNode->next;
        }    

        currNode=currNode->next;
    }   
    student.first=lst;
    student.grade=grade;
    return student; 
}
//insertDataToEndList gets a list and data, and inserts it to end of the list
void insertDataToEndList(List* lst, char ch) {
	ListNode* newTail;

	newTail = createNewListNode(ch, NULL);
	insertNodeToEndList(lst, newTail);
}

//The function createNewListNode gets data and the next list node, and creates new list node from the data
ListNode* createNewListNode(char ch, ListNode* next) 
{
	ListNode* res;

	res = (ListNode*)malloc(sizeof(ListNode));
    checkAlloc(res);
	res->dataPtr = (char*)malloc(sizeof(char));
    checkAlloc(res);
	*(res->dataPtr) = ch;
	res->next = next;

	return res;
}

//insertNodeToEndList gest a list and a new tail, and 
void insertNodeToEndList(List* lst, ListNode * newTail) {
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

//isEmptyList function checks if a list is empty, and returns 1 if the list is empty
int isEmptyList(const List* lst)
{
    return lst->head == NULL;
}

//freeList function free dynamic allocation of a list
void freeList(List* lst)
{

    //Define variables
    ListNode* currNode=lst->head;
    ListNode* tempNode;

    if(lst->head != NULL)
    {
        while(currNode != NULL)
        {
            tempNode=currNode;
            free(tempNode->dataPtr);
            free(tempNode);
            currNode=currNode->next;
        }
    }

}

void printList(List* lst)
{
	ListNode* currentNode=lst->head;
	while(currentNode != NULL)
    {
		printf("%c",*(currentNode->dataPtr));
		currentNode=currentNode->next;
	}
    printf("\n");
}

void printStudent(Student* student)
{
    printf("Name: ");
    printList(&(student->first));
    printf("Grade: %d", student->grade);
    printf("\n");
}

void makeEmptyList(List* lst)
{
	(*lst).head = (*lst).tail = NULL;
}

void deleteNodeFromList( List* list,ListNode* prevNode, ListNode* nodeToBeDeleted)
{
    //Define variables
    char* tempDataPtr;
    ListNode * tempNode;

    //Set the node to be deleted into temp variables
    tempNode = nodeToBeDeleted;
    tempDataPtr=nodeToBeDeleted->dataPtr;

    //Set the prev node to point to the node after the node to be deleted
    if((list->head == nodeToBeDeleted) && (prevNode == NULL))
    {
        list->head=nodeToBeDeleted->next;
    }
    else
    {
        prevNode->next = nodeToBeDeleted->next;
    }
    
    if(list->tail == nodeToBeDeleted)
    {
        list->tail = prevNode;
    }
    free(tempDataPtr);
    free(tempNode);
}

void checkAlloc(void* val )
{
    if (!val) {
        puts("Allocation error\n");
        exit(0);
    }
}    