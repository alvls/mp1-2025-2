#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	while (1) {
		int length;
		printf("Введите длину числа\n");
		scanf_s("%i", &length);

		int secret[5];
		bool used[10] = { false };

		int first_digit = 1 + rand() % 9;
		secret[0] = first_digit;
		used[first_digit] = true;

		for (int i = 1; i < length; i++) {
			int digit;

			do { digit = rand() % 10; } 
			while (used[digit]);

			secret[i] = digit;
			used[digit] = true;
		}

		printf("Сгенерировано\n");
		int user_attempt;

		while (1) {
			scanf_s("%i", &user_attempt);

			int halves = 0, fulls = 0;

			for (int i = 0; i < length; i++) {
				int digit = user_attempt % 10;
				user_attempt = (user_attempt - digit) / 10;

				for (int k = 0; k < length; k++) {
					if (secret[k] == digit && i == k)
						fulls++;
					else if (secret[k] == digit)
						halves++;
				}
			}

			if (fulls == length) {
				printf("Совершенно верно! Угадано!\n");
				break;
			}

			printf("Коров: %i, Быков: %i\n", halves, fulls);
		}
	}

	return 0;
}