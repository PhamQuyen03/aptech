/*
 * BAI THI LAP TRINH C: HE THONG QUAN LY SACH THU VIEN
 * THUC HIEN CAU 1, CAU 2, CAU 3 & CAU 4
 * 
 * Cau 1 (3 diem): Dinh nghia struct Book va Menu chinh
 * Cau 2 (5 diem): Them va hien thi sach su dung mang tinh va con tro
 * Cau 3 (4 diem): Tim sach theo ID tra ve con tro Book*
 * Cau 4 (5 diem): Cap nhat gia sach su dung lai ham findBook thong qua con tro
 */

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 10

// ==================== CAU 1: KHAI BAO STRUCTURE ====================

// Dinh nghia struct Book theo dung yeu cau de bai
typedef struct Book
{
    int bookID;       // So nguyen (int)
    char title[50];   // Chuoi toi da 50 ky tu
    float price;      // So thuc (float)
} Book;

// ==================== HAM TIEN ICH ====================

// Xoa bo dem ban phim (stdin) de tranh troi lenh khi ket hop scanf va fgets
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// ==================== CAU 3: TIM KIEM SACH THEO ID ====================

/*
 * Ham tim kiem sach theo ID:
 * - books: Con tro tro toi mang sach
 * - count: So luong sach hien co
 * - bookID: Ma sach can tim
 * Tra ve: Con tro Book* tro toi quyen sach tim thay, hoac NULL neu khong tim thay
 */
Book* findBook(Book *books, int count, int bookID)
{
    Book *ptr = books;
    for (int i = 0; i < count; i++, ptr++)
    {
        if (ptr->bookID == bookID)
        {
            return ptr; // Tra ve con tro den sach tim thay
        }
    }
    return NULL; // Khong tim thay
}

// Kiem tra bookID da ton tai trong mang chua (tai su dung findBook)
int isBookIDExist(Book *books, int count, int id)
{
    return (findBook(books, count, id) != NULL);
}

// ==================== CAU 2: THEM VA HIEN THI SACH ====================

/*
 * Ham them sach moi vao mang:
 * - books: Con tro tro toi mang sach
 * - count: Con tro tro toi bien dem so luong sach
 */
