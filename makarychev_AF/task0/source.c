#include <stdio.h>
#include <math.h>
#include <locale.h>
void main()
{
    char* locale = setlocale(LC_ALL, "");
    double x1,y1,r1,x2, y2, r2,d;
    scanf_s("%lf %lf %lf %lf %lf %lf", &x1,&y1,&r1, &x2, &y2, &r2);
    d = pow(pow((x1 - x2), 2) + pow((y1 - y2), 2), 0.5);
    if ((d==r1+r2)||(d==fabs(r1-r2)))
    {
        printf("Окружности касаются");
    }
    else
        if ((d < r1 + r2) && (d > abs(r1 - r2)))
    {
        printf("Окружности пересекаются");
    }
        else
        {
            printf("Окружности не пересекаются");
        }
}
