#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#define MAX_TOVAR 10

typedef struct {
    char barcode[5];
    char name[30];
    float price;
    int discount;
} Product;

typedef struct {
    Product product;
    int quantity;
    float total;
} CheckItem;

Product products[] =
{
    {"1234", "Хлеб", 40.0, 10},
    {"5678", "Молоко", 70.0, 5},
    {"1111", "Сыр", 250.0, 20},
    {"2222", "Яблоки", 120.0, 15},
    {"3333", "Шоколад", 90.0, 25}
};

int numProducts = 5;
CheckItem check[MAX_TOVAR];
int checkCount = 0;

Product* findProduct(char* barcode) {
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].barcode, barcode) == 0)
            return &products[i];
    }
    return NULL;
}

void addToCheck(Product* p, int qty) {
    for (int i = 0; i < checkCount; i++) {
        if (strcmp(check[i].product.barcode, p->barcode) == 0) {
            check[i].quantity += qty;
            check[i].total += qty * p->price * (1 - p->discount / 100.0);
            return;
        }
    }
    check[checkCount].product = *p;
    check[checkCount].quantity = qty;
    check[checkCount].total = qty * p->price * (1 - p->discount / 100.0);
    checkCount++;
}

void printCheck() {
    float totalSum = 0;
    printf("\n----------- ЧЕК -----------\n");
    for (int i = 0; i < checkCount; i++) {
        CheckItem* item = &check[i];
        printf("%s - %.2f руб x %d (скидка %d%%) = %.2f руб\n",
            item->product.name,
            item->product.price,
            item->quantity,
            item->product.discount,
            item->total);
        totalSum += item->total;
    }
    printf("---------------------------\n");
    printf("Итого к оплате: %.2f руб\n", totalSum);
}

int main() {
    setlocale(LC_ALL, "");
    char barcode[5];
    int qty;
    printf("=== Электронная касса ===\n");
    while (1)
    {
        printf("\nВведите штрих-код товара (или 0000 для завершения): ");
        scanf("%s", barcode);
        if (strcmp(barcode, "0000") == 0) break;
        Product* p = findProduct(barcode);
        if (p == NULL) {
            printf("Товар с таким штрих-кодом не найден.\n");
            continue;
        }
        printf("Товар: %s, цена: %.2f руб, скидка: %d%%\n", p->name, p->price, p->discount);
        printf("Введите количество: ");
        scanf("%d", &qty);
        addToCheck(p, qty);
    }
    printCheck();
    return 0;
}