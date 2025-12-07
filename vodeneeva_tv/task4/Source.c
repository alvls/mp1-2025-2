#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define BAR_CODE_SIZE 5

typedef struct {
    char barcode[BAR_CODE_SIZE];
    char name[50];
    int price;
    int discount_percent;
} Product;

Product products[MAX_PRODUCTS] = {
    {"0001", "Coca Cola", 150, 5},
    {"0002", "Lays", 100, 0},
    {"0003", "Vine", 900, 15},
    {"0004", "Milka", 120, 0},
    {"0005", "Orbit", 60, 10}
};

typedef struct {
    Product product;
    unsigned int quantity; 
} Item;

Item cart[MAX_PRODUCTS];
int cartCount = 0;
Product *lastProduct = NULL;

int compare(char *barcode_a, char *barcode_b) {
    for (int i = 0; i < BAR_CODE_SIZE; i++) {
        if (barcode_a[i] != barcode_b[i]) {
            return 1;
        }
    }
    return 0;
}

Product* findProduct(char *barcode) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (compare(products[i].barcode, barcode) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

void scanProduct() {
    char barcode[5];
    printf("Введите штрихкод (4 символа): ");
    scanf("%4s", barcode);
    Product* p = findProduct(barcode);
    if (p != NULL) {
        lastProduct = p;
        printf("Товар найден: %s\n", p->name);
    } else {
        printf("Товар не найден.\n");
    }
}

void addToCart() {
    if (lastProduct == NULL) {
        printf("Нет выбранного товара. Выполните сканирование.\n");
        return;
    }
    unsigned int qty;
    printf("Введите количество: ");
    scanf("%u", &qty);
   
    for (int i = 0; i < cartCount; i++) {
        if (compare(cart[i].product.barcode, lastProduct->barcode) == 0) {
            cart[i].quantity += qty;
            printf("Обновлено: %s, %u\n", cart[i].product.name, cart[i].quantity);
            return;
        }
    }
  
    cart[cartCount].product = *lastProduct;
    cart[cartCount].quantity = qty;
    cartCount++;
    printf("Добавлено: %s, %u \n", lastProduct->name, qty);
}


void printCheck() {
    if (cartCount == 0) {
        printf("Чек пуст.\n");
        return;
    }
    int total = 0, totalDiscount = 0;
    printf("\n---- Чек ----\n");
    printf("%-15s %-10s %-10s %-10s\n", "Наименование", "Цена", "Кол-во", "Сумма");
    for (int i = 0; i < cartCount; i++) {
        Product p = cart[i].product;
        unsigned int qty = cart[i].quantity;
        int price = p.price;
        int fullPrice = price * qty;
        int discount = fullPrice * p.discount_percent / 100.0;
        int finalPrice = fullPrice - discount;
        total += finalPrice;
        totalDiscount += discount;
        printf("%-15s %-10d %-10d %-10d\n", p.name, price, qty, finalPrice);
    }
    printf("\nОбщая скидка: %u руб.\n", totalDiscount);
    printf("Итого к оплате: %u руб.\n", total);
    printf("--------------\n");
}

int main() {
    int choice;
    while(1) {
        printf("\nМеню:\n");
        printf("1. Сканиовать товар\n");
        printf("2. Добавить в чек\n");
        printf("3. Показать чек\n");
        printf("4. Оплатить\n");
        printf("5. Выйти\n");
        printf("Выберите: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                scanProduct();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                printCheck();
                break;
            case 4:
                printCheck();
                return 0;
            case 5:
                printf("Выход.\n");
                return 0;
            default:
                printf("Некорректный выбор.\n");
        }
    }
}
