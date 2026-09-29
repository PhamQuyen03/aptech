#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book
{
    int bookID;
    char title[50];
    float price;
} Book;

Book *findById(Book *books, int bookCount, int bookID);
Book *findByTitle(Book *books, int bookCount, const char *textSearch);
Book *addBook(Book *books, int *bookCount, int *capacity);
void displayBooks(Book *books, int bookCount);
void updateBookById(Book *books, int bookCount);

int main()
{
    int capacity = 5;
    int bookCount = 0;
    int choice;
    Book *books = (Book *)malloc(capacity * sizeof(Book));

    if (books == NULL)
    {
        printf("Lỗi: Không thể cấp phát bộ nhớ!\n");
        return 1;
    }

    do
    {
        printf("\n===================== MENU =====================\n");
        printf("1. Thêm sách\n");
        printf("2. Xem tất cả sách\n");
        printf("3. Tìm sách theo ID\n");
        printf("4. Tìm sách theo tiêu đề\n");
        printf("5. Sửa thông tin sách\n");
        printf("6. Thoát\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &choice);
        getchar();

        Book *foundBook = NULL;

        switch (choice)
        {
        case 1:
            books = addBook(books, &bookCount, &capacity);
            break;
        case 2:
            displayBooks(books, bookCount);
            break;
        case 3:
            printf("Nhập ID sách cần tìm: ");
            int bookID;
            scanf("%d", &bookID);
            getchar();
            foundBook = findById(books, bookCount, bookID);
            if (foundBook != NULL)
            {
                printf("Thông tin sách tìm thấy:\n");
                printf("%-10s %-55s %-10s\n", "ID", "Tiêu đề", "Giá");
                printf("%-10d %-55s %-10.2f\n", foundBook->bookID, foundBook->title, foundBook->price);
            }
            else
            {
                printf("Không tìm thấy sách với ID %d.\n", bookID);
            }
            break;
        case 4:
            printf("Nhập tiêu đề cần tìm: ");
            char textSearch[50];
            fgets(textSearch, sizeof(textSearch), stdin);
            textSearch[strcspn(textSearch, "\n")] = '\0';

            foundBook = findByTitle(books, bookCount, textSearch);

            if (foundBook != NULL)
            {
                printf("Thông tin sách tìm thấy:\n");
                printf("%-10s %-55s %-10s\n", "ID", "Tiêu đề", "Giá");
                printf("%-10d %-55s %-10.2f\n", foundBook->bookID, foundBook->title, foundBook->price);
            }
            else
            {
                printf("Không tìm thấy sách với tiêu đề %s.\n", textSearch);
            }
            break;
        case 5:
            updateBookById(books, bookCount);
            break;
        case 6:
            printf("Thoát chương trình.\n");
            break;
        default:
            printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
            break;
        }

    } while (choice != 6);

    free(books);
    books = NULL;

    return 0;
}

Book *findById(Book *books, int bookCount, int bookID)
{
    Book *ptr = books;

    for (int i = 0; i < bookCount; i++)
    {
        if (ptr->bookID == bookID)
        {
            return ptr;
        }
        ptr++;
    }
    return NULL;
}

Book *findByTitle(Book *books, int bookCount, const char *textSearch)
{
    Book *ptr = books;

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(ptr->title, textSearch) == 0)
        {
            return ptr;
        }
        ptr++;
    }
    return NULL;
}

Book *addBook(Book *books, int *bookCount, int *capacity)
{
    if (*bookCount >= *capacity)
    {
        if (*capacity == 0)
        {
            *capacity = 5;
        }
        else
        {
            (*capacity)++;
        }
        Book *temp = (Book *)realloc(books, (*capacity) * sizeof(Book));
        if (temp == NULL)
        {
            printf("Lỗi: Không thể cấp phát thêm bộ nhớ!\n");
            return books;
        }
        books = temp;
    }

    int bookID;

    do
    {
        printf("Nhập ID sách: ");
        scanf("%d", &bookID);
        getchar();
        if (findById(books, *bookCount, bookID) != NULL)
        {
            printf("Sách với ID %d đã tồn tại.\n", bookID);
        }
    } while (findById(books, *bookCount, bookID) != NULL);

    books[*bookCount].bookID = bookID;
    printf("Nhập tiêu đề sách: ");
    fgets(books[*bookCount].title, sizeof(books[*bookCount].title), stdin);
    books[*bookCount].title[strcspn(books[*bookCount].title, "\n")] = '\0';

    printf("Nhập giá sách: ");
    scanf("%f", &books[*bookCount].price);
    getchar();

    (*bookCount)++;
    printf("Thêm sách thành công!\n");

    return books;
}

void displayBooks(Book *books, int bookCount)
{
    printf("\nDanh sách sách:\n");
    printf("%-10s %-55s %-10s\n", "ID", "Tiêu đề", "Giá");

    for (int i = 0; i < bookCount; i++)
    {
        printf("%-10d %-55s %-10.2f\n", books[i].bookID, books[i].title, books[i].price);
    }
}

void updateBookById(Book *books, int bookCount)
{
    int bookID;
    printf("Nhập ID sách cần sửa: ");
    scanf("%d", &bookID);
    getchar();

    Book *foundBook = findById(books, bookCount, bookID);

    if (foundBook != NULL)
    {

        int choice;
        printf("Thông tin sách cần sửa:\n");
        printf("%-10s %-55s %-10s\n", "ID", "Tiêu đề", "Giá");
        printf("%-10d %-55s %-10.2f\n", foundBook->bookID, foundBook->title, foundBook->price);
        printf("Bạn muốn sửa thông tin nào?\n");
        printf("1. Tiêu đề\n");
        printf("2. Giá\n");
        printf("Nhập lựa chọn (1 hoặc 2): ");

        do
        {
            scanf("%d", &choice);
            getchar();

            if (choice == 1)
            {
                printf("Nhập tiêu đề mới: ");
                fgets(foundBook->title, sizeof(foundBook->title), stdin);
                foundBook->title[strcspn(foundBook->title, "\n")] = '\0';
                printf("Cập nhật tiêu đề thành công!\n");
            }
            else if (choice == 2)
            {
                printf("Nhập giá mới: ");
                scanf("%f", &foundBook->price);
                getchar();
                printf("Cập nhật giá thành công!\n");
            }
            else
            {
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
            }
        } while (choice != 1 && choice != 2);

        printf("Cập nhật thông tin sách thành công!\n");
    }
    else
    {
        printf("Không tìm thấy sách với ID %d.\n", bookID);
    }
}
