#include <stdio.h>
#include <cmath>

int main()
{
	double x1, y1, r1;  // данные для первой окружности
	double x2, y2, r2;  // данные для второй окружности
	scanf("%lf%lf%lf", &x1, &y1, &r1);  // ввод данных для первой окружности
	scanf("%lf%lf%lf", &x2, &y2, &r2);  // ввод данных для второй окружности
	double rr;  // расстояние между центрами окружностей
	if (y1 == y2) rr = abs(x2 - x1);  // проверка условия, что если центры окружностей находятся на одном уровне, то расстояние между центрами равно разницой x-сов
	else if (y1 != y2)  // если окружности находятся на разных уровнях
	{
		double c1 = 0, c2 = 0;  // задаем длины катетов
		c1 = abs(y2 - y1);  // катет 1
		c2 = abs(x2 - x1);  // катет 2
		rr = pow((pow(c1, 2) + pow(c2, 2)), 0.5);  // итоговое расстояние между окружностями
	}
	if (rr < r1 + r2 && rr > abs(r1 - r2)) printf("The circles intersect");  // окружности пересекаются
	else if (rr == r1 + r2) printf("The circles touch each other");  // окружности касаются 
	else if (x1 == x2 && y1 == y2)  // окружности имеют общий центр
	{
		if (r1 == r2) printf("The circles match");  // окружности совпадают
		else printf("One circle lies in the other");  // одна окружность лежит в другой
	}
	else if (rr > r1 + r2) printf("The circles don't intersect");  // окружности не пересекаются 
	return 0;
}