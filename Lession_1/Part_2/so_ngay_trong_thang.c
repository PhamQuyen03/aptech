#include <stdio.h>

int main()
{
    int thang, nam;

    printf("Nhập tháng: ");
    scanf("%d", &thang);

    printf("Nhập năm: ");
    scanf("%d", &nam);

    if (nam <= 0)
    {
        printf("Năm không hợp lệ!\n");
    }
    else if (thang < 1 || thang > 12)
    {
        printf("Tháng không hợp lệ!\n");
    }
    else
    {
        if (thang == 1 || thang == 3 || thang == 5 ||
            thang == 7 || thang == 8 || thang == 10 || thang == 12)
        {

            printf("Tháng %d năm %d có 31 ngày.\n", thang, nam);
        }
        else if (thang == 4 || thang == 6 ||
                 thang == 9 || thang == 11)
        {

            printf("Tháng %d năm %d có 30 ngày.\n", thang, nam);
        }
        else
        {
            if (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0))
            {
                printf("Tháng 2 năm %d có 29 ngày (năm nhuận).\n", nam);
            }
            else
            {
                printf("Tháng 2 năm %d có 28 ngày (năm thường).\n", nam);
            }
        }
    }

    return 0;
}