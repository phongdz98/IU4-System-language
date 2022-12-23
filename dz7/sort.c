#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i, int ascending)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (ascending)
    {
        if (l < n && arr[l] < arr[largest])
            largest = l;

        if (r < n && arr[r] < arr[largest])
            largest = r;
    }
    else
    {
        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;
    }

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest, ascending);
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