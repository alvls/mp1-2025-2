#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct Product
{
	int barcode[4];
	char* name;
	float price;
	char discount;
};

struct CartItem {
	struct Product* product;
	int count;
};

struct Product* FindProductByBarcode(struct Product products[], int size, int search_barcode[4]) {

	for (int i = 0; i < size; i++) {
		if (memcmp(products[i].barcode, search_barcode, 4 * sizeof(int)) == 0) {
			return &products[i];
		}
	}

	return NULL;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	struct Product products[] = {
		{{0, 0, 0, 0}, "Сырок творожный", 50.0f, 5},
		{{0, 0, 0, 1}, "Йогурт", 70.0f, 10},
		{{0, 0, 0, 2}, "Ряженка", 60.0f, 5},
		{{0, 0, 0, 3}, "Сигареты", 200.0f, 0},
	};
	int products_count = sizeof(products) / sizeof(products[0]);

	struct CartItem items[4];
	for (int i = 0; i < products_count; i++) {
		items[i].product = &products[i];
		items[i].count = 0;
	}

	int barcode[4] = {-1, 0, 0, 0};
	char input[5];
	printf("Опции:\n - Ввести штрихкод (0000 - 0003)\n - Ввести 0, чтобы получить информацию о последнем штрихкоде \n - Ввести 1, чтобы добавить последний штрихкод в корзину\n - Ввести 2, чтобы получить текущую итоговую сумму товаров из корзины\n - Ввести 3, чтобы получить чек\n");

	while (1) {
		scanf_s("%4s", input, (unsigned)_countof(input));

		if (strlen(input) == 1) {
			if (barcode[0] == -1) {
				printf("Вы ничего не просканировали\n");
				continue;
			}
			else if (input[0] == '0') {
				struct Product* product = FindProductByBarcode(products, products_count, barcode);

				if (product != NULL) {
					printf("Штрихкод: %d%d%d%d\n", product->barcode[0], product->barcode[1], product->barcode[2], product->barcode[3]);
					printf("Название: %s\nЦена: %f рублей\nПроцент скидки: %d\n", product->name, product->price, product->discount);
				}
			}
			else if (input[0] == '1') {
				struct Product* product = FindProductByBarcode(products, products_count, barcode);

				if (product != NULL) {
					for (int i = 0; i < products_count; i++) {
						if (items[i].product == product) {
							items[i].count++;
							printf("%d %s в корзине\n", items[i].count, product->name);
						}
					}
				}
			}
			else if (input[0] == '2') {
				float total_sum_discounted = 0;

				for (int i = 0; i < products_count; i++) {
					total_sum_discounted += (items[i].product->price * (1 - 0.01 * items[i].product->discount) * items[i].count);
				}

				printf("Общая стоимость товаров в чеке: %f рублей\n", total_sum_discounted);
			}
			else if (input[0] == '3') {
				float total_sum = 0;
				float total_sum_discounted = 0;

				for (int i = 0; i < products_count; i++) {
					total_sum += (items[i].product->price * items[i].count);
				}

				for (int i = 0; i < products_count; i++) {
					total_sum_discounted += (items[i].product->price * (1 - 0.01 * items[i].product->discount) * items[i].count);
				}

				float total_discount = (total_sum - total_sum_discounted) / total_sum * 100;

				printf("Чек:\n\n");

				for (int i = 0; i < products_count; i++) {
					if (items[i].count > 0) {
						printf("Название: %s\nЦена: %f рублей\nПроцент скидки: %d\nКоличество: %d\nИтоговая стоимость: %f рублей\n\n", items[i].product->name, items[i].product->price, items[i].product->discount, items[i].count, items[i].product->price * (1 - 0.01 * items[i].product->discount) * items[i].count);
					}
				}

				printf("Общая стоимость товаров (без скидки): %f рублей\nСуммарная скидка: %f\nИтоговая стоимость к оплате: %f рублей\n\n", total_sum, total_discount, total_sum_discounted);
			}
		}
		else if (strlen(input) == 4) {
			int valid = 1;

			for (int i = 0; i < 4; i++) {
				if (!isdigit(input[i])) {
					valid = 0;
					break;
				}
			}

			if (valid) {
				for (int i = 0; i < 4; i++) {
					barcode[i] = input[i] - '0';
				}
			}
		}

	}

	

	return 0;
}

//int** barcodes = NULL; это я не то сделал
//char input[5];
//int size = 0;
//printf("Вводите штрихкоды (0000 - 0003). Введите 0 чтобы закончить ввод.\n");
//
//while (1) {
//	scanf_s("%4s", input);
//
//	if (strlen(input) == 1 && input[0] == '0')
//		break;
//
//	if (strlen(input) == 4) {
//		int valid = 1;
//
//		for (int i = 0; i < 4; i++) {
//			if (!isdigit(input[i])) {
//				valid = 0;
//				break;
//			}
//		}
//
//		if (valid) {
//			int* barcode = malloc(4 * sizeof(int));
//
//			for (int i = 0; i < 4; i++) {
//				barcode[i] = input[i] - '0';
//			}
//
//			barcodes = realloc(barcodes, (size + 1) * sizeof(int*));
//			barcodes[size] = barcode;
//			size++;
//		}
//	}
//
//}
