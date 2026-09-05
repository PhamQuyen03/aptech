#include <stdio.h>

int main()
{
    int n;

    // Nhập kích thước ma trận
    do
    {
        printf("Nhập kích thước ma trận n: ");
        scanf("%d", &n);
    } while (n <= 0 || n > 100);

    int a[n][n];

    // Nhập ma trận
    printf("\nNhập các phần tử của ma trận:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    // In ma trận
    printf("\nMa trận vừa nhập:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }

    // Đường chéo chính
    int tongChinh = 0;

    printf("\nĐường chéo chính: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i][i]);
        tongChinh += a[i][i];
    }

    printf("\nTổng đường chéo chính = %d\n", tongChinh);

    // Đường chéo phụ
    int tongPhu = 0;

    printf("\nĐường chéo phụ: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i][n - 1 - i]);
        tongPhu += a[i][n - 1 - i];
    }

    printf("\nTổng đường chéo phụ = %d\n", tongPhu);

    return 0;
}