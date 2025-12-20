#include <stdio.h>
#include <math.h>
#include <corecrt_math_defines.h>
#include <FuncElement.h>
#include <locale.h>

int count;

double taylor(int N,double acc,double (*OneEl)(double y_past,double y,int n),double x,double res_math)
{
	double res = 0,el=0,fall=100;
	int Nsum = 0;
	while (Nsum != N && fall > acc)
	{
		el= OneEl(el, x, Nsum);
		res += el;
		Nsum++;
		fall = fabs(res_math - res);
	}
	count = Nsum;
	return res;

}
void main()
{
	char* locale = setlocale(LC_ALL, "");
	double x,acc,pred,val;

	double (*FuncAll[19])(double, double, int) = { Exp,Sin,Cos,NULL,Cosh,Arcsin,NULL,NULL,LnX,Ln1X,NULL,sqrtX,Arctg,NULL,NULL,NULL,Sinh,Arcsinh,NULL};
	double(*FuncAllMath[19])(double) = {exp,sin,cos,tan,cosh,asin,csc,coth,log,ln1x,sec,sqrt1,atan,cot,acot,tanh,sinh,asinh,acos};
	int choise,func,N,Nex;
	printf("РАСЧЁТ ЗНАЧЕНИЙ ФУНКЦИЙ С ПОМОЩЬЮ ФОРМУЛЫ МАКЛОРЕНА\n");
	do
	{
		printf("Выберите режим:\n1.Однократный подсчёт\n2.Серийный эксперимент\n0.Закончить вычисления\n");
		scanf_s(" %i", &choise);
		printf("Выбирите функцию:"
			"\n1.Экспонента-exp(x)"
			"\n2.Синус-sin(x)"
			"\n3.Косинус-cos(x)"
			"\n4.Тангенс - tg(x),|X|<пи/2"
			"\n5.Гиперболический косинус - ch(x)"
			"\n6.Арксинус - arcsin(x),|X|<=1"
			"\n7.Косеканс - csc(x),0<|X|<пи"
			"\n8.Гиперболический котангенс - cth(x),0<|X|<пи"
			"\n9.Логарифм - ln(x),0<x<=2"
			"\n10.Логарифм от 1 + х - ln(1 + x),-1<x<=1"
			"\n11.Секанс - sec(x),|X|<пи/2"
			"\n12.Квадратный корень из 1 + х - (1 + x) ^ 1 / 2,|X|<=1"
			"\n13.Арктангенс - arctg(x),|X|<=1"
			"\n14.Котангенс - ctg(x),0<|X|<пи"
			"\n15.Арккотангенс - arcctg(x),|X|<=1"
			"\n16.Гиперболический тангенс - th(x),|X|<пи/2"
			"\n17.Гиперболический синус - sh(x)"
			"\n18.Обратный гиперболический синус - arsh(x),|X|<=1"
			"\n19.Арккосинус - arccos(x),|X|<=1\n");
		scanf_s(" %d", &func);
		switch (choise)
		{
			case 1:
			{
				
				printf("Введите точку в которой нужно посчитать значение\nПРЕДУПРЕЖДЕНИЕ: при введении точки не из диапозона функции или крайних точек,точность не гарантируется!\n");
				scanf_s(" %lf", &x);
				printf("Введите точность вычислений >0,000001: ");
				scanf_s(" %lf", &acc);
				printf("Введите количество элементов ряда для выполнения расчетов от 1 до 1000: ");
				scanf_s(" %d", &N);
				if ((func > 19) || (func < 1) || (acc < 0.000001) || (N < 1) || (N > 1000))
				{
					printf("Введены некорректные данные\n");
					continue;
				}
				val = FuncAllMath[func-1](x);
				switch (func)
				{
					case 4:
					{
						pred = ((taylor(N, acc, Sin, x, sin(x)) / (taylor(N, acc, Cos, x, cos(x)))));
						break;
					}
					case 7:
					{
						pred = (1 / taylor(N, acc, Sin, x, sin(x)));
						break;
					}
					case 8:
					{
						pred = ((taylor(N, acc, Cosh, x, cosh(x)) / (taylor(N, acc, Sinh, x, sinh(x)))));
						break;
					}
					case 11:
					{
						pred = (1 / taylor(N, acc, Cos, x, cos(x)));
						break;
					}
					case 14:
					{
						pred = ((taylor(N, acc, Cos, x, cos(x)) / (taylor(N, acc, Sin, x, sin(x)))));
						break;
					}
					case 15:
					{
						pred = M_PI_2-(taylor(N, acc, Arctg, x, acot(x)));
						break;
					}
					case 16:
					{
						pred = (taylor(N, acc, Sinh, x, sinh(x))) / (taylor(N, acc, Cosh, x, cosh(x)));
						break;
					}
					case 19:
					{
						pred = M_PI_2 - (taylor(N, acc, Arcsin, x, acos(x)));
						break;
					}
					default:
					{
						pred = taylor(N, acc, FuncAll[func-1], x, FuncAllMath[func-1](x));
						break;
					}
				}
				printf("Значение функции в точке %lf:%lf\nРассчетное значение по формуле Маклорена:%lf\nОшибка:%lf\nКоличество посчитанных слогаемых:%d\n",x,val,pred,fabs(val-pred),count);
				break;

			}
			case 2:
			{
				printf("Введите точку в которой нужно посчитать значение: ");
				scanf_s(" %lf", &x);
				printf("Введите количество эксперементов от 1 до 25: ");
				scanf_s(" %d", &Nex);
				if (func > 19 || func < 1 ||  Nex < 1 || Nex>25)
				{
					printf("Введены некорректные данные\n");
					continue;
				}
				val = FuncAllMath[func - 1](x);
				acc = 0;
				printf("Значение функции в точке %lf:%lf\n", x, val);
				printf("КОЛИЧЕСТВО СЛОГАЕМЫХ\tОЦЕНКА%5cОШИБКА\n",' ');
				for (int n = 1; n <= Nex; n++)
				{
					switch (func)
					{
						case 4:
						{
							pred = ((taylor(n, acc, Sin, x, sin(x)) / (taylor(n, acc, Cos, x, cos(x)))));
							break;
						}
						case 7:
						{
							pred = (1 / taylor(n, acc, Sin, x, sin(x)));
							break;
						}
						case 8:
						{
							pred = ((taylor(n, acc, Cosh, x, cosh(x)) / (taylor(n, acc, Sinh, x, sinh(x)))));
							break;
						}
						case 11:
						{
							pred = (1 / taylor(n, acc, Cos, x, cos(x)));
							break;
						}
						case 14:
						{
							pred = ((taylor(n, acc, Cos, x, cos(x)) / (taylor(n, acc, Sin, x, sin(x)))));
							break;
						}
						case 15:
						{
							pred = M_PI_2 - (taylor(n, acc, Arctg, x, acot(x)));
							break;
						}
						case 16:
						{
							pred = (taylor(n, acc, Sinh, x, sinh(x))) / (taylor(n, acc, Cosh, x, cosh(x)));
							break;
						}
						case 19:
						{
							pred = M_PI_2 - (taylor(n, acc, Arcsin, x, acos(x)));
							break;
						}
						default:
						{
							pred = taylor(n, acc, FuncAll[func - 1], x, FuncAllMath[func - 1](x));
							break;
						}
					}
					printf("%d%20c\t%lf%3c%lf\n", n,' ', pred,' ', fabs(pred - val));
				}
			}
		}
	} while (choise);
}