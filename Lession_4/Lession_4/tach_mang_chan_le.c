#include <stdio.h>

int main()
{
    int a[10];
    int chan[10];
    int le[10];

    int soChan = 0;
    int soLe = 0;

    // Nhập mảng
    printf("Nhập 10 số nguyên:\n");

    for (int i = 0; i < 10; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    // Tách mảng chẵn và mảng lẻ
    for (int i = 0; i < 10; i++)
    {

        if (a[i] % 2 == 0)
        {
            chan[soChan] = a[i];
            soChan++;
        }
        else
        {
            le[soLe] = a[i];
            soLe++;
        }
    }

    // In mảng chẵn
    printf("\nMảng số chẵn: ");

    for (int i = 0; i < soChan; i++)
    {
        printf("%d ", chan[i]);
    }

    // In mảng lẻ
    printf("\nMảng số lẻ: ");

    for (int i = 0; i < soLe; i++)
    {
        printf("%d ", le[i]);
    }

    return 0;
}