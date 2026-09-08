#include <stdio.h>

int main() {
    int so;
    int tram, chuc, donVi;
    int tong;

    printf("Nhập vào số có 3 chữ số: ");
    scanf("%d", &so);

    tram = so / 100;
    chuc = (so / 10) % 10;
    donVi = so % 10;

    tong = tram + chuc + donVi;

    printf("Tổng các chữ số = %d\n", tong);

    return 0;
}