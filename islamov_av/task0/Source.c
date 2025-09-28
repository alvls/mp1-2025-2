#include <stdio.h>
#include <math.h>

 main() {
    double x1, y1, x2, y2, r1, r2, dist;
    printf("VVedite koordinati:");
    printf("x1 y1 r1 x2 y2 r2: ");
    scanf_s("%lf%lf%lf%lf%lf%lf", 
            &x1, &y1, &r1, &x2, &y2, &r2);
    dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    if (dist > r1 + r2) {
        printf("Okrughnosti ne peresekaytsya");
    }
    else if (dist == r1 + r2) {     
        printf("Okrughnosti kasaaytsya vneshne");
    }
    else if (dist == fabs(r1 - r2)) {  
        printf("Okrughnosti kasaaytsya vnutrenne");
    }
    else if (dist < fabs(r1 - r2)) {
        printf("Odna naxoditsya vnutri drugoi");
    }
    else if (dist == 0 && r1 == r2) {
        printf("Okrughnosti sovpadaut");  
    }
    else {                          
        printf("Okrughnosti peresekaytsya");
    }
    getchar();
    getchar();
    return 0;
}