void addBook(Book *books, int *count)
{
    // Kiem tra mang tinh da day chua (toi da 10 quyen)
    if (*count >= MAX_BOOKS)
    {
        printf("\n[LOI]: Danh sach sach da day (toi da %d quyen). Khong the them moi!\n", MAX_BOOKS);
        return;
    }

    // Su dung con tro tro toi vi tri phan tu moi can them
    Book *newBook = books + *count;

    int id;
    char title[100];
    float price;

    printf("\n--- THEM SACH MOI ---\n");

    // 1. Nhap va kiem tra bookID: phai la so nguyen duong va duy nhat
    while (1)
    {
        printf("Nhap ma sach (bookID): ");
        if (scanf("%d", &id) != 1)
        {
            printf("[LOI]: bookID phai la so nguyen. Vui long nhap lai!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (id <= 0)
        {
            printf("[LOI]: bookID phai la so nguyen duong (> 0). Vui long nhap lai!\n");
            continue;
        }

        if (isBookIDExist(books, *count, id))
        {
            printf("[LOI]: bookID %d da ton tai tren he thong. Vui long nhap ID khac!\n", id);
            continue;
        }

        break; // bookID hop le
    }

    // 2. Nhap va kiem tra title: khong duoc de trong
    while (1)
    {
        printf("Nhap tieu de sach (title): ");
        if (fgets(title, sizeof(title), stdin) == NULL)
        {
            printf("[LOI]: Khong the doc du lieu. Vui long thu lai!\n");
            continue;
        }
        title[strcspn(title, "\n")] = '\0'; // Xoa ky tu xuong dong

        // Kiem tra chuoi rong hoac chi chua khoang trang
        int len = strlen(title);
        int onlySpaces = 1;
        for (int i = 0; i < len; i++)
        {
            if (title[i] != ' ' && title[i] != '\t')
            {
                onlySpaces = 0;
                break;
            }
        }

        if (len == 0 || onlySpaces)
        {
            printf("[LOI]: Tieu de sach khong duoc de trong. Vui long nhap lai!\n");
            continue;
        }

        break; // title hop le
    }

    // 3. Nhap va kiem tra price: phai lon hon 0
    while (1)
    {
        printf("Nhap gia sach (price > 0): ");
        if (scanf("%f", &price) != 1)
        {
            printf("[LOI]: Gia sach phai la so thuc. Vui long nhap lai!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (price <= 0.0f)
        {
            printf("[LOI]: Gia sach phai lon hon 0. Vui long nhap lai!\n");
            continue;
        }

        break; // price hop le
    }

    // Gan du lieu truc tiep thong qua con tro
    newBook->bookID = id;
    strncpy(newBook->title, title, sizeof(newBook->title) - 1);
    newBook->title[sizeof(newBook->title) - 1] = '\0'; // Dam bao ket thuc chuoi an toan
    newBook->price = price;

    // Tang so luong sach thong qua con tro
    (*count)++;

    printf(">> Them sach moi thanh cong!\n");
    printf("   [ID: %d] \"%s\" - Gia: %.2f\n", newBook->bookID, newBook->title, newBook->price);
}

/*
 * Ham hien thi tat ca sach duoi dang bang:
 * - Bat buoc phai su dung con tro de duyet mang
 */
void displayBooks(const Book *books, int count)
{
    if (count == 0)
    {
        printf("\n(Danh sach sach hien dang trong. Chua co quyen sach nao!)\n");
        return;
    }

    printf("\n===================== DANH SACH SACH THU VIEN =====================\n");
    printf("%-10s | %-35s | %-12s\n", "Book ID", "Title", "Price");
    printf("-------------------------------------------------------------------\n");

    // Duyet mang thong qua con tro ptr
    const Book *ptr = books;
    for (int i = 0; i < count; i++, ptr++)
    {
        printf("%-10d | %-35s | %-12.2f\n", ptr->bookID, ptr->title, ptr->price);
    }

    printf("-------------------------------------------------------------------\n");
    printf("Tong so luong: %d / %d quyen sach.\n", count, MAX_BOOKS);
}

// ==================== CAU 3 & CAU 4: XU LY NGHIEP VU ====================

/*
 * Ham thuc hien chuc nang Cau 3: Tim sach theo ID
 * - Yeu cau nguoi dung nhap bookID
 * - Goi ham findBook() de lay con tro den quyen sach
 * - Neu tim thay: Hien thi thong tin sach
 * - Neu khong tim thay: Hien thi "Book not found"
 */
void searchBookByID(Book *books, int count)
{
    if (count == 0)
    {
        printf("\n(Danh sach hien dang trong. Chua co sach de tim kiem!)\n");
        return;
    }

    int searchID;
    printf("\n--- TIM SACH THEO ID ---\n");
    printf("Nhap ma sach (bookID) can tim: ");
    if (scanf("%d", &searchID) != 1)
    {
        printf("[LOI]: bookID phai la so nguyen!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Goi ham findBook tra ve con tro den sach tim duoc
    Book *foundBook = findBook(books, count, searchID);

    // Kiem tra con tro tra ve
    if (foundBook != NULL)
    {
        printf("\n>> Thong tin sach tim thay:\n");
        printf("   - Book ID: %d\n", foundBook->bookID);
        printf("   - Title:   %s\n", foundBook->title);
        printf("   - Price:   %.2f\n", foundBook->price);
    }
    else
    {
        // Dung theo yeu cau de bai: hien thi "Book not found"
        printf("\nBook not found\n");
    }
}

/*
 * Ham thuc hien chuc nang Cau 4: Cap nhat gia sach
 * - Yeu cau nguoi dung nhap bookID
 * - Su dung lai ham findBook o Cau 3 de tim sach thong qua con tro
 * - Neu tim thay: Nhap gia moi va cap nhat truc tiep qua con tro (book->price = newPrice;)
 * - Hien thi thong bao thanh cong / that bai
 */
void updateBookPrice(Book *books, int count)
{
    if (count == 0)
    {
        printf("\n(Danh sach hien dang trong. Chua co sach de cap nhat gia!)\n");
        return;
    }

    int updateID;
    printf("\n--- CAP NHAT GIA SACH ---\n");
    printf("Nhap ma sach (bookID) can cap nhat gia: ");
    if (scanf("%d", &updateID) != 1)
    {
        printf("[LOI]: bookID phai la so nguyen!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Su dung lai ham findBook o Cau 3 de lay con tro toi sach
    Book *book = findBook(books, count, updateID);

    if (book == NULL)
    {
        // Khong tim thay sach -> Thong bao loi
        printf("\nBook not found\n");
        printf("[LOI]: Khong the cap nhat do sach khong ton tai!\n");
        return;
    }

    printf(">> Da tim thay sach: [ID: %d] \"%s\" - Gia hien tai: %.2f\n",
           book->bookID, book->title, book->price);

    float newPrice;
    while (1)
    {
        printf("Nhap gia moi (price > 0): ");
        if (scanf("%f", &newPrice) != 1)
        {
            printf("[LOI]: Gia sach phai la so thuc. Vui long nhap lai!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (newPrice <= 0.0f)
        {
            printf("[LOI]: Gia sach phai lon hon 0. Vui long nhap lai!\n");
            continue;
        }

        break;
    }

    // Cap nhat truc tiep truong price thong qua con tro theo dung yeu cau de bai
    book->price = newPrice;

    printf(">> Cap nhat gia sach thanh cong!\n");
    printf("   [ID: %d] \"%s\" - Gia moi: %.2f\n", book->bookID, book->title, book->price);
}

// ==================== CAU 1: VONG LAP MENU CHINH ====================

int main()
{
    // Mang tinh luu toi da 10 quyen sach theo yeu cau Cau 2
    Book books[MAX_BOOKS];
    int count = 0; // So luong sach hien co trong mang
    int choice = 0;

    printf("===================================================================\n");
    printf("   BAI THI LAP TRINH C - HE THONG QUAN LY SACH THU VIEN\n");
    printf("===================================================================\n");

    while (1)
    {
        printf("\n=============== MENU CHINH ===============\n");
        printf("1. Them sach\n");
        printf("2. Xem tat ca sach\n");
        printf("3. Tim sach theo ID\n");
        printf("4. Cap nhat gia sach\n");
        printf("5. Thoat\n");
        printf("==========================================\n");
        printf("Moi ban nhap lua chon (1-5): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("[LOI]: Lua chon khong hop le! Vui long nhap so tu 1 den 5.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            // Truyen con tro den mang va con tro den bien count
            addBook(books, &count);
            break;

        case 2:
            // Truyen con tro den mang de duyet hien thi
            displayBooks(books, count);
            break;

        case 3:
            // Chuc nang Cau 3: Tim sach theo ID
            searchBookByID(books, count);
            break;

        case 4:
            // Chuc nang Cau 4: Cap nhat gia sach
            updateBookPrice(books, count);
            break;

        case 5:
            printf("\nCam on ban da su dung he thong. Chuong trinh ket thuc!\n");
            return 0;

        default:
            printf("[LOI]: Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
            break;
        }
    }

    return 0;
}
