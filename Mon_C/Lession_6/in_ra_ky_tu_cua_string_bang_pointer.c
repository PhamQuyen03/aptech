#include <stdio.h>

void print_string(char *str)
{
    // Lặp cho đến khi gặp ký tự kết thúc chuỗi '\0'
    while (*str != '\0')
    {
        printf("\n%c", *str); // In ký tự mà con trỏ đang trỏ tới
        str++;              // Dịch con trỏ sang ký tự tiếp theo
    }
}

int main()
{
    char text[] = "Xin chao, lap trinh C!";

    printf("In từng ký tự của string:\n");
    print_string(text);

    return 0;
}
