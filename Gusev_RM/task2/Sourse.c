#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int main(){
	srand(time(0));
	setlocale(LC_ALL, "Russian");;
	int reg, N=1000, ot=0;
	printf("Введите режим игры 1 или 2\n");
	scanf_s("%i", &reg);
	if (reg==1) {
		int n = rand() % (N+1), variant, popytki1=0;
		while (ot == 0) {
			printf("Введите ваш вариант ответа\n");
			scanf_s("%i", &variant);
			if (variant == n) {
				printf("Отгадали\n");
				printf("Кол попыток:%i\n", popytki1);
				ot = 1;
			}
			if (variant > n) {
				printf(" Меньше\n");
				popytki1+=1;
			}
			if (variant < n) {
				printf("Больше\n");
				popytki1+=1;
			}
		}
	}
	if (reg == 2) {
		printf("придумайте число, а я его отгадаю\n");
		printf("я буду печатать числа а вы отвечайте > - больше, < - меньше или = если число верно\n");
		int ot2 = 0, min = 0, max = 1000, varkomp=0, poytki2=0;
		char chelot='-';
		while (ot2 == 0) {
			varkomp = (min + max) / 2 ;
			printf("%d\n", varkomp);
			scanf_s(" %c", &chelot);
			if (chelot == '=') {
				printf("ура угадал\n");
				printf("кол попыток: %i\n", poytki2);
				ot2 = 1;
			}
			if (chelot == '>') {
				min = varkomp;
				poytki2 += 1;
			}
			if (chelot == '<') {
				max = varkomp;
				poytki2 += 1;
			}
		}


	}
	system("pause");
}