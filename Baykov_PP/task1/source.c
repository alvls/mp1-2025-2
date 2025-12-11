#include<stdio.h>
#include<math.h>
#include<locale.h>

int main(void)
{
	float h, w, d ;
	float back_wall, bocov, krishka, doors, polka, polka_count, massa;

	setlocale(LC_ALL, "rus");
	printf("Введите высоту шкафа от 180 до 220 см\n");
	scanf_s("%f", &h);
	printf("Введите ширину шкафа от 80 до 120 см\n");
	scanf_s("%f", &w);
	printf("Введите глубину шкафа от 50 до 90 см\n");
	scanf_s("%f", &d);

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

	printf("масса шкафа в килограммах =");
	printf("%f\n", massa);
	system("pause");
}