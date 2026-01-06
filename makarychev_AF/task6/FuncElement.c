#include <math.h>
#include <corecrt_math_defines.h>
#include "FuncElement.h"

double Exp(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return y_past * (y / n);
}

double Sin(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return fabs(y_past) * (y * y / (4 * n * n + 2 * n)) * pow(-1, n);
}

double Cos(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return fabs(y_past) * (y * y / (4 * n * n - 2 * n)) * pow(-1, n);
}

double Cosh(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return y_past * (y * y / (4 * n * n - 2 * n));
}
double Arcsin(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return y_past * (y * y * ((double)((2 * n - 1) * (2 * n - 1)) / (double)(2 * n * (2 * n + 1))));
}

double LnX(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y - 1;
	}
	return (pow(y - 1, n + 1) / (n + 1)) * pow(-1, n);
}
double Ln1X(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return (pow(y , n + 1) / (n + 1)) * pow(-1, n);
}
double sqrtX(double y_past, double y, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return y_past * y * ((double)(3 - 2 * n) / (double)(2 * n));
}
double Arctg(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return (pow(y, 2 * n + 1) / (2 * n + 1)) * pow(-1, n);
}

double Sinh(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return y_past * (y * y / (4 * n * n + 2 * n));
}
double Arcsinh(double y_past, double y, int n)
{
	if (n == 0)
	{
		return y;
	}
	return y_past * (y * y * ((double)((2 * n - 1) * (2 * n - 1)) / (double)(2 * n * (2 * n + 1)))) * pow(-1, n);
}
double csc(double x)
{
	return 1 / sin(x);
}
double coth(double x)
{
	return 1 / tanh(x);
}
double ln1x(double x)
{
	return log(1+x);
}
double sec(double x)
{
	return 1 / cos(x);
}
double sqrt1(double x)
{
	return sqrt(1+x);
}
double cot(double x)
{
	return 1/tan(x);
}
double acot(double x)
{
	return M_PI_2-atan(x);
}