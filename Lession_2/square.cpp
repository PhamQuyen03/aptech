#include <stdio.h>

int main()
{
    int dai, rong;
    int i, j;

    // Nhap chieu dai
    do
    {
        printf("Nhap chieu dai (> 2): ");

        if (scanf("%d", &dai) != 1)
        {
            printf("Vui long nhap so!\n");

            while (getchar() != '\n')
                ;
            dai = 0;
        }

    } while (dai <= 2);

    // Nhap chieu rong
    do
    {
        printf("Nhap chieu rong (> 2): ");

        if (scanf("%d", &rong) != 1)
        {
            printf("Vui long nhap so!\n");

            while (getchar() != '\n')
                ;
            rong = 0;
        }

    } while (rong <= 2);

    // Ve hinh
    i = 0;

    while (i < rong)
    {
        j = 0;

        while (j < dai)
        {

            if (i == 0 || i == rong - 1 ||
                j == 0 || j == dai - 1)
            {
                printf("*");
            }
            else if (rong > 1 &&
                     (j == i * (dai - 1) / (rong - 1) ||
                      j == (rong - 1 - i) * (dai - 1) / (rong - 1)))
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }

            j++;
        }

        printf("\n");
        i++;
    }

    return 0;
}