#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define MAX_LENGTH 5
#define MIN_LENGTH 2
int wherey(void) {
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (Console == INVALID_HANDLE_VALUE)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    if (GetConsoleScreenBufferInfo(Console, &buf))
        return buf.dwCursorPosition.Y;
    return -1;
}
typedef struct {
    int X;
    int Y;
} XY;
XY WhereXY(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    XY pos = { 0, 0 };
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        pos.X = consoleInfo.dwCursorPosition.X;
        pos.Y = consoleInfo.dwCursorPosition.Y;
    }
    return pos;
}
int contains_digit(int arr[], int size, int digit)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == digit)
            return 1;
    }
    return 0;
}
void generate_number(int length, int number[])
{
    int digits[10];
    for (int i = 0; i < 10; i++)
    {
        digits[i] = i;
    }
    for (int i = 9; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int t = digits[i];
        digits[i] = digits[j];
        digits[j] = t;
    }
    if (digits[0] == 0)
    {
        for (int i = 1; i < 10; i++)
        {
            if (digits[i] != 0)
            {
                int t = digits[0];
                digits[0] = digits[i];
                digits[i] = t;
                break;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        number[i] = digits[i];
    }
}
int validate_input(char input[], int length)
{
    if (strlen(input) != length)
        return 0;
    int digits[10] = { 0 };
    for (int i = 0; i < length; i++)
    {
        if (input[i] < '0' || input[i] > '9')
            return 0;
        int digit = input[i] - '0';
        if (digits[digit])
            return 0;
        digits[digit] = 1;
    }
    return 1;
}
void count_bulls_cows(int number[], int guess[], int length, int* bulls, int* cows)
{
    *bulls = 0;
    *cows = 0;
    for (int i = 0; i < length; i++)
    {
        if (guess[i] == number[i])
        {
            (*bulls)++;
        }
        else if (contains_digit(number, length, guess[i]))
        {
            (*cows)++;
        }
    }
}
void textcolor(int color) {
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (Console == INVALID_HANDLE_VALUE)
        return;

    SetConsoleTextAttribute(Console, color);
}
int main()
{
    int n;
    printf("Enter the length of the hidden number (from 2 to 5): ");
    scanf_s("%d", &n);
    if (n < MIN_LENGTH || n > MAX_LENGTH)
    {
        textcolor(12);
        printf("Incorrect length.\n");
        textcolor(7);
        return 1;
    }
    srand(time(NULL));
    int number[MAX_LENGTH];
    generate_number(n, number);
    printf("Guess the number!\n", n);
    while (1)
    {
        char input[100];
        printf("Print a number: ");
        scanf_s("%s", input, sizeof(input));
        if (!validate_input(input, n))
        {
            textcolor(14);
            printf("Error. Make sure that the number consists of different DIGITS or selected length = the length of the entered number.\n", n);
            textcolor(7);
            continue;
        }
        int guess[MAX_LENGTH];
        for (int i = 0; i < n; i++)
            guess[i] = input[i] - '0';
        int bulls = 0, cows = 0;
        count_bulls_cows(number, guess, n, &bulls, &cows);
        printf("Bulls: %d, Cows: %d\n", bulls, cows);
        if (bulls == n)
        {
            textcolor(10);
            printf("You are right!\n");
            textcolor(7);
            break;
        }
        else {
            textcolor(15);
        }
    }
    return 0;
}