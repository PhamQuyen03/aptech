/*
 * BÀI TẬP LỚN - HỆ THỐNG QUẢN LÝ THƯ VIỆN
 * GIAI ĐOẠN 3 (BƯỚC HOÀN THÀNH): STEP 1 + STEP 2 + 1.4 Menu Sinh viên
 *
 * Nội dung mới của giai đoạn này (lấy nguyên code STEP 1 và STEP 2 làm tiếp):
 * - Menu Sinh viên: xem danh sách sách (thông tin cơ bản), tìm kiếm sách
 * - Danh sách sách đang mượn CỦA TÔI (lọc theo ID của sinh viên đang đăng nhập)
 * - Hoàn thiện đầy đủ 3 vai trò: Admin, Staff (Thủ thư), Sinh viên
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

typedef struct Sach
{
    char ma_sach[20];   // Mã sách, duy nhất trong thư viện
    char ten_sach[100]; // Tên cuốn sách
    char tac_gia[50];   // Tác giả
    int nam_xb;         // Năm xuất bản
    int tong_sl;        // Tổng số lượng bản sách
    int da_muon;        // Số lượng bản đã cho sinh viên mượn
} Sach;

typedef struct PhieuMuon
{
    int id_phieu;      // Số phiếu tự động tăng, duy nhất cho từng lần mượn
    int id_nguoi_dung; // ID của sinh viên mượn sách (liên kết mảng tài khoản)
    char ma_sach[20];  // Mã sách được mượn (liên kết mảng sách)
    int trang_thai;    // 0 = đang mượn, 1 = đã trả
} PhieuMuon;

/* ===== BIẾN TOÀN CỤC: quản lý mảng động tài khoản ===== */
NguoiDung *ds_nguoi_dung = NULL; // Con trỏ trỏ đến mảng động các tài khoản
int so_luong_nguoi_dung = 0;     // Số tài khoản hiện có trong mảng
int id_nguoi_dung_tiep_theo = 1; // Biến tạo ID tự tăng để ID mới luôn là duy nhất

/* ===== BIẾN TOÀN CỤC: quản lý mảng động sách ===== */
Sach *ds_sach = NULL; // Con trỏ trỏ đến mảng động các cuốn sách
int so_luong_sach = 0;

/* ===== BIẾN TOÀN CỤC: quản lý mảng động phiếu mượn ===== */
PhieuMuon *ds_phieu_muon = NULL; // Con trỏ trỏ đến mảng động các phiếu mượn
int so_luong_phieu = 0;
int id_phieu_tiep_theo = 1; // Biến tạo số phiếu tự tăng

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
int ten_chua_tu_khoa(const char *ten, const char *tu_khoa);

/* Nhóm hàm tìm kiếm */
int tim_nguoi_dung_theo_ten(NguoiDung *ds, int n, const char *ten);
int tim_nguoi_dung_theo_id(NguoiDung *ds, int n, int id);
int tim_sach_theo_ma(Sach *ds, int n, const char *ma);
int tim_phieu_dang_muon(int id_sv, const char *ma);

/* Nhóm hàm nghiệp vụ Admin */
void hien_thi_danh_sach_tai_khoan();
void them_tai_khoan();
void xoa_tai_khoan();
void sua_tai_khoan();
void reset_mat_khau();

/* Nhóm hàm nghiệp vụ Staff */
void them_sach();
void hien_thi_danh_sach_sach();
void cap_nhat_sach();
void xoa_sach();
void tim_kiem_sach();
void sap_xep_sach();
void muon_sach();
void tra_sach();
void hien_thi_sach_dang_muon();

/* Nhóm hàm nghiệp vụ Sinh viên */
void hien_thi_sach_co_ban();
void sach_toi_dang_muon();

/* Nhóm hàm quản lý luồng chính */
void khoi_tao_du_lieu();
void giai_phong_bo_nho();
void dang_nhap();
void menu_admin();
void menu_staff();
void menu_sinh_vien();

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

