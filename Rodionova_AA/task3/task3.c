#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int n, a, b = 0, c = 0, d = 0, p = 1000;
    printf("������� ����� �����(�� 2 �� 5) ");
    scanf_s(" %i", &n);
    float arr1[5] = { 0 };
    arr1[n - 1] = 1 + rand() % (10 - 1);
    while (p != 0)
    {
        p = 0;
        for (int i = 0; i < n - 1; i++)
            arr1[i] = rand() % (10 - 0);
        for (int k = 0; k < n; k++)
            for (int l = 1; l < n - 1; l++)
                if ((arr1[k] == arr1[l]) && (l != k))
                    p = 1;
    }
    while (c != n)
    {
        c = 0;
        d = 0;
        printf("������� ����� \n");
        scanf_s("%d", &b);
        float arr2[5] = { 0 };
        for (int i = 0; i < n; i++)
        {
            arr2[i] = b % 10;
            b = b / 10;
        }
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
            {
                if ((arr2[i] == arr1[k]) && (i != k))
                    d++;
                if ((arr2[i] == arr1[k]) && (i == k))
                    c++;
            }
        printf("���������� ����� %d \n", d);
        printf("���������� ����� %d \n", c);
    }
    printf("�� ��������! \n");
}
        



















#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int n, a, b = 0, c = 0, d = 0;
    printf("������� ����� �����(�� 2 �� 5) ");
    scanf_s(" %i", &n);
    if (n == 2)
    {
        a = 10 + rand() % (100 - 10);
        while (a / 10 == a % 10)
            a = 10 + rand() % (100 - 10);
        float arr1[] = { a / 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("������� ����� \n");
            scanf_s("%d", &b);
            float arr2[] = { b / 10, b % 10 };
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf("���������� ����� %d \n", d);
            printf("���������� ����� %d \n", c);
        }
        printf("�� ��������!");
    }
    if (n == 3)
    {
        a = 100 + rand() % (1000 - 100);
        while (!((a / 100 != a % 10) && (a / 100 != (a % 100) / 10) && ((a % 100) / 10 != a % 10) && (a / 100 != a % 10)))
            a = 100 + rand() % (1000 - 100);
        float arr1[] = { a / 100, (a % 100) / 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("������� ����� \n");
            scanf_s("%d", &b);
            float arr2[] = { b / 100, (b % 100) / 10, b % 10 };
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf("���������� ����� %d \n", d);
            printf("���������� ����� %d \n", c);
        }
        printf("�� ��������! \n");
    }
    if (n == 4)
    {
        a = 1000 + rand() % (10000 - 1000);
        while (!((a / 1000 != a % 10) && (a / 1000 != (a / 100) % 10) && (a / 1000 != (a % 100) / 10) && (a / 1000 != a % 10) &&
            ((a / 100) % 10 != (a % 100) / 10) && ((a / 100) % 10 != a % 10) && ((a % 100) / 10 != a % 10)))
            a = 1000 + rand() % (10000 - 1000);
        float arr1[] = { a / 1000, (a / 100) % 10, (a % 100) / 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("������� ����� \n");
            scanf_s("%d", &b);
            float arr2[] = { b / 1000, (b / 100) % 10, (b % 100) / 10, b % 10 };
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf("���������� ����� %d \n", d);
            printf("���������� ����� %d \n", c);
        }
        printf("�� ��������!");
    }
    if (n == 5)
    {
        a = 10000 + rand() % (100000 - 10000);
        while (!(((a / 1000) % 10 != a % 10) && ((a / 1000) % 10 != (a / 100) % 10) && ((a / 1000) % 10 != (a % 100) / 10) &&
            ((a / 100) % 10 != (a % 100) / 10) && ((a / 100) % 10 != a % 10) && ((a % 100) / 10 != a % 10) &&
            (a / 10000 != a % 10) && (a / 10000 != (a / 100) % 10) && (a / 10000 != (a % 100) / 10) && (a / 10000 != (a / 1000) % 10)))
            a = 10000 + rand() % (100000 - 10000);
        float arr1[] = { a / 10000, (a / 1000) % 10, (a / 100) % 10, (a % 100) / 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("������� ����� \n");
            scanf_s("%d", &b);
            float arr2[] = { b / 10000, (b / 1000) % 10, (b / 100) % 10, (b % 100) / 10, b % 10 };
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf("���������� ����� %d \n", d);
            printf("���������� ����� %d \n", c);
        }
        printf("�� ��������!");
    }
}
