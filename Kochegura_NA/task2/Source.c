#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	int rezhim, g1; /*переменна€ дл€ выбора режима игры, g1 - переменна€ дл€ выхода*/
	printf("Select game mode\n");
	printf("1 - You guess the number. 2 - computer guess your number\n");
	scanf_s("%d", &rezhim);

	switch (rezhim) {
	case 1: {
		int chislo, predpolozhenie;
		int popitki = 0;
		
		srand(time(NULL)); /*генератор случайных чисел*/
		chislo = rand() % 1000 + 1;

		printf("The system has selected a number. Try to guess\n");
		do
		{
			scanf_s("%d", &predpolozhenie);
			popitki++;
			
			if (predpolozhenie < chislo) {
				printf("The hidden number is higher\n");
			}
			else if (predpolozhenie > chislo) {
				printf("The hidden number is smaller\n");
			}
			else {
				printf("WOW, you did it\n");
				printf("Attempts spent\n");
				printf("%d\n", popitki);
			}
		} while (predpolozhenie != chislo);
		break;
	}
	case 2: {
		int chislo2, vibor;
		int popitki2 = 0;
		int nizhnya_granica = 1;
		int verhnya_granica = 1000;
		char s1;

		printf("choese the number from 1 to 1000\n");
		scanf_s("%d", &chislo2);
		if ((chislo2 < 1) || (chislo2 > 1000)) { /*ѕроверка на верно заданное число*/
			printf("Error\n");
			break;
		}
	
		printf("The system will try to guess the number\n");
		printf("Please rate the number using the symbols < or > or = \n");
		printf("The GAME is BEGINNER\n");
		printf("_____________________________________\n");
		
		do {
			
			vibor = (nizhnya_granica + verhnya_granica) / 2;

				printf("The system has selected a number\n");
				printf("%d\n", vibor);
				printf("Your number is < or > or = system number?\n");

				char s1; /*ѕеременна€ дл€ оценки числа*/
				char char1 = '>';
				char char2 = '<';
				char char3 = '=';
				//s1 = getchar();
				while (getchar() != '\n');

				scanf_s("%c", &s1);
				printf("%c", s1);

				if (s1 == char2) {
					verhnya_granica = vibor - 1;
				}
				else if (s1 == char1) {
					nizhnya_granica = vibor + 1;
				}
				else if (s1 == char3) {
					printf("The system guessed the number. Attempts = %d\n", popitki2);
					break;
				}
			
			popitki2++;
		} while (nizhnya_granica <= verhnya_granica);
		
		break;
	}
	default:
		printf(" Unknow game mode\n");
	}
	printf("Game over, thank you\n Press Any Key for close windows\n");
	scanf_s("%d", &g1);
}