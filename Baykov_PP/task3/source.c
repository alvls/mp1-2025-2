#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    int n;
    printf("Введите количество цифр (от 2 до 5): ");
    scanf_s("%d", &n);
    if (n < 2 || n > 5) {
        printf("Число должно быть от 2 до 5!\n");
        return 1;
    }
    int secret[5], used[10] = { 0 };
    for (int i = 0; i < n; i++) {
        int digit;
        do {
            digit = rand() % 10;
            if (i == 0 && digit == 0 && n > 1) continue;
        } while (used[digit]);
        used[digit] = 1;
        secret[i] = digit;
    }
    printf("\n");
    int attempts = 0;
    while (1) {
        char guess_str[6];
        printf("Введите ваш вариант (%d цифр): ", n);
        scanf_s("%5s", guess_str, (unsigned)_countof(guess_str));
        if (strlen(guess_str) != n) {
            printf("Нужно ввести ровно %d цифр!\n", n);
            continue;
        }
        int guess[5], check[10] = { 0 };
        int valid = 1;
        for (int i = 0; i < n; i++) {
            if (guess_str[i] < '0' || guess_str[i] > '9') {
                valid = 0;
                break;
            }
            int digit = guess_str[i] - '0';

            if (check[digit]) {
                valid = 0;
                break;
            }
            check[digit] = 1;
            guess[i] = digit;
        }
        if (!valid) {
            printf("Некорректный ввод. Все цифры должны быть разными.\n");
            continue;
        }
        int bulls = 0, cows = 0;
        for (int i = 0; i < n; i++) {
            if (guess[i] == secret[i]) {
                bulls++;
            }
            else {
                for (int j = 0; j < n; j++) {
                    if (guess[i] == secret[j]) {
                        cows++;
                        break;
                    }
                }
            }
        }
        attempts++;
        printf("Быков: %d, Коров: %d\n", bulls, cows);
        if (bulls == n) {
            printf("Поздравляем! Вы угадали число за %d попыток.\n", attempts);
            break;
        }
    }
    system("pause");
    return 0;
}