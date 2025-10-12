#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
	setlocale(LC_ALL, "rus");
	int flag_0 = 1;
	do {
		int flag_1;
		printf("Выберите режим работы программы:\n  1. Вы отгадываете число программы.\n  2. Вы загадываете программе число.\nВаш выбор: ");
		scanf_s("%d", &flag_1);

		// режим 1
		if (flag_1 == 1) {
			srand(time(NULL));
			int random, count = 0;
			do {
				random = rand() % 1000;
			} while (random == 0);
			printf("\nРЕЖИМ 1.\nПрограмма загадала число, начинается игра! Введите любое число: ");
			int answer;
			while (1) {
				scanf_s("%d", &answer);
				if (answer == random) {
					count++;
					printf("Ураа, Вы отгадали число - %d! Число попыток: %d.\n", random, count);
					break;
				}
				else {
					if (answer > random)
						printf("Число программы меньше Вашего. Новое число: ");
					else
						printf("Число программы больше Вашего. Новое число: ");
					count++;
				}

			}
		}

		// режим 2
		else {
			int number;
			printf("\nРЕЖИМ 2.\nЗагадайте число от 1 до 1000 - и мы начнём! Загадали? Введите его (мы не расскажем программе): ");
			scanf_s("%d", &number);
			int left = 1, right = 999, flag_3, count = 0, answer = 0;
			while (1) {
				printf("Ваше число - %d? (Напишите в качестве ответа: 1) < / 2) > / 3) = ): ", (left + (right - left) / 2));
				scanf_s("%d", &flag_3);
				switch (flag_3) {
					case 1: {
						right = left + (right - left) / 2;
						break;
					}
					case 2: {
						left = left + (right - left) / 2;
						break;
					}
					case 3: {
						count++;
						printf("Ураа, программа отгадала число - %d! Количество попыток: %d.", number, count);
						answer = (left + (right - left) / 2);
						break;
					}
				}
				if (number == answer) break;
				count++;
			}
		}

		// продолжение игры
		printf("\nХотите продолжить игру?\n  1. Да.\n  2. Нет.\nВаш выбор: ");
		scanf_s("%d", &flag_0);
		printf("\n");

	} while (flag_0 == 1);

	return 0;
}