#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int gamemode, rnum, guess, number;
	char continue_playing = 'y';

	while (continue_playing == 'y' || continue_playing == 'Y') {
		int answer = 0, attempts = 1, min = 1, max = 1000;
		printf("Выберите режим игры:\n");
		printf("1 - Вы угадываете число\n");
		printf("2 - Компьютер угадывает число\n");
		printf("Ваш выбор: ");
		scanf_s("%d", &gamemode);
		if (gamemode == 1) {
			printf("Режим 1\n");
			rnum = rand() % 999 + 1;
			while (answer == 0) {
				printf("Попробуйте угадать число, которое я загадал\n");
				scanf_s("%d", &guess);
				if (guess == rnum) {
					printf("Вы угадали!\nКоличество попыток: %i\n", attempts);
					answer = 1;
				}
				else if (guess < rnum) {
					printf("Загаданное число больше\n");
					attempts += 1;
				}
				else if (guess > rnum) {
					printf("Загаданное число меньше\n");
					attempts += 1;
				}
			}
		}
		else if (gamemode == 2) {
			printf("Режим 2\n");
			printf("Загадайте число в диапазоне от 1 до 1000 и введите его\n");
			printf("Программа попытается отгадать это число, давайте подсказки программе.Если загаданное число больше, введите '>',\nесли загаданное число меньше, введите '<', если программа отгадала ваше число, введите '='\n");
			scanf_s("%d", &number);

			while (number > 1000 || number < 1) {
				printf("Вы ввели число не подходящее диапозону\n");
				scanf_s("%d", &number);
			}

			char comparison = '.';
			attempts = 1;
			answer = 0;

			while (answer == 0) {
				guess = (min + max) / 2;
				printf("Программа предполагает, что ваше число: %d\n", guess);
				printf("Введите '>', '<' или '='\n");
				scanf_s(" %c", &comparison, 1);

				if (comparison == '=') {
					printf("Число угадано\n");
					printf("Число попыток: %d\n", attempts);
					answer = 1;
				}
				else if (comparison == '>') {
					min = guess;
					attempts += 1;
				}
				else if (comparison == '<') {
					max = guess;
					attempts += 1;
				}
				else {
					printf("Неверный ввод, используйте только '>', '<' или '='\n");
				}
			}

		}
		else {
			printf("Неверный выбор!\n");
		}
		printf("\nХотите сыграть еще раз? (y/n): ");
		scanf_s(" %c", &continue_playing, 1);
	}
	
	system("pause");
}