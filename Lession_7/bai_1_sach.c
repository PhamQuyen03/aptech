#include <stdio.h>
#include <string.h>

typedef struct Sach
{
    char tenSach[100];
    char tacGia[50];
    int namXuatBan;
} Sach;

int main()
{
    Sach sach1;

    printf("Mời bạn nhập vào tên sách: ");
    fgets(sach1.tenSach, sizeof(sach1.tenSach), stdin);
    sach1.tenSach[strcspn(sach1.tenSach, "\n")] = '\0'; // Xóa ký tự xuống dòng do fgets tạo ra

    printf("Mời bạn nhập vào tác giả: ");
    fgets(sach1.tacGia, sizeof(sach1.tacGia), stdin);
    sach1.tacGia[strcspn(sach1.tacGia, "\n")] = '\0';

    printf("Mời bạn nhập vào năm xuất bản: ");
    scanf("%d", &sach1.namXuatBan);

    printf("=== THÔNG TIN SÁCH ===\n");
    printf("Tên sách:      %s\n", sach1.tenSach);
    printf("Tác giả:       %s\n", sach1.tacGia);
    printf("Năm xuất bản:  %d\n", sach1.namXuatBan);

    return 0;
}
