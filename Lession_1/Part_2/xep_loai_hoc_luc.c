#include <stdio.h>

int main()
{
    float diem;

    printf("Nhập điểm: ");
    scanf("%f", &diem);

    if (diem >= 9)
    {
        printf("Học lực: Xuất sắc\n");
    }
    else if (diem >= 8)
    {
        printf("Học lực: Giỏi\n");
    }
    else if (diem >= 6.5)
    {
        printf("Học lực: Khá\n");
    }
    else if (diem >= 5)
    {
        printf("Học lực: Trung bình\n");
    }
    else
    {
        printf("Học lực: Yếu\n");
    }

    return 0;
}