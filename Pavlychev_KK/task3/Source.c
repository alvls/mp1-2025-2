#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int contains(int arr[], int size, int digit) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == digit) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int n;
    int degit;
    int cnt_k;
    int cnt_b;
    int d;
    printf("napishite dliny zagadivaemogo chisla(2<=n<=5):");
    scanf_s("%i", &n);
    srand(time(NULL));
    int deg[5];
    int m[5];
    m[0] = rand() % 9 + 1;
    for (int i = 1; i < n; i++) {
        do {
            m[i] = rand() % 10;
        } while (contains(m, i, m[i]));
    }
    /*for(int i=0;i<n;i++){
        printf("%i", m[i]);
    }*/
    while (0 == 0) {
        cnt_k = 0;
        cnt_b = 0;
        //int korovi[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        //int biki[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        printf("poprpbyite otgatati chislo:");
        scanf_s("%i", &degit);
        for (int i = 0; i < n; i++) {
            deg[n - i - 1] = degit % 10;
            degit /= 10;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j && m[i] == deg[j]) {
                    cnt_b++;
                    break;
                }
                if (m[i] == deg[j]) {
                    cnt_k++;
                    break;
                }
            }
        }
        if (cnt_k == 0) {
            printf("korov net. ");
        }
        else {
            printf("korov = ");
            printf("%i ", cnt_k);
        }
        printf("\n");
        if (cnt_b == 0) {
            printf("bikov net.\n");
        }
        else {
            printf("bikov = ");
            printf("%i ", cnt_b);
        }
        printf("\n");
        if (cnt_b == n) {
            break;
        }
    }
    printf("Ti ygadal chislo!!!");
    return 0;
}