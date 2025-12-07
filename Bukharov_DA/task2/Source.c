#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int gamemode, rnum, guess, number;
	char continue_playing = 'y';

	while (continue_playing == 'y' || continue_playing == 'Y') {
		int answer = 0, attempts = 1, min = 1, max = 1000;
		printf("Âûáåðèòå ðåæèì èãðû:\n");
		printf("1 - Âû óãàäûâàåòå ÷èñëî\n");
		printf("2 - Êîìïüþòåð óãàäûâàåò ÷èñëî\n");
		printf("Âàø âûáîð: ");
		scanf_s("%d", &gamemode);
		if (gamemode == 1) {
			printf("Ðåæèì 1\n");
			rnum = rand() % 999 + 1;
			while (answer == 0) {
				printf("Ïîïðîáóéòå óãàäàòü ÷èñëî, êîòîðîå ÿ çàãàäàë:\n");
				scanf_s("%d", &guess);
				if (guess == rnum) {
					printf("Âû óãàäàëè!\nÊîëè÷åñòâî ïîïûòîê: %i\n", attempts);
					answer = 1;
				}
				else if (guess < rnum) {
					printf("Çàãàäàííîå ÷èñëî áîëüøå\n");
					attempts += 1;
				}
				else if (guess > rnum) {
					printf("Çàãàäàííîå ÷èñëî ìåíüøå\n");
					attempts += 1;
				}
			}
		}
		else if (gamemode == 2) {
			printf("Ðåæèì 2\n");
			printf("Çàãàäàéòå ÷èñëî â äèàïàçîíå îò 1 äî 1000 è ââåäèòå åãî: ");
			scanf_s("%d", &number);

			while (number > 1000 || number < 1) {
				printf("Âû ââåëè ÷èñëî íå ïîäõîäÿùåå äèàïàçîíó. Ââåäèòå ÷èñëî îò 1 äî 1000: ");
				scanf_s("%d", &number);
			}

			char comparison = '.';
			attempts = 1;
			answer = 0;

			while (answer == 0) {
				guess = (min + max) / 2;
				printf("Ïðîãðàììà ïðåäïîëàãàåò, ÷òî âàøå ÷èñëî: %d\n", guess);
				printf("Ââåäèòå '>', '<' èëè '='\n");
				scanf_s(" %c", &comparison, 1);

				if (comparison == '=') {
					printf("×èñëî óãàäàíî\n");
					printf("Êîëè÷åñòâî ïîïûòîê: %d\n", attempts);
					answer = 1;
				}
				else if (comparison == '>') {
					min = guess;
					attempts += 1;
				}
				else if (comparison == '<') {
					max = guess;
					attempts += 1;
				}
				else {
					printf("Íåâåðíûé ââîä, èñïîëüçóéòå òîëüêî '>', '<' èëè '='\n");
				}
			}

		}
		else {
			printf("Íåâåðíûé âûáîð!\n");
		}
		printf("\nÕîòèòå ñûãðàòü åùå ðàç? (y/n): ");
		scanf_s(" %c", &continue_playing, 1);
	}

	system("pause");
}