#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int n, a, b = 0, c = 0, d = 0, p = 1000;
    printf("Введите длину числа(от 2 до 5) ");
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
        printf("Введите число \n");
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
        printf("количество коров %d \n", d);
        printf("количество быков %d \n", c);
    }
    printf("Вы победили! \n");
}

