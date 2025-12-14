#include <stdio.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float h, w, d, t1, t2, massa;
	printf("введите высоту (180-220 см), ширину (80-120) см, глубину (50-90) см\n");
	scanf_s("%f %f %f", &h, &w, &d);
	int n;
	n = h / 40;
	t1 = 15 * 0.1 * 0.01;
	t2 = 1 * 0.01;
	h *= 0.01;
	w *= 0.01;
	d *= 0.01;
	float zwall, side, lid, door, vnshelf;
	zwall = h * w * 5 * 0.1 * 0.01 * 800;
	side = h * d * 15 * 0.1 * 0.01 * 750 * 2;
	lid = w * d * 15 * 0.1 * 0.01 * 750 * 2;
	door = h * w * 0.01 * 600 * 2;
	vnshelf = (w - 30 * 0.1 * 0.01) * (d - 5 * 0.1 * 0.01) * 15 * 0.1 * 0.01 * 750 * n;
	massa = zwall + side + lid + door + vnshelf;
	printf("%f\n", massa);
	system("pause");
}