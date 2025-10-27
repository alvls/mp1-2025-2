#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char* locale = setlocale(LC_ALL, "");
    srand(time(NULL));
    int len;
    printf("Введите длину числа (2-5): ");
    scanf_s("%d", &len);

    // Проверка корректности длины
    if (len < 2 || len > 5) {
        printf("Неверная длина! Должна быть от 2 до 5.\n");
        return 1;
    }

    // Массивы для хранения загаданного числа и доступных цифр (размер массива "с запасом")
    int num[5];
    int available_digits[10] = { 0,1,2,3,4,5,6,7,8,9 };

    // Генерация загаданного числа с неповторяющимися цифрами
    for (int i = 0; i < len; i++) {
        int found = 0;
        while (!found) 
        {
            int index;
            if (i == 0) // Первая цифра не может быть 0
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
                available_digits[index] = -1; // цифра использована => помечаем
                found = 1;
            }
        }
    }

    printf("Компьютер загадал %d-значное число с неповторяющимися цифрами.\n", len);
    printf("Попробуйте угадать!\n");

    int attempts = 0;
    int guess[5];
    int game_over = 0;

    // Основной игровой цикл
    while (!game_over) 
    {
        attempts++;
        printf("\nПопытка #%d\n", attempts);
        // Ввод предположения игрока
        for (int i = 0; i < len; i++)
        {
            printf("Введите цифру на позиции %d: ", i + 1);
            scanf_s("%d", &guess[i]);

            // Проверка на корректность цифры
            if (guess[i] < 0 || guess[i] > 9) 
            {
                printf("Ошибка: цифра должна быть от 0 до 9!\n");
                i--; // Повторяем ввод для этой позиции
                continue;
            }
        }

        // Проверка на повторяющиеся цифры
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
            printf("Ошибка: цифры не должны повторяться!\n");
            attempts--;
            continue;
        }

        // Подсчет быков и коров
        int bulls = 0;
        int cows = 0;

        for (int i = 0; i < len; i++) 
        {
            if (guess[i] == num[i]) 
            {
                bulls++; // Цифра на правильной позиции
            }
            else 
            {
                for (int j = 0; j < len; j++) 
                {
                    if (guess[i] == num[j]) 
                    {
                        cows++; // Цифра есть в числе, но на неправильной позиции
                        break;
                    }
                }
            }
        }

        // Вывод результата
        printf("Результат: %d бык(ов), %d коров(а)\n", bulls, cows);

        if (bulls == len) 
        {
            printf("\nПоздравляем! Вы угадали число: ");
            for (int i = 0; i < len; i++) 
            {
                printf("%d", num[i]);
            }
            printf(" за %d попыток!\n", attempts);
            game_over = 1;
        }
    }

    return 0;
}