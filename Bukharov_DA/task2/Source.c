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
		printf("�������� ����� ����:\n");
		printf("1 - �� ���������� �����\n");
		printf("2 - ��������� ��������� �����\n");
		printf("��� �����: ");
		scanf_s("%d", &gamemode);
		if (gamemode == 1) {
			printf("����� 1\n");
			rnum = rand() % 999 + 1;
			while (answer == 0) {
				printf("���������� ������� �����, ������� � �������:\n");
				scanf_s("%d", &guess);
				if (guess == rnum) {
					printf("�� �������!\n���������� �������: %i\n", attempts);
					answer = 1;
				}
				else if (guess < rnum) {
					printf("���������� ����� ������\n");
					attempts += 1;
				}
				else if (guess > rnum) {
					printf("���������� ����� ������\n");
					attempts += 1;
				}
			}
		}
		else if (gamemode == 2) {
			printf("����� 2\n");
			printf("��������� ����� � ��������� �� 1 �� 1000 � ������� ���: ");
			//printf("????????? ?????????? ???????? ??? ?????, ??????? ????????? ?????????.???? ?????????? ????? ??????, ??????? '>',\n???? ?????????? ????? ??????, ??????? '<', ???? ????????? ???????? ???? ?????, ??????? '='\n");
			scanf_s("%d", &number);

			while (number > 1000 || number < 1) {
				printf("�� ����� ����� �� ���������� ���������. ������� ����� �� 1 �� 1000: ");
				scanf_s("%d", &number);
			}

			char comparison = '.';
			attempts = 1;
			answer = 0;

			while (answer == 0) {
				guess = (min + max) / 2;
				printf("��������� ������������, ��� ���� �����: %d\n", guess);
				printf("������� '>', '<' ��� '='\n");
				scanf_s(" %c", &comparison, 1);

				if (comparison == '=') {
					printf("����� �������\n");
					printf("���������� �������: %d\n", attempts);
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
					printf("�������� ����, ����������� ������ '>', '<' ��� '='\n");
				}
			}

		}
		else {
			printf("�������� �����!\n");
		}
		printf("\n������ ������� ��� ���? (y/n): ");
		scanf_s(" %c", &continue_playing, 1);
	}

	system("pause");
}