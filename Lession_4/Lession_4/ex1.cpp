#include <stdio.h>

int main()
{
    int a[10];
    int x;
    int dem = 0;

    // Nhập mảng
    printf("Nhập 10 số nguyên:\n");

    for (int i = 0; i < 10; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    // Nhập số x
    printf("Nhập số x: ");
    scanf("%d", &x);

    // Đếm số lần x xuất hiện
    for (int i = 0; i < 10; i++)
    {
        if (a[i] == x)
        {
            dem++;
        }
    }

    // In kết quả
    printf("Số %d xuất hiện %d lần trong mảng.\n", x, dem);

    return 0;
}