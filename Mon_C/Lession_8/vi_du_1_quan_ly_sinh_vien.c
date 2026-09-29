/*
 * VÍ DỤ 1: QUẢN LÝ SINH VIÊN (đầy đủ nhưng ngắn gọn)
 * Kết hợp: typedef struct + mảng động + malloc/realloc/free
 *
 * Đặc điểm:
 * - Thêm sinh viên KHÔNG GIỚI HẠN số lượng (realloc mở rộng mỗi lần thêm)
 * - Mã sinh viên TỰ TĂNG (không cần nhập, không bao giờ trùng dù đã xóa)
 * - Tìm kiếm sinh viên theo tên (dùng strstr)
 * - Xóa sinh viên theo mã (dời mảng, thu nhỏ bộ nhớ)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien
{
    int ma_sv;     // Mã sinh viên được gán tự động
    char ten[50];  // Họ tên sinh viên
    float diem_tb; // Điểm trung bình
} SinhVien;

SinhVien *ds_sv = NULL;  // Con trỏ mảng động, ban đầu chưa cấp phát (NULL)
int so_luong_sv = 0;     // Số sinh viên hiện có
int ma_sv_tiep_theo = 1; // Biến tạo mã tự tăng, luôn tăng nên mã không bao giờ trùng lặp

// Đọc bỏ ký tự '\n' dư thừa trong bộ đệm stdin sau scanf
void xoa_bo_dem()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Đọc một chuỗi có dấu cách và tự cắt '\n' do fgets để lại
void nhap_chuoi(const char *thong_bao, char *s, int kich_thuoc)
{
    printf("%s", thong_bao);
    if (fgets(s, kich_thuoc, stdin) != NULL)
    {
        s[strcspn(s, "\n")] = '\0';
    }
}

// Thêm sinh viên mới: realloc mở rộng mảng thêm 1 ô nên không giới hạn số lượng
void them_sv()
{
    SinhVien sv_moi;
    SinhVien *temp;

    nhap_chuoi("Nhập tên sinh viên: ", sv_moi.ten, sizeof(sv_moi.ten));
    printf("Nhập điểm trung bình: ");
    scanf("%f", &sv_moi.diem_tb);
    xoa_bo_dem();

    // realloc tự giữ nguyên dữ liệu cũ và mở rộng thêm 1 ô cuối mảng
    temp = realloc(ds_sv, (so_luong_sv + 1) * sizeof(SinhVien));
    if (temp == NULL)
    {
        printf("Lỗi: Không đủ bộ nhớ!\n");
        return;
    }
    ds_sv = temp; // Chỉ nhận con trỏ mới khi realloc thành công

    sv_moi.ma_sv = ma_sv_tiep_theo++; // Gán mã tự tăng rồi tăng biến lên cho lần thêm sau
    ds_sv[so_luong_sv] = sv_moi;
    so_luong_sv++;

    printf("Đã thêm sinh viên mã %d thành công!\n", sv_moi.ma_sv);
}

// In danh sách sinh viên dạng bảng
void hien_thi()
{
    if (so_luong_sv == 0)
    {
        printf("Danh sách sinh viên đang trống.\n");
        return;
    }

    printf("\n================ DANH SÁCH SINH VIÊN ================\n");
    printf("%-8s %-25s %-10s\n", "Mã SV", "Họ và tên", "Điểm TB");

    for (int i = 0; i < so_luong_sv; i++)
    {
        printf("%-8d %-25s %-10.2f\n", ds_sv[i].ma_sv, ds_sv[i].ten, ds_sv[i].diem_tb);
    }
}

// Tìm và in các sinh viên có tên chứa từ khóa nhập vào
void tim_theo_ten()
{
    char tu_khoa[50];
    int tim_thay = 0;

    nhap_chuoi("Nhập tên cần tìm: ", tu_khoa, sizeof(tu_khoa));

    printf("\n================ KẾT QUẢ TÌM KIẾM ================\n");
    for (int i = 0; i < so_luong_sv; i++)
    {
        // strstr trả về khác NULL khi tên chứa từ khóa cần tìm
        if (strstr(ds_sv[i].ten, tu_khoa) != NULL)
        {
            printf("Mã %-4d %-25s Điểm TB: %.2f\n", ds_sv[i].ma_sv, ds_sv[i].ten, ds_sv[i].diem_tb);
            tim_thay = 1;
        }
    }

    if (!tim_thay)
    {
        printf("Không tìm thấy sinh viên nào khớp từ khóa \"%s\".\n", tu_khoa);
    }
}

// Tìm vị trí của sinh viên theo mã. Trả về index hoặc -1 nếu không thấy
int tim_vi_tri_theo_ma(int ma)
{
    for (int i = 0; i < so_luong_sv; i++)
    {
        if (ds_sv[i].ma_sv == ma)
        {
            return i;
        }
    }
    return -1;
}

// Xóa sinh viên theo mã: dời mảng đè lên phần tử bị xóa rồi thu nhỏ bộ nhớ
void xoa_sv()
{
    int ma, vt;
    SinhVien *temp;

    printf("Nhập mã sinh viên cần xóa: ");
    scanf("%d", &ma);
    xoa_bo_dem();

    vt = tim_vi_tri_theo_ma(ma);
    if (vt == -1)
    {
        printf("Lỗi: Không tìm thấy sinh viên mã %d.\n", ma);
        return;
    }

    // Dời các phần tử phía sau lên 1 vị trí để lấp chỗ của phần tử bị xóa
    for (int i = vt; i < so_luong_sv - 1; i++)
    {
        ds_sv[i] = ds_sv[i + 1];
    }
    so_luong_sv--;

    if (so_luong_sv == 0)
    {
        free(ds_sv); // Xóa hết sinh viên thì trả vùng nhớ về cho hệ thống
        ds_sv = NULL;
    }
    else
    {
        // Thu nhỏ mảng động cho đúng số phần tử còn lại
        temp = realloc(ds_sv, so_luong_sv * sizeof(SinhVien));
        if (temp != NULL)
        {
            ds_sv = temp;
        }
    }

    printf("Đã xóa sinh viên mã %d thành công!\n", ma);
}

int main()
{
    int lua_chon;

    do
    {
        printf("\n============ QUẢN LÝ SINH VIÊN ============\n");
        printf("1. Thêm sinh viên (không giới hạn)\n");
        printf("2. Hiển thị danh sách\n");
        printf("3. Tìm kiếm theo tên\n");
        printf("4. Xóa sinh viên theo mã\n");
        printf("0. Thoát\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &lua_chon);
        xoa_bo_dem();

        switch (lua_chon)
        {
        case 1:
            them_sv();
            break;
        case 2:
            hien_thi();
            break;
        case 3:
            tim_theo_ten();
            break;
        case 4:
            xoa_sv();
            break;
        case 0:
            free(ds_sv); // Giải phóng bộ nhớ trước khi thoát chương trình
            printf("Đã giải phóng bộ nhớ. Tạm biệt!\n");
            break;
        default:
            printf("Lựa chọn không hợp lệ!\n");
        }
    } while (lua_chon != 0);

    return 0;
}
