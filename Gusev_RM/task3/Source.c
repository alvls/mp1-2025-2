#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
void main() {
	int n, number[5] = { 0 }, chek1 = 0, ot=0;
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	printf("Игра 'Быки и коровы'\n");
	printf("Я загадываю число, а вы его отгадываете по моим подсказкам\n");
	printf("Я буду говорить количество быков (сколько цифр угаданно вплоть до позиции) и коров (сколько цифр угадано без совпадения с их позициями)\n");
	printf("Введите длину числа (от 2 до 5)\n");
	scanf_s("%d", &n);
	number[0] = rand() % 9 + 1;;
	while (chek1<20) {
		for (int i = 1; i < 5; i++) {
			number[i] = rand() % 10;
		}
		for (int i = 1; i < 5; i++) {
			for (int ii = 0; ii < i; ii++) {
				if (number[i] != number[ii]) {
					chek1 += 1;
				}
				else {
					chek1 = 0;
					continue;
				}
			}
		}
	}	
	for (int i = 0; i < n; i++) {
		ot = ot*10 + number[i];
	}
	//printf("%d\n", ot);
	int chek2 = 0, var, number2[5] = {0}, bull = 0, cow=0;
	while (chek2 == 0) {
		printf("Введите ваш вариант ответа\n");
		scanf_s("%d", &var);
		for (int i = n-1; i != -1; i--) {
			number2[i] = var % 10;
			var = var / 10;
		}
		for (int i = 0; i < n; i++) {
			if (number[i] == number2[i]) {
				bull += 1;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int ii = 0; ii < n; ii++) {
				if (number[i] == number2[ii]) {
					cow += 1;
				}
			}
		}
		cow = cow - bull;
		if (bull == n) {
			printf("Поздравляю, вы угадали число\n");
			chek2 = 1;
			break;
		}
		if (bull == 1 && cow == 1) {
			printf("в вашем числе %i бык и %i корова\n", bull, cow);
		}
		if ( bull>=2 && bull <= 4 && 2 <= cow && cow<= 4) {
			printf("в вашем числе %i быка и %i коровы\n", bull, cow);
		}
		if ( bull>=2 && bull<=4 && cow == 1) {
			printf("в вашем числе %i быка и %i корова\n", bull, cow);
		}
		if (bull == 1 && cow>=2 && cow <=4 ) {
			printf("в вашем числе %i бык и %i коровы\n", bull, cow);
		}
		if (bull == 5 && cow == 5) {
			printf("в вашем числе %i быков и %i коров\n", bull, cow);
		}
		if (bull == 0 && cow == 5) {
			printf("в вашем числе %i быков и %i коров\n", bull, cow);
		}
		if (bull == 0 && cow == 1) {
			printf("в вашем числе %i быков и %i корова\n", bull, cow);
		}
		if (bull == 0 && cow >= 2 && cow <= 4) {
			printf("в вашем числе %i быков и %i коровы\n", bull, cow);
		}
		if (bull == 1 && cow == 0) {
			printf("в вашем числе %i бык и %i коров\n", bull, cow);
		}
		if (bull >= 2 && bull <= 4 && cow == 0) {
			printf("в вашем числе %i быка и %i коров\n", bull, cow);
		}
		if (bull == 0 && cow == 0) {
			printf("в вашем числе нет быков и коров\n");
		}
		cow = 0;
		bull = 0;
	}
	system("pause");
}