#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char* locale = setlocale(LC_ALL, "");
    srand(time(NULL));
    int len;
    printf("������� ����� ����� (2-5): ");
    scanf_s("%d", &len);

    // �������� ������������ �����
    if (len < 2 || len > 5) {
        printf("�������� �����! ������ ���� �� 2 �� 5.\n");
        return 1;
    }

    // ������� ��� �������� ����������� ����� � ��������� ���� (������ ������� "� �������")
    int num[5];
    int available_digits[10] = { 0,1,2,3,4,5,6,7,8,9 };

    // ��������� ����������� ����� � ���������������� �������
    for (int i = 0; i < len; i++) {
        int found = 0;
        while (!found) 
        {
            int index;
            if (i == 0) // ������ ����� �� ����� ���� 0
            {
                index = 1 + rand() % 9;
            }
            else 
            {
                index = rand() % 10;
            }

            if (available_digits[index] != -1) 
            {
                num[i] = available_digits[index];
                available_digits[index] = -1; // ����� ������������ => ��������
                found = 1;
            }
        }
    }

    printf("��������� ������� %d-������� ����� � ���������������� �������.\n", len);
    printf("���������� �������!\n");

    int attempts = 0;
    int guess[5];
    int game_over = 0;

    // �������� ������� ����
    while (!game_over) 
    {
        attempts++;
        printf("\n������� #%d\n", attempts);
        // ���� ������������� ������
        for (int i = 0; i < len; i++)
        {
            printf("������� ����� �� ������� %d: ", i + 1);
            scanf_s("%d", &guess[i]);

            // �������� �� ������������ �����
            if (guess[i] < 0 || guess[i] > 9) 
            {
                printf("������: ����� ������ ���� �� 0 �� 9!\n");
                i--; // ��������� ���� ��� ���� �������
                continue;
            }
        }

        // �������� �� ������������� �����
        int has_duplicates = 0;
        for (int i = 0; i < len; i++) 
        {
            for (int j = i + 1; j < len; j++) 
            {
                if (guess[i] == guess[j]) 
                {
                    has_duplicates = 1;
                    break;
                }
            }
            if (has_duplicates) break;
        }

        if (has_duplicates) 
        {
            printf("������: ����� �� ������ �����������!\n");
            attempts--;
            continue;
        }

        // ������� ����� � �����
        int bulls = 0;
        int cows = 0;

        for (int i = 0; i < len; i++) 
        {
            if (guess[i] == num[i]) 
            {
                bulls++; // ����� �� ���������� �������
            }
            else 
            {
                for (int j = 0; j < len; j++) 
                {
                    if (guess[i] == num[j]) 
                    {
                        cows++; // ����� ���� � �����, �� �� ������������ �������
                        break;
                    }
                }
            }
        }

        // ����� ����������
        printf("���������: %d ���(��), %d �����(�)\n", bulls, cows);

        if (bulls == len) 
        {
            printf("\n�����������! �� ������� �����: ");
            for (int i = 0; i < len; i++) 
            {
                printf("%d", num[i]);
            }
            printf(" �� %d �������!\n", attempts);
            game_over = 1;
        }
    }

    return 0;
}