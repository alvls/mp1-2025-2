#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 10
#define MAX_RECEIPT 50

typedef struct {
    char barcode[5];
    char name[50];
    int price;      // rubles
    int discount;   // %
} Product;

typedef struct {
    Product product;
    int quantity;
} ReceiptItem;

Product store[MAX_PRODUCTS] = {
    {"1234", "Milk", 80, 10},
    {"5678", "Bread", 40, 5},
    {"4321", "Chocolate", 120, 20},
    {"9999", "Juice", 90, 15}
};

ReceiptItem receipt[MAX_RECEIPT];
int receiptCount = 0;

Product* findProduct(char barcode[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(store[i].barcode, barcode) == 0)
            return &store[i];
    }
    return NULL;
}

void addToReceipt(Product* p) {
    for (int i = 0; i < receiptCount; i++) {
        if (strcmp(receipt[i].product.barcode, p->barcode) == 0) {
            receipt[i].quantity++;
            return;
        }
    }
    receipt[receiptCount].product = *p;
    receipt[receiptCount].quantity = 1;
    receiptCount++;
}

void printReceipt() {
    int totalBefore = 0;
    int totalDiscount = 0;

    printf("\n====== RECEIPT ======\n");
    for (int i = 0; i < receiptCount; i++) {
        int qty = receipt[i].quantity;
        int price = receipt[i].product.price;
        int disc = receipt[i].product.discount;

        int cost = qty * price;
        int saving = cost * disc / 100;

        totalBefore += cost;
        totalDiscount += saving;

        printf("%s | %d RUB | qty=%d | total=%d | discount=%d%%\n",
               receipt[i].product.name,
               price,
               qty,
               cost - saving,
               disc);
    }

    printf("------------------------\n");
    printf("Total before discounts: %d\n", totalBefore);
    printf("Total discount:         %d\n", totalDiscount);
    printf("Final amount to pay:    %d\n", totalBefore - totalDiscount);
}

int main() {
    char barcode[10];

    while (1) {
        printf("\nEnter barcode (or '0' to finish): ");
        scanf("%s", barcode);

        if (strcmp(barcode, "0") == 0)
            break;

        Product* p = findProduct(barcode);

        if (!p) {
            printf("Product not found.\n");
        } else {
            printf("Scanned: %s | Price=%d RUB | Discount=%d%%\n",
                   p->name, p->price, p->discount);

            addToReceipt(p);
        }
    }

    printReceipt();
    return 0;
}