#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

// Hàm nhập thông tin 1 sinh viên sử dụng con trỏ
void nhap_sv(char *ten_sv, float *diem_sv)
{
    printf("Nhập họ và tên: ");
    fgets(ten_sv, 50, stdin);

    // Xóa ký tự xuống dòng '\n' do fgets để lại bằng strchr
    char *p = strchr(ten_sv, '\n');
    if (p != NULL)
    {
        *p = '\0';
    }

    do
    {
        printf("Nhập điểm (0.0 - 10.0): ");
        scanf("%f", diem_sv);
        getchar();

        if (*diem_sv < 0.0f || *diem_sv > 10.0f)
        {
            printf("Điểm không hợp lệ! Điểm phải nằm trong khoảng [0.0, 10.0]. Vui lòng nhập lại.\n");
        }
    } while (*diem_sv < 0.0f || *diem_sv > 10.0f);
}

// Hàm chuẩn hóa tên: xóa khoảng trắng thừa ở đầu/cuối, viết hoa chữ cái đầu mỗi từ
// 2. Hàm chuẩn hóa tên bằng kỹ thuật hai con trỏ (read và write)
void chuan_hoa_ten(char *s)
{
    // Bước 1: Xóa khoảng trắng thừa (cắt bớt ký tự thừa)
    char *read = s;
    char *write = s;

    // Bỏ qua khoảng trắng ở đầu
    while (*read == ' ' || *read == '\t')
    {
        read++;
    }

    // Dịch chuyển và xóa khoảng trắng ở giữa
    while (*read != '\0')
    {
        if (*read != ' ' && *read != '\t')
        {
            *write = *read;
            write++;
            read++;
        }
        else
        {
            // Chỉ ghi 1 khoảng trắng nếu ký tự trước đó chưa phải là khoảng trắng
            if (write > s && *(write - 1) != ' ')
            {
                *write = ' ';
                write++;
            }
            // Bỏ qua các khoảng trắng liên tiếp
            while (*read == ' ' || *read == '\t')
            {
                read++;
            }
        }
    }

    // Xóa khoảng trắng ở cuối nếu có
    if (write > s && *(write - 1) == ' ')
    {
        *(write - 1) = '\0';
    }
    else
    {
        *write = '\0';
    }

    // Bước 2: Viết hoa chữ cái đầu tiên của mỗi từ
    char *p = s;
    while (*p != '\0')
    {
        if (p == s || *(p - 1) == ' ')
        {
            *p = toupper((unsigned char)*p);
        }
        else
        {
            *p = tolower((unsigned char)*p);
        }
        p++;
    }
}
void tim_thu_khoa(float diem[], int n, int *idx_max)
{
    if (n <= 0)
    {
        *idx_max = -1;
        return;
    }

    *idx_max = 0;
    for (int i = 1; i < n; i++)
    {
        if (diem[i] > diem[*idx_max])
        {
            *idx_max = i;
        }
    }
}

int tim_sv(char ten[][50], int n, const char *tu_khoa)
{
    for (int i = 0; i < n; i++)
    {
        if (strstr(ten[i], tu_khoa) != NULL)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    char ten[MAX][50];
    float diem[MAX];
    int n;

    do
    {
        printf("Nhập số lượng sinh viên (1 - %d): ", MAX);
        scanf("%d", &n);
        getchar();

        if (n < 1 || n > MAX)
        {
            printf("Số lượng không hợp lệ! Vui lòng nhập từ 1 đến %d.\n", MAX);
        }
    } while (n < 1 || n > MAX);

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Nhập thông tin sinh viên thứ %d ---\n", i + 1);
        nhap_sv(ten[i], &diem[i]);
        chuan_hoa_ten(ten[i]);
    }

    printf("\n==================== DANH SÁCH SINH VIÊN ====================\n");
    printf("%-5s %-30s %-10s\n", "STT", "Họ và tên", "Điểm");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-30s %-10.2f\n", i + 1, ten[i], diem[i]);
    }

    int idx_max;
    tim_thu_khoa(diem, n, &idx_max);
    if (idx_max != -1)
    {
        printf("\n>>> Thủ khoa của lớp là: %s với điểm số: %.2f\n", ten[idx_max], diem[idx_max]);
    }

    char tuKhoa[50];
    printf("\nNhập tên sinh viên cần tìm: ");
    fgets(tuKhoa, sizeof(tuKhoa), stdin);
    char *p = strchr(tuKhoa, '\n');
    if (p != NULL)
    {
        *p = '\0';
    }

    int idx_tim = tim_sv(ten, n, tuKhoa);
    if (idx_tim != -1)
    {
        printf("=> Tìm thấy sinh viên: %s - Điểm: %.2f (Vị trí thứ %d trong danh sách)\n",
               ten[idx_tim], diem[idx_tim], idx_tim + 1);
    }
    else
    {
        printf("=> Không tìm thấy sinh viên có tên chứa \"%s\"!\n", tuKhoa);
    }

    return 0;
}
