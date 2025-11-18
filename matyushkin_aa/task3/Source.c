#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));
	int n, r;
	int A[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("Введите скольки значным будет загаданное число: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			int x = 1 + rand() % 9;
			r = x * (int)pow(10, n - i - 1);
			A[x] = -1;
		}
		else {
			int x = rand() % 10;
			if (A[x] != -1) {
				r += x * (int)pow(10, n - i - 1);
				A[x] = -1;
			}
			else {
				for (int j = 0; j < 9; j++) {
					if (A[(x + j + 1) % 10] != -1) {
						r += ((x + j + 1) % 10) * (int)pow(10, n - i - 1);
						A[(x + j + 1) % 10] = -1;
						break;
					}
				}
			}
		}
	}
	int p, b = 0, c = 0;
	printf("Введите число: ");
	scanf_s("%d", &p);
	while (r != p) {
		b = 0;
		c = 0;
		for (int i = 0; i < n; i++) {
			if (r % (int)pow(10, n - i) / (int)pow(10, n - i - 1) == p % (int)pow(10, n - i) / (int)pow(10, n - i - 1)) {
				b++;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					if (r % (int)pow(10, n - i) / (int)pow(10, n - i - 1) == p % (int)pow(10, n - j) / (int)pow(10, n - j - 1)) {
						c++;
					}
				}
			}
		}
		printf("%d коров %d быков\n", c, b);
		printf("Введите число: ");
		scanf_s("%d", &p);
	}
	printf("Вы угадали загаданное число!\n");
	system("pause");
}