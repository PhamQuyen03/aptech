#include <stdio.h>

void calc(int a, int b, int *tong, int *tich, int *hieu, float *thuong)
{
    *tong = a + b;          // Tính tổng và lưu vào địa chỉ mà tong trỏ tới
    *tich = a * b;          // Tính tích và lưu vào địa chỉ mà tich trỏ tới
    *hieu = a - b;          // Tính hiệu và lưu vào địa chỉ mà hieu trỏ tới
    *thuong = (float)a / b; // Tính thương và lưu vào địa chỉ mà thuong trỏ tới
}

int main()
{
    int a, b;
    int tong, tich, hieu;
    float thuong;

    printf("Nhập số thứ nhất (a): ");
    scanf("%d", &a);
    printf("Nhập số thứ hai (b): ");
    scanf("%d", &b);

    calc(a, b, &tong, &tich, &hieu, &thuong); // Truyền địa chỉ của các biến vào hàm

    printf("\nKết quả:\n");
    printf("Tổng: %d\n", tong);
    printf("Tích: %d\n", tich);
    printf("Hiệu: %d\n", hieu);
    printf("Thương: %.2f\n", thuong);

    return 0;
}
