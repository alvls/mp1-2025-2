#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Структура для товара
struct Product {
    char barcode[5];    // Штрих-код
    char name[50];
    int price;
    int discount;       // шаг в 5%
};

// Структура для позиции в чеке
struct ReceiptItem {
    char name[50];
    int unit_price;
    int quantity;
    int total_price;
};

// Структура для чека
struct Receipt {
    struct ReceiptItem items[100];  // Позиции в чеке
    int item_count;                 // Количество позиций
    int total_cost;
    int total_discount;
    int final_amount;
};

// Глобальные переменные
struct Product products[] = {
    {"0001", "Хлеб Бородинский", 45, 10},
    {"0002", "Молоко 2.5%", 85, 5},
    {"0003", "Сыр Российский", 320, 15},
    {"0004", "Колбаса Докторская", 280, 20},
    {"0005", "Яблоки красные", 120, 25},
    {"0006", "Шоколад молочный", 65, 10},
    {"0007", "Чай черный", 150, 30},
    {"0008", "Кофе зерновой", 450, 35},
    {"0009", "Сахар 1кг", 55, 5},
    {"0010", "Масло сливочное", 180, 15}
};

int product_count = 10;
struct Receipt current_receipt;
char current_barcode[5] = "";

// Функция для сканирования товара
void scan_product() {
    char input[10];

    printf("Введите штрих-код (4 цифры): ");
    scanf("%s", input);

    // Проверка длины штрих-кода
    if (strlen(input) != 4) {
        printf("Ошибка: штрих-код должен содержать ровно 4 цифры!\n");
        return;
    }

    // Проверка, что все символы - цифры
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Ошибка: штрих-код должен содержать только цифры!\n");
            return;
        }
    }

    strcpy(current_barcode, input);

    // Поиск товара в базе
    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].barcode, current_barcode) == 0) {
            found = 1;
            printf("Товар отсканирован: %s\n", products[i].name);
            break;
        }
    }

    if (!found) {
        printf("Товар с штрих-кодом %s не найден в базе!\n", current_barcode);
        strcpy(current_barcode, "");
    }
}

// Функция для вывода описания отсканированного товара
void show_product_description() {
    if (strlen(current_barcode) == 0) {
        printf("Сначала отсканируйте товар\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].barcode, current_barcode) == 0) {
            struct Product p = products[i];
            int price_with_discount = p.price - (p.price * p.discount / 100);

            printf("\n=== Описание товара ===\n");
            printf("Штрих-код: %s\n", p.barcode);
            printf("Наименование: %s\n", p.name);
            printf("Стоимость за единицу: %d руб.\n", p.price);
            printf("Скидка: %d%%\n", p.discount);
            printf("Цена со скидкой: %d руб.\n", price_with_discount);
            printf("========================\n");
            return;
        }
    }

    printf("Товар не найден!\n");
}

// Функция для добавления товара в чек
void add_to_receipt() {
    if (strlen(current_barcode) == 0) {
        printf("Сначала отсканируйте товар\n");
        return;
    }

    // Поиск товара в базе
    int product_index = -1;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].barcode, current_barcode) == 0) {
            product_index = i;
            break;
        }
    }

    if (product_index == -1) {
        printf("Товар не найден в базе!\n");
        return;
    }

    struct Product p = products[product_index];
    int price_with_discount = p.price - (p.price * p.discount / 100);

    // Проверка того, есть ли товар уже в чеке
    for (int i = 0; i < current_receipt.item_count; i++) {
        if (strcmp(current_receipt.items[i].name, p.name) == 0) {
            // Увеличивание количество
            current_receipt.items[i].quantity++;
            current_receipt.items[i].total_price =
                current_receipt.items[i].quantity * price_with_discount;
            printf("Количество товара '%s' увеличено до %d\n",
                p.name, current_receipt.items[i].quantity);
            return;
        }
    }

    // Добавление нового товара в чек
    if (current_receipt.item_count < 100) {
        struct ReceiptItem new_item;
        strcpy(new_item.name, p.name);
        new_item.unit_price = price_with_discount;
        new_item.quantity = 1;
        new_item.total_price = price_with_discount;

        current_receipt.items[current_receipt.item_count] = new_item;
        current_receipt.item_count++;

        printf("Товар '%s' добавлен в чек\n", p.name);
    }
    else {
        printf("Достигнуто максимальное количество позиций в чеке!\n");
    }
}

