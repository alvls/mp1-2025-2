#include <stdio.h>
#include <math.h>
#include <locale.h>

void main()
{
    char* locale = setlocale(LC_ALL, "");
    double h, w, d, dv, ds, dr, m;
    printf("высота(см), ширина(см), глубина(см) ");
    scanf_s("%lf %lf %lf", &h, &w, &d);
    ds = 700;
    dv = 800;
    dr = 650;
    if ((180 <= h) && (h <= 220) && (80 <= w) && (w <= 120) && (50 <= d) && (d <= 90))
    {
        m = (h * w * 0.5 /1000000 * dv) + ((h * d * 1.5 / 1000000 * ds) * 2) + ((w * d * 1.5 / 1000000 * ds) * 2) + ((h * w  /1000000 * dr) * 2) + (w * d /1000000 * round((h-3)/40)*ds);
        printf("Масса (кг) %lf", m);
    }
    else
    {
        printf("Ошибка ввода");
    }
}