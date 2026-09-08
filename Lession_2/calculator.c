#include <stdio.h>

int main()
{
    int a, b, chon;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Cộng (+)\n");
        printf("2. Trừ (-)\n");
        printf("3. Nhân (*)\n");
        printf("4. Chia (/)\n");
        printf("0. Thoát\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &chon);

        if (chon >= 1 && chon <= 4)
        {
            printf("Nhập số thứ nhất: ");
            scanf("%d", &a);

            do
            {
                printf("Nhập số thứ hai: ");
                scanf("%d", &b);

                if (chon == 4 && b == 0)
                {
                    printf("Số thứ hai phải khác 0 khi chia!\n");
                }

            } while (chon == 4 && b == 0);

            switch (chon)
            {
            case 1:
                printf("%d + %d = %d\n", a, b, a + b);
                break;

            case 2:
                printf("%d - %d = %d\n", a, b, a - b);
                break;

            case 3:
                printf("%d * %d = %d\n", a, b, a * b);
                break;

            case 4:
                printf("%d / %d = %.2f\n", a, b, (float)a / b);
                break;
            }
        }
        else if (chon != 0)
        {
            printf("Lựa chọn không hợp lệ!\n");
        }

    } while (chon != 0);

    printf("Đã thoát chương trình!\n");

    return 0;
}