#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_LENGTH 5
#define MIN_LENGTH 2
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
int main()
{
    int n;
    printf("Enter the length of the hidden number (from 2 to 5): ");
    scanf_s("%d", &n);
    if (n < MIN_LENGTH || n > MAX_LENGTH)
    {
        printf("Incorrect length.\n");
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
            printf("Error. Make sure that the number consists of different DIGITS or selected length = the length of the entered number.\n", n);
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
            printf("You are right!\n");
            break;
        }
    }
    return 0;
}