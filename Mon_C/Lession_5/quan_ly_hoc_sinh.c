#include <stdio.h>
#include <string.h>

#define MAX_HS 100

// =====================================================
// CÁC HÀM TIỆN ÍCH & NHẬP LIỆU CƠ BẢN
// =====================================================

// Xóa dữ liệu thừa trong bộ đệm bàn phím
void xoaBoDem()
{
    while (getchar() != '\n')
        ;
}

// Kiểm tra giới tính
int laNam(const char gioiTinh[])
{
    return (strcmp(gioiTinh, "Nam") == 0 || strcmp(gioiTinh, "nam") == 0);
}

int laNu(const char gioiTinh[])
{
    return (strcmp(gioiTinh, "Nu") == 0 || strcmp(gioiTinh, "nu") == 0);
}

// Nhập số học sinh ban đầu (1 - 100)
int nhapSoHocSinhBanDau()
{
    int n = 0;
    do
    {
        printf("Nhập số học sinh: ");

        if (scanf("%d", &n) != 1)
        {
            printf("Vui lòng nhập số nguyên!\n");
            xoaBoDem();
            n = 0;
        }
        else
        {
            xoaBoDem();

            if (n <= 0 || n > MAX_HS)
            {
                printf("Số học sinh phải từ 1 đến %d!\n", MAX_HS);
            }
        }

    } while (n <= 0 || n > MAX_HS);

    return n;
}

// Nhập tuổi (số nguyên > 0)
int nhapTuoi()
{
    int tuoi = 0;
    do
    {
        printf("Nhập tuổi: ");

        if (scanf("%d", &tuoi) != 1)
        {
            printf("Tuổi bắt buộc phải là số nguyên!\n");
            xoaBoDem();
            tuoi = 0;
        }
        else
        {
            char c = getchar();

            if (c != '\n')
            {
                printf("Tuổi chỉ được nhập số nguyên!\n");
                xoaBoDem();
                tuoi = 0;
            }

            if (tuoi <= 0)
            {
                printf("Tuổi phải lớn hơn 0!\n");
            }
        }

    } while (tuoi <= 0);

    return tuoi;
}

// Nhập tên (không để trống)
void nhapTen(char ten[])
{
    do
    {
        printf("Nhập tên: ");
        scanf(" %[^\n]", ten);

        if (strlen(ten) == 0)
        {
            printf("Tên không được để trống!\n");
        }

    } while (strlen(ten) == 0);

    xoaBoDem();
}

// Nhập giới tính (Nam/nam hoặc Nu/nu)
void nhapGioiTinh(char gioiTinh[])
{
    do
    {
        printf("Nhập giới tính (Nam/Nu): ");
        scanf("%9s", gioiTinh);
        xoaBoDem();

        if (!laNam(gioiTinh) && !laNu(gioiTinh))
        {
            printf("Giới tính chỉ được nhập Nam, nam, Nu hoặc nu!\n");
        }

    } while (!laNam(gioiTinh) && !laNu(gioiTinh));
}

// Nhập điểm (0.0 - 10.0)
float nhapDiem()
{
    float diem = -1;
    do
    {
        printf("Nhập điểm: ");

        if (scanf("%f", &diem) != 1)
        {
            printf("Điểm bắt buộc phải là số!\n");
            xoaBoDem();
            diem = -1;
        }
        else
        {
            char c = getchar();

            if (c != '\n')
            {
                printf("Điểm chỉ được nhập số!\n");
                xoaBoDem();
                diem = -1;
            }

            if (diem < 0 || diem > 10)
            {
                printf("Điểm phải từ 0 đến 10!\n");
            }
        }

    } while (diem < 0 || diem > 10);

    return diem;
}

// Nhập thông tin của 1 học sinh
void nhap1HocSinh(char ten[][50], int tuoi[], char gioiTinh[][10], float diem[], int i)
{
    printf("\n===== NHẬP HỌC SINH THỨ %d =====\n", i + 1);
    tuoi[i] = nhapTuoi();
    nhapTen(ten[i]);
    nhapGioiTinh(gioiTinh[i]);
    diem[i] = nhapDiem();
    printf("Đã nhập học sinh thành công!\n");
}

// Tính số ký tự hiển thị trực quan của chuỗi UTF-8 (bỏ qua continuation bytes)
int demKyTuUTF8(const char s[])
{
    int count = 0;
    int i = 0;
    while (s[i] != '\0')
    {
        if ((s[i] & 0xC0) != 0x80)
        {
            count++;
        }
        i++;
    }
    return count;
}

