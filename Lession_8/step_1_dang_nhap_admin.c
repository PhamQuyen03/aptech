/*
 * BÀI TẬP LỚN - HỆ THỐNG QUẢN LÝ THƯ VIỆN
 *
 * Nội dung giai đoạn:
 * - Quản lý tài khoản bằng mảng động (malloc/realloc)
 * - Đăng nhập: kiểm tra tên đăng nhập tồn tại -> kiểm tra mật khẩu -> đọc vai trò
 * - Menu Admin: xem/thêm/xóa/sửa tài khoản, reset mật khẩu, đăng xuất, thoát
 * - Chương trình tạo sẵn 1 tài khoản Admin gốc: TEN_DANG_NHAP_MAC_DINH/MAT_KHAU_MAC_DINH
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 = Admin, 2 = Staff (Thủ thư), 3 = SinhVien
#define VAI_TRO_ADMIN 1
#define VAI_TRO_STAFF 2
#define VAI_TRO_SINH_VIEN 3
#define MAT_KHAU_MAC_DINH "123456"
#define TEN_DANG_NHAP_MAC_DINH "admin"

typedef struct NguoiDung
{
    int id;                 // ID tự động tăng, duy nhất cho từng tài khoản
    char ten_dang_nhap[50]; // Tên dùng để đăng nhập, không được trùng
    char mat_khau[50];      // Mật khẩu của tài khoản
    int vai_tro;
} NguoiDung;

/* ===== BIẾN TOÀN CỤC: quản lý mảng động tài khoản ===== */
NguoiDung *ds_nguoi_dung = NULL; // Con trỏ trỏ đến mảng động các tài khoản
int so_luong_nguoi_dung = 0;     // Số tài khoản hiện có trong mảng
int id_nguoi_dung_tiep_theo = 1; // Biến tạo ID tự tăng để ID mới luôn là duy nhất

/* ===== BIẾN TOÀN CỤC: trạng thái đăng nhập của chương trình ===== */
int id_dang_nhap = -1; // ID của tài khoản đang đăng nhập (-1 = chưa đăng nhập)
int vai_tro_dang_nhap; // Vai trò của tài khoản đang đăng nhập
int da_dang_nhap = 0;  // Cờ trạng thái: 1 = đã đăng nhập, 0 = chưa

/* ==================== KHAI BÁO TIỀN CÁC HÀM ==================== */

/* Nhóm hàm tiện ích */
void xoa_bo_dem();
void nhap_chuoi(const char *thong_bao, char *s, int kich_thuoc);
int nhap_so_nguyen(const char *thong_bao);
int xac_nhan(const char *thong_bao);
const char *ten_vai_tro(int vai_tro);

/* Nhóm hàm tìm kiếm */
int tim_nguoi_dung_theo_ten(NguoiDung *ds, int n, const char *ten);

/* Nhóm hàm nghiệp vụ Admin */
void hien_thi_danh_sach_tai_khoan();
void them_tai_khoan();
void xoa_tai_khoan();
void sua_tai_khoan();
void reset_mat_khau();

/* Nhóm hàm quản lý luồng chính */
void khoi_tao_du_lieu();
void giai_phong_bo_nho();
void dang_nhap();
void menu_admin();

/* ==================== NHÓM HÀM TIỆN ÍCH ==================== */

// Đọc bỏ ký tự '\n' dư thừa trong bộ đệm stdin (chống trôi lệnh cho fgets)
void xoa_bo_dem()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// In câu hỏi, đọc một chuỗi có thể chứa dấu cách và tự xóa '\n' do fgets để lại
void nhap_chuoi(const char *thong_bao, char *s, int kich_thuoc)
{
    printf("%s", thong_bao);
    if (fgets(s, kich_thuoc, stdin) != NULL)
    {
        s[strcspn(s, "\n")] = '\0'; // fgets luôn để lại '\n' cuối chuỗi nên phải cắt bỏ
    }
    else
    {
        s[0] = '\0'; // Hết dữ liệu nhập thì trả về chuỗi rỗng
    }
}

