#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main(void) {
    double x1, x2, y1, y2, r1, r2, rmax, rmin, dist;
    printf("enter x1, y1, r1 \n");
    scanf("%lf" "%lf" "%lf", &x1, &y1, &r1);
    printf("enter x2, y2, r2 \n");
    scanf("%lf" "%lf" "%lf", &x2, &y2, &r2);
    dist = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
    rmax = fmax(r1, r2);
    rmin = fmin(r1, r2);
    if (r1 < 0 || r2 < 0) {
        printf("error, try again");//
    }
    else if (r1 == r1 && x1 == x2 && y1 == y2) {
        printf("circles matches"); //окружности совпадают
    }
    else if (dist > r1 + r2) {
        printf("don`t intersects");//не пересекаются
    }
    else if(dist == r1+r2)
    {
        printf("intersects in one point outside");//касаются снаружи
    }
    else if (rmax > dist+rmin) {
        printf("one circle inside other");//одна окружность внутри другой
    }
    else if (rmax == dist + rmin) {
        printf("circles intersects in one point inside");//касаются внутри
    }
    else {
        printf("circles intersects in two points");//пересекаются в друх точках
    }
    return 0;
}