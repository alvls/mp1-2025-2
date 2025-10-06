#include <stdio.h>
#include <math.h>
#include <locale.h>

void main()
{
    char* locale = setlocale(LC_ALL, "");
    double h, w, d, dv, ds, dr, m1, m2, m3, m4, m5, m;
    printf("высота(см), ширина(см), глубина(см) ");
    scanf_s("%lf %lf %lf", &h, &w, &d);
    ds = 700;
    dv = 800;
    dr = 650;
    if ((180 <= h) && (h <= 220) && (80 <= w) && (w <= 120) && (50 <= d) && (d <= 90))
    {
        m1 = h * w * 0.5 / 1000000 * dv;
        m2 = (h * d * 1.5 / 1000000 * ds) * 2;
        m3 = (w * d * 1.5 / 1000000 * ds) * 2;
        m4 = (h * w / 1000000 * dr) * 2;
        m5= w * d / 1000000 * round((h - 3) / 40) * ds;
        m = m1 + m2 + m3 + m4 + m5;
        printf("Масса (кг) %lf", m);
    }
    else
    {
        printf("Ошибка ввода");
    }
}