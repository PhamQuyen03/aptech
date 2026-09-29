#include <stdio.h>

int main()
{
    int n, i, dem;

    do
    {
        printf("Nhập số nguyên dương n (> 2): ");
        scanf("%d", &n);
    } while (n <= 2);

    dem = 0;
    i = 1;
    int count = n / 2 + 1;

    while (i <= count)
    {
        if (n % i == 0)
        {
            dem++;
        }
        i++;
    }

    if (dem == 1)
    {
        printf("%d là số nguyên tố", n);
    }
    else
    {
        printf("%d không phải là số nguyên tố", n);
    }

    return 0;
}
