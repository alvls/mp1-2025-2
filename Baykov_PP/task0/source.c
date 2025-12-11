#include "stdio.h"
#include <math.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float x1, x2, y1, y2, d1, d2, dist;
	printf("Введите координаты первой окружности\n");
	scanf_s("%f %f", &x1, &y1);
	printf("Введите радиус первой окружности\n");
	scanf_s("%f", &d1);
	printf("Введите координаты второй окружности\n");
	scanf_s("%f %f", &x2, &y2);
	printf("Введите радиус второй окружности\n");
	scanf_s("%f", &d2);
	dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if ((dist < d1 + d2) && dist > fabs(d1 - d2)) {
		printf("Окружности пересекаются в двух точках\n");
	}
	else if (dist == 0 && d1 == d2) {
		printf("Окружности совпадают\n");
	}
	else if (dist == d1 + d2 || dist == fabs(d1 - d2)) {
		printf("Окружности пересекаются в одной точке\n");
	}
	else if (dist > d1 + d2 || dist < fabs(d1 - d2)) {
		printf("Окружности не пересекаются\n");
	}

	system("pause");
}