#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
void main()
{
	char* locale = setlocale(LC_ALL, "");
	srand(time(NULL));
	int  num[5], num_choise[11] = { 0,1,2,3,4,5,6,7,8,9 }, num_guess[5];
	int len, i, a = rand() % 10, flag = 1, cow, bull, j;
	printf("Ââåäèòå äëèíó ÷èñëà: ");
	scanf_s("%d", &len);
	for (i=0; i <= len - 1; i++)
	{
		while ((num[i]>10)||(num[i]<0))
		{
			if (i==0) 
				a=1+ rand() % 10;
			else 
				a = rand() % 10;
			num[i] = num_choise[a];
			num_choise[a] = -1;
		}	
	}
	while (flag)
	{
		cow = 0;
		bull = 0;
		for (i = 0; i <= len - 1; i++)
		{
			printf("Êàêàÿ öèôðà ñòîèò íà ïîçèöèè %d: ", i+1);
			scanf_s("%d", &num_guess[i]);
			if 
				(num_guess[i] == num[i]) bull++;
			else 
				for (j = 0; j <= len - 1; j++) 
					if (num_guess[i] == num[j]) 
						cow++;
		}
		if (bull == len)
		{ 
			printf("Âû óãàäàëè ÷èñëî: "); 
			for (j = 0; j <= len - 1; j++) 
				printf("%d", num[j]);
			flag = 0;
		}
		else 
			printf("Êîëè÷åñòâî êîðîâ: %d\nÊîëè÷åñòâî áûêîâ: %d\n", cow, bull);
	}	
}
