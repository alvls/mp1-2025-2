#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Ru");
    double x1, y1, r1;
    double x2, y2, r2;

    printf("Введите координаты центра первой окружности (x1 y1): ");
    scanf_s("%lf %lf", &x1, &y1);
    printf("Введите радиус первой окружности: ");
    scanf_s("%lf", &r1);

    printf("Введите координаты центра второй окружности (x2 y2): ");
    scanf_s("%lf %lf", &x2, &y2);
    printf("Введите радиус второй окружности: ");
    scanf_s("%lf", &r2);

    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    if (distance > r1 + r2) {
        printf("Окружности не пересекаются\n");
    }
    else if (distance < fabs(r1 - r2)) {
        printf("Одна окружность внутри другой\n");
    }
    else if (distance == fabs(r1 - r2)) {
        printf("Окружности касаются изнутри\n");
    }
    else if (distance == r1 + r2) {
        printf("Окружности касаются снаружи\n");
    }
    else {
        printf("Окружности пересекаются в двух точках\n");
    }

    return 0;
}