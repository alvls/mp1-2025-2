#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_ITEMS 100
#define NUM_PRODUCTS 9


// Массивы для хранения данных о товарах
char barcodes[NUM_PRODUCTS][6] = { "12944", "12212", "10994", "18990", "13367",
                                   "13349", "19438", "10900", "13687" }; // Штрих-коды товаров
char names[NUM_PRODUCTS][50] = { "Ананас", "Арбуз", "Слива", "Клубника",
                                "Персик", "Яблоко",
                                "Банан", "Груша", "Дыня" }; // Наименования товаров
int prices[NUM_PRODUCTS] = { 250, 530, 410, 1100, 390, 170, 350, 210, 340 }; // Цены товаров
int discounts[NUM_PRODUCTS]; // Скидки товаров (случайные)

// Массивы для чека
char receipt_barcodes[MAX_ITEMS][6]; // Штрих-коды товаров в чеке
int receipt_quantities[MAX_ITEMS];    // Количество товаров в чеке
int receipt_prices[MAX_ITEMS];        // Стоимость товара с учетом скидки в чеке
int receipt_size = 0; // Количество товаров в чеке

// Функция для поиска товара по штрих-коду
int find_product_by_barcode(const char* barcode) {
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        if (strcmp(barcodes[i], barcode) == 0) {
            return i;
        }
    }
    return -1;
}

// Функция для расчета стоимости товара с учетом скидки
int calculate_discounted_price(int price, int discount) {
    return price - (price * discount) / 100;
}

// Функция для добавления товара в чек
void add_to_receipt(int product_index, int quantity) {
    if (receipt_size < MAX_ITEMS) {
        strcpy_s(receipt_barcodes[receipt_size], sizeof(receipt_barcodes[0]), barcodes[product_index]);
        receipt_quantities[receipt_size] = quantity;
        receipt_prices[receipt_size] = calculate_discounted_price(prices[product_index], discounts[product_index]) * quantity;
        receipt_size++;
    }
    else {
        printf("Чек закончился. Повторите запуска.\n");
    }
}

// Функция для печати чека
void print_receipt() {
    int total = 0;
    int total_discount = 0;

    printf("\nЧек товаров\n");
    printf("__________\n");
    for (int i = 0; i < receipt_size; i++) {
        int product_index = find_product_by_barcode(receipt_barcodes[i]);
        if (product_index != -1) {
            int original_price = prices[product_index] * receipt_quantities[i];
            int discount_amount = original_price - receipt_prices[i];
            total += receipt_prices[i];
            total_discount += discount_amount;

            printf("%s - %d руб. - %d ед. - %d руб. (скидка %d%%)\n",
                names[product_index], prices[product_index], receipt_quantities[i], receipt_prices[i], discounts[product_index]);
        }
    }
    printf("__________\n");
    printf("Общая стоимость товаров: %d руб.\n", total);
    printf("Общая скидка: %d руб.\n", total_discount);
    printf("Итоговая цена: %d руб.\n", total);
}

// Функция для вывода каталога товаров
void print_product_catalog() {
    printf("\n**Запуска проведен. Обнаружены незначительные повреждения **\n** Блаженны оружейники! Ибо без них нет Империума **\n** Каталог доступных товаров **\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        printf("Штрих-код: %s, Название: %s, Цена: %d руб., Скидка: %d%%\n",
            barcodes[i], names[i], prices[i], discounts[i]);
    }
    printf("------------------------------------------------\n");
}

// Функция для инициализации скидок случайными числами
void initialize_discounts() {
    srand(time(NULL));

    // Генерация случайных скидок для каждого товара (от 5% до 50%, шаг 5%)
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        discounts[i] = 6 * (rand() % 10 + 1); // Скидка от 5% до 50%
    }
}

// Основная функция программы
int main() {
    char* locale = setlocale(LC_ALL, "");
    char barcode[6];
    int quantity;
    int choice;

    initialize_discounts();

    print_product_catalog();

    while (1) {
        printf("\nСписок алгоритмов: готов\n");
        printf("1. Сканировать товар\n");
        printf("2. Печать чека\n");
        printf("3. Завершение\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            printf("Введите штрих-код товара: ");
            scanf_s("%s", barcode, sizeof(barcode));

            int product_index = find_product_by_barcode(barcode);
            if (product_index != -1) {
                printf("Товар найден: %s, Цена: %d руб., Скидка: %d%%\n", names[product_index], prices[product_index], discounts[product_index]);
                printf("Введите количество(в кг): ");
                scanf_s("%d", &quantity);
                add_to_receipt(product_index, quantity);
            }
            else {
                printf("Этот товар не найден в архивах.\n");
            }
        }
        else if (choice == 2) {
            print_receipt();
        }
        else if (choice == 3) {
            printf("Завершение алгоритма.\n");
            break;
        }
        else {
            printf("Ошибка.\n");
        }
    }

    return 0;
}