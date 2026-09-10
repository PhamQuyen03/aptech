#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a; // *a: Lấy giá trị tại địa chỉ ô nhớ a đang trỏ tới
    *a = *b;       // Gán giá trị tại ô nhớ b vào ô nhớ a
    *b = temp;     // Gán giá trị temp vào ô nhớ b
}

int main()
{
    int a, b;

    printf("Nhập số thứ nhất (a): ");
    scanf("%d", &a);
    printf("Nhập số thứ hai (b): ");
    scanf("%d", &b);

    printf("\nTrước khi hoán đổi: a = %d, b = %d\n", a, b);

    // Truyền địa chỉ của a và b vào hàm bằng toán tử &
    swap(&a, &b);

    printf("Sau khi hoán đổi:   a = %d, b = %d\n", a, b);

    return 0;
}
