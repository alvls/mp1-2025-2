#include <stdio.h>
#include <locale.h>
#include <math.h>

void main()
{
    char* locale = setlocale(LC_ALL, "");
    double r1, r2;
    double center1_x, center1_y;
    double center2_x, center2_y;
    double rast;

    printf("Введите координаты первой окружности и её радиус: \n");
    scanf_s("%lf %lf %lf", &center1_x, &center1_y, &r1);
    printf("Ввдите координаты второй окружности и её радиус: \n");
    scanf_s("%lf %lf %lf", &center2_x, &center2_y, &r2);
    printf("%lf %lf %lf \n", center1_x, center1_y, r1);
    printf("%lf %lf %lf \n", center2_x, center2_y, r2);
    rast = pow(pow((center1_x - center2_x), 2) + pow((center1_y - center2_y), 2), 0.5);
    if (rast == r1 + r2) {
        printf("1. Окружности касаются");
    }
    else if ((center1_x == center2_x) && (center1_y == center2_y)) {
        if (r1 == r2) { printf("2.1 Окружности идиентичны"); }
        else { printf("2.2 Одна окружность находится в другой"); }
    }
    else if (rast < r1 + r2) {
        printf("3. Окружности пересекаются");
    }
    else if (rast > r1 + r2) {
        printf("4. Окружности не пересекаются");
    }
}