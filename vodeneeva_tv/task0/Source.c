#include <stdio.h>
#include <math.h>

int main() 
{

 float center_x_1, center_y_1;  
 float center_x_2, center_y_2; 
 printf ("Введите центр первой окружности (x пробел y): ");
 scanf("%f %f", &center_x_1, &center_y_1);
 printf("Центр первой окружности: \tx: %f \ty: %f\n", center_x_1, center_y_1);
 int radius_1;
 printf ("Введите радиус первой окружности: ");
 scanf("%d", &radius_1);
 printf ("Радиус первой окружности: \t %d\n", radius_1);
 printf ("Введите центр второй окружности (x пробел y): ");
 scanf("%f %f", &center_x_2, &center_y_2);
 printf("Центр второй окружности: \tx: %f \ty: %f\n", center_x_2, center_y_2);
 int radius_2;
 printf ("Введите радиус второй окружности: ");
 scanf("%d", &radius_2);
 printf ("Радиус второй окружности: \t %d\n", radius_2);

 double distance = sqrt(pow(center_x_2 - center_x_1, 2) + pow(center_y_2 - center_y_1, 2));
 int sum_radius = radius_1 + radius_2;
 if (distance == sum_radius)
 {
    printf ("Окружности касаются в одной точке\n"); 
 }
 if (distance < sum_radius)
 {
    printf ("Окружности пересекаются\n"); 
 }
 if (distance > sum_radius)
 {
    printf ("Окружности не пересекаются и не касаются друг друга\n"); 
 }
 if (radius_1 == radius_2 && center_x_1 == center_x_2 && center_y_1 == center_y_2)
 {
   printf ("Окружности совпадают\n"); 
 }

 return 0;
}