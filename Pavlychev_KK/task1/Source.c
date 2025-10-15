const double dsp_p = 650;
const double dvp_p = 850;
const double wood_p = 550;
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
int main() {
    float h, w, d, m;
    printf("napishite: h w d.\n");
    scanf_s("%f %f %f", &h, &w, &d);
    m = (h * w * 0.005 * dvp_p) + (2 * h * d * 0.015 * dsp_p) + (2 * w * d * 0.015 * dsp_p) + (2 * h * w * 0.01 * wood_p) + (round((h - 0.03) / 40) * (w - 0.03) * d * dsp_p * 0.015);
    printf("m = ");
    printf("%.2f", m);
    printf("kg");
    system("pause");
    return 0;
}