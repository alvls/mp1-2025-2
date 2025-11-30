#include "stdio.h"
#include "locale.h"
#include "string.h"


int barcode[2][4] = { {1,2,3,4}, {5,6,7,8} }; // 1234 молоко 5678 хлеб
char name[2][10] = { "молоко", "хлеб" };
int price[2] = { 90, 40 };
int discount[2] = { 10, 25 };
int quantity[2] = { 0, 0 };
int quan[2] = { 0, 0 };

int barus[4];
int a;

void com1();
void com();
void com2();
void com3();

int main() {
    setlocale(LC_ALL, "Ru");
    do {
        com();
        switch (a) {
        case 1:
            com1();
            break;
        case 2:
            com2();
            break;
        }
    } while (a != 3);
    com3();
    return 0;
}

void com() {
    printf("\n1. Ввести штрихкод\n");
    printf("2. Вывести описание товара по штрихкоду\n");
    printf("3. Завершить сканирование/вывести чек\n");
    printf("Выберите действие: ");
    scanf_s("%d", &a);
}

void com1() {
    printf("Введите штрихкод (4 цифры через пробел): ");
    scanf_s("%d %d %d %d", &barus[0], &barus[1], &barus[2], &barus[3]);

    int found = 0;
    for (int i = 0; i < 2; i++) {
        int match = 1;
        for (int j = 0; j < 4; j++) {
            if (barcode[i][j] != barus[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            printf("Товар: %s добавлен в чек.\n", name[i]);
            quantity[i]++;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Ошибка: Штрихкод не найден в базе\n");
    }
}

void com2() {
    printf("Введите штрихкод (4 цифры через пробел): ");
    scanf_s("%d %d %d %d", &barus[0], &barus[1], &barus[2], &barus[3]);

    int found = 0;
    for (int i = 0; i < 2; i++) {
        int match = 1;
        for (int j = 0; j < 4; j++) {
            if (barcode[i][j] != barus[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            printf("Наименование: %s\n", name[i]);
            printf("Цена: %d\n", price[i]);
            printf("Скидка: %d%%\n", discount[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Ошибка: Штрихкод не найден в базе\n");
    }
}

void com3() {
    int res = 0;
    printf("\n=== ЧЕК ===\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Наименование", "Цена", "Кол-во", "Скидка", "Сумма");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < 2; i++) {
        if (quantity[i] != 0) {
            int tdiscount = price[i] * quantity[i];
            int discountt = (tdiscount * discount[i]) / 100;
            tdiscount = tdiscount - discountt;
            quan[i] = tdiscount;

            printf("%-20s %-10d %-10d %-9d%% %-10d\n",
                name[i], price[i], quantity[i], discount[i], tdiscount);
            res += tdiscount;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("Итоговая сумма: %d руб.\n", res);
}