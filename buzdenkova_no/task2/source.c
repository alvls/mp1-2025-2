#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Mode1();
void Mode2();
int main()
{
    int choice;
    printf(":\n");
    printf("Mode 1. Guess the number.\n");
    printf("Mode 2. Come up with a number.\n");
    printf("Select a mode 1 or a mode 2: ");
    scanf_s("%d", &choice);
    if (choice != 1 && choice != 2)
    {
        printf("Error. Try again.\n");
        return 1;
    }
    srand(time(NULL));
    if (choice == 1)
    {
        Mode1();
    }
    else
    {
        Mode2();
    }
    return 0;
}
void Mode1()
{
    int a = 1, b = 1000;
    int g, c = 0;
    int numb;
    numb = rand() % (b - a) + a;
    printf("Mode 1. Guess the number from 1 to 999.\n");
    while (1)
    {
        printf("Print a numder: ");
        scanf_s("%d", &g);
        c++;
        if (g < numb)
        {
            printf("The number is greater.\n");
        }
        else if (g > numb)
        {
            printf("The number is less.\n");
        }
        else
        {
            printf("You're right! Number of attempts: %d.\n", c);
            break;
        }
    }
}
void Mode2()
{
    int a = 1, b = 1000, c = 0;
    int g;
    char ans;
    printf("Mode 2: Come up with a number.\n");
    printf("Print a numder: ");
    scanf_s("%d", &g);
    if (g < a || g >= b)
    {
        printf("Error. Number < 1 or > 1000.\n");
        return;
    }
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        c++;
        printf("Is this your number?: %d\n", mid);
        printf("Number greater, less or equal? (> / < / =): ");
        scanf_s(" %c", &ans);
        if (ans == '=')
        {
            printf("Computer is right! Number of attempts: %d\n", c);
            break;
        }
        else if (ans == '>')
        {
            a = mid + 1;
        }
        else if (ans == '<')
        {
            b = mid - 1;
        }
        else
        {
            printf("Error. Try adain. (print >, <, =)\n");
            c--;
        }
    }
}