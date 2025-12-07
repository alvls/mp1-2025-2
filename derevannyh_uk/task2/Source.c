#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int mode, secret, guess, attempts, min = 1, max = 1000;
    char response;

    srand(time(NULL));

    printf("=== УГАДАЙ ЧИСЛО (1-1000) ===\n");
    printf("1 - Вы угадываете\n");
    printf("2 - Компьютер угадывает\n");
    printf("Выберите режим: ");
    scanf_s("%i", &mode);

    if (mode == 1) {
        secret = rand() % 1000 + 1;
        attempts = 0;

        printf("\nЯ загадал число от 1 до 1000. Угадайте!\n");

        do {
            printf("Ваша попытка: ");
            scanf_s("%i", &guess);
            attempts++;

            if (guess < secret) printf("Больше!\n");
            else if (guess > secret) printf("Меньше!\n");
            else printf("Угадали! Попыток: %i\n", attempts);
        } while (guess != secret);

    }
    else if (mode == 2) {
        printf("\nЗагадайте число от 1 до 1000.\n");
        printf("Отвечайте: > (больше), < (меньше), = (угадал)\n\n");

        attempts = 0;
        min = 1; max = 1000;

        do {
            guess = (min + max) / 2;
            attempts++;
            printf("Попытка %i: %i? ", attempts, guess);
            scanf_s(" %c", &response);

            if (response == '>') min = guess + 1;
            else if (response == '<') max = guess - 1;
            else if (response == '=') printf("Ура! Угадал за %i попыток!\n", attempts);
            else printf("Введите >, < или =\n");
        } while (response != '=');
    }

    return 0;
}