#include <stdio.h>

void reverse_string(char *str)
{
    // Kiểm tra nếu chuỗi rỗng hoặc NULL
    if (str == NULL || *str == '\0')
    {
        return;
    }

    char *start = str; // Con trỏ trỏ đến ký tự đầu chuỗi
    char *end = str;   // Con trỏ dùng để tìm ký tự cuối chuỗi

    // Dịch chuyển con trỏ end đến ký tự cuối cùng
    while (*end != '\0')
    {
        end++;
    }
    end--;

    // Hoán vị các ký tự giữa start và end cho đến khi gặp nhau
    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;

        start++; // Dịch start tiến lên
        end--;   // Dịch end lùi lại
    }
}

int main()
{
    char str1[] = "Hello World";
    printf("Chuỗi ban đầu:           %s\n", str1);
    reverse_string(str1);
    printf("Chuỗi sau khi đảo ngược: %s\n\n", str1);

    return 0;
}
