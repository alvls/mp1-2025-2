#include <conio.h>
#include <math.h>
#include <stdio.h>

int main()
{
	double x1, x2, y1, y2, r1, r2, D, k;
	printf("Enter the coordinates of the center and the radius of the \x1b[32m1st\x1b[0m circle: ");
	scanf_s("%lf %lf %lf", &x1, &y1, &r1);
	printf("Enter the coordinates of the center and the radius of the \x1b[32m2nd\x1b[0m circle: ");
	scanf_s("%lf %lf %lf", &x2, &y2, &r2);

	k = r1 + r2;
	
	D = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	if (D <= fmin(r1,r2))printf("A circle within a circle");
	else if (k > D) printf("The circles intersecting");
	if (k == D) printf("The circles touching");
	if (k < D) printf("The circles don't intersect");
	_getch(0);
	return 0;
}