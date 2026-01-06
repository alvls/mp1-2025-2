#include <stdio.h>
#include <math.h>

int main()
{
    double x, y;
    printf("Enter coordinates x and y: ");
    scanf("%lf %lf", &x, &y);

    // Example region: inside or on the circle centered at (0,0) with radius 5
    double r = 5.0;
    double distance = sqrt(x * x + y * y);

    if (distance <= r)
        printf("The point (%.2lf, %.2lf) is inside or on the circle.\n", x, y);
    else
        printf("The point (%.2lf, %.2lf) is outside the circle.\n", x, y); // fsfbf

    return 0;
}