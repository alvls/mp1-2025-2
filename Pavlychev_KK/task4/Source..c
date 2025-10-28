#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL, "Russian");
    char producty[3][7] = {"Хлеб", "Молоко", "Масло"};
    int shtrih[3][4] = { {1,2,3,4},{4,3,2,1},{5,6,7,8} };
    float scidka[3] = { 15, 10, 5 };
    float cena[3] = { 70, 95, 150 };
    int kod[4];
    int count[] = {0,0,0};
    int cnt = 0;
    int c=0;
    float sum = 0;
    float sum_scidka = 0.0;
    float procent = 0.0;
    printf("Штрих-код: 1111 зарезервирован под завершение сканирования.\n");
    while (1) {
        c = 0;
        for (int i = 0; i < 4; i++) {
            kod[i] = 0;   //Обнуление - kod = {0,0,0,0}
        }
        printf("Введите штрих-код(Цифры через пробел):");
        for (int i = 0; i < 4; i++) {
            scanf_s("%i", &kod[i]);
            if (kod[i] == 1) {
                c++;
            }
        }
        if (c == 4) {
            printf("Сканирование законченно.\n\n");
            break;
        }
        printf("\n");
        for (int i = 0; i < 3; i++) {
            cnt = 0;
            for (int j = 0; j < 4; j++) {
                if (kod[j] == shtrih[i][j]) {
                    cnt++;
                }
                else {
                    break;
                }
            }
            if (cnt == 4) {
                printf("Описание товара:\n");
                printf("Штрих-код = ");
                for (int i = 0; i < 4; i++) {
                    printf("%i", kod[i]);
                }
                printf("\nНаименование = %s\n", producty[i]);
                printf("Cтоимостью за единицу товара = %.0f рублей\n", cena[i]);
                printf("Скидка на товар = %.0f процентов\n\n", scidka[i]);
                count[i]++;
            }
        }
    }
    printf("Чек:\n");
    for (int i = 0; i < 3; i++) {
        if (count[i] != 0) {
            printf("%s-%.0f-%i-%.0f\n", producty[i], cena[i], count[i], cena[i] * count[i]);
            sum += cena[i] * count[i];
            procent = scidka[i] / 100;
            sum_scidka += ((cena[i] * count[i]) * procent);
        }
    }
    printf("Общая цена без скидки = %.0f рублей\n", sum);
    printf("Cуммарная скидка = %.0f рублей\n", sum_scidka);
    printf("Итоговая сумма к оплате = %.0f рублей.", sum - sum_scidka);
    system("pause");
    return 0;
}