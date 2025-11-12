#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int mode;
    printf("Выберите режим игры:\n");
    printf("1. Программа загадывает число, вы угадываете.\n");
    printf("2. Вы загадываете число, программа угадывает.\n");
    scanf("%d", &mode);
    if (mode == 1) {
        int secret = rand() % 999 + 1; 
        int guess, attempts = 0;
        printf("Я загадал число от 1 до 999. Попробуйте угадать!\n");
        while (1) {
            printf("Ваш вариант: ");
            scanf("%d", &guess);
            attempts++;
            if (guess < secret) {
                printf("Загаданное число больше.\n");
            } else if (guess > secret) {
                printf("Загаданное число меньше.\n");
            } else {
                printf("Угадали! Загаданное число: %d\n", secret);
                printf("Количество попыток: %d\n", attempts);
                break;
            }
        }
    } else if (mode == 2) {
        int low = 1, high = 1000, attempts = 0;
        char response;
        printf("Загадайте число от 1 до 1000. Я буду угадывать.\n");
        printf("Отвечайте: '>' если мое число меньше, '<' если больше, '=' если угадал.\n");
        while (low <= high) {
            int guess = (low + high) / 2;
            printf("Мое предположение: %d\n", guess);
            printf("Ваш ответ (> < =): ");
            scanf(" %c", &response); 
            attempts++;
            if (response == '=') {
                printf("Угадал! Загаданное число: %d\n", guess);
                printf("Количество попыток: %d\n", attempts);
                break;
            } else if (response == '>') {
                low = guess + 1;
            } else if (response == '<') {
                high = guess - 1;
            } else {
                printf("Неверный ввод. Введите '>', '<' или '='.\n");
                attempts--; 
            }
        }
    } 
    return 0;
}


