#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int mode;
    printf("Choose mode (1 - you guess, 2 - computer guesses): ");
    scanf("%d", &mode);

    if (mode == 1) {
        srand(time(NULL));
        int secret = rand() % 999 + 1; // random number [1, 1000)
        int guess, attempts = 0;

        printf("I have chosen a number between 1 and 999. Try to guess!\n");

        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);
            attempts++;

            if (guess < secret)
                printf("The number is bigger!\n");
            else if (guess > secret)
                printf("The number is smaller!\n");
            else
                printf("You guessed it in %d attempts!\n", attempts);

        } while (guess != secret);
    }

    else if (mode == 2) {
        int low = 1, high = 999, attempts = 0;
        char response;
        int mid;

        printf("Think of a number between 1 and 999.\n");

        do {
            mid = (low + high) / 2;
            attempts++;
            printf("Is your number %d? (enter <, > or =): ", mid);
            scanf(" %c", &response);

            if (response == '<')
                high = mid - 1;
            else if (response == '>')
                low = mid + 1;
        } while (response != '=');

        printf("I guessed your number in %d attempts!\n", attempts);
    }

    else {
        printf("Invalid mode.\n");
    }

    return 0;
}