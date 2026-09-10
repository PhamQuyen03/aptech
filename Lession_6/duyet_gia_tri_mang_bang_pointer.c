#include <stdio.h>

// int main()
// {
//     int a[5] = {10, 20, 30, 40, 50};
//     int *p; // Khai báo con trỏ p
//     for (int i = 0; i < 5; i++)
//     {
//         p = &a[i]; // Gán địa chỉ của phần tử thứ i của mảng a vào con trỏ p
//         printf("a[%d] Giá trị: %d\n", i, *p);
//     }

//     return 0;
// }

int main()
{
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a; // Khai báo con trỏ p
    for (int i = 0; i < 5; i++)
    {
        printf("a[%d] Giá trị: %d\n", i, *p);
        p++; // Di chuyển con trỏ p đến phần tử tiếp theo của mảng
    }

    return 0;
}