// In chuỗi có căn lề trái chuẩn theo số ký tự hiển thị thực tế
void inCanTraiUTF8(const char s[], int doRong)
{
    printf("%s", s);
    int len = demKyTuUTF8(s);
    for (int i = 0; i < doRong - len; i++)
    {
        putchar(' ');
    }
}

// In tiêu đề các cột của bảng
void inTieuDeBang()
{
    inCanTraiUTF8("STT", 6);
    inCanTraiUTF8("HỌ VÀ TÊN", 30);
    inCanTraiUTF8("TUỔI", 8);
    inCanTraiUTF8("GIỚI TÍNH", 12);
    inCanTraiUTF8("ĐIỂM", 8);
    printf("\n");
    printf("----------------------------------------------------------------\n");
}

// In một dòng thông tin học sinh
void inDongHocSinh(int stt, const char ten[], int tuoi, const char gioiTinh[], float diem)
{
    printf("%-6d", stt);
    inCanTraiUTF8(ten, 30);
    printf("%-8d", tuoi);
    inCanTraiUTF8(gioiTinh, 12);
    printf("%-8.2f\n", diem);
}

// =====================================================
// CÁC CHỨC NĂNG CHÍNH CỦA MENU
// =====================================================

// 1. Thêm học sinh (trả về số lượng học sinh mới sau khi thêm)
int themHocSinh(char ten[][50], int tuoi[], char gioiTinh[][10], float diem[], int n)
{
    int soLuongThem;

    if (n >= MAX_HS)
    {
        printf("\nDanh sách đã đủ %d học sinh!\n", MAX_HS);
        printf("Không thể thêm học sinh.\n");
        return n;
    }

    do
    {
        printf("Nhập số học sinh muốn thêm: ");

        if (scanf("%d", &soLuongThem) != 1)
        {
            printf("Vui lòng nhập số nguyên!\n");
            xoaBoDem();
            soLuongThem = 0;
        }
        else
        {
            xoaBoDem();

            if (soLuongThem <= 0)
            {
                printf("Số lượng phải lớn hơn 0!\n");
            }
            else if (n + soLuongThem > MAX_HS)
            {
                printf("Không thể thêm %d học sinh!\n", soLuongThem);
                printf("Hiện tại có %d học sinh.\n", n);
                printf("Chỉ có thể thêm tối đa %d học sinh.\n", MAX_HS - n);
            }
        }

    } while (soLuongThem <= 0 || n + soLuongThem > MAX_HS);

    for (int i = n; i < n + soLuongThem; i++)
    {
        nhap1HocSinh(ten, tuoi, gioiTinh, diem, i);
    }

    n = n + soLuongThem;

    printf("\nĐã thêm %d học sinh thành công!\n", soLuongThem);
    printf("Tổng số học sinh hiện tại: %d\n", n);

    return n;
}

// Hiển thị danh sách học sinh theo mode:
// mode = 1: Tất cả học sinh
// mode = 2: Học sinh nam
// mode = 3: Học sinh nữ
void hienThiDanhSach(char ten[][50], int tuoi[], char gioiTinh[][10], float diem[], int n, int mode)
{
    if (mode == 1)
    {
        printf("\n====================== DANH SÁCH HỌC SINH ======================\n");
    }
    else if (mode == 2)
    {
        printf("\n==================== DANH SÁCH HỌC SINH NAM ====================\n");
    }
    else if (mode == 3)
    {
        printf("\n==================== DANH SÁCH HỌC SINH NỮ ====================\n");
    }
    else
    {
        printf("\nChế độ hiển thị không hợp lệ!\n");
        return;
    }

    inTieuDeBang();

    int dem = 0;
    for (int i = 0; i < n; i++)
    {
        int thoaMan = 0;
        if (mode == 1)
        {
            thoaMan = 1;
        }
        else if (mode == 2 && laNam(gioiTinh[i]))
        {
            thoaMan = 1;
        }
        else if (mode == 3 && laNu(gioiTinh[i]))
        {
            thoaMan = 1;
        }

        if (thoaMan)
        {
            dem++;
            inDongHocSinh(dem, ten[i], tuoi[i], gioiTinh[i], diem[i]);
        }
    }

    if (dem == 0)
    {
        if (mode == 1)
        {
            printf("Danh sách học sinh trống!\n");
        }
        else if (mode == 2)
        {
            printf("Không có học sinh nam nào trong danh sách!\n");
        }
        else if (mode == 3)
        {
            printf("Không có học sinh nữ nào trong danh sách!\n");
        }
    }

    printf("================================================================\n");
}

