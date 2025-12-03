#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Mode1();
void Mode2();


int main() {
	srand(time(NULL));
	int mode;
	printf("Mode 1 - Guess the number \n");
	printf("Mode 2 - Think of a number \n");
	scanf_s("%d", &mode);

	if (mode == 1)
		Mode1();

	else if (mode == 2)
		Mode2();

	else
		printf("The wrong mode is selected");

	return 0;
}
void Mode1() {
	printf("1 mode is selected");
	int number = rand() % 1000;
	int a = 1, b = 1000, count = 1, numb;
	printf("Enter a number from 1 to 999 \n");
	while (1) {
		scanf_s("%d", &numb);
		if (numb > number) {
			printf("The hidden number is smaller than yours \n");
			count++;
		}
		else if (numb < number) {
			printf("The hidden number is bigger than yours \n");
			count++;
		}
		else {
			printf("You guessed the number. \n");
			printf("number of attempts: %d", count);
			break;
		}
	}
}

void Mode2() {
	int numb, x = 500, count = 1, y = 250;
	printf("2 mode is selected \n");
	printf("Guess the number from 1 to 1000: \n");

	while (1) {
		char sign;
		printf("this number is greater than(>).less than(<) or equal to(=) than: %d", x);
		scanf_s(" %c", &sign);
		if (sign == '>') {
			x -= y;
			count++;
		}

		else if (sign == '<') {
			x += y;
			count++;
		}

		else if (sign == '=') {
			printf("Attempts used: %d", count);
			break;
		}
		else {
			printf("Input error \n");
		}
		y = y / 2;
		if (x % 2 == 1) {
			y += 1;
		}

	}
}