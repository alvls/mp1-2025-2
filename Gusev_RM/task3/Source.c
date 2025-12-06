#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void main() {
    int n, number[5] = { 0 }, chek1 = 0, ot = 0;
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    printf("========================================\n");
    printf("Добро пожаловать в игру: <Быки и коровы>\n");
    printf("========================================\n");
    SetConsoleTextAttribute(hConsole, 6);
    printf("\nПравила:\n");
    printf("1. Вы выбирвете длину числа - n (от 2 до 5)\n");
    printf("2. Я загадываю n-значное число с неповторяющимися цифрами\n");
    printf("3. Вы вводите ваш вариант ответа n-значного числа\n");
    printf("4. сколько цифр угадано без совпадения с их позициями в загаданном числе (то есть количество коров)\n");
    printf("и сколько угадано вплоть до позиции в загаданном числе (то есть количество быков)\n");
    printf("5. Играем пока вы не угадаете число\n");
    SetConsoleTextAttribute(hConsole, 2);
    printf("\nИграем, введите число n\n");
    SetConsoleTextAttribute(hConsole, 7);
    scanf_s("%d", &n);
    number[0] = rand() % 9 + 1;;
    while (chek1 < 20) {
        for (int i = 1; i < 5; i++) {
            number[i] = rand() % 10;
        }
        for (int i = 1; i < 5; i++) {
            for (int ii = 0; ii < i; ii++) {
                if (number[i] != number[ii]) {
                    chek1 += 1;
                }
                else {
                    chek1 = 0;
                    continue;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        ot = ot * 10 + number[i];
    }
    //printf("%d\n", ot);
    int chek2 = 0, var, number2[5] = { 0 }, bull = 0, cow = 0;
    while (chek2 == 0) {
        SetConsoleTextAttribute(hConsole, 7);
        printf("\nВведите ваш вариант ответа\n");
        scanf_s("%d", &var);
        for (int i = n - 1; i != -1; i--) {
            number2[i] = var % 10;
            var = var / 10;
        }
        for (int i = 0; i < n; i++) {
            if (number[i] == number2[i]) {
                bull += 1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int ii = 0; ii < n; ii++) {
                if (number[i] == number2[ii]) {
                    cow += 1;
                }
            }
        }
        cow = cow - bull;
        if (bull == n) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("Поздравляю, вы угадали число\n");
            SetConsoleTextAttribute(hConsole, 7);
            chek2 = 1;
            break;
        }
        if (bull == 1 && cow == 1) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i бык", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i корова\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull >= 2 && bull <= 4 && 2 <= cow && cow <= 4) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быка", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коровы\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull >= 2 && bull <= 4 && cow == 1) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быка", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i корова\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 1 && cow >= 2 && cow <= 4) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i бык", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коровы\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 5 && cow == 5) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быков", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коров\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 0 && cow == 5) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быков", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коров\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 0 && cow == 1) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быков", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i корова\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 0 && cow >= 2 && cow <= 4) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быков", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коровы\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 1 && cow == 0) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i бык", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коров\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull >= 2 && bull <= 4 && cow == 0) {
            SetConsoleTextAttribute(hConsole, 2);
            printf("В вашем числе %i быка", bull);
            SetConsoleTextAttribute(hConsole, 6);
            printf(" и %i коров\n", cow);
            SetConsoleTextAttribute(hConsole, 7);
        }
        if (bull == 0 && cow == 0) {
            SetConsoleTextAttribute(hConsole, 4);
            printf("В вашем чиле нет быков и коров\n");
            SetConsoleTextAttribute(hConsole, 7);
        }
        cow = 0;
        bull = 0;

    }
    system("pause");
}