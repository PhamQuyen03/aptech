#include <stdio.h>

int main()
{
    int a, b, tam;

    printf("Nhap a: ");
    scanf("%d", &a);

    printf("Nhap b: ");
    scanf("%d", &b);

    printf("Trước khi hoán đổi: a = %d, b = %d\n", a, b);

    tam = a;
    a = b;
    b = tam;

    printf("Sau khi hoán đổi: a = %d, b = %d\n", a, b);

    return 0;
}