#include <stdio.h>
#include <math.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float x1, x2, y1, y2, r1, r2, rast;
	printf("Введите координаты первой окружности\n");
	scanf_s("%f %f", &x1, &y1);
	printf("Введите радиус первой окружности\n");
	scanf_s("%f", &r1);
	printf("Введите координаты второй окружности\n");
	scanf_s("%f %f", &x2, &y2);
	printf("Введите радиус второй окружности\n");
	scanf_s("%f", &r2);
	rast = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if ((rast < r1 + r2) && rast > fabs(r1 - r2)) {
		printf("Окружности пересекаются в двух точках\n");
	}
	else if (rast == 0 && r1 == r2) {
		printf("Окружности совпадают\n");
	}
	else if (rast == r1 + r2 || rast == fabs(r1 - r2)) {
		printf("Окружности пересекаются в одной точке\n");
	}
	else if (rast > r1 + r2 || rast < fabs(r1 - r2)) {
		printf("Окружности не пересекаются\n");
	}
	
	system("pause");
}