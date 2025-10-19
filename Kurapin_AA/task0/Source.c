#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Rus");

	double x1, y1, R1, x2, y2, R2;

	printf("Введите x1, y1:\n");
	scanf_s("%lf %lf", &x1, &y1);
	printf("Введите R1:\n");
	scanf_s("%lf", &R1);
	printf("Введите x2, y2:\n");
	scanf_s("%lf %lf", &x2, &y2);
	printf("Введите R2:\n");
	scanf_s("%lf", &R2);

	double distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	int maxC, minC;
	if (R1 > R2)
		maxC = 1, minC = 2;
	else
		maxC = 2, minC = 1;

	if (distance > R1 + R2) {
		printf("Окружности не пересекаются\n");
	}
	else if (distance < abs(R1 - R2)) {
		printf("Окружность %i полностью находится внутри окружности %i, они не касаются\n", minC, maxC);
	}
	else if (distance = R1 + R2) {
		printf("Окружности касаются внешне\n");
	}
	else if (distance == abs(R1 - R2) && distance != 0) {
		printf("Окружность %i находится внутри окружности %i, они касаются внутренне\n", minC, maxC);
	}
	else if (abs(R1 - R2) < distance < R1 + R2) {
		printf("Окружности пересекаются в двух точках\n");
	}
	else if (distance == 0 && R1 == R2) {
		printf("Окружности совпадают\n");
	}

	system("pause");

	return 1;
}