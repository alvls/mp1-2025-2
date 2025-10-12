#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int a=0, b, c=1, d=0;
    int choice;
    char ch;
    do
    {
        printf("Режим 1: вы отгадываете число \n");
        printf("Режим 2: вы загадываете число \n");
        printf("Режим 0: выход из игры \n");
        printf("Выберите режим \n");
        a = 0;
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 0:
        {
            printf("Игра завершена");
            break;
        }
        case 1:
        {
            a = rand() % 1000;
            b = 100000;
            while (b != a)
            {
                printf("Введите число\n");
                scanf_s("%d", &b);
                if ((b > 0) && (b < 1000))
                {
                    if (b < a)
                        printf("Загаданное число больше\n");
                    if (b > a)
                        printf("Загаданное число меньше\n");
                }
                else
                    printf("ошибка ввода\n");
            }
            printf("Вы выиграли!\n");
            break;
        }
        case 2:
        {
            printf("Загадайте число от 1 до 1000\n");
            printf("Если загаданное число больше введите >\n");
            printf("Если загаданное число меньше введите <\n");
            printf("Если загаданное число равно введите =\n");
            b = 1000;
            do
            { 
                d =c+ rand() % (b - c + 1);
                printf("%d\n", d);
                scanf_s(" %c", &ch);
                switch (ch)
                {
                case '>':
                    c = d + 1;
                    break;
                case '<':
                    b = d - 1;
                    break;
                case '=':
                    printf("Ваше число отгадали\n");
                    a = 12345678;
                    break;
                }
            }while (a < 12345678);
            break;
        }
        }
    } while (choice != 0);
}




