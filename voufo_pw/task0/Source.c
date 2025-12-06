#include <stdio.h>
#include <math.h>

int main()
{
    double x1, y1, r1;
    double x2, y2, r2;

    printf("Enter x1 y1 r1: ");
    scanf("%lf %lf %lf", &x1, &y1, &r1);

    printf("Enter x2 y2 r2: ");
    scanf("%lf %lf %lf", &x2, &y2, &r2);

    // Compute the distance between the centers
    double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    // Compare distance and radii
    if (d == 0 && r1 == r2)
    {
        printf("The circles coincide .\n");
    }
    else if (d > r1 + r2)
    {
        printf("The circles are separate .\n");
    }
    else if (fabs(d - (r1 + r2)) < 1e-9)
    {
        printf("The circles touch externally.\n");
    }
    else if (fabs(d - fabs(r1 - r2)) < 1e-9)
    {
        printf("The circles touch internally.\n");
    }
    else if (d < fabs(r1 - r2))
    {
        printf("One circle is inside the other.\n");
    }
    else
    {
        printf("The circles intersect in two points.\n");
    }

    return 0;
}