// Tính điểm trung bình theo mode:
// mode = 1: Cả lớp
// mode = 2: Học sinh nam
// mode = 3: Học sinh nữ
void tinhDiemTrungBinh(char gioiTinh[][10], float diem[], int n, int mode)
{
    if (n == 0)
    {
        printf("\nDanh sách học sinh trống!\n");
        return;
    }

    float tong = 0;
    int dem = 0;

    for (int i = 0; i < n; i++)
    {
        int thoaMan = 0;
        if (mode == 1)
        {
            thoaMan = 1;
        }
        else if (mode == 2 && laNam(gioiTinh[i]))
        {
            thoaMan = 1;
        }
        else if (mode == 3 && laNu(gioiTinh[i]))
        {
            thoaMan = 1;
        }

        if (thoaMan)
        {
            tong += diem[i];
            dem++;
        }
    }

    if (dem == 0)
    {
        if (mode == 2)
        {
            printf("\nKhông có học sinh nam!\n");
        }
        else if (mode == 3)
        {
            printf("\nKhông có học sinh nữ!\n");
        }
        else
        {
            printf("\nKhông có dữ liệu để tính!\n");
        }
    }
    else
    {
        if (mode == 1)
        {
            printf("\nĐiểm trung bình của cả lớp: %.2f\n", tong / dem);
        }
        else if (mode == 2)
        {
            printf("\nĐiểm trung bình của học sinh nam: %.2f\n", tong / dem);
        }
        else if (mode == 3)
        {
            printf("\nĐiểm trung bình của học sinh nữ: %.2f\n", tong / dem);
        }
    }
}

// In menu ra màn hình
void inMenu()
{
    printf("\n========== MENU ==========\n");
    printf("1. Thêm học sinh\n");
    printf("2. In ra thông tin tất cả học sinh\n");
    printf("3. In ra danh sách học sinh nữ\n");
    printf("4. In ra danh sách học sinh nam\n");
    printf("5. Tính điểm trung bình của cả lớp\n");
    printf("6. Tính điểm trung bình học sinh nữ\n");
    printf("7. Tính điểm trung bình của học sinh nam\n");
    printf("8. Thoát chương trình\n");
    printf("===========================\n");
}

// =====================================================
// HÀM MAIN
// =====================================================
int main()
{
    int n;
    char ten[MAX_HS][50];
    int tuoi[MAX_HS];
    char gioiTinh[MAX_HS][10];
    float diem[MAX_HS];

    // Nhập danh sách học sinh ban đầu
    n = nhapSoHocSinhBanDau();
    for (int i = 0; i < n; i++)
    {
        nhap1HocSinh(ten, tuoi, gioiTinh, diem, i);
    }

    int chon = 0;
    while (chon != 8)
    {
        inMenu();
        printf("Nhập lựa chọn: ");

        if (scanf("%d", &chon) != 1)
        {
            printf("Vui lòng nhập số từ 1 đến 8!\n");
            xoaBoDem();
            chon = 0;
            continue;
        }

        xoaBoDem();

        switch (chon)
        {
        // 1. Thêm học sinh vào danh sách
        case 1:
            n = themHocSinh(ten, tuoi, gioiTinh, diem, n);
            break;

        // 2. In ra thông tin tất cả học sinh (mode = 1)
        case 2:
            hienThiDanhSach(ten, tuoi, gioiTinh, diem, n, 1);
            break;

        // 3. In ra danh sách học sinh nữ (mode = 3)
        case 3:
            hienThiDanhSach(ten, tuoi, gioiTinh, diem, n, 3);
            break;

        // 4. In ra danh sách học sinh nam (mode = 2)
        case 4:
            hienThiDanhSach(ten, tuoi, gioiTinh, diem, n, 2);
            break;

        // 5. Tính điểm trung bình của cả lớp (mode = 1)
        case 5:
            tinhDiemTrungBinh(gioiTinh, diem, n, 1);
            break;

        // 6. Tính điểm trung bình của học sinh nữ (mode = 3)
        case 6:
            tinhDiemTrungBinh(gioiTinh, diem, n, 3);
            break;

        // 7. Tính điểm trung bình của học sinh nam (mode = 2)
        case 7:
            tinhDiemTrungBinh(gioiTinh, diem, n, 2);
            break;

        // 8. Thoát chương trình
        case 8:
            printf("\nĐã thoát chương trình!\n");
            break;

        default:
            printf("\nLựa chọn không hợp lệ!\n");
            printf("Vui lòng chọn từ 1 đến 8.\n");
            break;
        }
    }

    return 0;
}