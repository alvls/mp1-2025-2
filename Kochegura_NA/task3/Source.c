#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void) {
	int rezhim, g1; /*переменная для выбора режима игры, g1 - переменная для выхода*/
	printf("Select game mode\n");
	printf("2 - The length of the number is 2. 3 - The length of the number is 3\n");
	printf("4 - The length of the number is 4. 5 - The length of the number is 5\n");
	scanf_s("%d", &rezhim);

	switch (rezhim) {
	case 2: {
		int biki, corovi, c_1, c_2, p_1, p_2, chislo_compa, chislo_igroka;

		srand(time(NULL));

		do {
			chislo_compa = (rand() % 90) + 10;
			c_1 = (chislo_compa / 10) % 10;
			c_2 = chislo_compa % 10;
		} while (c_1 == c_2);

		printf("Computer make the number .\n");

		do {
			biki = 0;
			corovi = 0;
			printf("Your number is: ");
			scanf_s("%d", &chislo_igroka);
			if (chislo_igroka == chislo_compa) {
				printf("Great job, you did it!");
				break;
			}
			p_1 = (chislo_igroka / 10) % 10;
			p_2 = chislo_igroka % 10;
			if (p_1 == c_1) biki++;
			else if ((p_1 == c_2) && (p_2 != c_2)) corovi++;
			if (p_2 == c_2) biki++;
			else if ((p_2 == c_1) && (p_1 != c_1)) corovi++;
			printf("Bikov: %d. Korov: %d\n", biki, corovi);
		} while (chislo_igroka != chislo_compa);
	}
	case 3: {
		int biki, corovi, c_1, c_2, c_3, p_1, p_2, p_3, chislo_compa, chislo_igroka;

		srand(time(NULL));

		do {
			chislo_compa = (rand() % 900) + 100;
			c_1 = (chislo_compa / 100) % 10;
			c_2 = (chislo_compa / 10) % 10;
			c_3 = chislo_compa % 10;
		} while ((c_1 == c_2) || (c_1 == c_3) || (c_2 == c_3));

		printf("Computer make the number .\n");

		do {
			biki = 0;
			corovi = 0;
			printf("Your number is: ");
			scanf_s("%d", &chislo_igroka);
			if (chislo_igroka == chislo_compa) {
				printf("Great job, you did it!");
				break;
			}
			p_1 = (chislo_igroka / 100) % 10;
			p_2 = (chislo_igroka / 10) % 10;
			p_3 = chislo_igroka % 10;
			if (p_1 == c_1) biki++;
			else if ((p_1 == c_2 && p_2 != c_2) || (p_1 == c_3 && p_3 != c_3)) corovi++;
			if (p_2 == c_2) biki++;
			else if ((p_2 == c_1 && p_1 != c_1) || (p_2 == c_3 && p_3 != c_3)) corovi++;
			if (p_3 == c_3) biki++;
			else if ((p_3 == c_1 && p_1 != c_1) || (p_3 == c_2 && p_2 != c_2)) corovi++;
			printf("Bikov: %d. Korov: %d\n", biki, corovi);
		} while (chislo_igroka != chislo_compa);
	}
	case 4: {
		int biki, corovi, c_1, c_2, c_3, c_4, p_1, p_2, p_3, p_4, chislo_compa, chislo_igroka;

		srand(time(NULL));

		do {
			chislo_compa = (rand() % 9000) + 1000;
			c_1 = (chislo_compa / 1000) % 10;
			c_2 = (chislo_compa / 100) % 10;
			c_3 = (chislo_compa / 10) % 10;
			c_4 = chislo_compa % 10;
		} while ((c_1 == c_2) || (c_1 == c_3) || (c_1 == c_4) || (c_2 == c_3) || (c_2 == c_4) || (c_3 == c_4));

		printf("Computer make the number .\n");

		do {
			biki = 0;
			corovi = 0;
			printf("Your number is: ");
			scanf_s("%d", &chislo_igroka);
			if (chislo_igroka == chislo_compa) {
				printf("Great job, you did it!");
				break;
			}
			p_1 = (chislo_igroka / 1000) % 10;
			p_2 = (chislo_igroka / 100) % 10;
			p_3 = (chislo_igroka / 10) % 10;
			p_4 = chislo_igroka % 10;
			if (p_1 == c_1) biki++;
			else if ((p_1 == c_2 && p_2 != c_2) || (p_1 == c_3 && p_3 != c_3) || (p_1 == c_4 && p_4 != c_4)) corovi++;
			if (p_2 == c_2) biki++;
			else if ((p_2 == c_1 && p_1 != c_1) || (p_2 == c_3 && p_3 != c_3) || (p_2 == c_4 && p_4 != c_4)) corovi++;
			if (p_3 == c_3) biki++;
			else if ((p_3 == c_1 && p_1 != c_1) || (p_3 == c_2 && p_2 != c_2) || (p_3 == c_4 && p_4 != c_4)) corovi++;
			if (p_4 == c_4) biki++;
			else if ((p_4 == c_1 && p_1 != c_1) || (p_4 == c_2 && p_2 != c_2) || (p_4 == c_3 && p_3 != c_3)) corovi++;
			printf("Bikov: %d. Korov: %d\n", biki, corovi);
		} while (chislo_igroka != chislo_compa);
	}
	case 5: {
		int biki, corovi, c_1, c_2, c_3, c_4, c_5, p_1, p_2, p_3, p_4, p_5, chislo_compa, chislo_igroka;

		srand(time(NULL));

		do {
			chislo_compa = (rand() % 90000) + 10000;
			c_1 = (chislo_compa / 10000) % 10;
			c_2 = (chislo_compa / 1000) % 10;
			c_3 = (chislo_compa / 100) % 10;
			c_4 = (chislo_compa / 10) % 10;
			c_5 = chislo_compa % 10;
		} while ((c_1 == c_2) || (c_1 == c_3) || (c_1 == c_4) || (c_1 == c_5) || (c_2 == c_3) || (c_2 == c_4) || (c_2 == c_5) || (c_3 == c_4) || (c_3 == c_5) || (c_4 == c_5));

		printf("Computer make the number .\n");

		do {
			biki = 0;
			corovi = 0;
			printf("Your number is: ");
			scanf_s("%d", &chislo_igroka);
			if (chislo_igroka == chislo_compa) {
				printf("Great job, you did it!");
				break;
			}
			p_1 = (chislo_igroka / 10000) % 10;
			p_2 = (chislo_igroka / 1000) % 10;
			p_3 = (chislo_igroka / 100) % 10;
			p_4 = (chislo_igroka / 10) % 10;
			p_5 = chislo_igroka % 10;
			if (p_1 == c_1) biki++;
			else if ((p_1 == c_2 && p_2 != c_2) || (p_1 == c_3 && p_3 != c_3) || (p_1 == c_4 && p_4 != c_4) || (p_1 == c_5 && p_5 != c_5)) corovi++;
			if (p_2 == c_2) biki++;
			else if ((p_2 == c_1 && p_1 != c_1) || (p_2 == c_3 && p_3 != c_3) || (p_2 == c_4 && p_4 != c_4) || (p_2 == c_5 && p_5 != c_5)) corovi++;
			if (p_3 == c_3) biki++;
			else if ((p_3 == c_1 && p_1 != c_1) || (p_3 == c_2 && p_2 != c_2) || (p_3 == c_4 && p_4 != c_4) || (p_3 == c_5 && p_5 != c_5)) corovi++;
			if (p_4 == c_4) biki++;
			else if ((p_4 == c_1 && p_1 != c_1) || (p_4 == c_2 && p_2 != c_2) || (p_4 == c_3 && p_3 != c_3) || (p_4 == c_5 && p_5 != c_5)) corovi++;
			if (p_5 == c_5) biki++;
			else if ((p_5 == c_1 && p_1 != c_1) || (p_5 == c_2 && p_2 != c_2) || (p_5 == c_3 && p_3 != c_3) || (p_5 == c_4 && p_4 != c_4)) corovi++;
			printf("Bikov: %d. Korov: %d\n", biki, corovi);
		} while (chislo_igroka != chislo_compa);

	}
	default:
		printf(" Unknow game mode\n");
	}
	printf("Game over, thank you\n Press Any Key for close windows\n");
	scanf_s("%d", &g1);
}