// In câu hỏi, đọc một số nguyên; bắt nhập lại khi người dùng gõ không phải số
int nhap_so_nguyen(const char *thong_bao)
{
    int so;
    printf("%s", thong_bao);
    int kq = scanf("%d", &so);
    if (kq == EOF)
    {
        printf("\nHết dữ liệu nhập, thoát chương trình.\n");
        giai_phong_bo_nho();
        exit(0);
    }
    while (kq != 1) // scanf trả về 0 khi dữ liệu vào không phải số
    {
        xoa_bo_dem(); // Phải đọc bỏ dữ liệu sai rồi mới cho nhập lại
        printf("Lỗi: Vui lòng nhập một số nguyên: ");
        kq = scanf("%d", &so);
    }
    xoa_bo_dem(); // scanf để lại '\n' trong bộ đệm nên phải đọc bỏ trước khi gọi fgets
    return so;
}

// Hỏi người dùng câu hỏi xác nhận, trả về 1 nếu đồng ý (Y/y)
int xac_nhan(const char *thong_bao)
{
    char tra_loi[10];
    nhap_chuoi(thong_bao, tra_loi, sizeof(tra_loi));
    return strcmp(tra_loi, "Y") == 0 || strcmp(tra_loi, "y") == 0;
}

// Chuyển mã vai trò (1/2/3) thành chuỗi tên dễ đọc để in ra màn hình
const char *ten_vai_tro(int vai_tro)
{
    switch (vai_tro)
    {
    case VAI_TRO_ADMIN:
        return "Admin";
    case VAI_TRO_STAFF:
        return "Thủ thư";
    case VAI_TRO_SINH_VIEN:
        return "Sinh viên";
    default:
        return "Không hợp lệ";
    }
}

/* ==================== NHÓM HÀM TÌM KIẾM ==================== */

// Tìm vị trí tài khoản theo tên đăng nhập. Trả về index (0..n-1) hoặc -1 nếu không thấy
int tim_nguoi_dung_theo_ten(NguoiDung *ds, int n, const char *ten)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(ds[i].ten_dang_nhap, ten) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* ==================== NHÓM HÀM NGHIỆP VỤ ADMIN ==================== */

// 1.2.1 Hiển thị danh sách toàn bộ tài khoản (không hiển thị mật khẩu)
void hien_thi_danh_sach_tai_khoan()
{
    if (so_luong_nguoi_dung == 0)
    {
        printf("Chưa có tài khoản nào trong hệ thống.\n");
        return;
    }

    printf("\n====================== DANH SÁCH TÀI KHOẢN ======================\n");
    printf("%-5s %-25s %-15s\n", "ID", "Tên đăng nhập", "Vai trò");

    for (int i = 0; i < so_luong_nguoi_dung; i++)
    {
        printf("%-5d %-25s %-15s\n",
               ds_nguoi_dung[i].id,
               ds_nguoi_dung[i].ten_dang_nhap,
               ten_vai_tro(ds_nguoi_dung[i].vai_tro));
    }
}

