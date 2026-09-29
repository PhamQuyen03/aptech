/*
 * VÍ DỤ 2: CẤP PHÁT ĐỘNG CƠ BẢN VỚI MALLOC (ngắn gọn nhất)
 * Kết hợp: typedef struct + malloc + free
 *
 * Nhập trước số lượng n, cấp phát đúng n ô bằng malloc,
 * nhập thông tin, in ra rồi free. Không dùng realloc ở đây.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien
{
    int ma_sv;     // Mã sinh viên
    char ten[50];  // Họ tên
    float diem_tb; // Điểm trung bình
} SinhVien;

// Đọc bỏ ký tự '\n' dư thừa trong bộ đệm stdin sau scanf
void xoa_bo_dem()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main()
{
    SinhVien *ds_sv;
    int n;

    printf("Nhập số lượng sinh viên: ");
    scanf("%d", &n);
    xoa_bo_dem();

    if (n <= 0)
    {
        printf("Số lượng không hợp lệ!\n");
        return 1;
    }

    // Cấp phát động n ô kiểu SinhVien trên heap (mảng tĩnh phải biết trước kích thước)
    ds_sv = malloc(n * sizeof(SinhVien));
    if (ds_sv == NULL)
    {
        printf("Lỗi: Không đủ bộ nhớ!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Nhập sinh viên thứ %d ---\n", i + 1);
        ds_sv[i].ma_sv = i + 1; // Mã tăng dần theo thứ tự nhập

        printf("Nhập họ và tên: ");
        fgets(ds_sv[i].ten, sizeof(ds_sv[i].ten), stdin);
        ds_sv[i].ten[strcspn(ds_sv[i].ten, "\n")] = '\0';

        printf("Nhập điểm trung bình: ");
        scanf("%f", &ds_sv[i].diem_tb);
        xoa_bo_dem();
    }

    printf("\n================ DANH SÁCH SINH VIÊN ================\n");
    printf("%-8s %-25s %-10s\n", "Mã SV", "Họ và tên", "Điểm TB");
    for (int i = 0; i < n; i++)
    {
        printf("%-8d %-25s %-10.2f\n", ds_sv[i].ma_sv, ds_sv[i].ten, ds_sv[i].diem_tb);
    }

    // Vùng nhớ malloc cấp phát KHÔNG tự thu hồi, bắt buộc phải free trước khi kết thúc
    free(ds_sv);
    printf("\nĐã giải phóng bộ nhớ. Kết thúc chương trình!\n");

    return 0;
}
