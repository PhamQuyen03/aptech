/*
 * BAI TAP LON - HE THONG QUAN LY THU VIEN
 * GIAI DOAN 3 (BUOC HOAN THIEN): STEP 1 + STEP 2 + 1.4 Menu Sinh vien
 * Noi dung moi: menu Sinh vien xem danh sach sach, tim kiem sach
 * va danh sach sach dang muon CUA TOI (lay nguyen code STEP 1, 2 lam tiep)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TaiKhoan
{
    int id;
    char username[50];
    char password[50];
    int role; // 1 = Admin, 2 = Staff (Thu thu), 3 = Sinh vien
} TaiKhoan;

typedef struct Sach
{
    char maSach[20];  // ma sach, duy nhat trong thu vien
    char tenSach[100];
    char tacGia[50];
    int namXb;
    int tongSl;  // tong so luong ban sach
    int daMuon;  // so luong ban da cho muon
} Sach;

typedef struct PhieuMuon
{
    int idPhieu;      // so phieu tu tang
    int idNguoiDung;  // id sinh vien muon sach
    char maSach[20];
    int trangThai; // 0 = dang muon, 1 = da tra
} PhieuMuon;

void themTkMacDinh(TaiKhoan *danhSachTK, int *soluongTK);
void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkhientai);
void hienThiDsTk(TaiKhoan *danhSachTK, int soluongTK);
void hienThiDsSv(TaiKhoan *danhSachTK, int soluongTK, PhieuMuon *danhSachPhieu, int soluongPhieu);
TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, int *idTiepTheo);
TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, TaiKhoan *tkHienTai);
void suaTk(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkHienTai);
void resetMatKhau(TaiKhoan *danhSachTK, int soluongTK);
char *tenVaiTro(int role);
int timTkTheoTen(TaiKhoan *danhSachTK, int soluongTK, char *ten);
TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo, PhieuMuon *danhSachPhieu, int soluongPhieu,
                           TaiKhoan *tkHienTai);

Sach *themSach(Sach *danhSachSach, int *soluongSach, int *maxSizeSach);
void hienThiDsSach(Sach *danhSachSach, int soluongSach);
void capNhatSach(Sach *danhSachSach, int soluongSach);
Sach *xoaSach(Sach *danhSachSach, int *soluongSach, int *maxSizeSach);
void timKiemSach(Sach *danhSachSach, int soluongSach);
void sapXepSach(Sach *danhSachSach, int soluongSach);
PhieuMuon *muonSach(PhieuMuon *danhSachPhieu, int *soluongPhieu, int *maxSizePhieu,
                    int *idPhieuTiepTheo, TaiKhoan *danhSachTK, int soluongTK,
                    Sach *danhSachSach, int soluongSach);
void traSach(PhieuMuon *danhSachPhieu, int soluongPhieu, Sach *danhSachSach,
             int soluongSach, TaiKhoan *danhSachTK, int soluongTK);
void hienThiSachDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu,
                         TaiKhoan *danhSachTK, int soluongTK,
                         Sach *danhSachSach, int soluongSach);
int timTkTheoId(TaiKhoan *danhSachTK, int soluongTK, int id);
int timSachTheoMa(Sach *danhSachSach, int soluongSach, char *ma);
int timPhieuDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu, int idSv, char *maSach);
int tenChuaTuKhoa(char *ten, char *tuKhoa);
Sach *hienThiStaffMenu(Sach *danhSachSach, int *soluongSach, int *maxSizeSach,
                       PhieuMuon **danhSachPhieu, int *soluongPhieu, int *maxSizePhieu,
                       int *idPhieuTiepTheo, TaiKhoan *danhSachTK, int soluongTK,
                       TaiKhoan *tkHienTai);
void hienThiSinhVienMenu(Sach *danhSachSach, int soluongSach,
                         PhieuMuon *danhSachPhieu, int soluongPhieu, TaiKhoan *tkHienTai);
void sachToiDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu,
                     Sach *danhSachSach, int soluongSach, TaiKhoan *tkHienTai);

int main()
{
    int soluongTK = 0;
    int maxSizeTK = 5;
    int idTiepTheo = 3; // 2 tai khoan mac dinh da dung id 1 va 2
    int soluongSach = 0;
    int maxSizeSach = 5;
    int soluongPhieu = 0;
    int maxSizePhieu = 5;
    int idPhieuTiepTheo = 1;
    Sach *danhSachSach;
    PhieuMuon *danhSachPhieu;

    TaiKhoan *danhSachTK;
    TaiKhoan tkHienTai;
    tkHienTai.role = -1; // role = -1 nghia la CHUA dang nhap

    danhSachTK = (TaiKhoan *)malloc(maxSizeTK * sizeof(TaiKhoan));
    danhSachSach = (Sach *)malloc(maxSizeSach * sizeof(Sach));
    danhSachPhieu = (PhieuMuon *)malloc(maxSizePhieu * sizeof(PhieuMuon));
    themTkMacDinh(danhSachTK, &soluongTK);

    printf("Chao mung den voi He thong Quan ly Thu vien!\n");

    while (1)
    {
        // Chua dang nhap thi luon quay lai man hinh dang nhap
        if (tkHienTai.role == -1)
        {
            dangnhap(danhSachTK, soluongTK, &tkHienTai);
            continue;
        }

        switch (tkHienTai.role)
        {
        case 1: // Admin
            danhSachTK = hienThiAdminMenu(danhSachTK, &soluongTK, &maxSizeTK,
                                          &idTiepTheo, danhSachPhieu, soluongPhieu,
                                          &tkHienTai);
            break;
        case 2: // Thu thu
            danhSachSach = hienThiStaffMenu(danhSachSach, &soluongSach, &maxSizeSach,
                                            &danhSachPhieu, &soluongPhieu, &maxSizePhieu,
                                            &idPhieuTiepTheo, danhSachTK, soluongTK,
                                            &tkHienTai);
            break;
        case 3: // Sinh vien
            hienThiSinhVienMenu(danhSachSach, soluongSach, danhSachPhieu, soluongPhieu,
                                &tkHienTai);
            break;
        }

        // role = -2 nghia la nguoi dung chon "Thoat chuong trinh" trong menu
        if (tkHienTai.role == -2)
        {
            break;
        }
    }

    free(danhSachTK);
    free(danhSachSach);
    free(danhSachPhieu);
    printf("Da giai phong bo nho. Tam biet!\n");
    return 0;
}

TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo, PhieuMuon *danhSachPhieu, int soluongPhieu,
                           TaiKhoan *tkHienTai)
{
    int choice = 0;
    do
    {
        printf("\n===== MENU ADMIN =====\n");
        printf("1. Hien thi danh sach tai khoan\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Them tai khoan\n");
        printf("4. Xoa tai khoan\n");
        printf("5. Sua thong tin tai khoan\n");
        printf("6. Reset mat khau\n");
        printf("7. Dang xuat\n");
        printf("0. Thoat chuong trinh\n");
        printf("Moi ban nhap vao lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            if (c == EOF)
            {
                tkHienTai->role = -2; // het du lieu nhap, thoat chuong trinh
                return danhSachTK;
            }
            printf("Lua chon khong hop le! Vui long nhap vao so.\n");
            choice = -1; // dat gia tri trung tinh de vong do-while tiep tuc chay
            continue;
        }
        getchar();

        switch (choice)
        {
        case 1:
            hienThiDsTk(danhSachTK, *soluongTK);
            break;
        case 2:
            hienThiDsSv(danhSachTK, *soluongTK, danhSachPhieu, soluongPhieu);
            break;
        case 3:
            danhSachTK = themTk(danhSachTK, soluongTK, maxSizeTK, idTiepTheo);
            break;
        case 4:
            danhSachTK = xoaTk(danhSachTK, soluongTK, maxSizeTK, tkHienTai);
            break;
        case 5:
            suaTk(danhSachTK, *soluongTK, tkHienTai);
            break;
        case 6:
            resetMatKhau(danhSachTK, *soluongTK);
            break;
        case 7:
            tkHienTai->role = -1; // dang xuat, quay lai man hinh dang nhap
            printf("Da dang xuat khoi he thong.\n");
            break;
        case 0:
            tkHienTai->role = -2; // bao main biet nguoi dung muon thoat chuong trinh
            break;
        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 7 && choice != 0);

    return danhSachTK;
}

Sach *hienThiStaffMenu(Sach *danhSachSach, int *soluongSach, int *maxSizeSach,
                       PhieuMuon **danhSachPhieu, int *soluongPhieu, int *maxSizePhieu,
                       int *idPhieuTiepTheo, TaiKhoan *danhSachTK, int soluongTK,
                       TaiKhoan *tkHienTai)
{
    int choice = 0;
    do
    {
        printf("\n===== MENU THU THU =====\n");
        printf("1. Them sach moi\n");
        printf("2. Hien thi danh sach sach\n");
        printf("3. Cap nhat thong tin sach\n");
        printf("4. Xoa mot cuon sach\n");
        printf("5. Tim kiem sach\n");
        printf("6. Sap xep sach theo nam xuat ban\n");
        printf("7. Hien thi danh sach sinh vien\n");
        printf("8. Cho muon sach\n");
        printf("9. Tra sach\n");
        printf("10. Danh sach sach dang duoc muon\n");
        printf("11. Dang xuat\n");
        printf("0. Thoat chuong trinh\n");
        printf("Moi ban nhap vao lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            if (c == EOF)
            {
                tkHienTai->role = -2; // het du lieu nhap, thoat chuong trinh
                return danhSachSach;
            }
            printf("Lua chon khong hop le! Vui long nhap vao so.\n");
            choice = -1; // dat gia tri trung tinh de vong do-while tiep tuc chay
            continue;
        }
        getchar();

        switch (choice)
        {
        case 1:
            danhSachSach = themSach(danhSachSach, soluongSach, maxSizeSach);
            break;
        case 2:
            hienThiDsSach(danhSachSach, *soluongSach);
            break;
        case 3:
            capNhatSach(danhSachSach, *soluongSach);
            break;
        case 4:
            danhSachSach = xoaSach(danhSachSach, soluongSach, maxSizeSach);
            break;
        case 5:
            timKiemSach(danhSachSach, *soluongSach);
            break;
        case 6:
            sapXepSach(danhSachSach, *soluongSach);
            break;
        case 7:
            hienThiDsSv(danhSachTK, soluongTK, *danhSachPhieu, *soluongPhieu);
            break;
        case 8:
            // muonSach co the realloc lam DIA CHI mang phieu thay doi,
            // menu phai nhan lai dia chi moi qua con tro cap 2 de tra cho main
            *danhSachPhieu = muonSach(*danhSachPhieu, soluongPhieu, maxSizePhieu,
                                      idPhieuTiepTheo, danhSachTK, soluongTK,
                                      danhSachSach, *soluongSach);
            break;
        case 9:
            traSach(*danhSachPhieu, *soluongPhieu, danhSachSach, *soluongSach,
                    danhSachTK, soluongTK);
            break;
        case 10:
            hienThiSachDangMuon(*danhSachPhieu, *soluongPhieu, danhSachTK, soluongTK,
                                danhSachSach, *soluongSach);
            break;
        case 11:
            tkHienTai->role = -1; // dang xuat, quay lai man hinh dang nhap
            printf("Da dang xuat khoi he thong.\n");
            break;
        case 0:
            tkHienTai->role = -2; // bao main biet nguoi dung muon thoat chuong trinh
            break;
        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 11 && choice != 0);

    return danhSachSach;
}

Sach *themSach(Sach *danhSachSach, int *soluongSach, int *maxSizeSach)
{
    Sach sachNew;
    char ma[20];

    printf("Moi ban nhap vao ma sach: ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachSach;

    }
    getchar();

    // Ma sach phai duy nhat, trung thi huy ngay thao tac them
    if (timSachTheoMa(danhSachSach, *soluongSach, ma) != -1)
    {
        printf("Loi: Ma sach da ton tai.\n");
        return danhSachSach;
    }
    strcpy(sachNew.maSach, ma);

    printf("Moi ban nhap vao ten sach: ");
    fgets(sachNew.tenSach, sizeof(sachNew.tenSach), stdin);
    sachNew.tenSach[strcspn(sachNew.tenSach, "\n")] = 0;

    printf("Moi ban nhap vao tac gia: ");
    fgets(sachNew.tacGia, sizeof(sachNew.tacGia), stdin);
    sachNew.tacGia[strcspn(sachNew.tacGia, "\n")] = 0;

    printf("Moi ban nhap vao nam xuat ban: ");
    if (scanf("%d", &sachNew.namXb) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachSach;

    }
    getchar();

    printf("Moi ban nhap vao tong so luong: ");
    if (scanf("%d", &sachNew.tongSl) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachSach;

    }
    getchar();

    sachNew.daMuon = 0; // sach moi nhap ve nen chua cho muon cuon nao

    // Mang day thi mo rong them 1 o, realloc co the chuyen dia chi nen return con tro moi
    if (*soluongSach >= *maxSizeSach)
    {
        if (*maxSizeSach == 0)
        {
            *maxSizeSach = 5;
        }
        else
        {
            (*maxSizeSach)++;
        }
        danhSachSach = (Sach *)realloc(danhSachSach, *maxSizeSach * sizeof(Sach));
    }

    danhSachSach[*soluongSach] = sachNew;
    (*soluongSach)++;

    printf("Da them sach thanh cong!\n");
    return danhSachSach;
}

void hienThiDsSach(Sach *danhSachSach, int soluongSach)
{
    if (soluongSach == 0)
    {
        printf("Thu vien hien chua co cuon sach nao.\n");
        return;
    }

    printf("\n===== DANH MUC SACH =====\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Ma sach", "Ten sach", "Tac gia", "Nam XB", "Tong SL", "Da muon", "Hien co");
    for (int i = 0; i < soluongSach; i++)
    {
        // So luong hien co = tong so luong tru so ban da cho muon
        printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
               danhSachSach[i].maSach, danhSachSach[i].tenSach, danhSachSach[i].tacGia,
               danhSachSach[i].namXb, danhSachSach[i].tongSl, danhSachSach[i].daMuon,
               danhSachSach[i].tongSl - danhSachSach[i].daMuon);
    }
    printf("Hien thu vien co %d dau sach.\n", soluongSach);
}

void capNhatSach(Sach *danhSachSach, int soluongSach)
{
    char ma[20];
    int vt, choice;

    printf("Moi ban nhap vao ma sach can cap nhat: ");
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

    vt = timSachTheoMa(danhSachSach, soluongSach, ma);
    if (vt == -1)
    {
        printf("Loi: Ma sach khong ton tai.\n");
        return;
    }

    printf("Da tim thay sach: [%s] %s - %s\n",
           danhSachSach[vt].maSach, danhSachSach[vt].tenSach, danhSachSach[vt].tacGia);

    printf("1. Ten sach\n");
    printf("2. Tac gia\n");
    printf("3. Nam xuat ban\n");
    printf("4. Tong so luong\n");
    printf("Moi ban chon thong tin can sua: ");
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
        printf("Moi ban nhap vao ten sach moi: ");
        fgets(danhSachSach[vt].tenSach, sizeof(danhSachSach[vt].tenSach), stdin);
        danhSachSach[vt].tenSach[strcspn(danhSachSach[vt].tenSach, "\n")] = 0;
        break;
    case 2:
        printf("Moi ban nhap vao tac gia moi: ");
        fgets(danhSachSach[vt].tacGia, sizeof(danhSachSach[vt].tacGia), stdin);
        danhSachSach[vt].tacGia[strcspn(danhSachSach[vt].tacGia, "\n")] = 0;
        break;
    case 3:
        printf("Moi ban nhap vao nam xuat ban moi: ");
        if (scanf("%d", &danhSachSach[vt].namXb) != 1)
        {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

        }
        getchar();
        break;
    case 4:
        do
        {
            printf("Moi ban nhap vao tong so luong moi: ");
            if (scanf("%d", &danhSachSach[vt].tongSl) != 1)
            {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

            }
            getchar();
            // Rang buoc: tong so luong khong duoc thap hon so ban da cho muon
            if (danhSachSach[vt].tongSl < danhSachSach[vt].daMuon)
            {
                printf("Loi: Tong so luong khong duoc thap hon so luong da cho muon (%d). Nhap lai!\n",
                       danhSachSach[vt].daMuon);
            }
        } while (danhSachSach[vt].tongSl < danhSachSach[vt].daMuon);
        break;
    default:
        printf("Lua chon khong hop le!\n");
        return;
    }

    printf("Cap nhat thanh cong!\n");
}

Sach *xoaSach(Sach *danhSachSach, int *soluongSach, int *maxSizeSach)
{
    char ma[20];
    int vt;
    char traLoi;

    printf("Moi ban nhap vao ma sach can xoa: ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachSach;

    }
    getchar();

    vt = timSachTheoMa(danhSachSach, *soluongSach, ma);
    if (vt == -1)
    {
        printf("Loi: Ma sach khong ton tai.\n");
        return danhSachSach;
    }

    // Chi cho phep xoa khi khong ai dang muon cuon sach nay
    if (danhSachSach[vt].daMuon > 0)
    {
        printf("Loi: Khong the xoa sach dang co nguoi muon.\n");
        return danhSachSach;
    }

    printf("Thong tin sach can xoa:\n");
    printf("  Ma sach:       %s\n", danhSachSach[vt].maSach);
    printf("  Ten sach:      %s\n", danhSachSach[vt].tenSach);
    printf("  Tac gia:       %s\n", danhSachSach[vt].tacGia);
    printf("  Nam xuat ban:  %d\n", danhSachSach[vt].namXb);
    printf("  Tong so luong: %d\n", danhSachSach[vt].tongSl);
    printf("Ban co chac chan muon xoa cuon sach nay? (Y/N): ");
    scanf("%c", &traLoi);
    getchar();
    if (traLoi != 'Y' && traLoi != 'y')
    {
        printf("Da huy viec xoa sach.\n");
        return danhSachSach;
    }

    for (int i = vt; i < *soluongSach - 1; i++)
    {
        danhSachSach[i] = danhSachSach[i + 1];
    }
    (*soluongSach)--;

    if (*soluongSach == 0)
    {
        free(danhSachSach);
        danhSachSach = NULL;
        *maxSizeSach = 0;
    }
    else
    {
        *maxSizeSach = *soluongSach;
        danhSachSach = (Sach *)realloc(danhSachSach, *maxSizeSach * sizeof(Sach));
    }

    printf("Da xoa sach thanh cong!\n");
    return danhSachSach;
}

void timKiemSach(Sach *danhSachSach, int soluongSach)
{
    char tuKhoa[100];
    int timThay = 0;

    printf("Moi ban nhap vao tu khoa can tim: ");
    fgets(tuKhoa, sizeof(tuKhoa), stdin);
    tuKhoa[strcspn(tuKhoa, "\n")] = 0;

    printf("\n===== KET QUA TIM KIEM =====\n");
    printf("%-10s %-30s %-20s %-8s %-8s %-8s %-8s\n",
           "Ma sach", "Ten sach", "Tac gia", "Nam XB", "Tong SL", "Da muon", "Hien co");
    for (int i = 0; i < soluongSach; i++)
    {
        if (tenChuaTuKhoa(danhSachSach[i].tenSach, tuKhoa))
        {
            printf("%-10s %-30s %-20s %-8d %-8d %-8d %-8d\n",
                   danhSachSach[i].maSach, danhSachSach[i].tenSach, danhSachSach[i].tacGia,
                   danhSachSach[i].namXb, danhSachSach[i].tongSl, danhSachSach[i].daMuon,
                   danhSachSach[i].tongSl - danhSachSach[i].daMuon);
            timThay = 1;
        }
    }

    if (!timThay)
    {
        printf("Khong tim thay sach nao co ten chua tu khoa \"%s\".\n", tuKhoa);
    }
}

void sapXepSach(Sach *danhSachSach, int soluongSach)
{
    Sach temp;
    int choice;

    if (soluongSach == 0)
    {
        printf("Thu vien hien chua co cuon sach nao.\n");
        return;
    }

    printf("1. Sap xep theo nam xuat ban tang dan (tu cu den moi)\n");
    printf("2. Sap xep theo nam xuat ban giam dan (tu moi den cu)\n");
    printf("Moi ban nhap vao lua chon: ");
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

    if (choice != 1 && choice != 2)
    {
        printf("Lua chon khong hop le!\n");
        return;
    }

    for (int i = 0; i < soluongSach - 1; i++)
    {
        for (int j = 0; j < soluongSach - 1 - i; j++)
        {
            // Dieu kien hoan doi phu thuoc thu tu nguoi dung chon
            int canHoanDoi = (choice == 1)
                                 ? (danhSachSach[j].namXb > danhSachSach[j + 1].namXb)
                                 : (danhSachSach[j].namXb < danhSachSach[j + 1].namXb);
            if (canHoanDoi)
            {
                // Phai hoan doi nguyen struct chu khong chi hoan doi truong nam
                temp = danhSachSach[j];
                danhSachSach[j] = danhSachSach[j + 1];
                danhSachSach[j + 1] = temp;
            }
        }
    }

    printf("Da sap xep danh sach sach thanh cong!\n");
    hienThiDsSach(danhSachSach, soluongSach);
}

PhieuMuon *muonSach(PhieuMuon *danhSachPhieu, int *soluongPhieu, int *maxSizePhieu,
                    int *idPhieuTiepTheo, TaiKhoan *danhSachTK, int soluongTK,
                    Sach *danhSachSach, int soluongSach)
{
    PhieuMuon phieuNew;
    int idSv, vtSv, vtSach;
    char ma[20];

    printf("Moi ban nhap vao ID sinh vien muon sach: ");
    if (scanf("%d", &idSv) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachPhieu;

    }
    getchar();

    vtSv = timTkTheoId(danhSachTK, soluongTK, idSv);
    if (vtSv == -1)
    {
        printf("Loi: Khong tim thay sinh vien co ID %d.\n", idSv);
        return danhSachPhieu;
    }
    if (danhSachTK[vtSv].role != 3)
    {
        printf("Loi: Tai khoan ID %d khong phai la Sinh vien.\n", idSv);
        return danhSachPhieu;
    }

    printf("Moi ban nhap vao ma sach can muon: ");
    if (scanf("%s", ma) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachPhieu;

    }
    getchar();

    vtSach = timSachTheoMa(danhSachSach, soluongSach, ma);
    if (vtSach == -1)
    {
        printf("Loi: Ma sach khong ton tai.\n");
        return danhSachPhieu;
    }

    // Con sach de muon khi so ban da muon van nho hon tong so luong
    if (danhSachSach[vtSach].daMuon >= danhSachSach[vtSach].tongSl)
    {
        printf("Loi: Sach \"%s\" da het, khong con ban nao de muon.\n", danhSachSach[vtSach].tenSach);
        return danhSachPhieu;
    }

    // Moi sinh vien chi duoc muon 1 ban cua cung mot cuon sach tai mot thoi diem
    if (timPhieuDangMuon(danhSachPhieu, *soluongPhieu, idSv, ma) != -1)
    {
        printf("Loi: Sinh vien nay dang muon cuon sach nay va chua tra.\n");
        return danhSachPhieu;
    }

    danhSachSach[vtSach].daMuon++; // tang so ban da cho muon cua cuon sach len 1

    if (*soluongPhieu >= *maxSizePhieu)
    {
        if (*maxSizePhieu == 0)
        {
            *maxSizePhieu = 5;
        }
        else
        {
            (*maxSizePhieu)++;
        }
        danhSachPhieu = (PhieuMuon *)realloc(danhSachPhieu, *maxSizePhieu * sizeof(PhieuMuon));
    }

    phieuNew.idPhieu = (*idPhieuTiepTheo)++;
    phieuNew.idNguoiDung = idSv;
    strcpy(phieuNew.maSach, ma);
    phieuNew.trangThai = 0; // 0 = dang muon

    danhSachPhieu[*soluongPhieu] = phieuNew;
    (*soluongPhieu)++;

    printf("Cho muon thanh cong! Sinh vien %s (ID %d) muon sach \"%s\".\n",
           danhSachTK[vtSv].username, idSv, danhSachSach[vtSach].tenSach);
    return danhSachPhieu;
}

void traSach(PhieuMuon *danhSachPhieu, int soluongPhieu, Sach *danhSachSach,
             int soluongSach, TaiKhoan *danhSachTK, int soluongTK)
{
    int idSv, vtPhieu, vtSach, vtSv;
    char ma[20];

    printf("Moi ban nhap vao ID sinh vien tra sach: ");
    if (scanf("%d", &idSv) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

    }
    getchar();

    printf("Moi ban nhap vao ma sach can tra: ");
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

    vtPhieu = timPhieuDangMuon(danhSachPhieu, soluongPhieu, idSv, ma);
    if (vtPhieu == -1)
    {
        printf("Loi: Sinh vien khong co muon cuon sach nay.\n");
        return;
    }

    danhSachPhieu[vtPhieu].trangThai = 1; // doi trang thai 0 (dang muon) -> 1 (da tra)

    // Giam so ban da cho muon cua cuon sach xuong 1
    vtSach = timSachTheoMa(danhSachSach, soluongSach, ma);
    if (vtSach != -1)
    {
        danhSachSach[vtSach].daMuon--;
    }

    vtSv = timTkTheoId(danhSachTK, soluongTK, idSv);
    printf("Tra sach thanh cong! Da ghi nhan \"%s\" tra sach ma %s.\n",
           danhSachTK[vtSv].username, ma);
}

void hienThiSachDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu,
                         TaiKhoan *danhSachTK, int soluongTK,
                         Sach *danhSachSach, int soluongSach)
{
    int co = 0;
    int vtSv, vtSach;

    printf("\n===== SACH DANG DUOC MUON =====\n");
    printf("%-10s %-8s %-25s %-10s %-30s\n",
           "Ma phieu", "ID SV", "Ten sinh vien", "Ma sach", "Ten sach");
    for (int i = 0; i < soluongPhieu; i++)
    {
        if (danhSachPhieu[i].trangThai != 0)
        {
            continue; // bo qua cac phieu da tra
        }

        // Phieu muon chi luu ID va ma sach nen phai tra cuu nguoc 2 mang kia lay ten hien thi
        vtSv = timTkTheoId(danhSachTK, soluongTK, danhSachPhieu[i].idNguoiDung);
        vtSach = timSachTheoMa(danhSachSach, soluongSach, danhSachPhieu[i].maSach);
        if (vtSv != -1 && vtSach != -1)
        {
            printf("%-10d %-8d %-25s %-10s %-30s\n",
                   danhSachPhieu[i].idPhieu,
                   danhSachTK[vtSv].id,
                   danhSachTK[vtSv].username,
                   danhSachSach[vtSach].maSach,
                   danhSachSach[vtSach].tenSach);
            co = 1;
        }
    }

    if (!co)
    {
        printf("Hien khong co cuon sach nao dang duoc muon.\n");
    }
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

int timSachTheoMa(Sach *danhSachSach, int soluongSach, char *ma)
{
    for (int i = 0; i < soluongSach; i++)
    {
        if (strcmp(danhSachSach[i].maSach, ma) == 0)
        {
            return i;
        }
    }
    return -1;
}

int timPhieuDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu, int idSv, char *maSach)
{
    for (int i = 0; i < soluongPhieu; i++)
    {
        if (danhSachPhieu[i].idNguoiDung == idSv &&
            strcmp(danhSachPhieu[i].maSach, maSach) == 0 &&
            danhSachPhieu[i].trangThai == 0)
        {
            return i;
        }
    }
    return -1;
}

int tenChuaTuKhoa(char *ten, char *tuKhoa)
{
    char tenThuong[150], tuKhoaThuong[150];
    int i;

    // Chuyen ca ten sach va tu khoa ve chu thuong roi moi strstr
    // de "Co ban" khop voi "co ban" (khong phan biet hoa/thuong)
    for (i = 0; ten[i] != '\0' && i < 149; i++)
    {
        tenThuong[i] = tolower(ten[i]);
    }
    tenThuong[i] = '\0';

    for (i = 0; tuKhoa[i] != '\0' && i < 149; i++)
    {
        tuKhoaThuong[i] = tolower(tuKhoa[i]);
    }
    tuKhoaThuong[i] = '\0';

    return strstr(tenThuong, tuKhoaThuong) != NULL;
}

void hienThiSinhVienMenu(Sach *danhSachSach, int soluongSach,
                         PhieuMuon *danhSachPhieu, int soluongPhieu, TaiKhoan *tkHienTai)
{
    int choice = 0;
    do
    {
        printf("\n===== MENU SINH VIEN =====\n");
        printf("1. Danh sach sach\n");
        printf("2. Tim kiem sach\n");
        printf("3. Danh sach sach dang muon (cua toi)\n");
        printf("4. Dang xuat\n");
        printf("0. Thoat chuong trinh\n");
        printf("Moi ban nhap vao lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            if (c == EOF)
            {
                tkHienTai->role = -2; // het du lieu nhap, thoat chuong trinh
                return;
            }
            printf("Lua chon khong hop le! Vui long nhap vao so.\n");
            choice = -1; // dat gia tri trung tinh de vong do-while tiep tuc chay
            continue;
        }
        getchar();

        switch (choice)
        {
        case 1:
            hienThiDsSach(danhSachSach, soluongSach);
            break;
        case 2:
            timKiemSach(danhSachSach, soluongSach);
            break;
        case 3:
            sachToiDangMuon(danhSachPhieu, soluongPhieu, danhSachSach, soluongSach, tkHienTai);
            break;
        case 4:
            tkHienTai->role = -1; // dang xuat, quay lai man hinh dang nhap
            printf("Da dang xuat khoi he thong.\n");
            break;
        case 0:
            tkHienTai->role = -2; // bao main biet nguoi dung muon thoat chuong trinh
            break;
        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 4 && choice != 0);
}

void sachToiDangMuon(PhieuMuon *danhSachPhieu, int soluongPhieu,
                     Sach *danhSachSach, int soluongSach, TaiKhoan *tkHienTai)
{
    int co = 0;
    int vtSach;

    printf("\n===== SACH TOI DANG MUON =====\n");
    printf("%-10s %-10s %-30s %-20s %-8s\n",
           "Ma phieu", "Ma sach", "Ten sach", "Tac gia", "Nam XB");
    for (int i = 0; i < soluongPhieu; i++)
    {
        // Chi lay phieu cua chinh sinh vien dang dang nhap va con dang muon
        if (danhSachPhieu[i].idNguoiDung == tkHienTai->id && danhSachPhieu[i].trangThai == 0)
        {
            // Phieu chi luu ma sach nen phai tra lai mang sach lay thong tin hien thi
            vtSach = timSachTheoMa(danhSachSach, soluongSach, danhSachPhieu[i].maSach);
            if (vtSach != -1)
            {
                printf("%-10d %-10s %-30s %-20s %-8d\n",
                       danhSachPhieu[i].idPhieu,
                       danhSachSach[vtSach].maSach,
                       danhSachSach[vtSach].tenSach,
                       danhSachSach[vtSach].tacGia,
                       danhSachSach[vtSach].namXb);
                co = 1;
            }
        }
    }

    if (!co)
    {
        printf("Ban hien khong dang muon cuon sach nao.\n");
    }
}

TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, int *idTiepTheo)
{
    TaiKhoan tknew;
    char username[50];

    printf("Moi ban nhap vao username: ");
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

    // Ten dang nhap phai la duy nhat, trung thi huy ngay thao tac them
    if (timTkTheoTen(danhSachTK, *soluongTK, username) != -1)
    {
        printf("Loi: Ten dang nhap nay da duoc su dung.\n");
        return danhSachTK;
    }
    strcpy(tknew.username, username);

    printf("Moi ban nhap vao password: ");
    fgets(tknew.password, sizeof(tknew.password), stdin);
    tknew.password[strcspn(tknew.password, "\n")] = 0;

    do
    {
        printf("Moi ban nhap vao role (1 = Admin, 2 = Staff, 3 = Sinh vien): ");
        if (scanf("%d", &tknew.role) != 1)
        {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return danhSachTK;

        }
        getchar();
        if (tknew.role < 1 || tknew.role > 3)
        {
            printf("Loi: Role chi duoc chon 1, 2 hoac 3.\n");
        }
    } while (tknew.role < 1 || tknew.role > 3);

    // Mang day thi mo rong them 1 o (realloc co the CHUYEN mang sang dia chi moi
    // nen ham phai return con tro moi cho main nhan lai)
    if (*soluongTK >= *maxSizeTK)
    {
        if (*maxSizeTK == 0)
        {
            *maxSizeTK = 5; // mang vua bi xoa trang thi cap phat lai tu dau
        }
        else
        {
            (*maxSizeTK)++;
        }
        danhSachTK = (TaiKhoan *)realloc(danhSachTK, *maxSizeTK * sizeof(TaiKhoan));
    }

    tknew.id = (*idTiepTheo)++; // id tu tang de moi tai khoan luon co id duy nhat
    danhSachTK[*soluongTK] = tknew;
    (*soluongTK)++;

    printf("Da them tai khoan \"%s\" (ID = %d) thanh cong!\n", tknew.username, tknew.id);
    return danhSachTK;
}

TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, TaiKhoan *tkHienTai)
{
    char username[50];
    char thongBao[200];
    int vt;
    char traLoi;

    printf("Moi ban nhap vao username can xoa: ");
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
        printf("Loi: Khong tim thay tai khoan.\n");
        return danhSachTK;
    }

    // Tai khoan Admin goc (id = 1) va tai khoan dang dang nhap khong duoc phep xoa
    if (danhSachTK[vt].id == 1)
    {
        printf("Loi: Khong the xoa tai khoan Admin goc cua he thong.\n");
        return danhSachTK;
    }
    if (danhSachTK[vt].id == tkHienTai->id)
    {
        printf("Loi: Khong the tu xoa tai khoan ban dang dang nhap.\n");
        return danhSachTK;
    }

    // Ghep cau hoi xac nhan dung theo mau de bai yeu cau
    snprintf(thongBao, sizeof(thongBao), "Ban co chac muon xoa nguoi dung %s co vai tro %s (Y/N)? ",
            danhSachTK[vt].username, tenVaiTro(danhSachTK[vt].role));
    printf("%s", thongBao);
    scanf("%c", &traLoi);
    getchar();
    if (traLoi != 'Y' && traLoi != 'y')
    {
        printf("Da huy viec xoa tai khoan.\n");
        return danhSachTK;
    }

    // Doi cac phan tu phia sau len 1 vi tri de lap cho phan tu bi xoa
    for (int i = vt; i < *soluongTK - 1; i++)
    {
        danhSachTK[i] = danhSachTK[i + 1];
    }
    (*soluongTK)--;

    if (*soluongTK == 0)
    {
        free(danhSachTK); // xoa het thi tra vung nho, mang ve lai NULL
        danhSachTK = NULL;
        *maxSizeTK = 0;
    }
    else
    {
        // Thu nho mang dung bang so phan tu con lai
        *maxSizeTK = *soluongTK;
        danhSachTK = (TaiKhoan *)realloc(danhSachTK, *maxSizeTK * sizeof(TaiKhoan));
    }

    printf("Da xoa tai khoan thanh cong!\n");
    return danhSachTK;
}

void suaTk(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkHienTai)
{
    char username[50];
    int vt, choice, roleMoi;

    printf("Moi ban nhap vao username can sua: ");
    if (scanf("%s", username) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

    }
    getchar();

    vt = timTkTheoTen(danhSachTK, soluongTK, username);
    if (vt == -1)
    {
        printf("Loi: Khong tim thay tai khoan.\n");
        return;
    }

    printf("Da tim thay tai khoan: ID = %d | %s | Vai tro: %s\n",
           danhSachTK[vt].id, danhSachTK[vt].username, tenVaiTro(danhSachTK[vt].role));

    printf("1. Sua vai tro\n");
    printf("2. Sua mat khau\n");
    printf("Moi ban nhap vao lua chon: ");
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

    if (choice == 1)
    {
        do
        {
            printf("Moi ban nhap vao role moi (1 = Admin, 2 = Staff, 3 = Sinh vien): ");
            if (scanf("%d", &roleMoi) != 1)
            {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

            }
            getchar();
            if (roleMoi < 1 || roleMoi > 3)
            {
                printf("Loi: Role chi duoc chon 1, 2 hoac 3.\n");
            }
        } while (roleMoi < 1 || roleMoi > 3);

        danhSachTK[vt].role = roleMoi;

        // Neu admin tu sua vai tro cua chinh minh thi phai cap nhat luon tkHienTai
        if (danhSachTK[vt].id == tkHienTai->id)
        {
            tkHienTai->role = roleMoi;
        }
    }
    else if (choice == 2)
    {
        printf("Moi ban nhap vao mat khau moi: ");
        fgets(danhSachTK[vt].password, sizeof(danhSachTK[vt].password), stdin);
        danhSachTK[vt].password[strcspn(danhSachTK[vt].password, "\n")] = 0;
    }
    else
    {
        printf("Lua chon khong hop le!\n");
        return;
    }

    printf("Cap nhat thanh cong!\n");
}

void resetMatKhau(TaiKhoan *danhSachTK, int soluongTK)
{
    char username[50];
    int vt;

    printf("Moi ban nhap vao username can reset mat khau: ");
    if (scanf("%s", username) == EOF)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Du lieu khong hop le! Huy thao tac.\n");
        return;

    }
    getchar();

    vt = timTkTheoTen(danhSachTK, soluongTK, username);
    if (vt == -1)
    {
        printf("Loi: Khong tim thay tai khoan.\n");
        return;
    }

    strcpy(danhSachTK[vt].password, "123456");
    printf("Da reset mat khau cua \"%s\" ve \"123456\" thanh cong!\n", username);
}

void hienThiDsTk(TaiKhoan *danhSachTK, int soluongTK)
{
    if (soluongTK == 0)
    {
        printf("Chua co tai khoan nao trong he thong.\n");
        return;
    }

    printf("\n===== DANH SACH TAI KHOAN =====\n");
    printf("%-5s %-25s %-15s\n", "Id", "Username", "Role");
    for (int i = 0; i < soluongTK; i++)
    {
        printf("%-5d %-25s %-15s\n",
               danhSachTK[i].id, danhSachTK[i].username, tenVaiTro(danhSachTK[i].role));
    }
}

void hienThiDsSv(TaiKhoan *danhSachTK, int soluongTK, PhieuMuon *danhSachPhieu, int soluongPhieu)
{
    int co = 0;
    int dangMuon;

    printf("\n===== DANH SACH SINH VIEN =====\n");
    printf("%-5s %-25s %-12s\n", "Id", "Username", "Dang muon");
    for (int i = 0; i < soluongTK; i++)
    {
        // Chi loc nhung tai khoan co role la Sinh vien
        if (danhSachTK[i].role == 3)
        {
            // Dem so phieu con "dang muon" cua sinh vien nay de Thu thu theo doi
            dangMuon = 0;
            for (int j = 0; j < soluongPhieu; j++)
            {
                if (danhSachPhieu[j].idNguoiDung == danhSachTK[i].id && danhSachPhieu[j].trangThai == 0)
                {
                    dangMuon++;
                }
            }

            printf("%-5d %-25s %-12d\n", danhSachTK[i].id, danhSachTK[i].username, dangMuon);
            co = 1;
        }
    }

    if (!co)
    {
        printf("Chua co sinh vien nao trong he thong.\n");
    }
}

char *tenVaiTro(int role)
{
    if (role == 1)
    {
        return "Admin";
    }
    if (role == 2)
    {
        return "Thu thu";
    }
    if (role == 3)
    {
        return "Sinh vien";
    }
    return "Khong hop le";
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

void themTkMacDinh(TaiKhoan *danhSachTK, int *soluongTK)
{
    TaiKhoan tk1;
    tk1.id = 1;
    strcpy(tk1.username, "admin");
    strcpy(tk1.password, "123456");
    tk1.role = 1;

    TaiKhoan tk2;
    tk2.id = 2;
    strcpy(tk2.username, "staff");
    strcpy(tk2.password, "123456");
    tk2.role = 2;

    danhSachTK[0] = tk1;
    danhSachTK[1] = tk2;

    *soluongTK += 2;
}

void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkhientai)
{
    char user[50];
    char pass[50];
    int vt;
    int check = 0;

    printf("\n===== DANG NHAP =====\n");
    do
    {
        printf("Nhap username: ");
        if (scanf("%s", user) == EOF)
        {
            tkhientai->role = -2; // het du lieu nhap, bao main thoat chuong trinh
            return;
        }
        getchar();

        printf("Nhap password: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        vt = timTkTheoTen(danhSachTK, soluongTK, user);
        if (vt == -1)
        {
            printf("Loi: Ten dang nhap khong ton tai.\n");
        }
        else if (strcmp(danhSachTK[vt].password, pass) != 0)
        {
            printf("Loi: Sai mat khau.\n");
        }
        else
        {
            *tkhientai = danhSachTK[vt]; // dang nhap thanh cong, luu tai khoan hien tai
            printf("Dang nhap thanh cong! Xin chao \"%s\" voi vai tro %s.\n",
                   tkhientai->username, tenVaiTro(tkhientai->role));
            check = 1;
        }
    } while (check != 1);
}