// Функция для расчета итоговой суммы
void calculate_total() {
    if (current_receipt.item_count == 0) {
        printf("Чек пуст! Добавьте товары.\n");
        return;
    }

    current_receipt.total_cost = 0;
    current_receipt.total_discount = 0;
    current_receipt.final_amount = 0;

    // Расчет по каждой позиции в чеке
    for (int i = 0; i < current_receipt.item_count; i++) {
        // Находим оригинальную цену товара
        int original_price = 0;
        for (int j = 0; j < product_count; j++) {
            if (strcmp(products[j].name, current_receipt.items[i].name) == 0) {
                original_price = products[j].price;
                break;
            }
        }

        int cost_without_discount = original_price * current_receipt.items[i].quantity;
        int discount_amount = cost_without_discount - current_receipt.items[i].total_price;

        current_receipt.total_cost += cost_without_discount;
        current_receipt.total_discount += discount_amount;
        current_receipt.final_amount += current_receipt.items[i].total_price;
    }

    printf("Итоговая сумма рассчитана:\n");
    printf("Общая стоимость: %d руб.\n", current_receipt.total_cost);
    printf("Суммарная скидка: %d руб.\n", current_receipt.total_discount);
    printf("Итого к оплате: %d руб.\n", current_receipt.final_amount);
}

// Функция для формирования чека
void print_receipt() {
    if (current_receipt.item_count == 0) {
        printf("Чек пуст! Сначала добавьте товары.\n");
        return;
    }

    //итоги
    calculate_total();

    printf("\n");
    printf("==================================================\n");
    printf("                 ЭЛЕКТРОННЫЙ ЧЕК                 \n");
    printf("==================================================\n");
    printf("Наименование             Цена   Кол-во   Сумма   \n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < current_receipt.item_count; i++) {
        printf("%-20s   %-5d   %-5d   %-6d\n",
            current_receipt.items[i].name,
            current_receipt.items[i].unit_price,
            current_receipt.items[i].quantity,
            current_receipt.items[i].total_price);
    }

    printf("==================================================\n");
    printf("Общая стоимость товаров: %d руб.\n", current_receipt.total_cost);
    printf("Суммарная скидка: %d руб.\n", current_receipt.total_discount);
    printf("ИТОГО К ОПЛАТЕ: %d руб.\n", current_receipt.final_amount);
    printf("==================================================\n\n");
}

// Функция для показа всех доступных товаров
void show_all_products() {
    printf("\n=== ДОСТУПНЫЕ ТОВАРЫ ===\n");
    printf("Штрих-код  Наименование              Цена   Скидка\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < product_count; i++) {
        printf("%-10s %-25s %-5d %d%%\n",
            products[i].barcode,
            products[i].name,
            products[i].price,
            products[i].discount);
    }
    printf("--------------------------------------------------\n");
}

// Функция для очистки чека
void clear_receipt() {
    current_receipt.item_count = 0;
    current_receipt.total_cost = 0;
    current_receipt.total_discount = 0;
    current_receipt.final_amount = 0;
    printf("Чек очищен.\n");
}

// Главное меню
void show_menu() {
    printf("\n=== ЭЛЕКТРОННАЯ КАССА ===\n");
    printf("1. Сканировать товар\n");
    printf("2. Показать описание отсканированного товара\n");
    printf("3. Добавить товар в чек\n");
    printf("4. Сформировать чек за покупку\n");
    printf("5. Рассчитать итоговую сумму к оплате\n");
    printf("6. Показать все доступные товары\n");
    printf("7. Очистить чек\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

// Основная функция
int main() {
    int choice;

    // Инициализация чека
    current_receipt.item_count = 0;
    current_receipt.total_cost = 0;
    current_receipt.total_discount = 0;
    current_receipt.final_amount = 0;

    printf("Добро пожаловать в программу 'Электронная касса'!\n");

    do {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            scan_product();
            break;
        case 2:
            show_product_description();
            break;
        case 3:
            add_to_receipt();
            break;
        case 4:
            print_receipt();
            break;
        case 5:
            calculate_total();
            break;
        case 6:
            show_all_products();
            break;
        case 7:
            clear_receipt();
            break;
        case 0:
            printf("Выход из программы. До свидания!\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}