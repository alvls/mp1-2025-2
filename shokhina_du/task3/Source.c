#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

// генерация числа
void rand_number(int arr[], int min, int max, int n) {
	srand(time(NULL));
	int flag;
	do {
		flag = 0;
		for (int i = 0; i < n; i++)
			arr[i] = rand() % (max - min + 1) + min;

		if (arr[0] == 0)
			arr[0] = 1;

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (arr[i] == arr[j]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1)
				break;
		}
	} while (flag == 1);
}

int main() {
	setlocale(LC_ALL, "rus");
	int n;
	printf("Это игра <Быки и коровы>, где Вы будете отгадывать число по следующим правилам:\n");
	printf("  1. Быки - угаданы цифры на правильных позициях.\n  2. Коровы - угаданы цифры, но они не на своих позициях.\n");
	int flag0 = 1;
	do {
		printf("Теперь выберите количество цифр для числа (от 2 до 5): ");
		scanf_s("%d", &n);
		int* d = (int*)malloc(n * sizeof(int));
		rand_number(d, 0, 9, n);
		/* for (int i = 0; i < n; i++)
			printf("%d", d[i]); */

		printf("Программа загадала число, теперь Ваша очередь его отгадывать.\n");
		while (1) {
			int try;
			int* d1 = (int*)malloc(n * sizeof(int));
			printf("Введите число: ");
			scanf_s("%d", &try);
			for (int i = 0; i < n; i++) {
				d1[n - 1 - i] = try % 10;
				try /= 10;
			}

			// равны ли числа
			int flag1 = 1;
			for (int i = 0; i < n; i++) {
				if (d[i] != d1[i])
					flag1 = 0;
			}
			if (flag1) {
				printf("Ураа, Вы отгадали число!");
				break;
			}

			// считаем быков и коров
			else {
				int bull = 0, cow = 0;
				for (int i = 0; i < n; i++) {
					if (d[i] == d1[i])
						bull++;
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (i != j && d[i] == d1[j])
							cow++;
					}
				}
				printf("В Вашем числе быков - %d, коров - %d.\n", bull, cow);
			}
		}

		// продолжение игры
		printf("\n\nХотите продолжить игру?\n  1. Да.\n  2. Нет.\nВаш выбор: ");
		scanf_s("%d", &flag0);
		printf("\n");

	} while (flag0 == 1);

	return 0;
}
