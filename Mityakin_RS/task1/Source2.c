#include <stdio.h>
#include <math.h>
#include <conio.h>

int main(void) {
    double h, w, d;
    double dsp_density, dvp_density, wood_density;

    printf("Enter height, weight and deep separated by space (cm): ");
    scanf_s("%lf %lf %lf", &h, &w, &d);

    printf("Enter density dsp, dvp and wood density separated by space (kg/m3): ");
    scanf_s("%lf %lf %lf", &dsp_density, &dvp_density, &wood_density);

    // to meters
    h = h / 100.0;
    w = w / 100.0;
    d = d / 100.0;

    double dsp_th = 1.5 / 100.0;
    double dvp_th = 0.5 / 100.0;
    double wood_th = 1.0 / 100.0;

    double back_wall = h * w * dvp_th * dvp_density;
    double sidewalls = 2.0 * h * d * dsp_th * dsp_density;
    double topbottom_cover = 2.0 * w * d * dsp_th * dsp_density;
    double doors = h * w * wood_th * wood_density;

    // shelves count
    int count_shelves = (int)floor(h * 100.0 / 40.0) - 1;

    double shelf_w = w - 2.0 * dsp_th;
    double shelf_d = d - dvp_th;

    double shelves = count_shelves * shelf_w * shelf_d * dsp_th * dsp_density;

    double total = back_wall + sidewalls + topbottom_cover + doors + shelves;

    printf("Total weight: %.2lf kg", total);
    _getch();
}