#include <locale.h>
#include <stdio.h>
#include <time.h>

void main() {
    int n, number[5] = { 0 }, proverka1 = 0, ot = 0;
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    printf("»гра 'Ѕыки и коровы'\n");
    printf("я загадываю число, а вы его отгадываете по моим подсказкам\n");
    printf("я буду говорить количество быков (сколько цифр угадано вплоть до позиции) и коров (сколько цифр угадано без совпадени€ с их позици€ми)\n");
    printf("¬ведите длину числа (от 2 до 5)\n");
    scanf_s("%d", &n);

    number[0] = rand() % 9 + 1;

    while (proverka1 < 20) {
        for (int i = 1; i < 5; i++) {
            number[i] = rand() % 10;
        }
        for (int i = 1; i < 5; i++) {
            for (int ii = 0; ii < i; ii++) {
                if (number[i] != number[ii]) {
                    proverka1 += 1;
                }
                else {
                    proverka1 = 0;
                    continue;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ot = ot * 10 + number[i];
    }
    //printf("%d\n", ot);

    int proverka2 = 0, var, number2[5] = { 0 }, byki = 0, korovy = 0;

    while (proverka2 == 0) {
        printf("¬ведите ваш вариант ответа\n");
        scanf_s("%d", &var);

        for (int i = n - 1; i != -1; i--) {
            number2[i] = var % 10;
            var = var / 10;
        }

        for (int i = 0; i < n; i++) {
            if (number[i] == number2[i]) {
                byki += 1;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int ii = 0; ii < n; ii++) {
                if (number[i] == number2[ii]) {
                    korovy += 1;
                }
            }
        }

        korovy = korovy - byki;

        if (byki == n) {
            printf("ѕоздравл€ю, вы угадали число\n");
            proverka2 = 1;
            break;
        }

        printf("%i быков %i коров\n", byki, korovy);

        korovy = 0;
        byki = 0;
    }

    system("pause");
}