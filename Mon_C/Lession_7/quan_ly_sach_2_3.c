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

void xoa_bo_dem();

int tim_theo_ma(Sach ds[], int n, const char *ma);

void them_sach(Sach ds[], int *n);
void hien_thi_danh_sach(const Sach ds[], int n);

void cap_nhat_sach(Sach ds[], int n);

void xoa_sach(Sach ds[], int *n);

void tim_kiem_sach(const Sach ds[], int n);

void sap_xep_sach(Sach ds[], int n);

int main()
{
    Sach ds_sach[MAX];
    int so_luong_sach = 0;
    int lua_chon;

    do
    {
        printf("\n==================== QUẢN LÝ THƯ VIỆN - MENU THỦ THƯ ====================\n");
        printf("1. Thêm sách mới\n");
        printf("2. Hiển thị danh sách sách\n");
        printf("3. Cập nhật thông tin sách\n");
        printf("4. Xóa cuốn sách\n");
        printf("5. Tìm kiếm sách theo tên\n");
        printf("6. Sắp xếp sách theo năm xuất bản\n");
        printf("0. Thoát chương trình\n");
        printf("Nhập lựa chọn của bạn: ");
        scanf("%d", &lua_chon);
        xoa_bo_dem();

        switch (lua_chon)
        {
        case 1:
            them_sach(ds_sach, &so_luong_sach);
            break;
        case 2:
            hien_thi_danh_sach(ds_sach, so_luong_sach);
            break;
        case 3:
            cap_nhat_sach(ds_sach, so_luong_sach);
            break;
        case 4:
            xoa_sach(ds_sach, &so_luong_sach);
            break;
        case 5:
            tim_kiem_sach(ds_sach, so_luong_sach);
            break;
        case 6:
            sap_xep_sach(ds_sach, so_luong_sach);
            break;
        case 0:
            printf("Đã thoát chương trình.\n");
            break;
        default:
            printf("Lựa chọn không hợp lệ! Vui lòng chọn lại.\n");
        }
    } while (lua_chon != 0);

    return 0;
}

void xoa_bo_dem()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Tìm vị trí cuốn sách theo mã.
// Trả về vị trí từ 0 đến n-1 nếu thấy, hoặc -1 nếu không tìm thấy
int tim_theo_ma(Sach ds[], int n, const char *ma)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(ds[i].ma_sach, ma) == 0)
        {
            return i;
        }
    }
    return -1;
}

void them_sach(Sach ds[], int *n)
{
    if (*n >= MAX)
    {
        printf("Thư viện đã đầy (%d cuốn), không thể thêm sách mới!\n", MAX);
        return;
    }

    Sach s;

    while (1)
    {
        printf("Nhập mã sách: ");
        fgets(s.ma_sach, sizeof(s.ma_sach), stdin);
        s.ma_sach[strcspn(s.ma_sach, "\n")] = '\0'; // Xóa ký tự xuống dòng do fgets tạo ra

        if (tim_theo_ma(ds, *n, s.ma_sach) == -1)
        {
            break;
        }
        printf("Mã sách đã tồn tại! Vui lòng nhập mã khác.\n");
    }

    printf("Nhập tên sách: ");
    fgets(s.ten_sach, sizeof(s.ten_sach), stdin);
    s.ten_sach[strcspn(s.ten_sach, "\n")] = '\0';

    printf("Nhập tác giả: ");
    fgets(s.tac_gia, sizeof(s.tac_gia), stdin);
    s.tac_gia[strcspn(s.tac_gia, "\n")] = '\0';

    printf("Nhập năm xuất bản: ");
    scanf("%d", &s.nam_xb);
    xoa_bo_dem();

    printf("Nhập tổng số lượng: ");
    scanf("%d", &s.tong_sl);
    xoa_bo_dem();

    s.da_muon = 0;

    ds[*n] = s;
    (*n)++;

    printf("Đã thêm sách thành công!\n");
}

void hien_thi_danh_sach(const Sach ds[], int n)
{
    if (n == 0)
    {
        printf("Danh sách sách đang trống!\n");
        return;
    }

    printf("\n======================== DANH MỤC SÁCH TRONG THƯ VIỆN ========================\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Tổng SL", "Đã mượn", "Hiện có");

    for (int i = 0; i < n; i++)
    {
        printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
               ds[i].ma_sach, ds[i].ten_sach, ds[i].tac_gia,
               ds[i].nam_xb, ds[i].tong_sl, ds[i].da_muon,
               ds[i].tong_sl - ds[i].da_muon);
    }

    printf("Hiện tại thư viện có %d cuốn sách.\n", n);
}

