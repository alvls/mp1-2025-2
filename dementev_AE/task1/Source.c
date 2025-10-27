#include <stdio.h>

// ��������� ��� 650 ��/�^3
// ��������� ��� 1000 ��/�^3 
// ��������� ������ 700 ��/�^3 
int main() {
	// �������� ������
	float h, w, d;
	do {
		printf("Enter the height(DVP) in meters: ");
		scanf_s("%f", &h);
		if (h < 1.8 || h > 2.2) {
			printf("Input error\n");
		}
	} while (h < 1.8 || h > 2.2);

	do {
		printf("Enter the width (DVP) in meters: ");
		scanf_s("%f", &w);
		if (w < 0.8 || w > 1.2) {
			printf("Input error\n");
		}
	} while (w < 0.8 || w > 1.2);

	do {
		printf("Enter the depth (DCP) in meters: ");
		scanf_s("%f", &d);
		if (d < 0.5 || d > 0.9) {
			printf("Input error\n");
		}
	} while (d < 0.5 || d > 0.9);

	// ���������� �������
	float m_zs, m_bs, m_d, m_vk, m_p, mas;
	m_zs = h * w * 0.005 * 1000;
	m_bs = d * h * 0.015 * 650 * 2;
	m_d = h * w * 0.01 * 700;
	m_vk = w * d * 0.015 * 650 * 2;
	m_p = d * w * 0.015 * (h / 40);
	mas = m_zs + m_bs + m_d + m_vk + m_p;
	printf("%f", mas);
	return 0;
}