// 1.2.2 Thêm tài khoản mới (tên đăng nhập bắt buộc phải duy nhất)
void them_tai_khoan()
{
    NguoiDung moi;
    char ten[50];
    int vai_tro;
    NguoiDung *temp;

    nhap_chuoi("Nhập tên đăng nhập: ", ten, sizeof(ten));

    if (tim_nguoi_dung_theo_ten(ds_nguoi_dung, so_luong_nguoi_dung, ten) != -1)
    {
        printf("Lỗi: Tên đăng nhập này đã được sử dụng.\n");
        return; // Trùng tên thì hủy ngay thao tác thêm
    }

    nhap_chuoi("Nhập mật khẩu: ", moi.mat_khau, sizeof(moi.mat_khau));

    do
    {
        vai_tro = nhap_so_nguyen("Nhập vai trò (1 = Admin, 2 = Staff, 3 = SinhVien): ");
        if (vai_tro < 1 || vai_tro > 3)
        {
            printf("Lỗi: Vai trò chỉ được chọn 1, 2 hoặc 3.\n");
        }
    } while (vai_tro < 1 || vai_tro > 3);

    // Cấp phát thêm 1 ô nhớ cho mảng động trước khi thêm phần tử mới
    temp = realloc(ds_nguoi_dung, (so_luong_nguoi_dung + 1) * sizeof(NguoiDung));
    if (temp == NULL)
    {
        printf("Lỗi: Không đủ bộ nhớ để thêm tài khoản!\n");
        return;
    }
    ds_nguoi_dung = temp; // Chỉ gán lại con trỏ khi realloc thành công

    moi.id = id_nguoi_dung_tiep_theo++; // Gán ID tự tăng, sau đó tăng biến đếm ID cho lần thêm kế tiếp
    strcpy(moi.ten_dang_nhap, ten);
    moi.vai_tro = vai_tro;

    ds_nguoi_dung[so_luong_nguoi_dung] = moi; // Thêm vào cuối mảng
    so_luong_nguoi_dung++;

    printf("Đã thêm tài khoản \"%s\" (ID = %d) thành công!\n", moi.ten_dang_nhap, moi.id);
}

// 1.2.3 Xóa tài khoản (không cho xóa Admin gốc và tài khoản đang đăng nhập)
void xoa_tai_khoan()
{
    char ten[50];
    char thong_bao[200];
    int vt;
    NguoiDung *temp;

    nhap_chuoi("Nhập tên đăng nhập của tài khoản cần xóa: ", ten, sizeof(ten));

    vt = tim_nguoi_dung_theo_ten(ds_nguoi_dung, so_luong_nguoi_dung, ten);
    if (vt == -1)
    {
        printf("Lỗi: Không tìm thấy tài khoản.\n");
        return;
    }

    if (ds_nguoi_dung[vt].id == 1)
    {
        printf("Lỗi: Không thể xóa tài khoản Admin gốc của hệ thống.\n");
        return;
    }

    if (ds_nguoi_dung[vt].id == id_dang_nhap)
    {
        printf("Lỗi: Không thể tự xóa tài khoản bạn đang đăng nhập.\n");
        return;
    }

    // Ghép câu hỏi xác nhận đúng theo mẫu: "... người dùng ... có vai trò ... (Y/N)?"
    snprintf(thong_bao, sizeof(thong_bao),
             "Bạn có chắc muốn xóa người dùng %s có vai trò %s (Y/N)? ",
             ds_nguoi_dung[vt].ten_dang_nhap, ten_vai_tro(ds_nguoi_dung[vt].vai_tro));

    if (!xac_nhan(thong_bao))
    {
        printf("Đã hủy việc xóa tài khoản.\n");
        return;
    }

    // Dời các phần tử phía sau lên 1 vị trí để lấp chỗ trống của phần tử bị xóa
    for (int i = vt; i < so_luong_nguoi_dung - 1; i++)
    {
        ds_nguoi_dung[i] = ds_nguoi_dung[i + 1];
    }
    so_luong_nguoi_dung--;

    if (so_luong_nguoi_dung == 0)
    {
        free(ds_nguoi_dung); // Xóa hết phần tử thì trả cả vùng nhớ về cho hệ thống
        ds_nguoi_dung = NULL;
    }
    else
    {
        // Thu nhỏ mảng động cho đúng số phần tử mới để tiết kiệm bộ nhớ
        temp = realloc(ds_nguoi_dung, so_luong_nguoi_dung * sizeof(NguoiDung));
        if (temp != NULL)
        {
            ds_nguoi_dung = temp;
        }
    }

    printf("Đã xóa tài khoản thành công!\n");
}

