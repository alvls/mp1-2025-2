#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int mode;
    printf("Выберите режим работы:\n");
    printf("1 - Компьютер загадывает число\n");
    printf("2 - Пользователь загадывает число\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &mode);

    if (mode == 1) {
        int secret = rand() % 1000 + 1;
        int guess, attempts = 0;

        printf("\nКомпьютер загадал число от 1 до 1000.\n");
        printf("Попробуйте угадать!\n\n");

        do {
            printf("Введите вашу догадку: ");
            scanf_s("%d", &guess);
            attempts++;

            if (guess < secret) {
                printf("Загаданное число больше\n");
            }
            else if (guess > secret) {
                printf("Загаданное число меньше\n");
            }
            else {
                printf("Поздравляем! Вы угадали число %d\n", secret);
                printf("Количество попыток: %d\n", attempts);
            }
        } while (guess != secret);

    }
    else if (mode == 2) {
        int min = 1, max = 1000;
        int guess, attempts = 0;
        char response;

        printf("\nЗагадайте число от 1 до 1000.\n");
        printf("Компьютер будет угаывать число.\n");
        printf("Вводите:\n");
        printf("> - если ваше число больше\n");
        printf("< - если ваше число меньше\n");
        printf("= - если компьютер угадал\n\n");

        do {
            guess = (min + max) / 2;
            attempts++;

            printf("Компьютер предполагает: %d\n", guess);
            printf("Ваш ответ: ");
            scanf_s(" %c", &response);

            if (response == '>') {
                min = guess + 1;
            }
            else if (response == '<') {
                max = guess - 1;
            }
            else if (response == '=') {
                printf("Компьютер угадал число %d!\n", guess);
                printf("Количество попыток: %d\n", attempts);
            }
            else {
                printf("Некорректный ввод. Используйте >, < или =\n");
                attempts--;
            }

            if (min > max) {
                printf("Ошибка - так быть не может\n");
                break;
            }

        } while (response != '=');

    }
    else {
        printf("Ошибка: выбран неверный режим\n");
        return 1;
    }

    return 0;
}