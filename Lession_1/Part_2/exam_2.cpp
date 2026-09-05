#include <stdio.h>

int main()
{
    int a, b, c;
    int max;

    printf("Nhập số nguyên a: ");
    scanf("%d", &a);

    printf("Nhập số nguyên b: ");
    scanf("%d", &b);

    printf("Nhập số nguyên c: ");
    scanf("%d", &c);

    if (a >= b && a >= c)
    {
        max = a;
    }
    else if (b >= a && b >= c)
    {
        max = b;
    }
    else
    {
        max = c;
    }

    printf("Số lớn nhất là: %d\n", max);

    return 0;
}