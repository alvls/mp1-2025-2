#include <stdio.h>
#include <math.h>
#define DVP  600 
#define DSP  700  
#define WOOD  600 // взял среднюю плотность в кг/м^3

double calculate_mass(double h, double w, double d) 
{
    const double t_dvp = 0.005;     // толщина ДВП в м
    const double t_dsp = 0.015;     // толщина ДСП в м
    const double t_wood = 0.01;     // толщина дерева в м

    double v_dvp = h * w * t_dvp;                 
    double v_bokoviny = 2 * h * d * t_dsp;       
    double v_kryshki = 2 * w * d * t_dsp;         
    double v_doors = h * w * t_wood;              

    int num_polok = floor(h / 0.4);                               // число полок 
    double v_polok = num_polok * w * d * t_dsp;   

    return (
        v_dvp * DVP +
        v_bokoviny * DSP +
        v_kryshki * DSP +
        v_doors * WOOD +
        v_polok * DSP
        );
}

int main() {
    
    double h, w, d;
    scanf_s("%lf%lf%lf", &h, &w, &d); //        179<h<221              79<w<121            49<d<91
   
    h /= 100; 
    w /= 100;
    d /= 100;

    double mass = calculate_mass(h, w, d);

    printf("Massa shkafa: %.2f kg\n", mass);
    getchar();
    getchar();
    return 0;
}