#include <stdio.h>
#include <math.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL, "rus");
	double x1, y1, x2, y2, r1, r2;
	printf("Введите координаты Окр1 (через пробел): ");
	scanf_s("%lf %lf", &x1, &y1);
	printf("Введите координаты Окр2 (через пробел): ");
	scanf_s("%lf %lf", &x2, &y2);
	printf("Введите радиусы Окр1 и Окр2 (через пробел): ");
	scanf_s("%lf %lf", &r1, &r2);
	double s = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);

	if (s == 0)
	{
		if (r1 == r2)
			printf("Окружности совпадают");
		else
		{
			if (r1 > r2)
				printf("Окр2 лежит внутри Окр1, и у них совпадают центры");
			else
				printf("Окр1 лежит внутри Окр2, и у них совпадают центры");
		}
	}
	else
	{
		if (s > r1 + r2)
			printf("Окружности не пересекаются");
		else
		{
			if (s == r1 + r2)
				printf("Окружности пересекаются в 1 точке");
			else
			{
				if (s == fabs(r1 - r2))
				{
					if (r1 > r2)
						printf("Окр2 лежит внутри Окр1, и они имеют 1 общую точку");
					else
						printf("Окр1 лежит внутри Окр2, и они имеют 1 общую точку");
				}
				else
				{
					if (s < fabs(r1 - r2))
					{
						if (r1 > r2)
							printf("Окр2 лежит внутри Окр1");
						else
							printf("Окр1 лежит внутри Окр2");
					}
					else
						printf("Окружности пересекаются в 2 точках");
				}
			}
		}
	}
	getchar();
	getchar();
}
