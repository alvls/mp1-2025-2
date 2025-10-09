#include <stdio.h>
const double DSP_Density = 600;
const double DVP_Density = 850;
const double Wood_Density = 500;
int main()
{
	double h, w, d;
	stop:printf("Enter height \x1b[32m(180 ≤ h ≤ 220)\x1b[0m, width \x1b[32m(80 ≤ w ≤ 120)\x1b[0m and depth \x1b[32m(50 ≤ d ≤ 90)\x1b[0m: ");
	scanf_s("%lf %lf %lf", &h, &w, &d);
	if ((180 <= h) && (80 <= w) && (50 <= d) && (220 >= h) && (120 >= w) && (90 >= d)) {
		double overhead_back_wall = DVP_Density * h * w * 0.5 * 0.000001;
		double sidewalls = DSP_Density * h * d * 1.5 * 0.000001;
		double overhead_covers = 2 * DSP_Density * w * d * 1.5 * 0.000001;
		double overhead_doors = Wood_Density * h * w * 1 * 0.000001;
		double internal_shelves = Wood_Density * (int)((h - 0.3) / (40+1.5)) * w * d * 1.5 * 0.000001;  //не могу пре
		double summ = overhead_back_wall + sidewalls + overhead_covers + overhead_doors + internal_shelves;
		printf("The wardrobe weighs: %.2lf kg", summ);
	}
	else {
		printf("\x1b[31mIncorrectly entered data, repeat the input\x1b[0m\n");
		goto stop;
	}
}