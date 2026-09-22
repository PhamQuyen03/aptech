#include <stdio.h>

#define SIZE 7

int main()
{
    int arr[SIZE] = {23, 41, 12, 8, 34, 56, 19};

    for (int i = 0; i < SIZE - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}