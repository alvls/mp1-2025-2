#include "stdio.h"
#include <math.h>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Russian");
	float x1, x2, y1, y2, r1, r2, rast;
	printf("������� ���������� ������ ����������\n");
	scanf_s("%f %f", &x1, &y1);
	printf("������� ������ ������ ����������\n");
	scanf_s("%f", &r1);
	printf("������� ���������� ������ ����������\n");
	scanf_s("%f %f", &x2, &y2);
	printf("������� ������ ������ ����������\n");
	scanf_s("%f", &r2);
	rast = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if ((rast < r1 + r2) && rast > fabs(r1 - r2)) {
		printf("���������� ������������ � ���� ������\n");
	}
	else if (rast == 0 && r1 == r2) {
		printf("���������� ���������\n");
	}
	else if (rast == r1 + r2 || rast == fabs(r1 - r2)) {
		printf("���������� ������������ � ����� �����\n");
	}
	else if (rast > r1 + r2 || rast < fabs(r1 - r2)) {
		printf("���������� �� ������������\n");
	}
	
	system("pause");
}