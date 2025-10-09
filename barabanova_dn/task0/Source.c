#include <stdio.h>
#include <math.h>

int main()
{
    double x1, y1, r1, x2, y2, r2;

    printf("Enter the coordinates of the center and radius of the first circle without a comma x1 y1 r1: ");
    scanf_s("%lf %lf %lf", &x1, &y1, &r1);

    printf("Enter the coordinates of the center and radius of the second circle without a comma x2 y2 r2: ");
    scanf_s("%lf %lf %lf", &x2, &y2, &r2);

    double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if (d == 0 && r1 == r2)
    {
        printf("The circles coincide.\n");
    }
    else if (d > r1 + r2)
    {
        printf("The outer circles do not intersect.\n");
    }
    else if (d == r1 + r2)
    {
        printf("The circles touch externally.\n");
    }
    else if (d < fabs(r1 - r2))
    {
        printf("One circle inside another entirely.\n");
    }
    else if (d == fabs(r1 - r2))
    {
        printf("The circles touch internally.\n");
    }
    else
    {
        printf("The circles intersect at two points.\n");
    }
    getchar();
    getchar();
    return 0;
}
