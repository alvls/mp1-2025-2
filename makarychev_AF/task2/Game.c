#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
void main()
{
	char* locale = setlocale(LC_ALL, "");
	int num=20,zag,otg=0,count,a=1001,b=1;
	char cha;
	do
	{
	count = 0;
	printf("Выберите режим игры\n0 выйти из игры\n1Вы угадываете\n2Вы загадываете\nВаш выбор:");
	scanf_s('%i', &num);
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
					printf("Сделайте предположение:");
					scanf_s("%d", &otg);
					count++;
					if (otg < zag)
						printf("Загаданное число больше");
					else
						if (otg > zag)
							printf("Загаданное число меньше");

				}
				printf("Вы отгадали!Использованно попыток: %d",count);
			}
			case 2:
			{
				printf("Загадайте число от 1 до 1000: ");
				scanf_s("%d", &zag);
				cha = "";
				while (cha!='=')
				{
					otg = b + rand() % (a-b+1);
					printf("Моё предположение: %d\nОно больше?Меньше?Верно?",otg);
					scanf_s("%c", &cha);
					count++;
					switch (cha)
					{
						case '<':
							b = otg;
							break;
						case '>':
							a = otg;
							break;
						case '=':
							printf("Я отгадал число! У меня получилось за %d попыток", count);
							break;

					}

				}

			}
		}
	} while ( num != 0);

}