#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_ITEMS 100
#define NUM_PRODUCTS 10

// Массивы для хранения данных о товарах
char barcodes[NUM_PRODUCTS][5] = { "1234", "2345", "3456", "4567", "5678",
                                   "6789", "7890", "8901", "9012", "0123" }; // Штрих-коды товаров
char names[NUM_PRODUCTS][50] = { "Кроциус", "Печать чистоты", "Силовая броня", "Силовой топор",
                                "Запчасти для генератора поля Геллера", "Болтер 'Милость Императора'",
                                "Баки с прометием", "Набор аугметики", "Мехадендрит", "Сервочереп" }; // Наименования товаров
int prices[NUM_PRODUCTS] = { 2500, 200, 5000, 1500, 10000, 3000, 350, 4000, 120, 500 }; // Цены товаров
int discounts[NUM_PRODUCTS]; // Скидки товаров (случайные)

// Массивы для чека
char receipt_barcodes[MAX_ITEMS][5]; // Штрих-коды товаров в чеке
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
        printf("Пространство в чеке истощено! Повторите литанию запуска.\n");
    }
}

// Функция для печати чека
void print_receipt() {
    int total = 0;
    int total_discount = 0;

    printf("\n** Чек товаров **\n");
    printf("**-*---*-*----------***--------*-----**--------*\n");
    for (int i = 0; i < receipt_size; i++) {
        int product_index = find_product_by_barcode(receipt_barcodes[i]);
        if (product_index != -1) {
            int original_price = prices[product_index] * receipt_quantities[i];
            int discount_amount = original_price - receipt_prices[i];
            total += receipt_prices[i];
            total_discount += discount_amount;

            printf("%s - %d Юн. - %d ед. - %d Юн. (скидка %d%%)\n",
                names[product_index], prices[product_index], receipt_quantities[i], receipt_prices[i], discounts[product_index]);
        }
    }
    printf("-**-----*-------**-*-----------*--**----*--**---\n");
    printf("Общая стоимость товаров: %d Юн.\n", total);
    printf("Общая скидка: %d Юн.\n", total_discount);
    printf("Итоговая цена: %d Юн.\n", total);
}

// Функция для вывода каталога товаров
void print_product_catalog() {
    printf("\n** Литания запуска проведена. Запуск успешен. Обнаружены незначительные повреждения механизма **\n** Блаженны оружейники! Ибо без них нет Империума **\n** Каталог доступных артефактов Механикума **\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        printf("Штрих-код: %s, Наименование: %s, Цена: %d Юн., Скидка: %d%%\n",
            barcodes[i], names[i], prices[i], discounts[i]);
    }
    printf("------------------------------------------------\n");
}

// Функция для инициализации скидок случайными числами
void initialize_discounts() {
    srand(time(NULL));

    // Генерация случайных скидок для каждого товара (от 5% до 50%, шаг 5%)
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        discounts[i] = 5 * (rand() % 10 + 1); // Скидка от 5% до 50%
    }
}

// Основная функция программы
int main() {
    char* locale =setlocale(LC_ALL, "");
    char barcode[5];
    int quantity;
    int choice;

    initialize_discounts();

    print_product_catalog();

    while (1) {
        printf("\n** Главный интерфейс. Состояние машинного духа: спокойное. Список алгоритмов: подготовлен **\n");
        printf("1. Сканировать артефакт\n");
        printf("2. Печать чека\n");
        printf("3. Литания завершения алгоритма\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            printf("Введите штрих-код артефакта (4 руны): ");
            scanf_s("%s", barcode, sizeof(barcode));

            int product_index = find_product_by_barcode(barcode);
            if (product_index != -1) {
                printf("Артефакт найден: %s, Цена: %d Юн., Скидка: %d%%\n", names[product_index], prices[product_index], discounts[product_index]);
                printf("Введите количество: ");
                scanf_s("%d", &quantity);
                add_to_receipt(product_index, quantity);
            }
            else {
                printf("Этот артефакт не найден в архивах Механикума! Возможно, он был утерян во время варп-перехода.\n");
            }
        }
        else if (choice == 2) {
            print_receipt();
        }
        else if (choice == 3) {
            printf("Литания завершения алгоритма. Слава Омниссии\n");
            break;
        }
        else {
            printf("Ошибка! Вы нарушили алгоритм. Позовите техножреца и повторите литанию запуска.\n");
        }
    }

    return 0;
}
