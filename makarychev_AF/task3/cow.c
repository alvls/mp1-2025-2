#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	char* locale = setlocale(LC_ALL, "");
	srand(time(NULL));
	int len,num[5];
	scanf_s("%d", &len);

	
}