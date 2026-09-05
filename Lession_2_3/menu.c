#include <stdio.h>

int main() {
    int choice;

    do {
        // ===== In ra menu =====
        printf("\n============ MENU ============\n");
        printf("1. Dãy số chia hết cho cả 3 và 5\n");
        printf("2. Tính tổng các số\n");
        printf("3. In ra bảng cửu chương\n");
        printf("4. Kiểm tra số hoàn hảo\n");
        printf("5. Tìm ước chung lớn nhất\n");
        printf("6. Tìm bội chung nhỏ nhất\n");
        printf("7. In hình chữ nhật\n");
        printf("8. In hình tam giác vuông\n");
        printf("9. In hình tam giác cân\n");
        printf("10. Thoát\n");
        printf("==============================\n");
        printf("Mời bạn chọn (1-10): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // In các số chia hết cho cả 3 và 5 từ 0 đến n
                int n;
                printf("Nhập vào 1 số: ");
                scanf("%d", &n);
                printf("Các số chia hết cho cả 3 và 5 từ 0 đến %d là:\n", n);
                for (int i = 0; i <= n; i++) {
                    if (i % 3 == 0 && i % 5 == 0) {
                        printf("%d ", i);
                    }
                }
                printf("\n");
                break;
            }
            case 2: {
                // Tính tổng các số từ 1 đến n
                int n, sum = 0;
                printf("Nhập vào số n: ");
                scanf("%d", &n);
                for (int i = 1; i <= n; i++) {
                    sum += i;
                }
                printf("Tổng các số từ 1 đến %d là: %d\n", n, sum);
                break;
            }
            case 3: {
                // In bảng cửu chương từ 1x1 đến 10x10
                printf("Bảng cửu chương từ 1x1 đến 10x10:\n");
                for (int i = 1; i <= 10; i++) {
                    for (int j = 1; j <= 10; j++) {
                        printf("%2d x %2d = %3d   ", i, j, i * j);
                    }
                    printf("\n");
                }
                break;
            }
            case 4: {
                // Kiểm tra số hoàn hảo: tổng các ước (khác chính nó) bằng chính nó
                int n, sum = 0;
                printf("Nhập vào 1 số: ");
                scanf("%d", &n);
                for (int i = 1; i < n; i++) {
                    if (n % i == 0) {
                        sum += i;
                    }
                }
                if (sum == n && n > 0) {
                    printf("%d là số hoàn hảo\n", n);
                } else {
                    printf("%d không phải là số hoàn hảo\n", n);
                }
                break;
            }
            case 5: {
                // Tìm ước chung lớn nhất (ƯCLN)
                int a, b, gcd;
                printf("Nhập 2 số a, b: ");
                scanf("%d %d", &a, &b);
                int min = (a < b) ? a : b;
                for (int i = min; i >= 1; i--) {
                    if (a % i == 0 && b % i == 0) {
                        gcd = i;
                        break;
                    }
                }
                printf("ƯCLN của %d và %d là: %d\n", a, b, gcd);
                break;
            }
            case 6: {
                // Tìm bội chung nhỏ nhất (BCNN) = a*b / ƯCLN
                int a, b, gcd, lcm;
                printf("Nhập 2 số a, b: ");
                scanf("%d %d", &a, &b);
                int min = (a < b) ? a : b;
                for (int i = min; i >= 1; i--) {
                    if (a % i == 0 && b % i == 0) {
                        gcd = i;
                        break;
                    }
                }
                lcm = (a * b) / gcd;
                printf("BCNN của %d và %d là: %d\n", a, b, lcm);
                break;
            }
            case 7: {
                // In hình chữ nhật bằng dấu sao
                int dai, rong;
                printf("Nhập chiều dài: ");
                scanf("%d", &dai);
                printf("Nhập chiều rộng: ");
                scanf("%d", &rong);
                for (int i = 1; i <= rong; i++) {
                    for (int j = 1; j <= dai; j++) {
                        printf("* ");
                    }
                    printf("\n");
                }
                break;
            }
            case 8: {
                // In hình tam giác vuông bằng dấu sao
                int h;
                printf("Nhập chiều cao tam giác: ");
                scanf("%d", &h);
                for (int i = 1; i <= h; i++) {
                    for (int j = 1; j <= i; j++) {
                        printf("* ");
                    }
                    printf("\n");
                }
                break;
            }
            case 9: {
                // In hình tam giác cân bằng dấu sao
                int h;
                printf("Nhập chiều cao tam giác: ");
                scanf("%d", &h);
                for (int i = 1; i <= h; i++) {
                    // In khoảng trắng trước dấu sao để hai bên cân bằng nhau
                    for (int j = 1; j <= h - i; j++) {
                        printf("  ");
                    }
                    // Mỗi hàng có (2*i - 1) ngôi sao
                    for (int j = 1; j <= 2 * i - 1; j++) {
                        printf("* ");
                    }
                    printf("\n");
                }
                break;
            }
            case 10:
                printf("Cảm ơn bạn đã sử dụng chương trình. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ! Vui lòng chọn từ 1 đến 10.\n");
        }
    } while (choice != 10);  // lặp lại cho đến khi chọn 10 (Thoát)

    return 0;
}