// Kiểm tra tên sách có chứa từ khóa hay không (không phân biệt hoa/thường)
int ten_chua_tu_khoa(const char *ten, const char *tu_khoa)
{
    char ten_thuong[150], tu_khoa_thuong[150];
    int i;

    // Chuyển cả tên sách và từ khóa về chữ thường rồi mới strstr để "Cơ bản" khớp với "cơ bản"
    for (i = 0; ten[i] != '\0' && i < 149; i++)
    {
        ten_thuong[i] = tolower((unsigned char)ten[i]);
    }
    ten_thuong[i] = '\0';

    for (i = 0; tu_khoa[i] != '\0' && i < 149; i++)
    {
        tu_khoa_thuong[i] = tolower((unsigned char)tu_khoa[i]);
    }
    tu_khoa_thuong[i] = '\0';

    return strstr(ten_thuong, tu_khoa_thuong) != NULL;
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

// Tìm vị trí tài khoản theo ID. Trả về index (0..n-1) hoặc -1 nếu không thấy
int tim_nguoi_dung_theo_id(NguoiDung *ds, int n, int id)
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// Tìm vị trí cuốn sách theo mã sách. Trả về index (0..n-1) hoặc -1 nếu không thấy
int tim_sach_theo_ma(Sach *ds, int n, const char *ma)
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

// Tìm phiếu mượn "đang mượn" (trạng thái 0) của một sinh viên cho một cuốn sách cụ thể.
// Trả về index trong mảng phiếu hoặc -1 nếu sinh viên này không mượn cuốn sách đó
int tim_phieu_dang_muon(int id_sv, const char *ma)
{
    for (int i = 0; i < so_luong_phieu; i++)
    {
        if (ds_phieu_muon[i].id_nguoi_dung == id_sv &&
            strcmp(ds_phieu_muon[i].ma_sach, ma) == 0 &&
            ds_phieu_muon[i].trang_thai == 0)
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

/* ==================== NHÓM HÀM NGHIỆP VỤ STAFF ==================== */

// 1.3.1 Thêm sách mới (mã sách phải duy nhất, da_muon tự động = 0)
void them_sach()
{
    Sach moi;
    char ma[20];
    Sach *temp;

    nhap_chuoi("Nhập mã sách: ", ma, sizeof(ma));

    if (tim_sach_theo_ma(ds_sach, so_luong_sach, ma) != -1)
    {
        printf("Lỗi: Mã sách đã tồn tại.\n");
        return;
    }
    strcpy(moi.ma_sach, ma);

    nhap_chuoi("Nhập tên sách: ", moi.ten_sach, sizeof(moi.ten_sach));
    nhap_chuoi("Nhập tác giả: ", moi.tac_gia, sizeof(moi.tac_gia));
    moi.nam_xb = nhap_so_nguyen("Nhập năm xuất bản: ");
    moi.tong_sl = nhap_so_nguyen("Nhập tổng số lượng: ");
    moi.da_muon = 0; // Sách mới nhập về nên chưa cho mượn cuốn nào

    temp = realloc(ds_sach, (so_luong_sach + 1) * sizeof(Sach));
    if (temp == NULL)
    {
        printf("Lỗi: Không đủ bộ nhớ để thêm sách!\n");
        return;
    }
    ds_sach = temp;

    ds_sach[so_luong_sach] = moi;
    so_luong_sach++;

    printf("Đã thêm sách thành công!\n");
}

// 1.3.2 Hiển thị danh sách sách (kèm cột "Hiện có" = tổng số lượng - đã mượn)
void hien_thi_danh_sach_sach()
{
    if (so_luong_sach == 0)
    {
        printf("Thư viện hiện chưa có cuốn sách nào.\n");
        return;
    }

    printf("\n========================= DANH MỤC SÁCH =========================\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Tổng SL", "Đã mượn", "Hiện có");

    for (int i = 0; i < so_luong_sach; i++)
    {
        // Số lượng hiện có được tính bằng tổng số lượng trừ đi số bản đã cho mượn
        printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
               ds_sach[i].ma_sach, ds_sach[i].ten_sach, ds_sach[i].tac_gia,
               ds_sach[i].nam_xb, ds_sach[i].tong_sl, ds_sach[i].da_muon,
               ds_sach[i].tong_sl - ds_sach[i].da_muon);
    }

    printf("Hiện thư viện có %d đầu sách.\n", so_luong_sach);
}

// 1.3.3 Cập nhật thông tin sách theo mã
void cap_nhat_sach()
{
    char ma[20];
    int vt, lua_chon;

    nhap_chuoi("Nhập mã sách cần cập nhật: ", ma, sizeof(ma));

    vt = tim_sach_theo_ma(ds_sach, so_luong_sach, ma);
    if (vt == -1)
    {
        printf("Lỗi: Mã sách không tồn tại.\n");
        return;
    }

    printf("Đã tìm thấy sách: [%s] %s - %s\n",
           ds_sach[vt].ma_sach, ds_sach[vt].ten_sach, ds_sach[vt].tac_gia);

    printf("1. Tên sách\n");
    printf("2. Tác giả\n");
    printf("3. Năm xuất bản\n");
    printf("4. Tổng số lượng\n");
    lua_chon = nhap_so_nguyen("Chọn thông tin cần sửa: ");

    switch (lua_chon)
    {
    case 1:
        nhap_chuoi("Nhập tên sách mới: ", ds_sach[vt].ten_sach, sizeof(ds_sach[vt].ten_sach));
        break;
    case 2:
        nhap_chuoi("Nhập tác giả mới: ", ds_sach[vt].tac_gia, sizeof(ds_sach[vt].tac_gia));
        break;
    case 3:
        ds_sach[vt].nam_xb = nhap_so_nguyen("Nhập năm xuất bản mới: ");
        break;
    case 4:
        do
        {
            ds_sach[vt].tong_sl = nhap_so_nguyen("Nhập tổng số lượng mới: ");
            // Ràng buộc: tổng số lượng không được thấp hơn số bản đã cho mượn
            if (ds_sach[vt].tong_sl < ds_sach[vt].da_muon)
            {
                printf("Lỗi: Tổng số lượng không được thấp hơn số lượng đã cho mượn (%d). Nhập lại!\n",
                       ds_sach[vt].da_muon);
            }
        } while (ds_sach[vt].tong_sl < ds_sach[vt].da_muon);
        break;
    default:
        printf("Lựa chọn không hợp lệ!\n");
        return;
    }

    printf("Cập nhật thành công!\n");
}

// 1.3.4 Xóa sách (chỉ xóa được khi sách không đang được ai mượn)
void xoa_sach()
{
    char ma[20];
    int vt;
    Sach *temp;

    nhap_chuoi("Nhập mã sách cần xóa: ", ma, sizeof(ma));

    vt = tim_sach_theo_ma(ds_sach, so_luong_sach, ma);
    if (vt == -1)
    {
        printf("Lỗi: Mã sách không tồn tại.\n");
        return;
    }

    if (ds_sach[vt].da_muon > 0)
    {
        printf("Lỗi: Không thể xóa sách đang có người mượn.\n");
        return;
    }

    printf("Thông tin sách cần xóa:\n");
    printf("  Mã sách:       %s\n", ds_sach[vt].ma_sach);
    printf("  Tên sách:      %s\n", ds_sach[vt].ten_sach);
    printf("  Tác giả:       %s\n", ds_sach[vt].tac_gia);
    printf("  Năm xuất bản:  %d\n", ds_sach[vt].nam_xb);
    printf("  Tổng số lượng: %d\n", ds_sach[vt].tong_sl);

    if (!xac_nhan("Bạn có chắc chắn muốn xóa cuốn sách này? (Y/N): "))
    {
        printf("Đã hủy việc xóa sách.\n");
        return;
    }

    for (int i = vt; i < so_luong_sach - 1; i++)
    {
        ds_sach[i] = ds_sach[i + 1];
    }
    so_luong_sach--;

    if (so_luong_sach == 0)
    {
        free(ds_sach);
        ds_sach = NULL;
    }
    else
    {
        temp = realloc(ds_sach, so_luong_sach * sizeof(Sach));
        if (temp != NULL)
        {
            ds_sach = temp;
        }
    }

    printf("Đã xóa sách thành công!\n");
}

// 1.3.5 Tìm kiếm sách theo từ khóa trong tên (không phân biệt hoa/thường)
void tim_kiem_sach()
{
    char tu_khoa[100];
    int tim_thay = 0;

    nhap_chuoi("Nhập từ khóa cần tìm: ", tu_khoa, sizeof(tu_khoa));

    printf("\n======================= KẾT QUẢ TÌM KIẾM =======================\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Tổng SL", "Đã mượn", "Hiện có");

    for (int i = 0; i < so_luong_sach; i++)
    {
        if (ten_chua_tu_khoa(ds_sach[i].ten_sach, tu_khoa))
        {
            printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
                   ds_sach[i].ma_sach, ds_sach[i].ten_sach, ds_sach[i].tac_gia,
                   ds_sach[i].nam_xb, ds_sach[i].tong_sl, ds_sach[i].da_muon,
                   ds_sach[i].tong_sl - ds_sach[i].da_muon);
            tim_thay = 1;
        }
    }

    if (!tim_thay)
    {
        printf("Không tìm thấy sách nào có tên chứa từ khóa \"%s\".\n", tu_khoa);
    }
}

// 1.3.6 Sắp xếp danh sách sách theo năm xuất bản (tăng dần hoặc giảm dần)
void sap_xep_sach()
{
    Sach temp;
    int lua_chon;

    if (so_luong_sach == 0)
    {
        printf("Thư viện hiện chưa có cuốn sách nào.\n");
        return;
    }

    printf("1. Sắp xếp theo năm xuất bản tăng dần (từ cũ đến mới)\n");
    printf("2. Sắp xếp theo năm xuất bản giảm dần (từ mới đến cũ)\n");
    lua_chon = nhap_so_nguyen("Nhập lựa chọn: ");

    if (lua_chon != 1 && lua_chon != 2)
    {
        printf("Lựa chọn không hợp lệ!\n");
        return;
    }

    for (int i = 0; i < so_luong_sach - 1; i++)
    {
        for (int j = 0; j < so_luong_sach - 1 - i; j++)
        {
            // Điều kiện hoán đổi phụ thuộc thứ tự người dùng chọn
            int can_hoan_doi = (lua_chon == 1)
                                   ? (ds_sach[j].nam_xb > ds_sach[j + 1].nam_xb)
                                   : (ds_sach[j].nam_xb < ds_sach[j + 1].nam_xb);

            if (can_hoan_doi)
            {
                // Phải hoán đổi nguyên struct chứ không chỉ hoán đổi trường năm
                temp = ds_sach[j];
                ds_sach[j] = ds_sach[j + 1];
                ds_sach[j + 1] = temp;
            }
        }
    }

    printf("Đã sắp xếp danh sách sách thành công!\n");
    hien_thi_danh_sach_sach();
}

// 1.3.7 Cho mượn sách: kiểm tra sinh viên, sách, còn sách, chưa mượn rồi mới tạo phiếu
void muon_sach()
{
    PhieuMuon moi;
    PhieuMuon *temp;
    int id_sv, vt_sv, vt_sach;
    char ma[20];

    id_sv = nhap_so_nguyen("Nhập ID của sinh viên mượn sách: ");

    vt_sv = tim_nguoi_dung_theo_id(ds_nguoi_dung, so_luong_nguoi_dung, id_sv);
    if (vt_sv == -1)
    {
        printf("Lỗi: Không tìm thấy sinh viên có ID %d.\n", id_sv);
        return;
    }
    if (ds_nguoi_dung[vt_sv].vai_tro != VAI_TRO_SINH_VIEN)
    {
        printf("Lỗi: Tài khoản ID %d không phải là Sinh viên.\n", id_sv);
        return;
    }

    nhap_chuoi("Nhập mã sách cần mượn: ", ma, sizeof(ma));

    vt_sach = tim_sach_theo_ma(ds_sach, so_luong_sach, ma);
    if (vt_sach == -1)
    {
        printf("Lỗi: Mã sách không tồn tại.\n");
        return;
    }

    // Còn sách để mượn khi số bản đã mượn vẫn nhỏ hơn tổng số lượng
    if (ds_sach[vt_sach].da_muon >= ds_sach[vt_sach].tong_sl)
    {
        printf("Lỗi: Sách \"%s\" đã hết, không còn bản nào để mượn.\n", ds_sach[vt_sach].ten_sach);
        return;
    }

    // Mỗi sinh viên chỉ được mượn 1 bản của cùng một cuốn sách tại một thời điểm
    if (tim_phieu_dang_muon(id_sv, ma) != -1)
    {
        printf("Lỗi: Sinh viên này đang mượn cuốn sách này và chưa trả.\n");
        return;
    }

    ds_sach[vt_sach].da_muon++; // Tăng số bản đã cho mượn của cuốn sách lên 1

    temp = realloc(ds_phieu_muon, (so_luong_phieu + 1) * sizeof(PhieuMuon));
    if (temp == NULL)
    {
        printf("Lỗi: Không đủ bộ nhớ để ghi phiếu mượn!\n");
        ds_sach[vt_sach].da_muon--; // Ghi phiếu thất bại thì hoàn lại số mượn vừa tăng
        return;
    }
    ds_phieu_muon = temp;

    moi.id_phieu = id_phieu_tiep_theo++;
    moi.id_nguoi_dung = id_sv;
    strcpy(moi.ma_sach, ma);
    moi.trang_thai = 0; // 0 = đang mượn

    ds_phieu_muon[so_luong_phieu] = moi;
    so_luong_phieu++;

    printf("Cho mượn thành công! Sinh viên %s (ID %d) mượn sách \"%s\".\n",
           ds_nguoi_dung[vt_sv].ten_dang_nhap, id_sv, ds_sach[vt_sach].ten_sach);
}

// 1.3.8 Trả sách: tìm phiếu đang mượn, đổi trạng thái và giảm số đã mượn
void tra_sach()
{
    int id_sv, vt_phieu, vt_sach, vt_sv;
    char ma[20];

    id_sv = nhap_so_nguyen("Nhập ID của sinh viên trả sách: ");
    nhap_chuoi("Nhập mã sách cần trả: ", ma, sizeof(ma));

    vt_phieu = tim_phieu_dang_muon(id_sv, ma);
    if (vt_phieu == -1)
    {
        printf("Lỗi: Sinh viên không có mượn cuốn sách này.\n");
        return;
    }

    ds_phieu_muon[vt_phieu].trang_thai = 1; // Đổi trạng thái 0 (đang mượn) -> 1 (đã trả)

    // Giảm số bản đã cho mượn của cuốn sách xuống 1
    vt_sach = tim_sach_theo_ma(ds_sach, so_luong_sach, ma);
    if (vt_sach != -1)
    {
        ds_sach[vt_sach].da_muon--;
    }

    vt_sv = tim_nguoi_dung_theo_id(ds_nguoi_dung, so_luong_nguoi_dung, id_sv);
    printf("Trả sách thành công! Đã ghi nhận \"%s\" trả sách mã %s.\n",
           ds_nguoi_dung[vt_sv].ten_dang_nhap, ma);
}

// 1.3.9 Danh sách toàn bộ sách đang được mượn (tra cứu ngược tên SV và tên sách)
void hien_thi_sach_dang_muon()
{
    int co = 0;
    int vt_sv, vt_sach;

    printf("\n==================== SÁCH ĐANG ĐƯỢC MƯỢN ====================\n");
    printf("%-10s %-8s %-25s %-10s %-30s\n",
           "Mã phiếu", "ID SV", "Tên sinh viên", "Mã sách", "Tên sách");

    for (int i = 0; i < so_luong_phieu; i++)
    {
        if (ds_phieu_muon[i].trang_thai != 0)
        {
            continue; // Bỏ qua các phiếu đã trả
        }

        // Phiếu mượn chỉ lưu ID và mã sách nên phải tra cứu ngược 2 mảng kia để lấy tên hiển thị
        vt_sv = tim_nguoi_dung_theo_id(ds_nguoi_dung, so_luong_nguoi_dung,
                                       ds_phieu_muon[i].id_nguoi_dung);
        vt_sach = tim_sach_theo_ma(ds_sach, so_luong_sach, ds_phieu_muon[i].ma_sach);

        if (vt_sv != -1 && vt_sach != -1)
        {
            printf("%-10d %-8d %-25s %-10s %-30s\n",
                   ds_phieu_muon[i].id_phieu,
                   ds_nguoi_dung[vt_sv].id,
                   ds_nguoi_dung[vt_sv].ten_dang_nhap,
                   ds_sach[vt_sach].ma_sach,
                   ds_sach[vt_sach].ten_sach);
            co = 1;
        }
    }

    if (!co)
    {
        printf("Hiện không có cuốn sách nào đang được mượn.\n");
    }
}

/* ==================== NHÓM HÀM NGHIỆP VỤ SINH VIÊN ==================== */

// 1.4.1 Danh sách sách cho Sinh viên: chỉ hiện thông tin cơ bản + số lượng hiện có
void hien_thi_sach_co_ban()
{
    if (so_luong_sach == 0)
    {
        printf("Thư viện hiện chưa có cuốn sách nào.\n");
        return;
    }

    printf("\n===================== DANH MỤC SÁCH (RÚT GỌN) =====================\n");
    printf("%-10s %-30s %-20s %-8s %-8s\n",
           "Mã sách", "Tên sách", "Tác giả", "Năm XB", "Hiện có");

    for (int i = 0; i < so_luong_sach; i++)
    {
        // Sinh viên chỉ cần biết còn bao nhiêu bản để mượn nên không in các cột quản lý
        printf("%-10s %-30s %-20s %-8d %-8d\n",
               ds_sach[i].ma_sach, ds_sach[i].ten_sach, ds_sach[i].tac_gia,
               ds_sach[i].nam_xb, ds_sach[i].tong_sl - ds_sach[i].da_muon);
    }
}

// 1.4.3 Danh sách sách đang mượn CỦA TÔI: lọc phiếu theo ID sinh viên đang đăng nhập
void sach_toi_dang_muon()
{
    int co = 0;
    int vt_sach;

    printf("\n================= SÁCH TÔI ĐANG MƯỢN =================\n");
    printf("%-10s %-10s %-30s %-20s %-8s\n",
           "Mã phiếu", "Mã sách", "Tên sách", "Tác giả", "Năm XB");

    for (int i = 0; i < so_luong_phieu; i++)
    {
        // Chỉ lấy phiếu của chính sinh viên đang đăng nhập và còn đang mượn
        if (ds_phieu_muon[i].id_nguoi_dung == id_dang_nhap && ds_phieu_muon[i].trang_thai == 0)
        {
            // Phiếu chỉ lưu mã sách nên phải tra lại mảng sách để lấy thông tin hiển thị
            vt_sach = tim_sach_theo_ma(ds_sach, so_luong_sach, ds_phieu_muon[i].ma_sach);

            if (vt_sach != -1)
            {
                printf("%-10d %-10s %-30s %-20s %-8d\n",
                       ds_phieu_muon[i].id_phieu,
                       ds_sach[vt_sach].ma_sach,
                       ds_sach[vt_sach].ten_sach,
                       ds_sach[vt_sach].tac_gia,
                       ds_sach[vt_sach].nam_xb);
                co = 1;
            }
        }
    }

    if (!co)
    {
        printf("Bạn hiện không đang mượn cuốn sách nào.\n");
    }
}

/* ==================== NHÓM HÀM QUẢN LÝ LUỒNG CHÍNH ==================== */

// Khởi tạo dữ liệu ban đầu: tạo tài khoản Admin gốc (TEN_DANG_NHAP_MAC_DINH/MAT_KHAU_MAC_DINH) để đăng nhập lần đầu
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

// Giải phóng toàn bộ bộ nhớ động của cả 3 mảng trước khi thoát chương trình
void giai_phong_bo_nho()
{
    free(ds_nguoi_dung);
    ds_nguoi_dung = NULL;
    so_luong_nguoi_dung = 0;

    free(ds_sach);
    ds_sach = NULL;
    so_luong_sach = 0;

    free(ds_phieu_muon);
    ds_phieu_muon = NULL;
    so_luong_phieu = 0;

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

// 1.3 Menu Staff (Thủ thư): quản lý sách và nghiệp vụ mượn/trả
void menu_staff()
{
    int lua_chon;

    do
    {
        printf("\n========================= MENU THỦ THƯ =========================\n");
        printf("1. Thêm sách mới\n");
        printf("2. Hiển thị danh sách sách\n");
        printf("3. Cập nhật thông tin sách\n");
        printf("4. Xóa một cuốn sách\n");
        printf("5. Tìm kiếm sách\n");
        printf("6. Sắp xếp sách theo năm xuất bản\n");
        printf("7. Cho mượn sách\n");
        printf("8. Trả sách\n");
        printf("9. Danh sách sách đang được mượn\n");
        printf("10. Đăng xuất\n");
        printf("0. Thoát chương trình\n");
        lua_chon = nhap_so_nguyen("Nhập lựa chọn của bạn: ");

        switch (lua_chon)
        {
        case 1:
            them_sach();
            break;
        case 2:
            hien_thi_danh_sach_sach();
            break;
        case 3:
            cap_nhat_sach();
            break;
        case 4:
            xoa_sach();
            break;
        case 5:
            tim_kiem_sach();
            break;
        case 6:
            sap_xep_sach();
            break;
        case 7:
            muon_sach();
            break;
        case 8:
            tra_sach();
            break;
        case 9:
            hien_thi_sach_dang_muon();
            break;
        case 10:
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
    } while (da_dang_nhap);
}

// 1.4 Menu Sinh viên: chỉ có quyền xem thông tin
void menu_sinh_vien()
{
    int lua_chon;

    do
    {
        printf("\n======================== MENU SINH VIÊN ========================\n");
        printf("1. Danh sách sách\n");
        printf("2. Tìm kiếm sách\n");
        printf("3. Danh sách sách đang mượn (của tôi)\n");
        printf("4. Đăng xuất\n");
        printf("0. Thoát chương trình\n");
        lua_chon = nhap_so_nguyen("Nhập lựa chọn của bạn: ");

        switch (lua_chon)
        {
        case 1:
            hien_thi_sach_co_ban();
            break;
        case 2:
            tim_kiem_sach();
            break;
        case 3:
            sach_toi_dang_muon();
            break;
        case 4:
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
    } while (da_dang_nhap);
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
        else if (vai_tro_dang_nhap == VAI_TRO_STAFF)
        {
            menu_staff();
        }
        else
        {
            menu_sinh_vien();
        }
    }

    return 0;
}
