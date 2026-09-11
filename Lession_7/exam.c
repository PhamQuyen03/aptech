#include <stdio.h>
#include <string.h>

struct SinhVien
{
    char ten[50];
    int tuoi, maSV;
    char gioiTinh[10];
    char lop[10];
    float diemTB;
};

int main()
{
    struct SinhVien sv1;

    printf("Mời bạn nhập vào tên: ");
    fgets(sv1.ten, sizeof(sv1.ten), stdin);
    sv1.ten[strcspn(sv1.ten, "\n")] = '\0'; // Xóa ký tự xuống dòng do fgets tạo ra

    printf("Mời bạn nhập vào tuổi: ");
    scanf("%d", &sv1.tuoi);

    printf("Mời bạn nhập vào mã sinh viên: ");
    scanf("%d", &sv1.maSV);

    printf("Mời bạn nhập vào giới tính (Nam/Nữ): ");
    scanf("%s", sv1.gioiTinh);

    printf("Mời bạn nhập vào lớp: ");
    scanf("%s", sv1.lop);

    printf("Mời bạn nhập vào điểm trung bình: ");
    scanf("%f", &sv1.diemTB);

    printf("\n=== THÔNG TIN SINH VIÊN ===\n");
    printf("Họ tên: %s\n", sv1.ten);
    printf("Tuổi: %d\n", sv1.tuoi);
    printf("Mã SV: %d\n", sv1.maSV);
    printf("Giới tính: %s\n", sv1.gioiTinh);
    printf("Lớp: %s\n", sv1.lop);
    printf("Điểm TB: %.2f\n", sv1.diemTB);

    return 0;
}
