#include <stdio.h>

// Hàm xóa bộ nhớ đệm bàn phím
void xoaBoDem()
{
    while (getchar() != '\n')
        ;
}

// Hàm nhập số thực và kiểm tra tính hợp lệ
float nhapSo(const char *thongBao)
{
    float so;
    while (1)
    {
        printf("%s", thongBao);
        if (scanf("%f", &so) == 1)
        {
            xoaBoDem();
            return so;
        }
        printf("Lỗi: Vui lòng nhập số hợp lệ!\n");
        xoaBoDem();
    }
}

// Hàm tính tổng của 2 số: a + b
float tinhTong(float a, float b)
{
    return a + b;
}

// Hàm tính tích của 2 số: a * b
float tinhTich(float a, float b)
{
    return a * b;
}

// Hàm hiển thị menu lựa chọn
void inMenu()
{
    printf("\n===== CHỌN PHÉP TÍNH =====\n");
    printf("1. Tính tổng (a + b)\n");
    printf("2. Tính tích (a * b)\n");
    printf("3. Nhập lại 2 số mới\n");
    printf("0. Thoát chương trình\n");
    printf("==========================\n");
    printf("Nhập lựa chọn của bạn: ");
}

// =====================================================
// HÀM MAIN
// =====================================================
int main()
{
    printf("=== CHƯƠNG TRÌNH TÍNH TỔNG HOẶC TÍCH 2 SỐ ===\n");
    float a = nhapSo("Nhập số thứ nhất (a): ");
    float b = nhapSo("Nhập số thứ hai (b): ");

    int chon;
    do
    {
        inMenu();
        if (scanf("%d", &chon) != 1)
        {
            printf("\nLỗi: Vui lòng nhập số nguyên tương ứng trong menu!\n");
            xoaBoDem();
            continue;
        }
        xoaBoDem();

        switch (chon)
        {
        case 1:
            printf("\n=> Kết quả tổng: %.2f + %.2f = %.2f\n", a, b, tinhTong(a, b));
            break;

        case 2:
            printf("\n=> Kết quả tích: %.2f * %.2f = %.2f\n", a, b, tinhTich(a, b));
            break;

        case 3:
            printf("\n--- Nhập lại 2 số mới ---\n");
            a = nhapSo("Nhập số thứ nhất (a): ");
            b = nhapSo("Nhập số thứ hai (b): ");
            break;

        case 0:
            printf("\nĐã thoát chương trình. Tạm biệt!\n");
            break;

        default:
            printf("\nLựa chọn không hợp lệ! Vui lòng chọn từ 0 đến 3.\n");
            break;
        }

    } while (chon != 0);

    return 0;
}
