#include <stdio.h>

int main()
{
    int n;
    do
    {
        printf("Nhập số chiều dài của mảng: ");
        scanf("%d", &n);
    } while (n <= 0);

    int arr[n];

    // Nhập mảng
    printf("Nhập %d phần tử:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    // In mảng
    printf("\nMảng vừa nhập: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Tìm lớn nhất và nhỏ nhất
    int max = arr[0];
    int min = arr[0];

    int posMax = 0;
    int posMin = 0;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            posMax = i;
        }

        if (arr[i] < min)
        {
            min = arr[i];
            posMin = i;
        }
    }

    // In mảng nghịch đảo
    printf("\nMảng sau khi nghịch đảo: ");
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
    printf("\n======================================\n");

    // In lớn nhất và nhỏ nhất
    printf("\nPhần tử lớn nhất là: %d", max);
    printf("\nVị trí của phần tử lớn nhất là: %d", posMax);
    printf("\n======================================\n");
    printf("\nPhần tử nhỏ nhất là: %d", min);
    printf("\nVị trí của phần tử nhỏ nhất là: %d", posMin);

    printf("\n======================================\n");

    // Tìm giá trị trong mảng
    int x;
    bool notFound = true;

    printf("\n\nNhập giá trị muốn tìm: ");
    scanf("%d", &x);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            printf("Giá trị %d nằm ở vị trí arr[%d]\n", x, i);
            notFound = false;
        }
    }

    if (notFound)
    {
        printf("Không tìm thấy giá trị %d trong mảng.\n", x);
    }

    return 0;
}