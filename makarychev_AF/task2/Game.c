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
		printf("�������� ����� ����\n0 ����� �� ����\n1 �� ����������\n2 �� �����������\n��� �����:");
		scanf_s("%i", &num);
		switch (num)
		{
			case 0:
			{
				printf("������� �� ����!");
				break;
			}
			case 1:
			{
				zag = 1 + rand() % 1000;
				while (zag != otg)
				{
					printf("�������� �������������: ");
					scanf_s("%i", &otg);
					count++;
					if (otg < zag)
						printf("���������� ����� ������\n");
					else
						if (otg > zag)
							printf("���������� ����� ������\n");
				}
				printf("�� ��������!������������� �������: %d\n",count);
				break;
			}
			case 2:
			{
				printf("��������� ����� �� 1 �� 1000: ");
				scanf_s("%d", &zag);
				b = 1; a = 1001;
				printf("�������� ����� ���������:\n1 �������(����� ����������� ���������)\n2 �������(�������� �����)\n��� �����:");
				scanf_s("%i", &dif);
				switch (dif)
				{
				case 1:
					do
					{
						otg = b + rand() % (a - b + 1);
						count++;
						printf("�� �������������: %d\n��� ������?������?�����?", otg);
						scanf_s(" %c", &cha, 1);
						switch (cha)
						{
							case '<':b = otg;break;
							case '>':a = otg;break;
							case '=':
								printf("� ������� �����! � ���� ���������� �� %d �������\n", count);
								break;
						}

					} while (cha != '=');
					break;
				case 2:
					do
					{
						otg = ((a - b) / 2) - ((a - b) % 2) + b;
						count++;
						printf("�� �������������: %d\n��� ������?������?�����?", otg);
						scanf_s(" %�", &cha, 1);
						switch (cha)
						{
							case '<':b = otg;break;
							case '>':a = otg;break;
							case '=':
								printf("� ������� �����! � ���� ���������� �� %d �������\n", count);
								break;
						}

					} while (cha != '=');
				}

			}
		}
	} while ( num != 0);
}