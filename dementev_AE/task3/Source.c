#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool numbArr(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] == arr[j])
				return false;
		}
	}
	return true;
}

int main() {
	int n, numb, x, countK, countB;
	int digits[5], nArr[5];// nArr - массив с рандомным числом
	printf("Set the range from 2 to 5 \n");
	scanf_s("%d", &n);
	srand(time(NULL));
	bool res = false;

	while (!res) {
		nArr[0] = rand() % 9 + 1;
		for (int i = 1; i < n; i++)
			nArr[i] = rand() % 10;
		res = numbArr(nArr, n);
		if (res)
			break;
	}
	//for (int i = 0; i < n; i++)
	//	printf("%d", nArr[i]);




	do {
		printf("BBedite chislo: \n");
		scanf_s("%d", &x);
		for (int i = n - 1; i >= 0; i--) {
			digits[i] = x % 10;
			x = x / 10;
		}
		countB = -1;
		countK = 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (nArr[i] == digits[j]) {
					if (i == j) {
						countB++;
						break;
					}
					else {
						countK++;
						break;
					}
				}
			}
		}
		printf("B: %d, K: %d \n", countB, countK);
	} while (countB != n);
	system("pause");
	return 0;
}