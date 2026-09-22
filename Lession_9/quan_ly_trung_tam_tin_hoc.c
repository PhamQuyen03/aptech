/*
 * BAI TAP LON - HE THONG QUAN LY TRUNG TAM TIN HOC
 * Khong su dung bien toan cuc, quan ly bo nho bang mang dong malloc/realloc/free
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct Nguoi dung / Tai khoan
typedef struct TaiKhoan
{
    int id;
    char username[50];
    char password[50];
    int role; // 1 = Admin, 2 = Teacher (Giao vien), 3 = Student (Hoc vien)
} TaiKhoan;

// Struct Khoa hoc
typedef struct KhoaHoc
{
    char maKhoaHoc[30]; // Ma khoa hoc, duy nhat
    char tenKhoaHoc[100];
    int idGiaoVien;   // ID giao vien phu trach (role = 2, 0 neu chua phan cong)
    int siSoToiDa;    // Si so toi da cua lop hoc
    int siSoDaDangKy; // Si so da dang ky hien tai (khoi tao = 0)
} KhoaHoc;

// Struct Dang ky
typedef struct DangKy
{
    int idDangKy;       // So dang ky tu tang
    int idHocVien;      // ID hoc vien
    char maKhoaHoc[30]; // Ma khoa hoc
    int trangThai;      // 0 = Dang hoc, 1 = Da hoan thanh
} DangKy;

// ==================== KHAI BAO NGUYEN MAU HAM ====================

void themTkMacDinh(TaiKhoan *danhSachTK, int *soluongTK);
void themKhoaHocMacDinh(KhoaHoc *danhSachKH, int *soluongKH);
void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkHienTai);
char *tenVaiTro(int role);
int timTkTheoTen(TaiKhoan *danhSachTK, int soluongTK, char *ten);
int timTkTheoId(TaiKhoan *danhSachTK, int soluongTK, int id);
int timKhoaHocTheoMa(KhoaHoc *danhSachKH, int soluongKH, char *ma);

// Menu Admin
TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo,
                           KhoaHoc **danhSachKH, int *soluongKH, int *maxSizeKH,
                           DangKy **danhSachDK, int *soluongDK, int *maxSizeDK,
                           TaiKhoan *tkHienTai);

// Chuc nang quan ly Tai khoan
void hienThiDsTk(TaiKhoan *danhSachTK, int soluongTK);
TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, int *idTiepTheo);
TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                TaiKhoan *tkHienTai,
                KhoaHoc *danhSachKH, int soluongKH,
                DangKy **danhSachDK, int *soluongDK, int *maxSizeDK);

// Chuc nang quan ly Khoa hoc
KhoaHoc *themKhoaHoc(KhoaHoc *danhSachKH, int *soluongKH, int *maxSizeKH,
                     TaiKhoan *danhSachTK, int soluongTK);
void suaKhoaHoc(KhoaHoc *danhSachKH, int soluongKH, TaiKhoan *danhSachTK, int soluongTK);
KhoaHoc *xoaKhoaHoc(KhoaHoc *danhSachKH, int *soluongKH, int *maxSizeKH);
void sapXepKhoaHocGiamDanSiSo(KhoaHoc *danhSachKH, int soluongKH);
void hienThiDsKhoaHoc(KhoaHoc *danhSachKH, int soluongKH, TaiKhoan *danhSachTK, int soluongTK);

// ==================== HAM MAIN ====================

int main()
{
    // Quan ly mang dong TaiKhoan
    int soluongTK = 0;
    int maxSizeTK = 5;
    int idTkTiepTheo = 4; // 3 tai khoan mac dinh id: 1, 2, 3
    TaiKhoan *danhSachTK;

    // Quan ly mang dong KhoaHoc
    int soluongKH = 0;
    int maxSizeKH = 5;
    KhoaHoc *danhSachKH;

    // Quan ly mang dong DangKy
    int soluongDK = 0;
    int maxSizeDK = 5;
    DangKy *danhSachDK;

    // Luu thong tin tai khoan dang dang nhap
    TaiKhoan tkHienTai;
    tkHienTai.role = -1; // -1 nghia la CHUA dang nhap

    // Cap phat bo nho dong cho 3 mang
    danhSachTK = (TaiKhoan *)malloc(maxSizeTK * sizeof(TaiKhoan));
    danhSachKH = (KhoaHoc *)malloc(maxSizeKH * sizeof(KhoaHoc));
    danhSachDK = (DangKy *)malloc(maxSizeDK * sizeof(DangKy));

    if (danhSachTK == NULL || danhSachKH == NULL || danhSachDK == NULL)
    {
        printf("Loi: Khong the cap phat bo nho ban dau!\n");
        return 1;
    }

    // Khoi tao du lieu ban dau (Admin goc va mau du lieu de kiem thu)
    themTkMacDinh(danhSachTK, &soluongTK);
    themKhoaHocMacDinh(danhSachKH, &soluongKH);

    printf("====================================================\n");
    printf("  CHAO MUNG DEN VOI HE THONG QUAN LY TRUNG TAM TIN HOC\n");
    printf("====================================================\n");

    while (1)
    {
        if (tkHienTai.role == -1)
        {
            dangnhap(danhSachTK, soluongTK, &tkHienTai);
            continue;
        }

        switch (tkHienTai.role)
        {
        case 1: // Vai tro Admin
            danhSachTK = hienThiAdminMenu(danhSachTK, &soluongTK, &maxSizeTK,
                                          &idTkTiepTheo,
                                          &danhSachKH, &soluongKH, &maxSizeKH,
                                          &danhSachDK, &soluongDK, &maxSizeDK,
                                          &tkHienTai);
            break;

        case 2: // Vai tro Teacher (Giao vien)
        case 3: // Vai tro Student (Hoc vien)
            printf("\nMenu cua vai tro \"%s\" se duoc xay dung o giai doan sau. Tam thoi dang xuat.\n",
                   tenVaiTro(tkHienTai.role));
            tkHienTai.role = -1;
            break;
        }

        // role = -2 nghia la nguoi dung chon "Thoat chuong trinh" hoac gap EOF
        if (tkHienTai.role == -2)
        {
            break;
        }
    }

    // Giai phong toan bo bo nho 3 mang dong truoc khi thoat
    if (danhSachTK != NULL)
    {
        free(danhSachTK);
        danhSachTK = NULL;
    }
    if (danhSachKH != NULL)
    {
        free(danhSachKH);
        danhSachKH = NULL;
    }
    if (danhSachDK != NULL)
    {
        free(danhSachDK);
        danhSachDK = NULL;
    }

    printf("\nDa giai phong toan bo bo nho. Chuong trinh ket thuc. Tam biet!\n");
    return 0;
}

// ==================== HAM TIEN ICH & KHOI TAO ====================

char *tenVaiTro(int role)
{
    if (role == 1)
    {
        return "Admin";
    }
    if (role == 2)
    {
        return "Giao vien";
    }
    if (role == 3)
    {
        return "Hoc vien";
    }
    return "Khong xac dinh";
}

int timTkTheoTen(TaiKhoan *danhSachTK, int soluongTK, char *ten)
{
    for (int i = 0; i < soluongTK; i++)
    {
        if (strcmp(danhSachTK[i].username, ten) == 0)
        {
            return i;
        }
    }
    return -1;
}

int timTkTheoId(TaiKhoan *danhSachTK, int soluongTK, int id)
{
    for (int i = 0; i < soluongTK; i++)
    {
        if (danhSachTK[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int timKhoaHocTheoMa(KhoaHoc *danhSachKH, int soluongKH, char *ma)
{
    for (int i = 0; i < soluongKH; i++)
    {
        if (strcmp(danhSachKH[i].maKhoaHoc, ma) == 0)
        {
            return i;
        }
    }
    return -1;
}

void themTkMacDinh(TaiKhoan *danhSachTK, int *soluongTK)
{
    // Tai khoan Admin goc (ID = 1, bat buoc de dang nhap lan dau)
    TaiKhoan admin;
    admin.id = 1;
    strcpy(admin.username, "admin");
    strcpy(admin.password, "admin");
    admin.role = 1;

    // Tai khoan Giao vien mau (ID = 2) de thuan tien phan cong khoa hoc
    TaiKhoan gv;
    gv.id = 2;
    strcpy(gv.username, "teacher1");
    strcpy(gv.password, "123456");
    gv.role = 2;

    // Tai khoan Hoc vien mau (ID = 3)
    TaiKhoan hv;
    hv.id = 3;
    strcpy(hv.username, "student1");
    strcpy(hv.password, "123456");
    hv.role = 3;

    danhSachTK[0] = admin;
    danhSachTK[1] = gv;
    danhSachTK[2] = hv;

    *soluongTK = 3;
}

void themKhoaHocMacDinh(KhoaHoc *danhSachKH, int *soluongKH)
{
    // Khoa hoc mau 1
    KhoaHoc kh1;
    strcpy(kh1.maKhoaHoc, "C_BASIC");
    strcpy(kh1.tenKhoaHoc, "Lap trinh C Co ban");
    kh1.idGiaoVien = 2; // Giao vien ID 2
    kh1.siSoToiDa = 30;
    kh1.siSoDaDangKy = 0;

    // Khoa hoc mau 2
    KhoaHoc kh2;
    strcpy(kh2.maKhoaHoc, "PYTHON_ADV");
    strcpy(kh2.tenKhoaHoc, "Lap trinh Python Nang cao");
    kh2.idGiaoVien = 2;
    kh2.siSoToiDa = 20;
    kh2.siSoDaDangKy = 0;

    danhSachKH[0] = kh1;
    danhSachKH[1] = kh2;

    *soluongKH = 2;
}

// ==================== DANG NHAP ====================

void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkHienTai)
{
    char user[50];
    char pass[50];
    int vt;
    int check = 0;

    printf("\n===== DANG NHAP HE THONG =====\n");
    do
    {
        printf("Nhap ten dang nhap: ");
        if (scanf("%s", user) == EOF)
        {
            tkHienTai->role = -2; // Het du lieu stdin, bao main thoat chuong trinh
            return;
        }
        getchar(); // Xoa ky tu newline con sot sau scanf

        printf("Nhap mat khau: ");
        if (fgets(pass, sizeof(pass), stdin) == NULL)
        {
            tkHienTai->role = -2;
            return;
        }
        pass[strcspn(pass, "\n")] = '\0';

        vt = timTkTheoTen(danhSachTK, soluongTK, user);
        if (vt == -1)
        {
            printf("Loi: Ten dang nhap khong ton tai. Vui long thu lai!\n\n");
        }
        else if (strcmp(danhSachTK[vt].password, pass) != 0)
        {
            printf("Loi: Sai mat khau. Vui long thu lai!\n\n");
        }
        else
        {
            *tkHienTai = danhSachTK[vt];
            printf(">> Dang nhap thanh cong! Xin chao \"%s\" voi vai tro %s.\n",
                   tkHienTai->username, tenVaiTro(tkHienTai->role));
            check = 1;
        }
    } while (check != 1);
}

// ==================== MENU ADMIN ====================

TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo,
                           KhoaHoc **danhSachKH, int *soluongKH, int *maxSizeKH,
                           DangKy **danhSachDK, int *soluongDK, int *maxSizeDK,
                           TaiKhoan *tkHienTai)
{
    int choice = 0;
    do
    {
        printf("\n================ MENU ADMIN ================\n");
        printf("1. Danh sach tai khoan\n");
        printf("2. Them tai khoan\n");
        printf("3. Xoa tai khoan\n");
        printf("4. Them khoa hoc moi\n");
        printf("5. Sua thong tin khoa hoc\n");
        printf("6. Xoa khoa hoc\n");
        printf("7. Xem danh sach khoa hoc (sap xep theo si so)\n");
        printf("8. Dang xuat\n");
        printf("0. Thoat chuong trinh\n");
        printf("Moi ban nhap vao lua chon: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            hienThiDsTk(danhSachTK, *soluongTK);
            break;
        case 2:
            danhSachTK = themTk(danhSachTK, soluongTK, maxSizeTK, idTiepTheo);
            break;
        case 3:
            danhSachTK = xoaTk(danhSachTK, soluongTK, maxSizeTK, tkHienTai,
                               *danhSachKH, *soluongKH,
                               danhSachDK, soluongDK, maxSizeDK);
            break;
        case 4:
            *danhSachKH = themKhoaHoc(*danhSachKH, soluongKH, maxSizeKH, danhSachTK, *soluongTK);
            break;
        case 5:
            suaKhoaHoc(*danhSachKH, *soluongKH, danhSachTK, *soluongTK);
            break;
        case 6:
            *danhSachKH = xoaKhoaHoc(*danhSachKH, soluongKH, maxSizeKH);
            break;
        case 7:
            hienThiDsKhoaHoc(*danhSachKH, *soluongKH, danhSachTK, *soluongTK);
            break;
        case 8:
            tkHienTai->role = -1; // Dang xuat, quay lai man hinh dang nhap
            printf("Da dang xuat khoi he thong.\n");
            break;
        case 0:
            tkHienTai->role = -2; // Bao main thoat chuong trinh
            break;
        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 8 && choice != 0);

    return danhSachTK;
}

// ==================== QUAN LY TAI KHOAN ====================

void hienThiDsTk(TaiKhoan *danhSachTK, int soluongTK)
{
    if (soluongTK == 0)
    {
        printf("Chua co tai khoan nao trong he thong.\n");
        return;
    }

    printf("\n===== DANH SACH TOAN BO TAI KHOAN =====\n");
    printf("%-5s %-25s %-15s\n", "ID", "Ten dang nhap", "Vai tro");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < soluongTK; i++)
    {
        printf("%-5d %-25s %-15s\n",
               danhSachTK[i].id, danhSachTK[i].username, tenVaiTro(danhSachTK[i].role));
    }
    printf("Tong cong: %d tai khoan.\n", soluongTK);
}

TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, int *idTiepTheo)
{
    TaiKhoan tkNew;
    char username[50];

    printf("\n--- THEM TAI KHOAN MOI ---\n");
    printf("Moi ban nhap vao ten dang nhap: ");
    if (scanf("%s", username) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachTK;
    }
    getchar();

    // Kiem tra tinh duy nhat cua ten dang nhap
    if (timTkTheoTen(danhSachTK, *soluongTK, username) != -1)
    {
        printf("Loi: Ten dang nhap nay da duoc su dung.\n");
        return danhSachTK;
    }
    strcpy(tkNew.username, username);

    printf("Moi ban nhap vao mat khau: ");
    if (fgets(tkNew.password, sizeof(tkNew.password), stdin) == NULL)
    {
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachTK;
    }
    tkNew.password[strcspn(tkNew.password, "\n")] = '\0';

    do
    {
        printf("Moi ban nhap vai tro (1 = Admin, 2 = Teacher, 3 = Student): ");
        if (scanf("%d", &tkNew.role) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Du lieu khong hop le! Vui long nhap so.\n");
            continue;
        }
        getchar();

        if (tkNew.role < 1 || tkNew.role > 3)
        {
            printf("Loi: Vai tro chi duoc chon 1 (Admin), 2 (Teacher), hoac 3 (Student)!\n");
        }
    } while (tkNew.role < 1 || tkNew.role > 3);

    // Mo rong mang neu da day
    if (*soluongTK >= *maxSizeTK)
    {
        if (*maxSizeTK == 0)
        {
            *maxSizeTK = 5;
        }
        else
        {
            (*maxSizeTK)++;
        }
        TaiKhoan *temp = (TaiKhoan *)realloc(danhSachTK, *maxSizeTK * sizeof(TaiKhoan));
        if (temp == NULL)
        {
            printf("Loi: Khong the cap phat them bo nho!\n");
            return danhSachTK;
        }
        danhSachTK = temp;
    }

    tkNew.id = (*idTiepTheo)++;
    danhSachTK[*soluongTK] = tkNew;
    (*soluongTK)++;

    printf(">> Da them tai khoan \"%s\" (ID = %d, Vai tro = %s) thanh cong!\n",
           tkNew.username, tkNew.id, tenVaiTro(tkNew.role));
    return danhSachTK;
}

TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                TaiKhoan *tkHienTai,
                KhoaHoc *danhSachKH, int soluongKH,
                DangKy **danhSachDK, int *soluongDK, int *maxSizeDK)
{
    char username[50];
    int vt;
    char traLoi;

    printf("\n--- XOA TAI KHOAN ---\n");
    printf("Moi ban nhap ten dang nhap can xoa: ");
    if (scanf("%s", username) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachTK;
    }
    getchar();

    vt = timTkTheoTen(danhSachTK, *soluongTK, username);
    if (vt == -1)
    {
        printf("Loi: Khong tim thay tai khoan voi ten dang nhap \"%s\".\n", username);
        return danhSachTK;
    }

    // Rang buoc 1: Tai khoan admin goc (ID = 1) khong the bi xoa
    if (danhSachTK[vt].id == 1)
    {
        printf("Loi: Tai khoan admin goc (ID = 1) khong the bi xoa.\n");
        return danhSachTK;
    }

    // Rang buoc 2: Admin khong the tu xoa chinh minh
    if (danhSachTK[vt].id == tkHienTai->id)
    {
        printf("Loi: Admin khong the tu xoa chinh tai khoan minh dang dang nhap.\n");
        return danhSachTK;
    }

    // Hien thi thong tin tai khoan can xoa
    printf("\nThong tin tai khoan can xoa:\n");
    printf("  - ID:            %d\n", danhSachTK[vt].id);
    printf("  - Ten dang nhap: %s\n", danhSachTK[vt].username);
    printf("  - Vai tro:       %s\n", tenVaiTro(danhSachTK[vt].role));

    // Thong bao xac nhan (Y/N) truoc khi xoa
    printf("Ban co chac chan muon xoa tai khoan nay? (Y/N): ");
    scanf("%c", &traLoi);
    getchar();

    if (traLoi != 'Y' && traLoi != 'y')
    {
        printf("Da huy thao tac xoa tai khoan.\n");
        return danhSachTK;
    }

    int idBiXoa = danhSachTK[vt].id;
    int roleBiXoa = danhSachTK[vt].role;

    // Xu ly nang cao theo yeu cau de bai:
    // 1. Khi xoa Giao vien (role == 2): Gan ID giao vien cua lop do ve 0
    if (roleBiXoa == 2)
    {
        int soLopAnhHuong = 0;
        for (int i = 0; i < soluongKH; i++)
        {
            if (danhSachKH[i].idGiaoVien == idBiXoa)
            {
                danhSachKH[i].idGiaoVien = 0; // 0 nghia la chua phan cong giao vien
                soLopAnhHuong++;
            }
        }
        if (soLopAnhHuong > 0)
        {
            printf(">> Thong bao: Da cap nhat %d khoa hoc ve trang thai chua phan cong giao vien (ID = 0).\n",
                   soLopAnhHuong);
        }
    }

    // 2. Khi xoa Hoc vien (role == 3): Xoa cac ban ghi dang ky cua hoc vien do
    if (roleBiXoa == 3 && *danhSachDK != NULL && *soluongDK > 0)
    {
        int i = 0;
        int soBanGhiXoa = 0;
        while (i < *soluongDK)
        {
            if ((*danhSachDK)[i].idHocVien == idBiXoa)
            {
                // Neu dang hoc thi giam si so da dang ky cua khoa hoc do
                if ((*danhSachDK)[i].trangThai == 0)
                {
                    int vtKh = timKhoaHocTheoMa(danhSachKH, soluongKH, (*danhSachDK)[i].maKhoaHoc);
                    if (vtKh != -1 && danhSachKH[vtKh].siSoDaDangKy > 0)
                    {
                        danhSachKH[vtKh].siSoDaDangKy--;
                    }
                }

                // Doi cac ban ghi dang ky phia sau len 1 vi tri
                for (int j = i; j < *soluongDK - 1; j++)
                {
                    (*danhSachDK)[j] = (*danhSachDK)[j + 1];
                }
                (*soluongDK)--;
                soBanGhiXoa++;
            }
            else
            {
                i++;
            }
        }

        if (soBanGhiXoa > 0)
        {
            printf(">> Thong bao: Da xoa %d ban ghi dang ky cua hoc vien nay.\n", soBanGhiXoa);
            if (*soluongDK == 0)
            {
                free(*danhSachDK);
                *danhSachDK = NULL;
                *maxSizeDK = 0;
            }
            else
            {
                *maxSizeDK = *soluongDK;
                *danhSachDK = (DangKy *)realloc(*danhSachDK, *maxSizeDK * sizeof(DangKy));
            }
        }
    }

    // Xoa tai khoan khoi danhSachTK bang cach don mang
    for (int i = vt; i < *soluongTK - 1; i++)
    {
        danhSachTK[i] = danhSachTK[i + 1];
    }
    (*soluongTK)--;

    // Thu nho mang bang realloc
    if (*soluongTK == 0)
    {
        free(danhSachTK);
        danhSachTK = NULL;
        *maxSizeTK = 0;
    }
    else
    {
        *maxSizeTK = *soluongTK;
        TaiKhoan *temp = (TaiKhoan *)realloc(danhSachTK, *maxSizeTK * sizeof(TaiKhoan));
        if (temp != NULL)
        {
            danhSachTK = temp;
        }
    }

    printf(">> Da xoa tai khoan thanh cong!\n");
    return danhSachTK;
}

// ==================== QUAN LY KHOA HOC ====================

KhoaHoc *themKhoaHoc(KhoaHoc *danhSachKH, int *soluongKH, int *maxSizeKH,
                     TaiKhoan *danhSachTK, int soluongTK)
{
    KhoaHoc khNew;
    char ma[30];

    printf("\n--- THEM KHOA HOC MOI ---\n");
    printf("Moi ban nhap ma khoa hoc (duy nhat): ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachKH;
    }
    getchar();

    // Kiem tra ma khoa hoc duy nhat
    if (timKhoaHocTheoMa(danhSachKH, *soluongKH, ma) != -1)
    {
        printf("Loi: Ma khoa hoc \"%s\" da ton tai tren he thong.\n", ma);
        return danhSachKH;
    }
    strcpy(khNew.maKhoaHoc, ma);

    printf("Moi ban nhap ten khoa hoc: ");
    if (fgets(khNew.tenKhoaHoc, sizeof(khNew.tenKhoaHoc), stdin) == NULL)
    {
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachKH;
    }
    khNew.tenKhoaHoc[strcspn(khNew.tenKhoaHoc, "\n")] = '\0';

    // Nhap ID giao vien: phai ton tai va co vai tro la Giao vien (role == 2)
    do
    {
        printf("Moi ban nhap ID cua giao vien phu trach: ");
        if (scanf("%d", &khNew.idGiaoVien) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Du lieu khong hop le! Vui long nhap so.\n");
            continue;
        }
        getchar();

        int vtGv = timTkTheoId(danhSachTK, soluongTK, khNew.idGiaoVien);
        if (vtGv == -1)
        {
            printf("Loi: Khong tim thay tai khoan co ID = %d. Vui long nhap lai!\n", khNew.idGiaoVien);
        }
        else if (danhSachTK[vtGv].role != 2)
        {
            printf("Loi: Tai khoan \"%s\" (ID = %d) co vai tro la %s, khong phai la Giao vien!\n",
                   danhSachTK[vtGv].username, khNew.idGiaoVien, tenVaiTro(danhSachTK[vtGv].role));
        }
        else
        {
            printf(">> Da xac nhan giao vien: %s (ID = %d)\n",
                   danhSachTK[vtGv].username, khNew.idGiaoVien);
            break;
        }
    } while (1);

    // Nhap si so toi da (phai lon hon 0)
    do
    {
        printf("Moi ban nhap si so toi da cua khoa hoc: ");
        if (scanf("%d", &khNew.siSoToiDa) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Du lieu khong hop le! Vui long nhap so.\n");
            continue;
        }
        getchar();

        if (khNew.siSoToiDa <= 0)
        {
            printf("Loi: Si so toi da phai lon hon 0. Nhap lai!\n");
        }
    } while (khNew.siSoToiDa <= 0);

    // Si so da dang ky tu dong duoc gan la 0
    khNew.siSoDaDangKy = 0;

    // Mo rong mang neu can
    if (*soluongKH >= *maxSizeKH)
    {
        if (*maxSizeKH == 0)
        {
            *maxSizeKH = 5;
        }
        else
        {
            (*maxSizeKH)++;
        }
        KhoaHoc *temp = (KhoaHoc *)realloc(danhSachKH, *maxSizeKH * sizeof(KhoaHoc));
        if (temp == NULL)
        {
            printf("Loi: Khong the mo rong bo nho cho danh sach khoa hoc!\n");
            return danhSachKH;
        }
        danhSachKH = temp;
    }

    danhSachKH[*soluongKH] = khNew;
    (*soluongKH)++;

    printf(">> Da them khoa hoc \"%s\" - %s thanh cong!\n", khNew.maKhoaHoc, khNew.tenKhoaHoc);
    return danhSachKH;
}

void suaKhoaHoc(KhoaHoc *danhSachKH, int soluongKH, TaiKhoan *danhSachTK, int soluongTK)
{
    char ma[30];
    int vt, choice;

    printf("\n--- SUA THONG TIN KHOA HOC ---\n");
    printf("Moi ban nhap ma khoa hoc can sua: ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;
    }
    getchar();

    vt = timKhoaHocTheoMa(danhSachKH, soluongKH, ma);
    if (vt == -1)
    {
        printf("Loi: Khong tim thay khoa hoc co ma \"%s\".\n", ma);
        return;
    }

    printf("\nDa tim thay khoa hoc: [%s] %s (Si so: %d/%d, ID GV: %d)\n",
           danhSachKH[vt].maKhoaHoc, danhSachKH[vt].tenKhoaHoc,
           danhSachKH[vt].siSoDaDangKy, danhSachKH[vt].siSoToiDa, danhSachKH[vt].idGiaoVien);

    printf("--- Chon thong tin muon sua ---\n");
    printf("1. Ten khoa hoc\n");
    printf("2. ID giao vien phu trach\n");
    printf("3. Si so toi da\n");
    printf("Moi ban chon thong tin muon sua (1-3): ");

    if (scanf("%d", &choice) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;
    }
    getchar();

    switch (choice)
    {
    case 1:
    {
        char tenMoi[100];
        printf("Moi ban nhap ten khoa hoc moi: ");
        if (fgets(tenMoi, sizeof(tenMoi), stdin) == NULL)
        {
            printf("Du lieu khong hop le! Huy thao tac.\n");
            return;
        }
        tenMoi[strcspn(tenMoi, "\n")] = '\0';
        strcpy(danhSachKH[vt].tenKhoaHoc, tenMoi);
        printf(">> Cap nhat ten khoa hoc thanh cong!\n");
        break;
    }
    case 2:
    {
        int idGvMoi;
        printf("Moi ban nhap ID giao vien moi: ");
        if (scanf("%d", &idGvMoi) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Du lieu khong hop le! Huy thao tac.\n");
            return;
        }
        getchar();

        // Kiem tra ID giao vien moi co ton tai va dung la Giao vien (role == 2) khong
        int vtGv = timTkTheoId(danhSachTK, soluongTK, idGvMoi);
        if (vtGv == -1)
        {
            printf("Loi: Khong tim thay tai khoan co ID = %d. Khong the cap nhat!\n", idGvMoi);
            return;
        }
        if (danhSachTK[vtGv].role != 2)
        {
            printf("Loi: Tai khoan \"%s\" (ID = %d) co vai tro la %s, khong phai la Giao vien!\n",
                   danhSachTK[vtGv].username, idGvMoi, tenVaiTro(danhSachTK[vtGv].role));
            return;
        }

        danhSachKH[vt].idGiaoVien = idGvMoi;
        printf(">> Cap nhat giao vien phu trach thanh cong (Giao vien: %s, ID: %d)!\n",
               danhSachTK[vtGv].username, idGvMoi);
        break;
    }
    case 3:
    {
        int siSoMoi;
        do
        {
            printf("Moi ban nhap si so toi da moi: ");
            if (scanf("%d", &siSoMoi) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
                printf("Du lieu khong hop le! Huy thao tac.\n");
                return;
            }
            getchar();

            // Rang buoc: khong duoc nho hon si so da dang ky hien tai
            if (siSoMoi < danhSachKH[vt].siSoDaDangKy)
            {
                printf("Loi: Si so toi da khong duoc nho hon si so da dang ky hien tai (%d). Nhap lai!\n",
                       danhSachKH[vt].siSoDaDangKy);
            }
            else if (siSoMoi <= 0)
            {
                printf("Loi: Si so toi da phai lon hon 0. Nhap lai!\n");
            }
        } while (siSoMoi < danhSachKH[vt].siSoDaDangKy || siSoMoi <= 0);

        danhSachKH[vt].siSoToiDa = siSoMoi;
        printf(">> Cap nhat si so toi da thanh cong (%d)!\n", siSoMoi);
        break;
    }
    default:
        printf("Lua chon khong hop le! Huy thao tac sua.\n");
        break;
    }
}

KhoaHoc *xoaKhoaHoc(KhoaHoc *danhSachKH, int *soluongKH, int *maxSizeKH)
{
    char ma[30];
    int vt;
    char traLoi;

    printf("\n--- XOA KHOA HOC ---\n");
    printf("Moi ban nhap ma khoa hoc can xoa: ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachKH;
    }
    getchar();

    vt = timKhoaHocTheoMa(danhSachKH, *soluongKH, ma);
    if (vt == -1)
    {
        printf("Loi: Khong tim thay khoa hoc co ma \"%s\".\n", ma);
        return danhSachKH;
    }

    // Rang buoc: Chi duoc xoa khi chua co ai dang ky (si so da dang ky la 0)
    if (danhSachKH[vt].siSoDaDangKy > 0)
    {
        printf("Loi: Khong the xoa khoa hoc \"%s\" vi da co %d hoc vien dang ky!\n",
               danhSachKH[vt].tenKhoaHoc, danhSachKH[vt].siSoDaDangKy);
        return danhSachKH;
    }

    printf("\nThong tin khoa hoc can xoa:\n");
    printf("  - Ma khoa hoc:  %s\n", danhSachKH[vt].maKhoaHoc);
    printf("  - Ten khoa hoc: %s\n", danhSachKH[vt].tenKhoaHoc);
    printf("  - ID giao vien: %d\n", danhSachKH[vt].idGiaoVien);
    printf("  - Si so toi da: %d\n", danhSachKH[vt].siSoToiDa);
    printf("  - Da dang ky:   %d\n", danhSachKH[vt].siSoDaDangKy);

    printf("Ban co chac chan muon xoa khoa hoc nay? (Y/N): ");
    scanf("%c", &traLoi);
    getchar();

    if (traLoi != 'Y' && traLoi != 'y')
    {
        printf("Da huy thao tac xoa khoa hoc.\n");
        return danhSachKH;
    }

    // Don cac phan tu sau len de xoa
    for (int i = vt; i < *soluongKH - 1; i++)
    {
        danhSachKH[i] = danhSachKH[i + 1];
    }
    (*soluongKH)--;

    // Thu nho mang
    if (*soluongKH == 0)
    {
        free(danhSachKH);
        danhSachKH = NULL;
        *maxSizeKH = 0;
    }
    else
    {
        *maxSizeKH = *soluongKH;
        KhoaHoc *temp = (KhoaHoc *)realloc(danhSachKH, *maxSizeKH * sizeof(KhoaHoc));
        if (temp != NULL)
        {
            danhSachKH = temp;
        }
    }

    printf(">> Da xoa khoa hoc thanh cong!\n");
    return danhSachKH;
}

void sapXepKhoaHocGiamDanSiSo(KhoaHoc *danhSachKH, int soluongKH)
{
    // Sap xep giam dan theo si so toi da su dung Bubble Sort
    KhoaHoc temp;
    for (int i = 0; i < soluongKH - 1; i++)
    {
        for (int j = 0; j < soluongKH - 1 - i; j++)
        {
            if (danhSachKH[j].siSoToiDa < danhSachKH[j + 1].siSoToiDa)
            {
                temp = danhSachKH[j];
                danhSachKH[j] = danhSachKH[j + 1];
                danhSachKH[j + 1] = temp;
            }
        }
    }
}

void hienThiDsKhoaHoc(KhoaHoc *danhSachKH, int soluongKH, TaiKhoan *danhSachTK, int soluongTK)
{
    if (soluongKH == 0)
    {
        printf("Trung tam hien chua co khoa hoc nao.\n");
        return;
    }

    // Yeu cau: Sap xep giam dan theo si so toi da truoc khi in
    sapXepKhoaHocGiamDanSiSo(danhSachKH, soluongKH);

    printf("\n===== DANH SACH KHOA HOC (SAP XEP GIAM DAN THEO SI SO TOI DA) =====\n");
    printf("%-12s %-32s %-20s %-12s %-12s\n",
           "Ma KH", "Ten khoa hoc", "Giao vien", "Si so toi da", "Da dang ky");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < soluongKH; i++)
    {
        char tenGv[60] = "Chua phan cong";
        if (danhSachKH[i].idGiaoVien > 0)
        {
            int vtGv = timTkTheoId(danhSachTK, soluongTK, danhSachKH[i].idGiaoVien);
            if (vtGv != -1)
            {
                snprintf(tenGv, sizeof(tenGv), "%s (ID:%d)",
                         danhSachTK[vtGv].username, danhSachKH[i].idGiaoVien);
            }
            else
            {
                snprintf(tenGv, sizeof(tenGv), "ID:%d", danhSachKH[i].idGiaoVien);
            }
        }

        printf("%-12s %-32s %-20s %-12d %-12d\n",
               danhSachKH[i].maKhoaHoc,
               danhSachKH[i].tenKhoaHoc,
               tenGv,
               danhSachKH[i].siSoToiDa,
               danhSachKH[i].siSoDaDangKy);
    }
    printf("Tong cong: %d khoa hoc.\n", soluongKH);
}
