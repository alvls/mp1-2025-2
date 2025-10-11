#include<stdio.h>
#include<math.h>
#include<locale.h>

int main(void)
{
	double h, w, d, g1; /* высота, ширина, глубина, Плотностью ДВП и ДСП будем счиать 800, g1 - переменная для выхода */
	double back_wall, bocov, krishka, doors, polka, polka_count, massa; /* Задняя стенка, боковая стенка, крышка, дверь, полка, количество полок, масса шкафа*/

	setlocale(LC_ALL, "russia.UTF-8");

	printf("Vvedite visoty shkafa ot 180 do 220 sm\n");
	scanf_s("%lf", &h);

	printf("Vvedite shirinu shkafa ot 80 do 120 sm\n");
	scanf_s("%lf", &w);

	printf("Vvedite glubinu shkafa ot 50 do 90 sm\n");
	scanf_s("%lf", &d);

	back_wall = (h * 0.01) * (w * 0.01) * 0.005 * 800;
	bocov = 2 * ((h * 0.01) * (d * 0.01) * 0.015 * 800);
	krishka = 2 * ((w * 0.01) * (d * 0.01) * 0.015 * 800);
	doors = (h * 0.01) * (w * 0.01) * 0.01 * 800;
	
	if (h < 200) {
		polka_count = 4;
	}

	if (h > 199) {
		polka_count = 5;
	}

	polka = polka_count * ((0.015 * ((w * 0.01) - 0.03) * ((d * 0.01) - 0.015)) * 800);
	
	massa = polka + back_wall + bocov + krishka + doors;

	printf("massa shkafa v kilogrammah =");
	printf("%lf", massa);

	printf("\nprogramm end\n");
	scanf_s("%lf", &g1);

}