#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "rus");

    int barcodes[5] = { 1111, 2222, 3333, 4444, 5555 };
    char names[5][15] = {
        "Яйца",
        "Томаты",
        "Картофель",
        "Персики",
        "Мандарины"
    };

    int prices[5] = { 100, 78, 140, 203, 142 };
    int discounts[5] = { 5, 10, 15, 20, 30 };
    char continue_purchasing = 'y';
    int user_barcode;
    int quantities[5] = { 0 };

    printf("Товары в магазине:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d - %s - %d рублей - скидка на товары %d%%\n", barcodes[i], names[i], prices[i], discounts[i]);
    }

    while (continue_purchasing == 'y') {
        printf("Введите штрих-код товара который хотите купить (4 цифры): \n");
        scanf_s("%d", &user_barcode);
        if (user_barcode < 1000 || user_barcode > 9999) {
            printf("Ошибка штрих код имеет четыре цифры\n");
        }
        int found = 0;
        int product_index;
        for (int i = 0; i < 5; i++) {
            if (user_barcode == barcodes[i]) {
                found = 1;
                product_index = i;
                break;
            }
        }
        if (found == 1) {
            quantities[product_index]++;
            printf("Товар %s стоимостью %d рублей со скидкой %d%% добавлен в корзину\n", names[product_index], prices[product_index], discounts[product_index]);
        }
        else {
            printf("Товар с штрих кодом %d не найден\n", user_barcode);
        }
        printf("Вы хотите продолжить покупки? (y/n): \n");
        scanf_s(" %c", &continue_purchasing, 1);
    }
    printf("\n ЧЕК \n");
    int total = 0;
    int total_discount = 0;
    for (int i = 0; i < 5; i++) {
        if (quantities[i] > 0) {
            int price = prices[i];
            int quantity = quantities[i];
            int discount = discounts[i];
            int total_price = price * quantity;
            int discount_amount = total_price * discount / 100;
            int f_price = total_price - discount_amount;

            printf("%s - %d рублей %d + скидка %d%% = %d рублей\n", names[i], price, quantity, discount, f_price);
            total += f_price;
            total_discount += discount_amount;
        }
    }
    printf("Итого к оплате %d руб\n", total);
    printf("Вы сэкономили %d руб\n", total_discount);
    system("pause");
}