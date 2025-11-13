#include <stdio.h>
#include <string.h>

struct Product {
    char shtrihcode[5];
    char tovar[20];
    int price;
    int discount;
};

struct Receipt {
    char tovar[20];
    int price;
    int quantity;
    int total;
};

//Initial Massive
struct Product products[5];


int product_count = 5;

struct Receipt receipt[10];
int receipt_count = 0;

void scanProduct();
void showReceipt();
void calculateTotal();
void showMenu();
int main() {
    int choice;
  // #1
    snprintf(products[0].shtrihcode, sizeof(products[0].shtrihcode), "1234");
    snprintf(products[0].tovar, sizeof(products[0].tovar), "Hleb");
    products[0].price = 50;
    products[0].discount = 10;
  // #2
    snprintf(products[1].shtrihcode, sizeof(products[1].shtrihcode), "5678");
    snprintf(products[1].tovar, sizeof(products[1].tovar), "Moloko");
    products[1].price = 80;
    products[1].discount = 5;
  // #3
    snprintf(products[2].shtrihcode, sizeof(products[2].shtrihcode), "9012");
    snprintf(products[2].tovar, sizeof(products[2].tovar), "Sir");
    products[2].price = 200;
    products[2].discount = 15;
  // #4
    snprintf(products[3].shtrihcode, sizeof(products[3].shtrihcode), "3456");
    snprintf(products[3].tovar, sizeof(products[3].tovar), "Voda");
    products[3].price = 40;
    products[3].discount = 5;
 // #5
    snprintf(products[4].shtrihcode, sizeof(products[4].shtrihcode), "4321");
    snprintf(products[4].tovar, sizeof(products[4].tovar), "Sok");
    products[4].price = 90;
    products[4].discount = 10;
    while (1) {
        showMenu();
        printf("Choise button: ");
        scanf_s("%d", &choice);
        
        switch (choice) {            
        case 1:
            scanProduct();
            break;
        case 2:
            showReceipt();
            break;
        case 3:
            calculateTotal();
            break;
        case 4:
            printf("End from programm\n");
            return 0;
        default:
            printf("Bad choise!\n");
        }
    }
}

void showMenu() {
    printf("\n* Menu *\n");
    printf("1. Scan tovar\n");
    printf("2. Show chek\n");
    printf("3. Get full price\n");
    printf("4. Exit\n");
    printf("****\n");
}

void scanProduct() {
    char shtrihcode[5];
    int i, found = 100;
    printf("Enter shtrihcode 4 digits: ");
    while (getchar() != '\n');
    fgets(shtrihcode, sizeof(shtrihcode), stdin);
   // scanf_s("%4s", &shtrihcode, 1);
    //printf("product_count =  %d |", product_count);
    for (i = 0; i < product_count; i++) {

          if (strcmp(products[i].shtrihcode, shtrihcode) == 0) {
             found = i;
            break;
        }
    }
    //printf("[FOUND   %d ]", found);
    if (found==100) {
        printf("not Tovar in base!\n");
        return;
    }
    
    printf("find tovar: %s\n", products[found].tovar);
    printf("Price: %d rub.\n", products[found].price);
    printf("Discount: %d%%\n", products[found].discount);

    int full_price = products[found].price;
    int price_with_discount = products[found].price * (100 - products[found].discount) / 100;
    for (int j = 0; j < receipt_count; j++) {
        if (strcmp(receipt[j].tovar, products[found].tovar) == 0) {
            receipt[j].quantity++;
            receipt[j].total = receipt[j].quantity * price_with_discount;
            printf("Tovar add in chek (now is: %d)\n", receipt[j].quantity);
            return;
        }
    }

    if (receipt_count < 10) {
        int r = strcpy_s(receipt[receipt_count].tovar, sizeof(receipt[receipt_count].tovar), products[found].tovar);
        receipt[receipt_count].price = full_price;
        receipt[receipt_count].quantity = 1;
        receipt[receipt_count].total = price_with_discount;
        receipt_count++;
        printf("Tovar add in chek!\n");
    }

    else {
        printf("full chek!\n");
    }
}

void showReceipt() {
    int summ_oplati = 0;
    if (receipt_count == 0) {
        printf("zero chek!\n");
        return;
    }

    printf("\n=== CHEK ===\n");
    printf("Tovar\t\t Price\t Total\t Summ\t Discount\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < receipt_count; i++) {
        summ_oplati += receipt[i].total;
        printf("%s\t\t%d\t%d\t%d\t(%d %%)\n",
            receipt[i].tovar,
            receipt[i].price,
            receipt[i].quantity,
            receipt[i].total,
            products[i].discount);
    }
    printf("------------------------------------------------\n");
    printf("Full payment =  %d rub.\n", summ_oplati);
    printf("------------------------------------------------\n");
}

void calculateTotal() {
    if (receipt_count == 0) {
        printf("Zero chek!\n");
        return;
    }
    int total = 0;
    int total_discount = 0;
    int final_total = 0;

    for (int i = 0; i < receipt_count; i++) {
        total += receipt[i].total;
    }

    final_total = total;
    printf("\n=== ITOG ===\n");
    printf("Full price: %d rub.\n", total);
    printf("Itog price: %d rub.\n", final_total);
    printf("================\n");
}