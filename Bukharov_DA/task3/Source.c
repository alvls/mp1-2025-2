#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int n;
	printf("Введите длину числа (от 2 до 5): ");
	scanf_s("%d", &n);

	while (n < 2 || n > 5) {
		printf("Длина числа должна быть в диапазоне от 2 до 5\n");
		scanf_s("%d", &n);
	}
	int digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int i = 0;
	while (i < 10) {
		int random_index = rand() % 10;
		int temp = digits[i];
		digits[i] = digits[random_index];
		digits[random_index] = temp;
		i++;
	}
	int start_pos = 0;
	if (n > 1) {
		int j = 0;
		while (j < 10) {
			if (digits[j] != 0) {
				start_pos = j;
				break;
			}
			j++;
		}
	}

	int secret_num = 0;
	int k = 0;
	while (k < n) {
		secret_num = secret_num * 10 + digits[start_pos + k];
		k++;
	}
	int guess, answer = 0, number[5] = {0}, cow = 0, bull = 0, total_matches = 0;
	printf("Я загадал число длиной в %d символа(-ов), попробуйте его отгадать\n", n);
	while (answer == 0) {
		scanf_s("%d", &guess);
		for (int i = n - 1; i != -1; i--) {
			number[i] = guess % 10;
			guess /= 10;
		}
		for (int i = 0; i < n; i++) {
			if (digits[start_pos + i] == number[i]) {
				bull += 1;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (digits[start_pos + i] == number[j]) {
					total_matches++;
					break;
				}
			}
		}
		cow = total_matches - bull;

		printf("Быки: %d, Коровы: %d\n", bull, cow);

		if (bull == n) {
			printf("Вы угадали!\n");
			answer = 1;
		}
		else {
			printf("Попробуйте еще раз: ");
			bull = 0;
			cow = 0;
			total_matches = 0;
		}
	}
	
	system("pause");
}