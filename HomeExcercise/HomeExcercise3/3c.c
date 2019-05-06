void DeleteValue(ArrayList *lst, int value);
void makeEmptyList(ArrayList* lst);
LIST getlist();
void insertDataToEndList(ArrayList* lst, int **arr, int size);
ArrayNode* createNewListNode(int **arr, int size, ArrayNode* next);
void insertNodeToEndList(ArrayList* lst, ArrayNode * newTail);
int isEmptyList(const ArrayList* lst);
void freeList(const ArrayList* lst);
void checkAlloc(void* val);
