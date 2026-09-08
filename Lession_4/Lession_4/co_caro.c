#include <stdio.h>

int main()
{
    char board[3][3];

    int hang, cot;
    int luot = 0;
    int thang = 0;

    // Khởi tạo bàn cờ
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }

    // Bắt đầu trò chơi
    while (luot < 9 && thang == 0)
    {

        // In bàn cờ
        printf("\n-------------\n");

        for (int i = 0; i < 3; i++)
        {
            printf("|");

            for (int j = 0; j < 3; j++)
            {
                printf(" %c |", board[i][j]);
            }

            printf("\n-------------\n");
        }

        // Xác định người chơi
        char nguoiChoi;

        if (luot % 2 == 0)
        {
            nguoiChoi = 'X';
        }
        else
        {
            nguoiChoi = 'O';
        }

        printf("Lượt của người chơi %c\n", nguoiChoi);

        // Nhập vị trí
        printf("Nhập hàng (1-3): ");
        scanf("%d", &hang);

        printf("Nhập cột (1-3): ");
        scanf("%d", &cot);

        // Kiểm tra vị trí
        if (hang < 1 || hang > 3 || cot < 1 || cot > 3)
        {
            printf("Vị trí không hợp lệ! Vui lòng nhập lại.\n");
            continue;
        }

        // Chuyển về chỉ số của mảng
        hang--;
        cot--;

        // Kiểm tra ô đã được đánh chưa
        if (board[hang][cot] != ' ')
        {
            printf("Ô này đã được đánh! Vui lòng chọn ô khác.\n");
            continue;
        }

        // Đánh X hoặc O
        board[hang][cot] = nguoiChoi;

        // Kiểm tra hàng ngang
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == nguoiChoi &&
                board[i][1] == nguoiChoi &&
                board[i][2] == nguoiChoi)
            {

                thang = 1;
            }
        }

        // Kiểm tra hàng dọc
        for (int j = 0; j < 3; j++)
        {
            if (board[0][j] == nguoiChoi &&
                board[1][j] == nguoiChoi &&
                board[2][j] == nguoiChoi)
            {

                thang = 1;
            }
        }

        // Kiểm tra đường chéo chính
        if (board[0][0] == nguoiChoi &&
            board[1][1] == nguoiChoi &&
            board[2][2] == nguoiChoi)
        {

            thang = 1;
        }

        // Kiểm tra đường chéo phụ
        if (board[0][2] == nguoiChoi &&
            board[1][1] == nguoiChoi &&
            board[2][0] == nguoiChoi)
        {

            thang = 1;
        }

        // Thông báo người thắng
        if (thang == 1)
        {
            printf("\n🎉 Người chơi %c đã thắng!\n", nguoiChoi);
        }

        luot++;
    }

    // In bàn cờ cuối cùng
    printf("\n===== BÀN CỜ CUỐI CÙNG =====\n");

    printf("-------------\n");

    for (int i = 0; i < 3; i++)
    {
        printf("|");

        for (int j = 0; j < 3; j++)
        {
            printf(" %c |", board[i][j]);
        }

        printf("\n-------------\n");
    }

    // Kiểm tra hòa
    if (thang == 0)
    {
        printf("Trò chơi hòa!\n");
    }

    return 0;
}