// 1.2.4 Sửa thông tin tài khoản (chọn sửa vai trò hoặc sửa mật khẩu)
void sua_tai_khoan()
{
    char ten[50];
    int vt, lua_chon, vai_tro_moi;

    nhap_chuoi("Nhập tên đăng nhập của tài khoản cần sửa: ", ten, sizeof(ten));

    vt = tim_nguoi_dung_theo_ten(ds_nguoi_dung, so_luong_nguoi_dung, ten);
    if (vt == -1)
    {
        printf("Lỗi: Không tìm thấy tài khoản.\n");
        return;
    }

    printf("Đã tìm thấy tài khoản: ID = %d | %s | Vai trò: %s\n",
           ds_nguoi_dung[vt].id, ds_nguoi_dung[vt].ten_dang_nhap,
           ten_vai_tro(ds_nguoi_dung[vt].vai_tro));

    printf("1. Sửa vai trò\n");
    printf("2. Sửa mật khẩu\n");
    lua_chon = nhap_so_nguyen("Nhập lựa chọn: ");

    if (lua_chon == 1)
    {
        do
        {
            vai_tro_moi = nhap_so_nguyen("Nhập vai trò mới (1 = Admin, 2 = Staff, 3 = SinhVien): ");
            if (vai_tro_moi < 1 || vai_tro_moi > 3)
            {
                printf("Lỗi: Vai trò chỉ được chọn 1, 2 hoặc 3.\n");
            }
        } while (vai_tro_moi < 1 || vai_tro_moi > 3);

        ds_nguoi_dung[vt].vai_tro = vai_tro_moi;

        // Nếu admin tự sửa vai trò của chính mình thì phải cập nhật luôn vai trò đang đăng nhập
        if (ds_nguoi_dung[vt].id == id_dang_nhap)
        {
            vai_tro_dang_nhap = vai_tro_moi;
        }
    }
    else if (lua_chon == 2)
    {
        nhap_chuoi("Nhập mật khẩu mới: ", ds_nguoi_dung[vt].mat_khau,
                   sizeof(ds_nguoi_dung[vt].mat_khau));
    }
    else
    {
        printf("Lựa chọn không hợp lệ!\n");
        return;
    }

    printf("Cập nhật thành công!\n");
}

// 1.2.5 Reset mật khẩu của một tài khoản về giá trị mặc định "123456"
void reset_mat_khau()
{
    char ten[50];
    int vt;

    nhap_chuoi("Nhập tên đăng nhập của tài khoản cần reset mật khẩu: ", ten, sizeof(ten));

    vt = tim_nguoi_dung_theo_ten(ds_nguoi_dung, so_luong_nguoi_dung, ten);
    if (vt == -1)
    {
        printf("Lỗi: Không tìm thấy tài khoản.\n");
        return;
    }

    strcpy(ds_nguoi_dung[vt].mat_khau, MAT_KHAU_MAC_DINH);
    printf("Đã reset mật khẩu của \"%s\" về \"%s\" thành công!\n", ten, MAT_KHAU_MAC_DINH);
}

/* ==================== NHÓM HÀM QUẢN LÝ LUỒNG CHÍNH ==================== */

// Khởi tạo dữ liệu ban đầu: tạo tài khoản Admin gốc (TEN_DANG_NHAP_MAC_DINH/MAT_KHAU_MAC_DINH)) để đăng nhập lần đầu
void khoi_tao_du_lieu()
{
    ds_nguoi_dung = malloc(sizeof(NguoiDung));
    if (ds_nguoi_dung == NULL)
    {
        printf("Lỗi: Không cấp phát được bộ nhớ!\n");
        exit(1);
    }

    ds_nguoi_dung[0].id = id_nguoi_dung_tiep_theo++;
    strcpy(ds_nguoi_dung[0].ten_dang_nhap, TEN_DANG_NHAP_MAC_DINH);
    strcpy(ds_nguoi_dung[0].mat_khau, MAT_KHAU_MAC_DINH);
    ds_nguoi_dung[0].vai_tro = VAI_TRO_ADMIN;
    so_luong_nguoi_dung = 1;
}

