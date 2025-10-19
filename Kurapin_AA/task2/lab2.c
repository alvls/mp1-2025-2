#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	while (1) {
		int mode;
		printf("Режим 1 или 2?\n");
		scanf_s("%i", &mode);

		if (mode == 1) {
			int secret = rand() % 1000;
			int user_attempt;

			while (1) {
				scanf_s("%i", &user_attempt);

				if (user_attempt == secret) {
					printf("=\n");
					break;
				}
				else if (user_attempt < secret)
					printf(">\n");
				else if (user_attempt > secret)
					printf("<\n");
			}


		}
		else if (mode == 2) {
			int current_min = 0, current_max = 999;
			int attempt;
			char user_hint;

			while (1) {
				attempt = rand() % (current_max - current_min + 1) + current_min;

				printf("%i?\n", attempt);
				scanf_s(" %c", &user_hint, 1);

				if (user_hint == '=') {
					printf("УРА!!!\n");
					break;
				}
				else if (user_hint == '<')
					current_max = attempt - 1;
				else if (user_hint == '>')
					current_min = attempt + 1;
			}
		}
	}

	return 0;
}