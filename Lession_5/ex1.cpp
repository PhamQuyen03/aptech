
#include <stdio.h>
#include <string.h>

int main()
{
    int n;

    // Khai báo tối đa 100 học sinh
    char ten[100][50];
    int tuoi[100];
    char gioiTinh[100][10];
    float diem[100];

    // =====================================================
    // NHẬP SỐ HỌC SINH BAN ĐẦU
    // =====================================================
    do
    {
        printf("Nhập số học sinh: ");

        if (scanf("%d", &n) != 1)
        {
            printf("Vui lòng nhập số nguyên!\n");

            // Xóa dữ liệu sai trong bộ đệm
            while (getchar() != '\n')
                ;
            n = 0;
        }
        else
        {
            // Xóa phần còn lại trong bộ đệm
            while (getchar() != '\n')
                ;

            if (n <= 0 || n > 100)
            {
                printf("Số học sinh phải từ 1 đến 100!\n");
            }
        }

    } while (n <= 0 || n > 100);

    // =====================================================
    // NHẬP THÔNG TIN HỌC SINH BAN ĐẦU
    // =====================================================
    for (int i = 0; i < n; i++)
    {
        printf("\n===== NHẬP HỌC SINH THỨ %d =====\n", i + 1);

        // -------------------------------------------------
        // NHẬP TUỔI
        // -------------------------------------------------
        do
        {
            printf("Nhập tuổi: ");

            if (scanf("%d", &tuoi[i]) != 1)
            {
                printf("Tuổi bắt buộc phải là số nguyên!\n");

                while (getchar() != '\n')
                    ;
                tuoi[i] = 0;
            }
            else
            {
                // Kiểm tra ký tự phía sau số
                char c = getchar();

                if (c != '\n')
                {
                    printf("Tuổi chỉ được nhập số nguyên!\n");

                    while (getchar() != '\n')
                        ;
                    tuoi[i] = 0;
                }

                if (tuoi[i] <= 0)
                {
                    printf("Tuổi phải lớn hơn 0!\n");
                }
            }

        } while (tuoi[i] <= 0);

        // -------------------------------------------------
        // NHẬP TÊN
        // -------------------------------------------------
        do
        {
            printf("Nhập tên: ");
            scanf(" %[^\n]", ten[i]);

            if (strlen(ten[i]) == 0)
            {
                printf("Tên không được để trống!\n");
            }

        } while (strlen(ten[i]) == 0);

        // Xóa Enter
        while (getchar() != '\n')
            ;

        // -------------------------------------------------
        // NHẬP GIỚI TÍNH
        // -------------------------------------------------
        do
        {
            printf("Nhập giới tính (Nam/Nu): ");
            scanf("%9s", gioiTinh[i]);

            // Xóa phần còn lại
            while (getchar() != '\n')
                ;

            if (strcmp(gioiTinh[i], "Nam") != 0 &&
                strcmp(gioiTinh[i], "nam") != 0 &&
                strcmp(gioiTinh[i], "Nu") != 0 &&
                strcmp(gioiTinh[i], "nu") != 0)
            {
                printf("Giới tính chỉ được nhập Nam, nam, Nu hoặc nu!\n");
            }

        } while (strcmp(gioiTinh[i], "Nam") != 0 &&
                 strcmp(gioiTinh[i], "nam") != 0 &&
                 strcmp(gioiTinh[i], "Nu") != 0 &&
                 strcmp(gioiTinh[i], "nu") != 0);

        // -------------------------------------------------
        // NHẬP ĐIỂM
        // -------------------------------------------------
        do
        {
            printf("Nhập điểm: ");

            if (scanf("%f", &diem[i]) != 1)
            {
                printf("Điểm bắt buộc phải là số!\n");

                while (getchar() != '\n')
                    ;
                diem[i] = -1;
            }
            else
            {
                char c = getchar();

                if (c != '\n')
                {
                    printf("Điểm chỉ được nhập số!\n");

                    while (getchar() != '\n')
                        ;
                    diem[i] = -1;
                }

                if (diem[i] < 0 || diem[i] > 10)
                {
                    printf("Điểm phải từ 0 đến 10!\n");
                }
            }

        } while (diem[i] < 0 || diem[i] > 10);

        printf("Đã nhập học sinh thành công!\n");
    }

    // =====================================================
    // MENU
    // =====================================================
    int chon = 0;

    while (chon != 7)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Thêm học sinh\n");
        printf("2. Hiển thị thông tin tất cả học sinh\n");
        printf("3. Tính điểm trung bình của học sinh nam\n");
        printf("4. Tính điểm trung bình của học sinh nữ\n");
        printf("5. Hiển thị danh sách học sinh nữ\n");
        printf("6. Hiển thị danh sách học sinh nam\n");
        printf("7. Thoát chương trình\n");
        printf("===========================\n");

        printf("Nhập lựa chọn: ");

        if (scanf("%d", &chon) != 1)
        {
            printf("Vui lòng nhập số từ 1 đến 7!\n");

            while (getchar() != '\n')
                ;
            chon = 0;
            continue;
        }

        while (getchar() != '\n')
            ;

        switch (chon)
        {
        // =====================================================
        // 1. THÊM HỌC SINH
        // =====================================================
        case 1:
        {
            int soLuongThem;

            if (n >= 100)
            {
                printf("\nDanh sách đã đủ 100 học sinh!\n");
                printf("Không thể thêm học sinh.\n");
                break;
            }

            // Nhập số lượng muốn thêm
            do
            {
                printf("Nhập số học sinh muốn thêm: ");

                if (scanf("%d", &soLuongThem) != 1)
                {
                    printf("Vui lòng nhập số nguyên!\n");

                    while (getchar() != '\n')
                        ;
                    soLuongThem = 0;
                }
                else
                {
                    while (getchar() != '\n')
                        ;

                    if (soLuongThem <= 0)
                    {
                        printf("Số lượng phải lớn hơn 0!\n");
                    }
                    else if (n + soLuongThem > 100)
                    {
                        printf("Không thể thêm %d học sinh!\n",
                               soLuongThem);

                        printf("Hiện tại có %d học sinh.\n", n);

                        printf("Chỉ có thể thêm tối đa %d học sinh.\n",
                               100 - n);
                    }
                }

            } while (soLuongThem <= 0 ||
                     n + soLuongThem > 100);

            // Nhập từng học sinh mới
            for (int i = n; i < n + soLuongThem; i++)
            {
                printf("\n===== NHẬP HỌC SINH THỨ %d =====\n", i + 1);

                // -------------------------------------------------
                // TUỔI
                // -------------------------------------------------
                do
                {
                    printf("Nhập tuổi: ");

                    if (scanf("%d", &tuoi[i]) != 1)
                    {
                        printf("Tuổi bắt buộc phải là số nguyên!\n");

                        while (getchar() != '\n')
                            ;
                        tuoi[i] = 0;
                    }
                    else
                    {
                        char c = getchar();

                        if (c != '\n')
                        {
                            printf("Tuổi chỉ được nhập số nguyên!\n");

                            while (getchar() != '\n')
                                ;
                            tuoi[i] = 0;
                        }

                        if (tuoi[i] <= 0)
                        {
                            printf("Tuổi phải lớn hơn 0!\n");
                        }
                    }

                } while (tuoi[i] <= 0);

                // -------------------------------------------------
                // TÊN
                // -------------------------------------------------
                printf("Nhập tên: ");
                scanf(" %[^\n]", ten[i]);

                while (getchar() != '\n')
                    ;

                // -------------------------------------------------
                // GIỚI TÍNH
                // -------------------------------------------------
                do
                {
                    printf("Nhập giới tính (Nam/Nu): ");
                    scanf("%9s", gioiTinh[i]);

                    while (getchar() != '\n')
                        ;

                    if (strcmp(gioiTinh[i], "Nam") != 0 &&
                        strcmp(gioiTinh[i], "nam") != 0 &&
                        strcmp(gioiTinh[i], "Nu") != 0 &&
                        strcmp(gioiTinh[i], "nu") != 0)
                    {
                        printf("Giới tính chỉ được nhập "
                               "Nam, nam, Nu hoặc nu!\n");
                    }

                } while (strcmp(gioiTinh[i], "Nam") != 0 &&
                         strcmp(gioiTinh[i], "nam") != 0 &&
                         strcmp(gioiTinh[i], "Nu") != 0 &&
                         strcmp(gioiTinh[i], "nu") != 0);

                // -------------------------------------------------
                // ĐIỂM
                // -------------------------------------------------
                do
                {
                    printf("Nhập điểm: ");

                    if (scanf("%f", &diem[i]) != 1)
                    {
                        printf("Điểm bắt buộc phải là số!\n");

                        while (getchar() != '\n')
                            ;
                        diem[i] = -1;
                    }
                    else
                    {
                        char c = getchar();

                        if (c != '\n')
                        {
                            printf("Điểm chỉ được nhập số!\n");

                            while (getchar() != '\n')
                                ;
                            diem[i] = -1;
                        }

                        if (diem[i] < 0 || diem[i] > 10)
                        {
                            printf("Điểm phải từ 0 đến 10!\n");
                        }
                    }

                } while (diem[i] < 0 || diem[i] > 10);

                printf("Đã nhập học sinh thành công!\n");
            }

            n = n + soLuongThem;

            printf("\nĐã thêm %d học sinh thành công!\n",
                   soLuongThem);

            printf("Tổng số học sinh hiện tại: %d\n", n);

            break;
        }

        // =====================================================
        // 2. HIỂN THỊ TẤT CẢ HỌC SINH
        // =====================================================
        case 2:
        {
            printf("\n====================== DANH SÁCH HỌC SINH ======================\n");

            printf("%-5s %-30s %-8s %-12s %-10s\n",
                   "STT",
                   "HỌ VÀ TÊN",
                   "TUỔI",
                   "GIỚI TÍNH",
                   "ĐIỂM");

            printf("-----------------------------------------------------------------\n");

            for (int i = 0; i < n; i++)
            {
                printf("%-5d %-30s %-8d %-12s %-10.2f\n",
                       i + 1,
                       ten[i],
                       tuoi[i],
                       gioiTinh[i],
                       diem[i]);
            }

            printf("=================================================================\n");

            break;
        }

        // =====================================================
        // 3. ĐIỂM TRUNG BÌNH NAM
        // =====================================================
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
                printf("\nKhông có học sinh nam!\n");
            }
            else
            {
                printf("\nĐiểm trung bình của học sinh nam: %.2f\n",
                       tong / dem);
            }

            break;
        }

        // =====================================================
        // 4. ĐIỂM TRUNG BÌNH NỮ
        // =====================================================
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
                printf("\nKhông có học sinh nữ!\n");
            }
            else
            {
                printf("\nĐiểm trung bình của học sinh nữ: %.2f\n",
                       tong / dem);
            }

            break;
        }

        // =====================================================
        // 5. DANH SÁCH NỮ
        // =====================================================
        case 5:
        {
            printf("\n================ DANH SÁCH HỌC SINH NỮ ================\n");

            printf("%-5s %-30s %-8s %-12s %-10s\n",
                   "STT",
                   "HỌ VÀ TÊN",
                   "TUỔI",
                   "GIỚI TÍNH",
                   "ĐIỂM");

            printf("----------------------------------------------------------\n");

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nu") == 0 ||
                    strcmp(gioiTinh[i], "nu") == 0)
                {
                    printf("%-5d %-30s %-8d %-12s %-10.2f\n",
                           i + 1,
                           ten[i],
                           tuoi[i],
                           gioiTinh[i],
                           diem[i]);
                }
            }

            printf("==========================================================\n");

            break;
        }

        // =====================================================
        // 6. DANH SÁCH NAM
        // =====================================================
        case 6:
        {
            printf("\n================ DANH SÁCH HỌC SINH NAM ================\n");

            printf("%-5s %-30s %-8s %-12s %-10s\n",
                   "STT",
                   "HỌ VÀ TÊN",
                   "TUỔI",
                   "GIỚI TÍNH",
                   "ĐIỂM");

            printf("----------------------------------------------------------\n");

            for (int i = 0; i < n; i++)
            {
                if (strcmp(gioiTinh[i], "Nam") == 0 ||
                    strcmp(gioiTinh[i], "nam") == 0)
                {
                    printf("%-5d %-30s %-8d %-12s %-10.2f\n",
                           i + 1,
                           ten[i],
                           tuoi[i],
                           gioiTinh[i],
                           diem[i]);
                }
            }

            printf("==========================================================\n");

            break;
        }

        // =====================================================
        // 7. THOÁT
        // =====================================================
        case 7:
        {
            printf("\nĐã thoát chương trình!\n");
            break;
        }

        default:
        {
            printf("\nLựa chọn không hợp lệ!\n");
            printf("Vui lòng chọn từ 1 đến 7.\n");
        }
        }
    }

    return 0;
}