void cap_nhat_sach(Sach ds[], int n)
{
    char ma[20];
    int vt;
    int lua_chon;

    printf("Nhập mã sách cần sửa: ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';

    vt = tim_theo_ma(ds, n, ma);
    if (vt == -1)
    {
        printf("Không tìm thấy sách có mã \"%s\"!\n", ma);
        return;
    }

    printf("Đã tìm thấy: [%s] %s - %s\n", ds[vt].ma_sach, ds[vt].ten_sach, ds[vt].tac_gia);
    printf("Chọn thông tin cần sửa:\n");
    printf("1. Tên sách\n");
    printf("2. Tác giả\n");
    printf("3. Năm xuất bản\n");
    printf("4. Tổng số lượng\n");
    printf("Nhập lựa chọn: ");
    scanf("%d", &lua_chon);
    xoa_bo_dem();

    switch (lua_chon)
    {
    case 1:
        printf("Nhập tên sách mới: ");
        fgets(ds[vt].ten_sach, sizeof(ds[vt].ten_sach), stdin);
        ds[vt].ten_sach[strcspn(ds[vt].ten_sach, "\n")] = '\0';
        break;
    case 2:
        printf("Nhập tác giả mới: ");
        fgets(ds[vt].tac_gia, sizeof(ds[vt].tac_gia), stdin);
        ds[vt].tac_gia[strcspn(ds[vt].tac_gia, "\n")] = '\0';
        break;
    case 3:
        printf("Nhập năm xuất bản mới: ");
        scanf("%d", &ds[vt].nam_xb);
        xoa_bo_dem();
        break;
    case 4:
        do
        {
            printf("Nhập tổng số lượng mới: ");
            scanf("%d", &ds[vt].tong_sl);
            xoa_bo_dem();

            if (ds[vt].tong_sl < ds[vt].da_muon)
            {
                printf("Tổng số lượng không được nhỏ hơn số lượng đã cho mượn (%d)! Vui lòng nhập lại.\n",
                       ds[vt].da_muon);
            }
        } while (ds[vt].tong_sl < ds[vt].da_muon);
        break;
    default:
        printf("Lựa chọn không hợp lệ!\n");
        return;
    }

    printf("Đã cập nhật thành công!\n");
}

void xoa_sach(Sach ds[], int *n)
{
    char ma[20];
    char xac_nhan;
    int vt;

    printf("Nhập mã sách cần xóa: ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';

    vt = tim_theo_ma(ds, *n, ma);
    if (vt == -1)
    {
        printf("Không tìm thấy sách có mã \"%s\"!\n", ma);
        return;
    }

    // Chỉ cho phép xóa khi sách chưa có ai mượn
    if (ds[vt].da_muon > 0)
    {
        printf("Không thể xóa sách đang có người mượn!\n");
        return;
    }

    printf("Sách cần xóa: [%s] %s - %s\n", ds[vt].ma_sach, ds[vt].ten_sach, ds[vt].tac_gia);
    printf("Bạn có chắc chắn muốn xóa? (Y/N): ");
    scanf("%c", &xac_nhan);
    xoa_bo_dem();

    if (xac_nhan == 'Y' || xac_nhan == 'y')
    {
        for (int i = vt; i < *n - 1; i++)
        {
            ds[i] = ds[i + 1];
        }
        (*n)--;
        printf("Đã xóa sách thành công!\n");
    }
    else
    {
        printf("Đã hủy việc xóa sách.\n");
    }
}

void tim_kiem_sach(const Sach ds[], int n)
{
    char tu_khoa[100];
    int tim_thay = 0;

    printf("Nhập từ khóa tên sách cần tìm: ");
    fgets(tu_khoa, sizeof(tu_khoa), stdin);
    tu_khoa[strcspn(tu_khoa, "\n")] = '\0';

    printf("\n========================= KẾT QUẢ TÌM KIẾM SÁCH =========================\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Tổng SL", "Đã mượn", "Hiện có");

    for (int i = 0; i < n; i++)
    {
        if (strstr(ds[i].ten_sach, tu_khoa) != NULL)
        {
            printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
                   ds[i].ma_sach, ds[i].ten_sach, ds[i].tac_gia,
                   ds[i].nam_xb, ds[i].tong_sl, ds[i].da_muon,
                   ds[i].tong_sl - ds[i].da_muon);
            tim_thay = 1;
        }
    }

    if (!tim_thay)
    {
        printf("Không tìm thấy sách nào có tên chứa từ khóa \"%s\".\n", tu_khoa);
    }
}

// Sắp xếp danh sách sách theo năm xuất bản tăng dần (từ cũ đến mới) (Bubble Sort)
void sap_xep_sach(Sach ds[], int n)
{
    Sach temp;

    if (n == 0)
    {
        printf("Danh sách sách đang trống, không thể sắp xếp!\n");
        return;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (ds[j].nam_xb > ds[j + 1].nam_xb)
            {
                temp = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = temp;
            }
        }
    }

    printf("Đã sắp xếp danh sách theo năm xuất bản tăng dần (từ cũ đến mới)!\n");
    hien_thi_danh_sach(ds, n);
}
