#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
    double x1, y1, r1, x2, y2, r2;
    setlocale(LC_ALL, "ru_RU.UTF-8");

    printf("Enter x1 y1 r1: ");
    scanf_s("%lf %lf %lf", &x1, &y1, &r1);

    printf("Enter x2 y2 r2: ");
    scanf_s("%lf %lf %lf", &x2, &y2, &r2);

    double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if ((int)d == 0 && r1 == r2) {
        printf("Окружности совпадают");
    }
    else if ((d > r1 + r2) || (d < fabs(r1 - r2))) {
        printf("Окружности не пересекаются");
    }
    else if (d == r1 + r2) {
        printf("Окружности касаются внешним образом");
    }
    else if (d == fabs(r1 - r2)) {
        printf("Окружности касаются внутренним образом");
    }
    else if ((fabs(r1 - r2) < d) && (d < r1 + r2)) {
        printf("Окружности пересекаются");
    }


    return 0;
}