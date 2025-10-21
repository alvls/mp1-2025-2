#include "stdio.h"
#include <math.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float x1, x2, y1, y2, r1, r2, rast;
	printf("¬ведите координаты первой окружности\n");
	scanf_s("%f %f", &x1, &y1);
	printf("¬ведите радиус первой окружности\n");
	scanf_s("%f", &r1);
	printf("¬ведите координаты второй окружности\n");
	scanf_s("%f %f", &x2, &y2);
	printf("¬ведите радиус второй окружности\n");
	scanf_s("%f", &r2);
	rast = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if ((rast < r1 + r2) && rast > fabs(r1 - r2)) {
		printf("окружности пересекаютс€ в двух точках\n");
	}
	if (rast == r1 + r2 || rast == fabs(r1 - r2)) {
		printf("окружности пересекаютс€ в одной точке\n");
	}
	if (rast > r1 + r2 || rast < fabs(r1 - r2)) {
		printf("окружности не пересекаютс€\n");
	}
	system("pause");
}