#include <stdio.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float h, w, d, t1, t2, ves;
	printf("введите высоту (180-220 см), ширину (80-120) см, глубину (50-90) см\n");
	scanf_s("%f %f %f", &h, &w, &d);
	const Pdsp = 750;
	const Pdvp = 800;
	const Pderev = 600;
	int n;
	n=h/40;
	t1 = 15 * 0.1 * 0.01;
	t2 = 1 * 0.01;
	h *= 0.01;
	w *= 0.01;
	d *= 0.01;
	float zdst, bok, krshk, dveri, vnpol;
	zdst = h * w * 5 * 0.1 * 0.01 * Pdvp;
	bok = h * d * 15 * 0.1 * 0.01 * Pdsp * 2;
	krshk = w * d * 15 * 0.1 * 0.01 * Pdsp * 2;
	dveri = h * w * 1 * 0.01 * Pderev * 2;
	vnpol = (w-30*0.1*0.01) * (d-5*0.1*0.01) *15 * 0.1 * 0.01 * Pdsp * n;
	ves = zdst + bok + krshk + dveri + vnpol;
	printf("%f\n",ves);
	system("pause");

}	