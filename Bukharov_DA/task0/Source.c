#include "stdio.h"
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    float x1, x2, y1, y2, r1, r2, d;
    printf("¬ведите координаты дл€ центра первой окружности\n");
    scanf_s("%f %f", &x1, &y1);
    printf("¬ведите радиус первой окружности\n");
    scanf_s("%f", &r1);
    printf("¬ведите координаты дл€ центра второй окружности\n");
    scanf_s("%f %f", &x2, &y2);
    printf("¬ведите радиус второй окружности\n");
    scanf_s("%f", &r2);

    d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if (d == 0 && r1 == r2) {
        printf("окружности полностью совпадают\n");
    }
    else if (d > r1 + r2 || d < fabs(r1 - r2)) {
        printf("окружности не пересекаютс€\n");
    }
    else if (d == r1 + r2 || d == fabs(r1 - r2)) {
        printf("окружности имеют одну общую точку\n");
    }
    else if (d < r1 + r2 && d > fabs(r1 - r2)) {
        printf("окружности имеют две общие точки\n");
    }

    system("pause");
}