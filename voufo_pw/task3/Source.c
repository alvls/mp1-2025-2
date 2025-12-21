#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_N 5

// Helper function: check if a digit already exists in array
bool contains(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

int main() {
    int n;
    printf("Enter length of number (2–5): ");
    scanf("%d", &n);

    if (n < 2 || n > MAX_N) {
        printf("Invalid length.\n");
        return 1;
    }

    srand(time(NULL));

    int secret[MAX_N];
    int i = 0;

    // --- Generate random number with unique digits ---
    while (i < n) {
        int digit = rand() % 10;
        if (i == 0 && digit == 0) continue;      // no leading zero
        if (!contains(secret, i, digit)) {
            secret[i] = digit;
            i++;
        }
    }

    printf("I've chosen a %d-digit number with unique digits. Try to guess!\n", n);

    int guess[MAX_N];
    int bulls, cows;
    char input[10];

    // --- Game loop ---
    do {
        printf("Enter your %d-digit guess: ", n);
        scanf("%s", input);

        // check input validity
        int len = 0;
        for (; input[len] != '\0'; len++);
        if (len != n) {
            printf("❌ Wrong length! Try again.\n");
            continue;
        }

        // convert to digits
        for (i = 0; i < n; i++) {
            guess[i] = input[i] - '0';
        }

        // count bulls and cows
        bulls = cows = 0;
        for (i = 0; i < n; i++) {
            if (guess[i] == secret[i])
                bulls++;
            else if (contains(secret, n, guess[i]))
                cows++;
        }

        printf("Result → Bulls: %d, Cows: %d\n", bulls, cows);

    } while (bulls != n);

    printf(" You guessed the number! Congratulations!\n");
    return 0;
}