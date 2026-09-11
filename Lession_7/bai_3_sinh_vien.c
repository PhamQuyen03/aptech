#include <stdio.h>
#include <string.h>

typedef struct SinhVien
{
    int mssv;
    char hoTen[50];
} SinhVien;

void inThongTinSV(SinhVien sv)
{
    printf("=== THÔNG TIN SINH VIÊN ===\n");
    printf("MSSV:   %d\n", sv.mssv);
    printf("Họ tên: %s\n", sv.hoTen);
}

void inThongTinSVPointer(SinhVien *sv)
{
    printf("=== ******** ===\n");
    printf("=== THÔNG TIN SINH VIÊN ===\n");
    printf("MSSV:   %d\n", sv->mssv);
    printf("Họ tên: %s\n", sv->hoTen);
}

int main()
{
    SinhVien sv1;

    printf("Mời bạn nhập vào mã số sinh viên: ");
    scanf("%d", &sv1.mssv);
    getchar();

    printf("Mời bạn nhập vào tên sinh viên: ");
    fgets(sv1.hoTen, sizeof(sv1.hoTen), stdin);
    sv1.hoTen[strcspn(sv1.hoTen, "\n")] = '\0';

    inThongTinSV(sv1);
    inThongTinSVPointer(&sv1);
    return 0;
}
