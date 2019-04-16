const int MAX_NAME_LEN = 100;
const int MAX_NUM_OF_CHILDREN = 20;

struct family {
    char name[MAX_NAME_LEN];
    int numChildren;
    int ages[MAX_NUM_OF_CHILDREN];
};
typedef struct family Family;

void switchArr(Family fams[], int first_index, int second_index);
void bigFamiliesFirst(Family fams[], int size, int bigSize);
void printArrFamily(Family fams[], int size);

int main()
{

}

void bigFamiliesFirst(Family fams[], int size, int bigSize)
{
    int left=0,right=size-1,i;
    for(i=0;i<size;i++)
    {
        if(fams[left].numChildren > bigSize)
            left++;
        else if(fams[right].numChildren <= bigSize)
            right--;
        else if ((fams[left].numChildren <= bigSize) && (fams[right].numChildren > bigSize))
        {
            switchArr(fams,left,right);           
        }
    }
}

void switchArr(Family fams[], int first_index, int second_index)
{
    Family temp;
    temp=arr[first_index];
    arr[first_index]=arr[second_index];
    arr[second_index]=temp;
}

void printArr(Family fams[], int size)
{
    int i;
    for(i=0;i<size;i++)
        printf("family %d: \n",i+1);
        printf("name: %s", fams[i].name );
        printf("Number of children: ",fams[i].numChildren);
        printf("Ages: ");
}