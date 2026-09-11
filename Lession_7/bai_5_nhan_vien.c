#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct NhanVien
{
    int id;
    char ten[50];
    char chucVu[50];
} NhanVien;

void themNhanVien(NhanVien danhSachNV[], int *n);

int main()
{
    NhanVien danhSachNV[MAX];
    int n = 0;
    int chon;

    themNhanVien(danhSachNV, &n);

    do
    {
        printf("\n========== MENU ==========\n");
        printf("1. Nhập thêm nhân viên\n");
        printf("2. In danh sách\n");
        printf("3. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &chon);
        getchar();

        switch (chon)
        {
        case 1:
            themNhanVien(danhSachNV, &n);
            break;

        case 2:
            if (n == 0)
            {
                printf("Danh sách nhân viên đang trống!\n");
                break;
            }
            printf("\n==================== DANH SÁCH NHÂN VIÊN ====================\n");
            printf("%-10s %-25s %-20s\n", "ID", "Họ và tên", "Chức vụ");
            printf("-------------------------------------------------------------\n");
            for (int i = 0; i < n; i++)
            {
                printf("%-10d %-25s %-20s\n", danhSachNV[i].id, danhSachNV[i].ten, danhSachNV[i].chucVu);
            }
            break;

        case 3:
            printf("Thoát chương trình thành công!\n");
            break;

        default:
            printf("Lựa chọn không hợp lệ, vui lòng chọn lại!\n");
            break;
        }
    } while (chon != 3);

    return 0;
}

void themNhanVien(NhanVien danhSachNV[], int *n)
{
    int soLuongThem;
    if (*n == 0)
    {
        printf("Nhập số lượng nhân viên: ");
    }
    else
    {
        printf("Nhập số lượng nhân viên muốn thêm: ");
    }
    scanf("%d", &soLuongThem);
    getchar();

    if (*n + soLuongThem > MAX)
    {
        printf("Không thể thêm! Vượt quá giới hạn danh sách (tối đa %d).\n", MAX);
        return;
    }

    for (int i = 0; i < soLuongThem; i++)
    {
        printf("\n--- Nhập thông tin nhân viên thứ %d ---\n", *n + 1);

        printf("Nhập ID: ");
        scanf("%d", &danhSachNV[*n].id);
        getchar();

        printf("Nhập họ và tên: ");
        fgets(danhSachNV[*n].ten, sizeof(danhSachNV[*n].ten), stdin);
        danhSachNV[*n].ten[strcspn(danhSachNV[*n].ten, "\n")] = '\0';

        printf("Nhập chức vụ: ");
        fgets(danhSachNV[*n].chucVu, sizeof(danhSachNV[*n].chucVu), stdin);
        danhSachNV[*n].chucVu[strcspn(danhSachNV[*n].chucVu, "\n")] = '\0';

        (*n)++;
    }
    printf("Thêm nhân viên thành công!\n");
}