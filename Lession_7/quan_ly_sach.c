#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct Sach
{
    char ma_sach[20];
    char ten_sach[100];
    char tac_gia[50];
    int nam_xb;
    int tong_sl;
    int da_muon;
} Sach;

int main()
{
    Sach ds_sach[MAX];
    int so_luong_sach = 0;
    int n;

    printf("Nhập số lượng sách cần thêm: ");
    scanf("%d", &n);
    getchar();

    if (n > MAX)
    {
        printf("Thư viện chỉ lưu tối đa %d cuốn sách!\n", MAX);
        n = MAX;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Nhập thông tin cuốn sách thứ %d ---\n", i + 1);

        // Nhập mã sách, bắt buộc không được trùng với mã đã có
        while (1)
        {
            int bi_trung = 0;

            printf("Nhập mã sách: ");
            fgets(ds_sach[i].ma_sach, sizeof(ds_sach[i].ma_sach), stdin);
            ds_sach[i].ma_sach[strcspn(ds_sach[i].ma_sach, "\n")] = '\0'; // Xóa ký tự xuống dòng do fgets tạo ra

            for (int j = 0; j < so_luong_sach; j++)
            {
                if (strcmp(ds_sach[j].ma_sach, ds_sach[i].ma_sach) == 0)
                {
                    bi_trung = 1;
                    break;
                }
            }

            if (!bi_trung)
            {
                break;
            }

            printf("Mã sách đã tồn tại! Vui lòng nhập mã khác.\n");
        }

        printf("Nhập tên sách: ");
        fgets(ds_sach[i].ten_sach, sizeof(ds_sach[i].ten_sach), stdin);
        ds_sach[i].ten_sach[strcspn(ds_sach[i].ten_sach, "\n")] = '\0';

        printf("Nhập tác giả: ");
        fgets(ds_sach[i].tac_gia, sizeof(ds_sach[i].tac_gia), stdin);
        ds_sach[i].tac_gia[strcspn(ds_sach[i].tac_gia, "\n")] = '\0';

        printf("Nhập năm xuất bản: ");
        scanf("%d", &ds_sach[i].nam_xb);
        getchar();

        printf("Nhập tổng số lượng: ");
        scanf("%d", &ds_sach[i].tong_sl);
        getchar();

        ds_sach[i].da_muon = 0;
        so_luong_sach++;
    }

    printf("\n==================== SÁCH TRONG THƯ VIỆN ====================\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s\n", "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Tổng SL", "Đã mượn");

    for (int i = 0; i < so_luong_sach; i++)
    {
        printf("%-10s %-30s %-20s %-8d %-8d %-8d\n",
               ds_sach[i].ma_sach, ds_sach[i].ten_sach, ds_sach[i].tac_gia,
               ds_sach[i].nam_xb, ds_sach[i].tong_sl, ds_sach[i].da_muon);
    }

    printf("\nHiện tại thư viện có %d cuốn sách.\n", so_luong_sach);

    return 0;
}
