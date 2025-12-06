#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_PRODUCTS 10
#define MAX_CHECK_ITEMS 100

typedef struct {
    char barcode[5];
    char name[50];
    int price;
    int discount;
} Product;

typedef struct {
    Product product;
    int quantity;
    int total;
} CheckItem;

typedef struct {
    CheckItem items[MAX_CHECK_ITEMS];
    int count;
    int total_cost;
    int total_discount;
    int final_cost;
} Check;

Product products[MAX_PRODUCTS] = {
    {"1234", "Хлеб", 50, 5},
    {"5678", "Молоко", 80, 10},
    {"9012", "Сыр", 200, 15},
    {"3456", "Колбаса", 300, 20},
    {"7890", "Вода", 40, 0},
    {"1111", "Шоколад", 100, 25},
    {"2222", "Печенье", 60, 10},
    {"3333", "Кофе", 350, 30},
    {"4444", "Чай", 250, 15},
    {"5555", "Сахар", 90, 5}
};

Check check = { 0 };

Product* find_product(const char* barcode) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(products[i].barcode, barcode) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

void scan_product() {
    char barcode[5];
    printf("Введите штрих-код (4 цифры): ");
    scanf_s("%4s", barcode, (unsigned)sizeof(barcode));

    Product* product = find_product(barcode);
    if (product) {
        printf("Найден товар: %s\n", product->name);
        printf("Цена: %d руб.\n", product->price);
        printf("Скидка: %d%%\n", product->discount);

        int found = 0;
        for (int i = 0; i < check.count; i++) {
            if (strcmp(check.items[i].product.barcode, barcode) == 0) {
                check.items[i].quantity++;
                check.items[i].total = check.items[i].quantity *
                    (check.items[i].product.price *
                        (100 - check.items[i].product.discount) / 100);
                found = 1;
                break;
            }
        }

        if (!found) {
            CheckItem new_item = {
                .product = *product,
                .quantity = 1,
                .total = product->price * (100 - product->discount) / 100
            };
            check.items[check.count++] = new_item;
        }

        printf("Товар добавлен в чек!\n");
    }
    else {
        printf("Товар не найден!\n");
    }
}

void print_check() {
    printf("\n========== ЭЛЕКТРОННЫЙ ЧЕК ==========\n");
    printf("Наименование    | Цена | Кол-во | Скидка%% | Итого\n");
    printf("-----------------------------------------------\n");

    check.total_cost = 0;
    check.total_discount = 0;

    for (int i = 0; i < check.count; i++) {
        CheckItem item = check.items[i];
        int original_total = item.product.price * item.quantity;
        int discount_amount = original_total - item.total;

        printf("%-15s | %4d | %6d | %7d%% | %4d руб.\n",
            item.product.name,
            item.product.price,
            item.quantity,
            item.product.discount,
            item.total);

        check.total_cost += original_total;
        check.total_discount += discount_amount;
    }

    check.final_cost = check.total_cost - check.total_discount;

    printf("-----------------------------------------------\n");
    printf("Общая стоимость: %d руб.\n", check.total_cost);
    printf("Сумма скидки: %d руб.\n", check.total_discount);
    printf("ИТОГО К ОПЛАТЕ: %d руб.\n", check.final_cost);
    printf("===============================================\n\n");
}

void print_last_scanned() {
    if (check.count > 0) {
        CheckItem last = check.items[check.count - 1];
        printf("Последний отсканированный товар:\n");
        printf("Штрих-код: %s\n", last.product.barcode);
        printf("Наименование: %s\n", last.product.name);
        printf("Цена: %d руб.\n", last.product.price);
        printf("Скидка: %d%%\n", last.product.discount);
        printf("Количество: %d\n", last.quantity);
        printf("Общая стоимость: %d руб.\n", last.total);
    }
    else {
        printf("Чек пуст!\n");
    }
}

void print_final_summary() {
    printf("\n=== ИТОГОВАЯ СВОДКА ===\n");
    printf("Общая стоимость товаров: %d руб.\n", check.total_cost);
    printf("Общая скидка: %d руб.\n", check.total_discount);
    printf("К оплате: %d руб.\n", check.final_cost);
    printf("========================\n\n");
}

int main() {
    setlocale(LC_ALL, "Ru");
    int choice;

    printf("=== ЭЛЕКТРОННАЯ КАССА ===\n");

    while (1) {
        printf("1 - Сканировать товар\n");
        printf("2 - Показать последний отсканированный товар\n");
        printf("3 - Показать чек\n");
        printf("4 - Итоговая сводка\n");
        printf("0 - Выход\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            scan_product();
            break;
        case 2:
            print_last_scanned();
            break;
        case 3:
            print_check();
            break;
        case 4:
            print_final_summary();
            break;
        case 0:
            printf("Работа завершена.\n");
            return 0;
        default:
            printf("Неверный выбор!\n");
        }
    }
    system("pause");
}