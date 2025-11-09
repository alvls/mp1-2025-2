#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    int n;
    printf("Введите длину числа (от 2 до 5): ");
    scanf("%d", &n);
    int secret[5], used[10] = {0};
    for (int i = 0; i < n; i++) {
        int d;
        do {
            d = rand() % 10;
            if (i == 0 && d == 0 && n > 1) continue;
        } while (used[d]);
        used[d] = 1;
        secret[i] = d;
    }
    int attempts = 0;
    while (1) {
        char guess_str[5];
        printf("Введите число из %d цифр (цифры не должны повторяться): ", n);
        scanf("%s", guess_str);
        int guess[5], check_used[10] = {0};
        int valid = 1;
        for (int i = 0; i < n; i++) {
            if (guess_str[i] < '0' || guess_str[i] > '9') {
                valid = 0; break;
            }
            int d = guess_str[i] - '0';
            if (check_used[d]) {
                valid = 0; break;
            }
            check_used[d] = 1;
            guess[i] = d;
        }
        if (!valid) {
            printf("Некорректный ввод. Попробуйте снова.\n");
            continue;
        }
        int bulls = 0, cows = 0;
        for (int i = 0; i < n; i++) {
            if (guess[i] == secret[i]) {
                bulls++;
            } else {
                for (int j = 0; j < n; j++) {
                    if (guess[i] == secret[j]) {
                        cows++;
                        break;
                    }
                }
            }
        }
        attempts++;
        printf("Быки: %d, Коровы: %d\n", bulls, cows);
        if (bulls == n) {
            printf("Поздравляем! Вы угадали за %d попыток.\n", attempts);
            break;
        }
    }
    return 0;
}