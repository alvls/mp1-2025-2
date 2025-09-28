#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");
    double x1, y1, r1, x2, y2, r2, d;
    
    printf("Введите x1 y1 r1 x2 y2 r2: ");
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2);
    
    d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    
    if ((d == r1 + r2) || (d == fabs(r1 - r2)))
    {
        printf("Окружности касаются");
    }
    else if ((d < r1 + r2) && (d > fabs(r1 - r2)))
    {
        printf("Окружности пересекаются");
    }
    else
    {
        printf("Окружности не пересекаются");
    }
    
    return 0;
}