/*
 * BAI TAP LON - HE THONG QUAN LY THU VIEN
 * GIAI DOAN 1 (STEP 1): 1.1 Dang nhap + 1.2 Menu Admin
 * Cac giai doan sau: step_2 them Menu Thu thu, step_3 hoan thien Menu Sinh vien
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TaiKhoan
{
    int id;
    char username[50];
    char password[50];
    int role; // 1 = Admin, 2 = Staff (Thu thu), 3 = Sinh vien
} TaiKhoan;

void themTkMacDinh(TaiKhoan *danhSachTK, int *soluongTK);
void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkhientai);
void hienThiDsTk(TaiKhoan *danhSachTK, int soluongTK);
void hienThiDsSv(TaiKhoan *danhSachTK, int soluongTK);
TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, int *idTiepTheo);
TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK, TaiKhoan *tkHienTai);
void suaTk(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkHienTai);
void resetMatKhau(TaiKhoan *danhSachTK, int soluongTK);
char *tenVaiTro(int role);
int timTkTheoTen(TaiKhoan *danhSachTK, int soluongTK, char *ten);
TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo, TaiKhoan *tkHienTai);

int main()
{
    int soluongTK = 0;
    int maxSizeTK = 5;
    int idTiepTheo = 3; // 2 tai khoan mac dinh da dung id 1 va 2
    TaiKhoan *danhSachTK;
    TaiKhoan tkHienTai;
    tkHienTai.role = -1; // role = -1 nghia la CHUA dang nhap

    danhSachTK = (TaiKhoan *)malloc(maxSizeTK * sizeof(TaiKhoan));
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
                                          &idTiepTheo, &tkHienTai);
            break;
        default: // cac vai tro khac se duoc xay dung o giai doan sau
            printf("Menu cua vai tro \"%s\" se duoc xay dung o giai doan sau. Tam thoi dang xuat.\n",
                   tenVaiTro(tkHienTai.role));
            tkHienTai.role = -1;
            break;
        }

        // role = -2 nghia la nguoi dung chon "Thoat chuong trinh" trong menu
        if (tkHienTai.role == -2)
        {
            break;
        }
    }

    free(danhSachTK);
    printf("Da giai phong bo nho. Tam biet!\n");
    return 0;
}

TaiKhoan *hienThiAdminMenu(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK,
                           int *idTiepTheo, TaiKhoan *tkHienTai)
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
            tkHienTai->role = -2; // het du lieu nhap, thoat chuong trinh
            return danhSachTK;
        }
        getchar();

        switch (choice)
        {
        case 1:
            hienThiDsTk(danhSachTK, *soluongTK);
            break;
        case 2:
            hienThiDsSv(danhSachTK, *soluongTK);
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

    printf("Ban co chac muon xoa nguoi dung %s?\n", danhSachTK[vt].username);
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

void hienThiDsSv(TaiKhoan *danhSachTK, int soluongTK)
{
    int co = 0;

    printf("\n===== DANH SACH SINH VIEN =====\n");
    printf("%-5s %-25s\n", "Id", "Username");
    for (int i = 0; i < soluongTK; i++)
    {
        // Chi loc nhung tai khoan co role la Sinh vien
        if (danhSachTK[i].role == 3)
        {
            printf("%-5d %-25s\n", danhSachTK[i].id, danhSachTK[i].username);
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
