#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "student.txt"

typedef struct SinhVien
{
    char name[50];
    int age;
    char gender[10];
    float point;
} SinhVien;

void nhapThemSinhVien()
{
    FILE *file_w = fopen(FILENAME, "a");
    if (file_w == NULL)
    {
        printf("Loi: Khong the mo file de ghi!\n");
        return;
    }

    while (1)
    {
        SinhVien sv;
        printf("\n--- Nhap thong tin sinh vien ---\n");

        printf("Nhap ho ten: ");
        fgets(sv.name, sizeof(sv.name), stdin);
        sv.name[strcspn(sv.name, "\n")] = '\0';

        printf("Nhap tuoi: ");
        scanf("%d", &sv.age);
        getchar();
        printf("Nhap gioi tinh: ");
        fgets(sv.gender, sizeof(sv.gender), stdin);
        sv.gender[strcspn(sv.gender, "\n")] = '\0';

        printf("Nhap diem: ");
        scanf("%f", &sv.point);
        getchar();

        fprintf(file_w, "%-25s %-10d %-10s %10.2f\n", sv.name, sv.age, sv.gender, sv.point);
        printf("=> Da luu thong tin sinh vien \"%s\" vao file!\n", sv.name);

        printf("\nBan co muon nhap tiep sinh vien khong? (Y/N): ");
        char tiep_tuc;
        scanf(" %c", &tiep_tuc);
        getchar();

        if (tiep_tuc == 'n' || tiep_tuc == 'N')
        {
            break;
        }
    }

    fclose(file_w);
}

void hienThiDanhSach()
{
    FILE *file_r = fopen(FILENAME, "r");
    if (file_r == NULL)
    {
        printf("\nChua co du lieu hoac khong the mo file %s!\n", FILENAME);
        return;
    }

    char line[1000];
    int count = 0;

    printf("\n======================= DANH SACH SINH VIEN =======================\n");
    printf("%-25s %-10s %-10s %10s\n", "Ho va Ten", "Tuoi", "Gioi tinh", "Diem");
    printf("-------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file_r) != NULL)
    {
        printf("%s", line);
        count++;
    }

    if (count == 0)
    {
        printf("(Danh sach hien dang trong)\n");
    }

    printf("===================================================================\n");

    fclose(file_r);
}

int main()
{
    int luaChon;

    while (1)
    {
        printf("\n===================== MENU =====================\n");
        printf("1. Nhap them sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Dong chuong trinh\n");
        printf("================================================\n");
        printf("Nhap lua chon cua ban (1-3): ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon)
        {
        case 1:
            nhapThemSinhVien();
            break;
        case 2:
            hienThiDanhSach();
            break;
        case 3:
            printf("\nDa dong chuong trinh\n");
            return 0;
        default:
            printf("\nLua chon khong hop le! Vui long nhap tu 1 den 3.\n");
            break;
        }
    }

    return 0;
}
