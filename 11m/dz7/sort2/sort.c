#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int showMenu(int *menuChoosedItemPtr)
{
    printf("\nMENU:\n");
    printf("1. Input\n");
    printf("2. Print\n");
    printf("3. Ascending\n");
    printf("4. Descending\n");
    printf("5. Exit\n");
    scanf("%d", menuChoosedItemPtr);
    return 0;
}

int heapSwap(char *str1_ptr, char *str2_ptr)
{
    char tmp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = tmp;
    return 0;
}

int heapAtomAsc(char *atomTopHeapPtr, int i, int n)
{
    int great = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && atomTopHeapPtr[left] > atomTopHeapPtr[great])
    {
        great = left;
    }
    if (right < n && atomTopHeapPtr[right] > atomTopHeapPtr[great])
    {
        great = right;
    }
    if (great != i)
    {
        heapSwap(&atomTopHeapPtr[i], &atomTopHeapPtr[great]);
        heapAtomAsc(atomTopHeapPtr, great, n);
    }
    return 0;
}

int heapAtomDesc(char *atomTopHeapPtr, int i, int n)
{
    int least = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && atomTopHeapPtr[left] < atomTopHeapPtr[least])
    {
        least = left;
    }
    if (right < n && atomTopHeapPtr[right] < atomTopHeapPtr[least])
    {
        least = right;
    }
    if (least != i)
    {
        heapSwap(&atomTopHeapPtr[i], &atomTopHeapPtr[least]);
        heapAtomDesc(atomTopHeapPtr, least, n);
    }
    return 0;
}

int exitHeapSort(char *topHeapPtr)
{
    free((void *)topHeapPtr);
    return 1;
}

int heapEnter(char *topHeapPtr)
{
    printf("Input data:");
    scanf(" %127[^\n]s", topHeapPtr);
    return 0;
}

int heapPrint(char *topHeapPtr)
{
    if (strlen(topHeapPtr) == 0)
    {
        printf("Array is empty!!!\n");
    }
    else
    {
        printf("Array: %s \n", topHeapPtr);
    }
    return 0;
}

int heapAsc(char *topHeapPtr)
{
    int nHeap;
    nHeap = strlen(topHeapPtr);
    if (nHeap == 0)
    {
        printf("Array is empty!!!\n");
    }
    else
    {
        for (int i = nHeap / 2 - 1; i >= 0; i--)
        {
            heapAtomAsc(topHeapPtr, i, nHeap);
        }
        for (int i = nHeap - 1; i >= 0; i--)
        {
            heapSwap(&(topHeapPtr[0]), &(topHeapPtr[i]));
            heapAtomAsc(topHeapPtr, 0, i);
        }
        printf("Succesfully sorted ascending...\n");
        heapPrint(topHeapPtr);
    }
    return 0;
}

int heapDesc(char *topHeapPtr)
{
    int nHeap;
    nHeap = strlen(topHeapPtr);
    if (nHeap == 0)
    {
        printf("Array is empty!!!\n");
    }
    else
    {
        for (int i = nHeap / 2 - 1; i >= 0; i--)
        {
            heapAtomDesc(topHeapPtr, i, nHeap);
        }
        for (int i = nHeap - 1; i >= 0; i--)
        {
            heapSwap(&(topHeapPtr[0]), &(topHeapPtr[i]));
            heapAtomDesc(topHeapPtr, 0, i);
        }
        printf("Succesfully sorted descending...\n");
        heapPrint(topHeapPtr);
    }
    return 0;
}

int main()
{
    char *heapPtr;
    heapPtr = (char *)malloc(128 * sizeof(char));
    int doProgram = 0;
    int choosedParameter = 5;
    while (doProgram == 0)
    {
        showMenu(&choosedParameter);
        printf("\n");
        switch (choosedParameter)
        {
        case 1:
        {
            doProgram = heapEnter(heapPtr);
            break;
        }
        case 2:
        {
            doProgram = heapPrint(heapPtr);
            break;
        }
        case 3:
        {
            doProgram = heapAsc(heapPtr);
            break;
        }
        case 4:
        {
            doProgram = heapDesc(heapPtr);
            break;
        }
        case 5:
        {
            doProgram = exitHeapSort(heapPtr);
            break;
        }
        default:
            printf("Invalid entered menu option. It should be 1-5...\n");
        }
    }
    return 0;
}