#include <stdio.h>
#include <math.h>
#include<locale.h>

void main()
{
	char* locale = setlocale(LC_ALL, "");
	double x1, x2, y1, y2, r1, r2, d;


	printf("x1, y1, r1 ");
	scanf_s("%lf %lf %lf", &x1, &y1, &r1);
	printf("x2, y2, r2 ");
	scanf_s("%lf %lf %lf", &x2, &y2, &r2);
	d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	if (((d > (r1 + r2))) || (d < (fabs(r1 - r2))))
		printf("не пересекаются");
	if ((d < (r1 + r2)) && (d > (fabs(r1 - r2))))
		printf("пересекаются");
	if (((d == (r1 + r2)) || (d == (fabs(r1 - r2))))&&((x1!=x2)||(y1!=y2)))
		printf("касаются");
	if((x1==x2)&&(y1==y2)&&(r1==r2))
		printf("совпадают");


}