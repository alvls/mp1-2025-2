#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    int n;
    printf("¬ведите длину числа (от 2 до 5): ");
    scanf_s("%d", &n);
    int sicret[5], us[10] = { 0 };
    for (int i = 0; i < n; i++) {
        int q;
        do {
            q = rand() % 10;
            if (i == 0 && q == 0 && n > 1) continue;
        } while (us[q]);
        us[q] = 1;
        sicret[i] = q;
    }
    int attempts = 0;
    while (1) {
        char guess_str[5];
        printf("¬ведите число из %d цифр (цифры не должны повтор€тьс€): ", n);
        scanf_s("%s", guess_str);
        int guess[5], check[10] = { 0 };
        int valid = 1;
        for (int i = 0; i < n; i++) {
            if (guess_str[i] < '0' || guess_str[i] > '9') {
                valid = 0; break;
            }
            int s = guess_str[i] - '0';
            if (check[s]) {
                valid = 0; break;
            }
            check[s] = 1;
            guess[i] = s;
        }
        if (!valid) {
            printf("некорректный ввод попробуйте снова\n");
            continue;
        }
        int Bulls = 0, Cows = 0;
        for (int i = 0; i < n; i++) {
            if (guess[i] == sicret[i]) {
                Bulls++;
            }
            else {
                for (int j = 0; j < n; j++) {
                    if (guess[i] == sicret[j]) {
                        Cows++;
                        break;
                    }
                }
            }
        }
        attempts++;
        printf("быки: %d, коровы: %d\n", Bulls, Cows);
        if (Bulls == n) {
            printf("”спешно разгадано за %d попыток\n", attempts);
            break;
        }
    }
    return 0;
}