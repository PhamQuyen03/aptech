#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TaiKhoan
{
    int id;
    char username[50];
    char password[50];
    int role;
} TaiKhoan;

void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkhientai);

void themTkmacdinh(TaiKhoan *danhSachTk, int *soluongTK);

void hienthidsTk(TaiKhoan *daSachTk, int soluongTK);

TaiKhoan *themTk(TaiKhoan *danhSachTK, int *soluongTK, int *soluongTkToiDa);
TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK);

TaiKhoan *hienThiAdminMenu(TaiKhoan *daSachTk, int *soluongTK, int *soluongTkToiDa);

int main()
{

    int soluongTK = 0;
    int maxSizetk = 5;
    TaiKhoan *danhSachTK;
    TaiKhoan tkHienTai;
    tkHienTai.role = -1;
    danhSachTK = (TaiKhoan *)malloc(maxSizetk * sizeof(TaiKhoan));
    themTkmacdinh(danhSachTK, &soluongTK);
    dangnhap(danhSachTK, soluongTK, &tkHienTai);
    if (tkHienTai.role != -1)
    {
        switch (tkHienTai.role)
        {
        case 1:
            danhSachTK = hienThiAdminMenu(danhSachTK, &soluongTK, &maxSizetk);
            break;
        case 2:
            break;
        case 3:
            break;
        }
    }

    free(danhSachTK);
}

TaiKhoan *hienThiAdminMenu(TaiKhoan *daSachTk, int *soluongTK, int *soluongTkToiDa)
{
    int choice = 0;
    do
    {
        printf("\n===== Menu ====\n");
        printf("1. Danh sach tai khoan\n");
        printf("2. Them tai khoan\n");
        printf("3. Xoa tai khoan\n");
        printf("4. Thoat\n");
        printf("Moi ban nhap vao lua chon:");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            hienthidsTk(daSachTk, *soluongTK);
            break;
        case 2:
            daSachTk = themTk(daSachTk, soluongTK, soluongTkToiDa);
            break;
        case 3:
            daSachTk = xoaTk(daSachTk, soluongTK, soluongTkToiDa);
            break;
        case 4:
            break;
        }
    } while (choice != 4);

    printf("\nTam biet %d ", choice);

    return daSachTk;
}

TaiKhoan *themTk(TaiKhoan *dsTam, int *soluongTK, int *soluongTkToiDa)
{
    if (*soluongTK >= *soluongTkToiDa)
    {
        (*soluongTkToiDa)++;
        dsTam = (TaiKhoan *)realloc(dsTam, *soluongTkToiDa * sizeof(TaiKhoan));
    }
    TaiKhoan tknew;
    printf("Moi ban nhap vao username\n");
    scanf("%s", tknew.username);
    getchar();
    printf("Moi ban nhap vao password\n");
    fgets(tknew.password, sizeof(tknew.password), stdin);
    tknew.password[strcspn(tknew.password, "\n")] = 0;

    printf("Moi ban nhap vao role\n");
    scanf("%d", &tknew.role);
    dsTam[*soluongTK] = tknew;
    (*soluongTK)++;

    return dsTam;
}

TaiKhoan *xoaTk(TaiKhoan *danhSachTK, int *soluongTK, int *maxSizeTK)
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

    if (danhSachTK[vt].id == 1)
    {
        printf("Loi: Khong the xoa tai khoan Admin goc cua he thong.\n");
        return danhSachTK;
    }

    printf("Ban co chac muon xoa nguoi dung %s?(Y/N)\n", danhSachTK[vt].username);
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

TaiKhoan *suaTk(TaiKhoan *danhSachTK, int *soluongTK)
{
    char username[50];
    char thongBao[200];
    int vt;
    char traLoi;

    printf("Moi ban nhap vao username can sua: ");
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

    if (danhSachTK[vt].id == 1)
    {
        printf("Loi: Khong the sua tai khoan Admin goc cua he thong.\n");
        return danhSachTK;
    }

    int choice;
    do
    {
        printf("1. Sua username\n");
        printf("2. Sua password\n");
        printf("3. Sua role\n");
        printf("0. Thoat\n");
        printf("Moi ban nhap vao lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Moi ban nhap vao username moi: ");
            scanf("%s", danhSachTK[vt].username);
            break;
        case 2:
            printf("Moi ban nhap vao password moi: ");
            fgets(danhSachTK[vt].password, sizeof(danhSachTK[vt].password), stdin);
            danhSachTK[vt].password[strcspn(danhSachTK[vt].password, "\n")] = 0;
            break;
        case 3:
            printf("Moi ban nhap vao role moi: ");
            scanf("%d", &danhSachTK[vt].role);
            break;
        case 0:
            break;
        default:
            printf("Lua chon khong hop le! Vui long nhap lai.\n");
            break;
        }

    } while (choice != 0);

    printf("Da sua tai khoan thanh cong!\n");
    return danhSachTK;
}

int timTkTheoTen(TaiKhoan *danhSachTK, int soluongTK, char *ten)
{
    for (int i = 0; i < soluongTK; i++)
    {
        if (strcmp(danhSachTK[i].username, ten) == 0)
            return i;
    }
    return -1;
}

void themTkmacdinh(TaiKhoan *danhSachTK, int *soluongTK)
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
void hienthidsTk(TaiKhoan *danhSachTK, int soluongTK)
{
    printf("%d", soluongTK);
    printf("%s", danhSachTK->username);
    printf("\n==== DANH SACH TAI KHOAN ====\n");

    printf("%-5s  %-20s  %-15s %-5s\n", "Id", "Username", "Password", "Role");
    for (int i = 0; i < soluongTK; i++)
    {
        printf("%-5d  %-20s  %-15s %-5d\n", danhSachTK->id, danhSachTK->username, danhSachTK->password, danhSachTK->role);
        danhSachTK++;
    }
}
void dangnhap(TaiKhoan *danhSachTK, int soluongTK, TaiKhoan *tkhientai)
{
    char user[50];
    char pass[50];

    printf("\n==== DANH NHAP ====\n");
    int check = 0;
    do
    {
        printf("Nhap username: ");
        scanf("%s", user);
        getchar();
        printf("Nhap password: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        for (int i = 0; i < soluongTK; i++)
        {
            if (strcmp(danhSachTK->username, user) == 0)
            {
                if (strcmp(danhSachTK->password, pass) == 0)
                {
                    *tkhientai = *danhSachTK;
                    printf("\nDang nhap thanh cong\n");
                    check = 1;
                }
                else
                {
                    printf("Mat khau khong dung\n");
                    check = 2;
                }
                break;
            }

            danhSachTK++;
        }
        if (check == 0)
        {
            printf("Khong tim thay tai khoan\n");
        }

    } while (check != 1);
}