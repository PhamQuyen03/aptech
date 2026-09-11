#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct SinhVien
{
    char ten[50];
    int tuoi;
    char gioiTinh[10];
    float diemTB;
} SinhVien;

int main()
{
    SinhVien ds[MAX];
    int n;

    printf("Nhập số lượng sinh viên: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Nhập sinh viên thứ %d ---\n", i + 1);

        printf("Nhập họ và tên: ");
        fgets(ds[i].ten, sizeof(ds[i].ten), stdin);
        ds[i].ten[strcspn(ds[i].ten, "\n")] = '\0'; // Xóa ký tự xuống dòng do fgets tạo ra

        printf("Nhập tuổi: ");
        scanf("%d", &ds[i].tuoi);
        getchar();

        printf("Nhập giới tính: ");
        fgets(ds[i].gioiTinh, sizeof(ds[i].gioiTinh), stdin);
        ds[i].gioiTinh[strcspn(ds[i].gioiTinh, "\n")] = '\0';

        printf("Nhập điểm trung bình: ");
        scanf("%f", &ds[i].diemTB);
        getchar();
    }

    printf("\n==================== DANH SÁCH SINH VIÊN ====================\n");
    printf("%-5s %-25s %-8s %-12s %-10s\n", "STT", "Họ và tên", "Tuổi", "Giới tính", "Điểm TB");

    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-25s %-8d %-12s %-10.2f\n",
               i + 1, ds[i].ten, ds[i].tuoi, ds[i].gioiTinh, ds[i].diemTB);
    }

    return 0;
}
