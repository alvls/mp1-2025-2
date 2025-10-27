#include <stdio.h>
#include <math.h>

int main() 
{

 float center_x_1, center_y_1;  
 float center_x_2, center_y_2; 
 printf ("Введите центр первой окружности (x пробел y): ");
 scanf("%f %f", &center_x_1, &center_y_1);
 printf("Центр первой окружности: \tx: %f \ty: %f\n", center_x_1, center_y_1);
 short radius_1;
 printf ("Введите радиус первой окружности: ");
 scanf("%hd", &radius_1);
 printf ("Радиус первой окружности: \t %d\n", radius_1);
 printf ("Введите центр второй окружности (x пробел y): ");
 scanf("%f %f", &center_x_2, &center_y_2);
 printf("Центр второй окружности: \tx: %f \ty: %f\n", center_x_2, center_y_2);
 short radius_2;
 printf ("Введите радиус второй окружности: ");
 scanf("%hd", &radius_2);
 printf ("Радиус второй окружности: \t %d\n", radius_2);

 double distance = sqrt(pow(center_x_2 - center_x_1, 2) + pow(center_y_2 - center_y_1, 2));
 if (distance == radius_1 + radius_2)
 {
    printf ("Окружности касаются в одной точке "); 
 }
 if (distance < radius_1 + radius_2)
 {
    printf ("Окружности пересекаются "); 
 }
 if (distance > radius_1 + radius_2)
 {
    printf ("Окружности не пересекаются и не касаются друг друга "); 
 }
 if (radius_1 == radius_2 && center_x_1 == center_x_2 && center_y_1 == center_y_2)
 {
   printf ("Окружности совпадают"); 
 }
 return 0;
}