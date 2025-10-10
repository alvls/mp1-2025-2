#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	double r1, r2, x1, y1, x2, y2, d;
	printf("Print r1: \n");
	scanf_s("%lf", &r1);
	printf("Print r2: \n");
	scanf_s("%lf", &r2);
	printf("Print x1: \n");
	scanf_s("%lf", &x1);
	printf("Print y1: \n");
	scanf_s("%lf", &y1);
	printf("Print x2: \n");
	scanf_s("%lf", &x2);
	printf("Print y2: \n");
	scanf_s("%lf", &y2);
	d = sqrt((x1 * x1 - 2 * x1 * x2 + x2 * x2) + (y1 * y1 - 2 * y1 * y2 + y2 * y2));
	if ((r1 <= 0) || (r2 <= 0))
	{
		printf("r1 or r2 = 0. False. Tri again.");
		return 1;
	}
	if ((x1 == x2) && (y1 == y2) && (r1 == r2))
	{
		printf("The circles match");
		return 0;
	}
	if (d > (r1 + r2))
	{
		printf("There are no common points");
		return 0;
	}
	if ((x1 == x2) && (y1 == y2) && (r1 != r2))
	{
		printf("There are no common points, the circle is in another circle");
		return 0;
	}
	if (d < fabs(r1 - r2))
	{
		printf("There are no common points, the circle is in another circle");
		return 0;
	}
	if (d == fabs(r1 - r2))
	{
		printf("The inner touch of the circle");
		return 0;
	}
	if (d == (r1 + r2))
	{
		printf("External touchind of the circles");
		return 0;
	}
	if (d < (r1 + r2))
	{
		printf("Intersection of circles");
		return 0;
	}
}