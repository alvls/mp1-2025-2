#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int mode;
    printf("�������� ����� ������:\n");
    printf("1 - ��������� ���������� �����\n");
    printf("2 - ������������ ���������� �����\n");
    printf("��� �����: ");
    scanf_s("%d", &mode);

    if (mode == 1) {
        int secret = rand() % 1000 + 1;
        int guess, attempts = 0;

        printf("\n��������� ������� ����� �� 1 �� 1000.\n");
        printf("���������� �������!\n\n");

        do {
            printf("������� ���� �������: ");
            scanf_s("%d", &guess);
            attempts++;

            if (guess < secret) {
                printf("���������� ����� ������\n");
            }
            else if (guess > secret) {
                printf("���������� ����� ������\n");
            }
            else {
                printf("�����������! �� ������� ����� %d\n", secret);
                printf("���������� �������: %d\n", attempts);
            }
        } while (guess != secret);

    }
    else if (mode == 2) {
        int min = 1, max = 1000;
        int guess, attempts = 0;
        char response;

        printf("\n��������� ����� �� 1 �� 1000.\n");
        printf("��������� ����� �������� �����.\n");
        printf("�������:\n");
        printf("> - ���� ���� ����� ������\n");
        printf("< - ���� ���� ����� ������\n");
        printf("= - ���� ��������� ������\n\n");

        do {
            guess = (min + max) / 2;
            attempts++;

            printf("��������� ������������: %d\n", guess);
            printf("��� �����: ");
            scanf_s(" %c", &response);

            if (response == '>') {
                min = guess + 1;
            }
            else if (response == '<') {
                max = guess - 1;
            }
            else if (response == '=') {
                printf("��������� ������ ����� %d!\n", guess);
                printf("���������� �������: %d\n", attempts);
            }
            else {
                printf("������������ ����. ����������� >, < ��� =\n");
                attempts--;
            }

            if (min > max) {
                printf("������ - ��� ���� �� �����\n");
                break;
            }

        } while (response != '=');

    }
    else {
        printf("������: ������ �������� �����\n");
        return 1;
    }

    return 0;
}