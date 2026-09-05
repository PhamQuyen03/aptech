#include <stdio.h>

int main()
{
    float km, tien;

    printf("Nhập số KM: ");
    scanf("%f", &km);

    if (km <= 0)
    {
        printf("Số KM không hợp lệ!\n");
    }
    else if (km <= 1)
    {
        tien = km * 15000;
        printf("Tiền cước taxi: %.0f đồng\n", tien);
    }
    else if (km <= 10)
    {
        tien = 15000 + (km - 1) * 13500;
        printf("Tiền cước taxi: %.0f đồng\n", tien);
    }
    else if (km <= 30)
    {
        tien = 15000 + 9 * 13500 + (km - 10) * 11000;
        printf("Tiền cước taxi: %.0f đồng\n", tien);
    }
    else
    {
        tien = 15000 + 9 * 13500 + 20 * 11000 + (km - 30) * 9000;

        // Giảm 10% nếu đi trên 30 km
        tien = tien * 0.9;

        printf("Tiền cước taxi sau khi giảm 10%%: %.0f đồng\n", tien);
    }

    return 0;
}