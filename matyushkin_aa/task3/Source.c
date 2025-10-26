#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));
	int A[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int n, r, a;
	printf("Введите скольки значное будет число: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			r = 1 + rand() % 9;
			a = (int)pow(10, n - 1) * r;
			A[r] = 1;
		}
		else {
			r = rand() % 10;
			if (A[r] == -1) {
				a += (int)pow(10, n - 1 - i) * r;
				A[r] = 1;
			}
			else {
				while (A[r] != -1) {
					r += (r + 1) % 10;
				}
				a += (int)pow(10, n - 1 - i) * r;
				A[r] = 1;
			}
		}
	}
	int B[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int C[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int k, a1, r1, a2 = a, z = 0;
	while (r != a) {
		printf("Отгадывайте число: ");
		scanf_s("%d", &r);
		r1 = r;
		a1 = a;
		k = 0;
		for (int i = 0; i < n; i++) {
			if (a1 % 10 == r1 % 10) {
				B[k] = a1 % 10;
				k++;
			}
			else {
				for (int j = 0; j < n; j++) {
					if (a2 % 10 == r % 10) {
						C[z] = r % 10;
						z++;
					}
					a2 /= 10;
				}
				a2 = a;
			}
			a1 /= 10;
			r1 /= 10;
		}
		if (k != n) {
			if (z > 0) {
				printf("%d цифр ", z);
				for (int i = 0; i < z; i++) {
					printf("<<%d>> ", C[i]);
				}
				printf("- стоят не на своих позициях ");
				z = 0;
			}
			if (k > 0) {
				printf("%d цифр стоят на своих позициях ", k);
				for (int i = 0; i < k; i++) {
					printf("<<%d>> ", B[i]);
				}
				printf("\n");
			}
		}
	}
	printf("Вы угадали\n");
	system("pause");
}