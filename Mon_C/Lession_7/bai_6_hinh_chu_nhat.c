#include <stdio.h>
#include <string.h>

typedef struct HinhChuNhat
{
    float chieuDai;
    float chieuRong;
} HinhChuNhat;

void tinhChuVi(HinhChuNhat hcn)
{
    printf("Chu vi: %.2f\n", 2 * (hcn.chieuDai + hcn.chieuRong));
}

void tinhDienTich(HinhChuNhat hcn)
{
    printf("Diện tích: %.2f\n", hcn.chieuDai * hcn.chieuRong);
}

void tinhChuViPointer(HinhChuNhat *hcn)
{
    printf("Chu vi: %.2f\n", 2 * (hcn->chieuDai + hcn->chieuRong));
}

void tinhDienTichPointer(HinhChuNhat *hcn)
{
    printf("Diện tích: %.2f\n", hcn->chieuDai * hcn->chieuRong);
}

int main()
{
    HinhChuNhat hcn1;

    printf("Mời bạn nhập vào chiều dài: ");
    scanf("%f", &hcn1.chieuDai);

    printf("Mời bạn nhập vào chiều rộng: ");
    scanf("%f", &hcn1.chieuRong);

    tinhChuVi(hcn1);
    tinhDienTich(hcn1);

    tinhChuViPointer(&hcn1);
    tinhDienTichPointer(&hcn1);
    return 0;
}
