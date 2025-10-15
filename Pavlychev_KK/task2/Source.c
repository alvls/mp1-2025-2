#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
    int flage = 0, max, min, cnt, tr, mid;
    printf("vibirite reshim(1 or 2).napishite nomer reshima:\n");
    scanf_s("%i", &flage);
    min = 1;
    max = 999;
    if (flage == 1) {
        int random_n = rand() % (max - 1) + 1;
        printf("%i", random_n);
        system("pause");
        printf("ygadaite chislo\n");
        while (1 == 1) {
            scanf_s("%i", &tr);
            cnt++;
            if (tr == random_n) {
                printf("ygadali!!!\n");
                printf("chislo popitok:");
                printf("%i", cnt);
                return 0;
            }
            else if (tr > random_n) {
                printf("zagadannoe chislo menshe\n");
                printf("poprobyite eshe\n");
            }
            else {
                printf("zagadannoe chislo bolshe\n");
                printf("poprobyite eshe\n");
            }
        }
    }
    else if (flage == 2) {
        printf("zagadaite 1 <= chislo < 1000\n");
        printf("500?\n");
        printf("napishi dogatky(<, >, =):\n");
        mid = 500;
        char rez;
        while (0 == 0) {
            scanf_s("%c", &rez);
            switch (rez) {
            case 60:
                min = mid;
                mid = (min + max) / 2;
                printf("%i", mid);
                printf("?\n");
                cnt++;
                break;
            case 62:
                max = mid;
                mid = (min + max) / 2;
                printf("%i", mid);
                printf("?\n");
                cnt++;
                break;
            case 61:
                printf("YRAA!\n");
                printf("chislo popitok:");
                cnt++;
                printf("%i", cnt);
                break;
            default:
                break;
            }
        }
    }
    else {
        printf("Oshibka vvoda");
    }
    return 0;
}