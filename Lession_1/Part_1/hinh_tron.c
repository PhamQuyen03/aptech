#include <stdio.h>

int main()
{
    float PI = 3.14159;
    float banKinh;
    float chuVi, dienTich;

    printf("Nhập vào bán kính: ");
    scanf("%f", &banKinh);

    chuVi = 2 * PI * banKinh;
    dienTich = PI * banKinh * banKinh;

    printf("Chu vi hình tròn = %.2f\n", chuVi);
    printf("Diện tích hình tròn = %.2f\n", dienTich);

    return 0;
}