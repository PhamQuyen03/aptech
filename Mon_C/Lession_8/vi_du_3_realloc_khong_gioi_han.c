/*
 * VÍ DỤ 3: MẢNG ĐỘNG KHÔNG GIỚI HẠN VỚI REALLOC
 * Kết hợp: typedef struct + malloc (ngầm qua realloc) + realloc + free
 *
 * Người dùng nhập sinh viên liên tục, nhập tên để trống thì dừng.
 * Mỗi lần thêm 1 sinh viên, mảng được realloc mở rộng thêm đúng 1 ô
 * -> không cần biết trước số lượng, muốn thêm bao nhiêu cũng được.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien
{
    int ma_sv;     // Mã sinh viên tự tăng
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
    SinhVien *ds_sv = NULL; // Bắt đầu bằng NULL: realloc(NULL, ...) hoạt động như malloc
    int so_luong = 0;
    int ma_tiep_theo = 1;

    printf("Nhập liên tục sinh viên (bỏ trống tên và Enter để dừng):\n");

    while (1)
    {
        SinhVien *temp;
        char ten[50];

        printf("\nNhập tên sinh viên thứ %d: ", so_luong + 1);
        fgets(ten, sizeof(ten), stdin);
        ten[strcspn(ten, "\n")] = '\0';

        if (ten[0] == '\0') // Người dùng Enter ngay = tên rỗng = dừng nhập
        {
            break;
        }

        // Mỗi lần thêm lại realloc mở rộng thêm 1 ô, dữ liệu cũ được giữ nguyên
        temp = realloc(ds_sv, (so_luong + 1) * sizeof(SinhVien));
        if (temp == NULL)
        {
            printf("Lỗi: Không đủ bộ nhớ!\n");
            break;
        }
        ds_sv = temp;

        strcpy(ds_sv[so_luong].ten, ten);
        ds_sv[so_luong].ma_sv = ma_tiep_theo++;

        printf("Nhập điểm trung bình: ");
        scanf("%f", &ds_sv[so_luong].diem_tb);
        xoa_bo_dem();

        so_luong++;
    }

    if (so_luong == 0)
    {
        printf("\nBạn chưa nhập sinh viên nào.\n");
        return 0;
    }

    printf("\n================ DANH SÁCH %d SINH VIÊN ================\n", so_luong);
    printf("%-8s %-25s %-10s\n", "Mã SV", "Họ và tên", "Điểm TB");
    for (int i = 0; i < so_luong; i++)
    {
        printf("%-8d %-25s %-10.2f\n", ds_sv[i].ma_sv, ds_sv[i].ten, ds_sv[i].diem_tb);
    }

    free(ds_sv); // Dùng xong phải trả vùng nhớ về cho hệ thống
    printf("\nĐã giải phóng bộ nhớ. Kết thúc chương trình!\n");

    return 0;
}
