#include <stdio.h>

const double DSP_density = 650;
const double DVP_density = 850;
const double Wood_density = 550;

int main()
{
    float h, w, d, m1, m2, m3, m4, m5, m;

    printf("Print h (1.8 <= h <= 2.2 m): \n");
    scanf_s("%f", &h);
    if ((h < 1.8) || (h > 2.2))
    {
        printf("h < 1.8 or h > 2.2. Try again.");
        return 1;
    }

    printf("Print w (0.8 <= w <= 1.2 m): \n");
    scanf_s("%f", &w);
    if ((w < 0.8) || (w > 1.2))
    {
        printf("w < 0.8 or w > 1.2. Try again.");
        return 1;
    }

    printf("Print d (0.5 <= d <= 0.9 m): \n");
    scanf_s("%f", &d);
    if ((d < 0.5) || (d > 0.9))
    {
        printf("d < 0.5 or d > 0.9. Try again.");
        return 1;
    }

    m1 = h * w * 0.005 * DVP_density;
    m2 = 2 * h * d * 0.015 * DSP_density;
    m3 = 2 * w * d * 0.015 * DSP_density;
    m4 = 2 * h * w * 0.01 * Wood_density;

    if (h < 2.075)
    {
        m5 = 4 * (w - 0.03) * 0.015 * d * DSP_density;
    }
    else
    {
        m5 = 5 * (w - 0.03) * 0.015 * d * DSP_density;
    }

    m = m1 + m2 + m3 + m4 + m5;
    printf("m = %.2f kg\n", m);

    return 0;
}