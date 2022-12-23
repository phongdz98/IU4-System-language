#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i, int ascending)
{
    int node = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (ascending)
    {
        if (l < n && arr[l] > arr[node])
            node = l;

        if (r < n && arr[r] > arr[node])
            node = r;
    }
    else
    {
        if (l < n && arr[l] < arr[node])
            node = l;

        if (r < n && arr[r] < arr[node])
            node = r;
    }

    if (node != i)
    {
        int temp = arr[i];
        arr[i] = arr[node];
        arr[node] = temp;

        heapify(arr, n, node, ascending);
    }
}

void heapSort(int arr[], int n, int ascending)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascending);

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0, ascending);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int ascending;
    printf("Do you want to sort in ascending or descending order (1 for ascending, 0 for descending)? ");
    scanf("%d", &ascending);

    heapSort(arr, n, ascending);

    printf("The sorted array is: ");
    printArray(arr, n);
}