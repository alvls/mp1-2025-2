#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
	double x1, y1, r1, x2, y2, r2, g1;
	//setlocale(LC_ALL, "ru_RU.UTF-8");

	printf("Enter x1  y1  r1\n");
	scanf_s("%lf %lf %lf", &x1, &y1, &r1);

	printf("Enter x2  y2  r2\n");
	scanf_s("%lf %lf %lf", &x2, &y2, &r2);

	double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	//printf("D = %lf | ", d);
	//printf("fabs = %lf | ", fabs(r1 - r2));
	printf("\nBegin Processing ......\n");
	if ((int)d == 0 && r1 == r2) {
		printf("The circles coincide");
	}
	else if (d == r1 + r2) {
		printf("The circles touch externally");
	}
	else if (d == fabs(r1 - r2)) {
		printf("The circles touch internally");
	}
	else if ((d > r1 + r2) || (d < fabs(r1 - r2))) {
		printf("The circles do not intersect");
	}
	else if ((fabs(r1 - r2) < d) && (d < (r1 + r2))) {
		printf("The circles intersect");
	}
	printf("\nprogramm end\n");
	scanf_s("%lf", &g1);
	//return 1; 
}


