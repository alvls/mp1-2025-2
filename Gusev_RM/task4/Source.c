#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "rus");
	int code[][5] = { {1234,100,15,1,0},{1111,120,20,1,1},{1112,40,25,1,2},{1113,200,30,1,3}}, pcode, chek = 0, chekt;
	char name[][20] = {"Молоко","Сыр","Хлеб","Колбаса"};
	int itog[100][6] = { 0 };
	int n = 0;

	while (chek == 0){
		printf("Введите код товара\n");
		scanf_s("%i", &pcode);
		printf("Если хотите добавить товар в корзину нажмите 1, если хотите посмотреть информацию о товаре нажмите 2\n");
		scanf_s("%i", &chekt);
		if (chekt == 2) {
			for (int i = 0; i < 4; i++) {
				if (code[i][0] == pcode) {
					int h;
					int propusk;
					h=code[i][4];
					printf("Товар цена скидка\n");
					printf("%s %i %i\n",name[h],code[i][1],code[i][2]);
					printf("Если хотите добавить товар в корзину нажмите 1, если хотите выбрать другой товар нажмите 2\n");
					scanf_s("%i", &propusk);
					if (propusk == 1) {
						chekt = 1;
					}
					else
					{
						break;
					}
				}
			}
		}
		if (chekt == 1){
			for (int i = 0; i <= n; i++) {
				if (itog[i][0] == pcode) {
					itog[i][4] += 1;
					break;
				}
				else if (itog[i][0] != pcode && itog[i][3] == 0){
					itog[i][0] = pcode;
					for (int y = 0; y < 4; y++) {
						if (code[y][0] == pcode) {
							itog[i][0] = code[y][0];
							itog[i][1] = code[y][1];
							itog[i][2] = code[y][2];
							itog[i][3] = code[y][3];
							itog[i][4] = 1;
							itog[i][5] = code[y][4];
						}
					}
					n += 1;
					break;
				}
				else if (itog[i][0] != pcode && itog[i][3] == 1) {
					continue;
				}
			}
			int prov;
			printf("Если хотите добавить товар нажмите 1 или 0 чтобы получить чек\n");
			scanf_s("%i", &prov);
			if (prov == 1 ) {
				chek = 0;
			}
			else
			{
				chek = 1;
			}
		}
	}
	float  sumskidka = 0;
	int sum = 0;
	printf("Товар цена скидка колличество\n");
	for (int i = 0; i < n; i++) {
		float skidka=0,skidkaproc;
		int q;
		skidkaproc = itog[i][2];
		skidka = itog[i][1]*(1 - (skidkaproc / 100)) * itog[i][4];
		q = itog[i][5];
		sum += itog[i][1] * itog[i][4];
		sumskidka += skidka;
		printf("%s %i %i %i\n", name[q], itog[i][1], itog[i][2], itog[i][4]);
	}
	printf("Сумма: %i\n", sum);
	printf("Итого сумма к оплате с учетом скидки: %f\n", sumskidka);
	system("pause");
	}