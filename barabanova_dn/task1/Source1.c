#include <stdio.h>
#include <math.h>

#define p_dsp 700     // плотность дсп из интернета 
#define p_dvp 800     // плотность двп из интернета
#define p_wood 720    // плотность дерева из интернета

#define t_dsp 0.015
#define t_dvp 0.005
#define t_wood 0.01

int main()
{
	double h, w, d;
	printf("Enter the altitude in meters(h) :");
	if (scanf_s("%lf", &h) != 1 || h < 1.8 || h > 2.2)
	{
		printf("INPUT ERROR");
		getchar();
		getchar();
		return 1;
	}
	printf("Enter the width in meters(w) :");
	if (scanf_s("%lf", &w) != 1 || w < 0.8 || w > 1.2)
	{
		printf("INPUT ERROR");
		getchar();
		getchar();
		return 1;
	}
	printf("Enter the depth in meters(d) :");
	if (scanf_s("%lf", &d) != 1 || d < 0.5 || d > 0.9)
	{
		printf("INPUT ERROR");
		getchar();
		getchar();
		return 1;
	}
	double m_backwall = h * w * t_dvp * p_dvp;
	double m2_sidewall = 2 * h * d * t_dsp * p_dsp;
	double m2_cover = 2 * w * d * t_dsp * p_dsp;
	double m2_door = 2 * h * w * t_wood * p_wood;
	int num_shelf = floor(h/0.4);
	double m_shelfs = num_shelf * w * d * t_dsp * p_dsp;
	double m = m_backwall + m2_sidewall + m2_cover + m2_door + m_shelfs;
	printf("Weight of the cabinet(kg): m = %2lf", m);
	getchar();
	getchar();
	return 0;
}