#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
    int flage = 0, max, min, cnt = 0, tr, mid;
    printf("выберите (1 или 2).напишите выбранный номер:\n");
    printf("f в первом режиме вы угадывайте число, во втором вычислите");
    scanf_s("%i", &flage);
    min = 1;
    max = 999;
    if (flage == 1) {
        int random_n = rand() % (max - 1) + 1;
        printf("угадайте число\n");
        while (1 == 1) {
            scanf_s("%i", &tr);
            cnt++;
            if (tr == random_n) {
                printf("верно\n");
                printf("число попыток:");
                printf("%i", cnt);
                return 0;
            }
            else if (tr > random_n) {
                printf("загаданное число меньше\n");
                printf("попробуй еще\n");
            }
            else {
                printf("загаданное число больше\n");
                printf("попробуй еще\n");
            }
        }
    }
    else if (flage == 2) {
        printf("загадайте число от 1 до 1000\n");
        printf("500?\n");
        printf("если ваше число больше то > если меньше то < если равно то =\n");
        mid = 500;
        char rez;
        while (0 == 0) {
            scanf_s("%c", &rez, 1);
            switch (rez) {
            case '<':
                min = mid;
                mid = (min + max) / 2;
                printf("%i", mid);
                printf("?\n");
                cnt++;
                break;
            case '>':
                max = mid;
                mid = (min + max) / 2;
                printf("%i", mid);
                printf("?\n");
                cnt++;
                break;
            case '=':
                printf("число попыток:");
                cnt++;
                printf("%i", cnt);
                break;
            default:
                break;
            }
        }
    }
    else {
        printf("Ошибка ввода");
    }
    return 0;
}