
#include <stdio.h>
#include <string.h>

int main()
{
    int n;

        // Nhập số học sinh
    do
    {
        printf("Nhập số học sinh: ");
        scanf("%d", &n);
    } while (n <= 0 || n > 100);

    char ten[n][50];
    int tuoi[n];
    char gioiTinh[n][10];
    float diem[n];

    // Nhập thông tin học sinh
    for (int i = 0; i < n; i++)
    {
        printf("\n===== NHẬP HỌC SINH THỨ %d =====\n", i + 1);

        printf("Nhập tên: ");
        scanf(" %[^\n]", ten[i]);

        printf("Nhập tuổi: ");
        scanf("%d", &tuoi[i]);

        printf("Nhập giới tính (Nam/Nu): ");
        scanf("%s", gioiTinh[i]);

        printf("Nhập điểm: ");
        scanf("%f", &diem[i]);
    }

    // Menu
    int chon = 0;

    while (chon != 7)
    {
        printf("\n========== MENU ==========\n");
        printf("2. In ra thông tin tất cả học sinh\n");
        printf("3. Tính điểm trung bình của học sinh nam\n");
        printf("4. Tính điểm trung bình của học sinh nữ\n");
        printf("5. In ra danh sách học sinh nữ\n");
        printf("6. In ra danh sách học sinh nam\n");
        printf("7. Thoát chương trình\n");
        printf("===========================\n");

        printf("Nhập lựa chọn: ");
        scanf("%d", &chon);

        switch (chon)
        {

        // 2. In tất cả học sinh
        case 2:
            printf("\n===== THÔNG TIN TẤT CẢ HỌC SINH =====\n");

            for (int i = 0; i < n; i++)
            {
                printf("\nHọc sinh thứ %d:\n", i + 1);
                printf("Tên: %s\n", ten[i]);
                printf("Tuổi: %d\n", tuoi[i]);
                printf("Giới tính: %s\n", gioiTinh[i]);
                printf("Điểm: %.2f\n", diem[i]);
            }
            break;

        // 3. Điểm trung bình học sinh nam
        case 3:
        {
            float tong = 0;
            int dem = 0;

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nam") == 0 ||
                    strcmp(gioiTinh[i], "nam") == 0)
                {

                    tong += diem[i];
                    dem++;
                }
            }

            if (dem == 0)
            {
                printf("Không có học sinh nam!\n");
            }
            else
            {
                printf("Điểm trung bình của học sinh nam: %.2f\n",
                       tong / dem);
            }

            break;
        }

        // 4. Điểm trung bình học sinh nữ
        case 4:
        {
            float tong = 0;
            int dem = 0;

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nu") == 0 ||
                    strcmp(gioiTinh[i], "nu") == 0)
                {

                    tong += diem[i];
                    dem++;
                }
            }

            if (dem == 0)
            {
                printf("Không có học sinh nữ!\n");
            }
            else
            {
                printf("Điểm trung bình của học sinh nữ: %.2f\n",
                       tong / dem);
            }

            break;
        }

        // 5. In danh sách học sinh nữ
        case 5:
            printf("\n===== DANH SÁCH HỌC SINH NỮ =====\n");

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nu") == 0 ||
                    strcmp(gioiTinh[i], "nu") == 0)
                {

                    printf("\nTên: %s\n", ten[i]);
                    printf("Tuổi: %d\n", tuoi[i]);
                    printf("Giới tính: %s\n", gioiTinh[i]);
                    printf("Điểm: %.2f\n", diem[i]);
                }
            }
            break;

        // 6. In danh sách học sinh nam
        case 6:
            printf("\n===== DANH SÁCH HỌC SINH NAM =====\n");

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nam") == 0 ||
                    strcmp(gioiTinh[i], "nam") == 0)
                {

                    printf("\nTên: %s\n", ten[i]);
                    printf("Tuổi: %d\n", tuoi[i]);
                    printf("Giới tính: %s\n", gioiTinh[i]);
                    printf("Điểm: %.2f\n", diem[i]);
                }
            }
            break;

        // 7. Thoát
        case 7:
            printf("Đã thoát chương trình!\n");
            break;

        default:
            printf("Lựa chọn không hợp lệ! Vui lòng chọn từ 2 đến 7.\n");
        }
    }

    return 0;
}
