#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int n, a, b = 0, c = 0, d = 0;
    printf("Введите длину числа(от 2 до 5)");
    scanf_s("%d", &n);
    a = rand() % ((pow(10, n - 1)) - pow(10, n)));
    if (n == 2)
    {
        float arr1 = { a / 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("Введите число");
            scanf_s("%d", &b);
            float arr2 = { b / 10, b % 10 };
            for (int i = 0, i < n, i++)
                for (int k = 0, k < n, k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf('количество коров %d', d);
            printf('количество быков %d', c);
        }
        printf('Вы победили!');
    }
    if (n == 3)
    {
        float arr1 = { a / 100, (a % 100) % 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("Введите число");
            scanf_s("%d", &b);
            float arr2 = { b / 100, (b % 100) % 10, b % 10 };
            for (int i = 0, i < n, i++)
                for (int k = 0, k < n, k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf('количество коров %d', d);
            printf('количество быков %d', c);
        }
        printf('Вы победили!');
    }
    if (n == 4)
    {
        float arr1 = { a / 1000, (a / 100) % 10, (a % 100) % 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("Введите число");
            scanf_s("%d", &b);
            float arr2 = { b / 1000, (b / 100) % 10, (b % 100) % 10, b % 10 };
            for (int i = 0, i < n, i++)
                for (int k = 0, k < n, k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf('количество коров %d', d);
            printf('количество быков %d', c);
        }
        printf('Вы победили!');
    }
    if (n == 5)
    {
        float arr1 = { a / 10000, (a / 1000) % 10, (a / 100) % 10, (a % 100) % 10, a % 10 };
        while (c != n)
        {
            c = 0;
            d = 0;
            printf("Введите число");
            scanf_s("%d", &b);
            float arr2 = { b / 10000, (b / 1000) % 10, (b / 100) % 10, (b % 100) % 10, b % 10 };
            for (int i = 0, i < n, i++)
                for (int k = 0, k < n, k++)
                {
                    if ((arr2[i] == arr1[k]) && (i != k))
                        d++;
                    if ((arr2[i] == arr1[k]) && (i == k))
                        c++;
                }
            printf('количество коров %d', d);
            printf('количество быков %d', c);
        }
        printf('Вы победили!');
    }
}


        
    