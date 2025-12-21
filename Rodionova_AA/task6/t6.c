#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

double exp1(double xp, double x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return xp * (x / n);
}

double sin1(double xp, double x, int n)
{
	if (n == 0)
	{
		return x;
	}
	return fabs(xp) * (x * x / (2 * n * (2 * n + 1))) * pow(-1, n);
}

double cos1(double xp, double x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return fabs(xp) * (x * x / (2 * n * (2 * n + 1))) * pow(-1, n);
}
double sh1(double xp, double x, int n)
{
	if (n == 0)
	{
		return x;
	}
	return xp * (x * x / (2 * n * (2 * n + 1)));
}
int count;
double taylor(int N, double acc, double (*st)(double xp, double x, int n), double x, double resm)
{
	double res = 0, e = 0, f = 10;
	int Nsum = 0;
	while (Nsum != N && f > acc)
	{
		e = st(e, x, Nsum);
		res += e;
		Nsum++;
		f = fabs(resm - res);
	}
	count = Nsum;
	return res;
}

void main()
{
	char* locale = setlocale(LC_ALL, "");
	double x, acc, b, c;
	int choice, func, n, ex, v = 0;
	do {
		printf("Режим 1: Однократный расчет функции в заданной точке\n");
		printf("Режим 2: вывести данные отсканированного товара \n");
		printf("Выход 0 \n");
		printf("Выберите режим \n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			printf("Выберите функцию:\n");
			printf("1. Sin(x)\n");
			printf("2. Cos(x)\n");
			printf("3. Exp(x)\n");
			printf("4. Sh(x)\n");
			scanf_s("%d", &func);
			printf("Введите точку x, в которой необходимо вычислить значение\n");
			scanf_s(" %lf", &x);
			printf("Введите точность вычислений >0,000001: ");
			scanf_s(" %lf", &acc);
			if (acc < 0.000001)
			{
				printf("Введена некорректная точность вычислений\n");
				continue;
			}
			printf("Введите количество элементов ряда для выполнения расчетов от 1 до 1000: \n");
			scanf_s(" %d", &n);
			if ((n < 1) || (n > 1000))
			{
				printf("Введено некорректное количество элементов ряда для выполнения расчетов\n");
				continue;
			}
			switch (func)
			{
			case 1:
			{
				b = sin(x);
				printf("эталонное значение %fl\n", b);
				c = taylor(n, acc, sin1, x, sin(x));
				printf("оценка значения функции %fl\n", c);
				printf("разница между оценкой и эталонным значением %fl\n", (fabs(b - c)));
				printf("количество слагаемых, которое было вычислено %d\n", count);
				break;

			}
			case 2:
			{
				b = cos(x);
				printf("эталонное значение %fl\n", b);
				c = taylor(n, acc, cos1, x, cos(x));
				printf("оценка значения функции %fl\n", c);
				printf("разница между оценкой и эталонным значением %fl\n", (fabs(b - c)));
				printf("количество слагаемых, которое было вычислено %d\n", count);
				break;
			}
			case 3:
			{
				b = exp(x);
				printf("эталонное значение %fl\n", b);
				c = taylor(n, acc, exp1, x, exp(x));
				printf("оценка значения функции %fl\n", c);
				printf("разница между оценкой и эталонным значением %fl\n", (fabs(b - c)));
				printf("количество слагаемых, которое было вычислено %d\n", count);
				break;
			}
			case 4:
			{
				b = exp(x);
				printf("эталонное значение %fl\n", b);
				c = taylor(n, acc, exp1, x, exp(x));
				printf("оценка значения функции %fl\n", c);
				printf("разница между оценкой и эталонным значением %fl\n", (fabs(b - c)));
				printf("количество слагаемых, которое было вычислено %d\n", count);
				break;
			}
			break;
			}
			break;
		}
		case 2:
		{
			printf("Выберите функцию:\n");
			printf("1. Sin(x)\n");
			printf("2. Cos(x)\n");
			printf("3. Exp(x)\n");
			printf("4. Sh(x)\n");
			scanf_s("%d", &func);
			printf("Введите точку в которой нужно посчитать значение: ");
			scanf_s(" %lf", &x);
			printf("Введите количество эксперементов от 1 до 25: ");
			scanf_s(" %d", &ex);
			acc = 0;
			for (int n = 1; n <= ex; n++)
			{
				switch (func)
				{
				case 1:
				{
					b = sin(x);
					if (n == 1)
					{
						printf("эталонное значение %fl\n", b);
						printf("количествово слагаемых - вычисленная оценка значения функции - разница между оценкой и эталонным значением");
					}
					c = taylor(n, acc, sin1, x, sin(x));
					printf("%d %fl %fl\n", &n, &c, (fabs(b - c)));
					break;
				}
				case 2:
				{
					b = cos(x);
					if (n == 1)
					{
						printf("эталонное значение %fl\n", b);
						printf("количествово слагаемых - вычисленная оценка значения функции - разница между оценкой и эталонным значением");
					}
					c = taylor(n, acc, cos1, x, cos(x));
					printf("%d %fl %fl\n", n, c, (fabs(b - c)));
					break;
				}
				case 3:
				{
					b = exp(x);
					if (n == 1)
					{
						printf("эталонное значение %fl\n", b);
						printf("количествово слагаемых - вычисленная оценка значения функции - разница между оценкой и эталонным значением");
					}
					c = taylor(n, acc, exp1, x, exp(x));
					printf("%d %fl %fl\n", n, c, (fabs(b - c)));
					break;
				}
				case 4:
				{
					b = sinh(x);
					if (n == 1)
					{
						printf("эталонное значение %fl\n", b);
						printf("количествово слагаемых - вычисленная оценка значения функции - разница между оценкой и эталонным значением");
					}
					c = taylor(n, acc, sh1, x, sinh(x));
					printf("%d %fl %fl\n", n, c, (fabs(b - c)));
					break;
				}
				break;
				}
				break;
			}
		}
		case 0:
		{
			v = 1;
			break;
		}
		break;
		}
	}while (v == 0);
}