// Giải phóng toàn bộ bộ nhớ động trước khi thoát chương trình
void giai_phong_bo_nho()
{
    free(ds_nguoi_dung);
    ds_nguoi_dung = NULL;
    so_luong_nguoi_dung = 0;
    printf("Đã giải phóng toàn bộ bộ nhớ. Tạm biệt!\n");
}

// 1.1 Xử lý đăng nhập: kiểm tra tên tồn tại -> kiểm tra mật khẩu -> đọc vai trò
void dang_nhap()
{
    char ten[50], mk[50];
    int vt;

    printf("\n==================== ĐĂNG NHẬP HỆ THỐNG ====================\n");
    nhap_chuoi("Tên đăng nhập: ", ten, sizeof(ten));
    nhap_chuoi("Mật khẩu: ", mk, sizeof(mk));

    vt = tim_nguoi_dung_theo_ten(ds_nguoi_dung, so_luong_nguoi_dung, ten);
    if (vt == -1)
    {
        printf("Lỗi: Tên đăng nhập không tồn tại.\n");
        return;
    }

    if (strcmp(ds_nguoi_dung[vt].mat_khau, mk) != 0)
    {
        printf("Lỗi: Sai mật khẩu.\n");
        return;
    }

    // Đăng nhập thành công: ghi nhớ thông tin người dùng hiện tại vào biến toàn cục
    id_dang_nhap = ds_nguoi_dung[vt].id;
    vai_tro_dang_nhap = ds_nguoi_dung[vt].vai_tro;
    da_dang_nhap = 1;

    printf("Đăng nhập thành công! Xin chào \"%s\" với vai trò %s.\n",
           ds_nguoi_dung[vt].ten_dang_nhap, ten_vai_tro(vai_tro_dang_nhap));
}

// 1.2 Menu Admin: quản lý các tài khoản trong hệ thống
void menu_admin()
{
    int lua_chon;

    do
    {
        printf("\n========================= MENU ADMIN =========================\n");
        printf("1. Hiển thị danh sách tài khoản\n");
        printf("2. Thêm tài khoản\n");
        printf("3. Xóa tài khoản\n");
        printf("4. Sửa thông tin tài khoản\n");
        printf("5. Reset mật khẩu\n");
        printf("6. Đăng xuất\n");
        printf("0. Thoát chương trình\n");
        lua_chon = nhap_so_nguyen("Nhập lựa chọn của bạn: ");

        switch (lua_chon)
        {
        case 1:
            hien_thi_danh_sach_tai_khoan();
            break;
        case 2:
            them_tai_khoan();
            break;
        case 3:
            xoa_tai_khoan();
            break;
        case 4:
            sua_tai_khoan();
            break;
        case 5:
            reset_mat_khau();
            break;
        case 6:
            // Đăng xuất: reset trạng thái để quay về màn hình đăng nhập
            da_dang_nhap = 0;
            id_dang_nhap = -1;
            printf("Đã đăng xuất khỏi hệ thống.\n");
            break;
        case 0:
            giai_phong_bo_nho();
            exit(0);
        default:
            printf("Lựa chọn không hợp lệ! Vui lòng chọn lại.\n");
        }
    } while (da_dang_nhap); // Vòng lặp kết thúc khi người dùng chọn đăng xuất
}

int main()
{
    khoi_tao_du_lieu();

    printf("Chào mừng đến với Hệ thống Quản lý Thư viện!\n");

    while (1)
    {
        // Chưa đăng nhập thì luôn quay lại màn hình đăng nhập trước tiên
        if (!da_dang_nhap)
        {
            dang_nhap();
            continue;
        }

        // Đọc vai trò của tài khoản vừa đăng nhập để chuyển đến menu tương ứng
        if (vai_tro_dang_nhap == VAI_TRO_ADMIN)
        {
            menu_admin();
        }
        else
        {
            printf("Menu của vai trò \"%s\" sẽ được xây dựng ở giai đoạn sau. Tạm thời đăng xuất.\n",
                   ten_vai_tro(vai_tro_dang_nhap));
            da_dang_nhap = 0;
        }
    }

    return 0;
}
