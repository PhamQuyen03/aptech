#include <stdio.h>

typedef struct Diem
{
    float x;
    float y;
} Diem;

int main()
{
    Diem diemA = {5, 15};

    printf("Tọa độ của điểm A: (%.1f, %.1f)\n", diemA.x, diemA.y);

    return 0;
}
