#include <stdio.h>
#include <locale.h>
#include <math.h>

void main()
{
    char* locale = setlocale(LC_ALL, "");
    double h, w, d; /* данные шкафа */
    double thickness_back, thickness_side, thickness_top_bottom, thickness_door; /* толщина зада, бока, верха, низа, дверей */
    double count_shelf; /* количество полок */
    double m_back, m_side, m_topbottom, m_door, m_shelf, M; /* массы каждого элемента отдельно и общая масса */
    int proverka; /* переменная для выхода из цикла */

    thickness_back = 0.5;
    thickness_side = thickness_top_bottom = 1.5;
    thickness_door = 1;
    proverka = 1;

    while (proverka == 1) {
        printf("Enter h, w, d\n");
        scanf_s("%lf %lf %lf", &h, &w, &d);
        if (((180 <= h) && (h <= 220)) && ((80 <= w) && (w <= 120)) && ((50 <= d) && (d <= 90))) { proverka = 0; }
    }
    printf("%lf %lf %lf \n\n", h, w, d);

    count_shelf = (int)h / 40;
    m_back = h * w * thickness_back;
    m_side = 2 * (h * d * thickness_side);
    m_topbottom = 2 * (w * d * thickness_top_bottom);
    m_door = 2 * (h * w * thickness_door);
    m_shelf = count_shelf * (d * w * thickness_top_bottom);

    M = (m_back + m_side + m_topbottom + m_door + m_shelf) / 1000;
    printf("The weight of the wardrobe = %lf kg", M);
}