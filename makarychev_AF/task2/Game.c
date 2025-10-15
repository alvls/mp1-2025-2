#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
void main()
{
	srand(time(NULL));
	char* locale = setlocale(LC_ALL, "");
	int num=20,zag,otg=0,count,a=1001,b=1,dif=0;
	char cha;
	do
	{
	count = 0;
	printf("Выберите режим игры\n0 выйти из игры\n1 Вы угадываете\n2 Вы загадываете\nВаш выбор:");
	scanf_s("%i", &num);
	switch (num)
		{
			case 0:
			{
			printf("Спасибо за игру!");
			break;
			}
			case 1:
			{
				zag = 1 + rand() % 1000;
				while (zag != otg)
				{
					printf("Сделайте предположение: ");
					scanf_s("%i", &otg);
					count++;
					if (otg < zag)
						printf("Загаданное число больше\n");
					else
						if (otg > zag)
							printf("Загаданное число меньше\n");

				}
				printf("Вы отгадали!Использованно попыток: %d\n",count);
				break;
			}
			case 2:
			{
				printf("Загадайте число от 1 до 1000: ");
				scanf_s("%d", &zag);
				b = 1; a = 1001;
				printf("Выбирете режим сложности:\n1 Простой(числа подбираются рандомнно)\n2 Сложный(бинарный поиск)\nВаш выбор:");
				scanf_s("%i", &dif);
				switch (dif)
				{
				case 1:
					do
					{
						otg = b + rand() % (a - b + 1);
						count++;
						printf("Моё предположение: %d\nОно больше?Меньше?Верно?", otg);
						scanf_s(" %c", &cha, 1);
						switch (cha)
						{
						case '<':b = otg;break;
						case '>':a = otg;break;
						case '=':
							printf("Я отгадал число! У меня получилось за %d попыток\n", count);
							break;

						}

					} while (cha != '=');
					break;
				case 2:
					do
					{
						otg = ((a - b) / 2) - ((a - b) % 2) + b;
						count++;
						printf("Моё предположение: %d\nОно больше?Меньше?Верно?", otg);
						scanf_s(" %c", &cha, 1);
						switch (cha)
						{
						case '<':b = otg;break;
						case '>':a = otg;break;
						case '=':
							printf("Я отгадал число! У меня получилось за %d попыток\n", count);
							break;

						}

					} while (cha != '=');
				}

			}
		}
	} while ( num != 0);

}