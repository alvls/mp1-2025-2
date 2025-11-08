#include "stdio.h"
#include "locale.h"

int barcode[2] = { 1234, 5678 }; // 1234 молоко 5678 хлеб
char name[2][10] = { "молоко", "хлеб" };
int price[2] = { 90, 40 };
int discount[2] = { 10, 25 };
int quantity[2] = { 0, 0 };
int quan[2] = { 0, 0 };

int barus;
int a;

void com1();
void com();
void com2();
void com3();

int main() {
	setlocale(LC_ALL, "Ru");
	do {
		com();
		switch (a) {
		case 1:
			com1();
			break;
		case 2:
			com2();
			break;
		}
	} while (a != 3);
	com3();
	return 0;
}

void com() {
	printf("1. Ввести штрихкод\n");
	printf("2. Вывести описание товара про штрихкоду\n");
	printf("3. Завершить сканирование/вывести чек\n");
	scanf_s("%d", &a);
}

void com1() {
	printf("Введите штрихкод: ");
	scanf_s("%d", &barus);
	for (int i = 0; i < 3; i++) {
		if (barcode[i] == barus) {
			printf("Товаp: %s добавлен в чек. \n", name[i]);
			quantity[i]++;
			break;
		}

	}
}

void com2() {
	printf("Введите штрихкод: \n");
	scanf_s("%d", &barus);
	for (int i = 0; i < 3; i++) {
		if (barcode[i] == barus) {
			printf("Наименование: %s\n", name[i]);
			printf("Цена: %d \n", price[i]);
			printf("Скидка: %d \n", discount[i]);
			break;
		}
		else {
			printf("Ошибка: Штрихкод не найден в базе \n");
			break;
		}
	}
}

void com3() {
	int res = 0;
	printf("\n=== ЧЕК ===\n");
	printf("%-20s %-10s %-10s %-10s %-10s\n", "Наименование", "Цена", "Кол-во", "Скидка", "Сумма");
	for (int i = 0; i < 2; i++) {
		if (quantity[i] != 0) {
			int a = price[i] * quantity[i];
			int b = (a * discount[i]) / 100;
			int c = a - b;
			quan[i] = c * quantity[i];
			printf("%-20s %-10d %-10d %-9d %-10d\n", name[i], price[i], quantity[i],
				discount[i], c);
		}
	}
	for (int i = 0; i < 2; i++)
		res += quan[i];
	printf("----------------\n");
	printf("Итоговая сумма: %d", res);
}