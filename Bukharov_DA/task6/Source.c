#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef double (*taylor_func)(double x, int n);

long long factorial(int n) {
    long long result = 1;
    int i;
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n > 0) {
        for (i = 1; i <= n; i++) {
            result *= i;
        }
    }
    return result;

}

double power(double x, int n) {
    double result = 1.0;
    int i;
    if (n == 0) return 1;
    if (n < 0)
        return 1.0 / power(x, -n);
    for (i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}


double taylor_sin(double x, int n) {
    double sum = 0.0;
    int i;
    double term;
    int sign;

    for (i = 0; i < n; i++) {
        if (i % 2 == 0) {
            sign = 1;
        }
        else {
            sign = -1;
        }
        term = sign * power(x, 2 * i + 1) / factorial(2 * i + 1);
        sum += term;
    }
    return sum;
}

double taylor_cos(double x, int n) {
    double sum = 0.0;
    int i;
    double term;
    int sign;

    for (i = 0; i < n; i++) {
        if (i % 2 == 0) {
            sign = 1;
        }
        else {
            sign = -1;
        }

        term = sign * power(x, 2 * i) / factorial(2 * i);
        sum += term;
    }
    return sum;
}

double taylor_exp(double x, int n) {
    double sum = 0.0;
    int i;
    double term;

    for (i = 0; i < n; i++) {
        term = power(x, i) / factorial(i);
        sum += term;
    }
    return sum;
}

double taylor_arcsin(double x, int n) {
    double sum = 0.0;
    int i;
    double term = 0.0;
    long long numerator, denominator;

    if (fabs(x) > 1.0) {
        return NAN;
    }

    if (n > 0) {
        term = x;
        sum = term;

        for (i = 1; i < n; i++) {
            double multiplier = (2 * i - 1) * (2 * i - 1) * x * x / (2 * i * (2 * i + 1));
            term *= multiplier;
            sum += term;
        }
    }

    return sum;
}


int get_int_input() {
    int value;
    int result;

    while (1) {
        result = scanf_s("%d", &value);
        if (result == 1) {
            while (getchar() != '\n');
            return value;
        }
        else {
            printf("Error! Enter an integer: ");
            while (getchar() != '\n');
        }
    }
}

double get_double_input() {
    double value;
    int result;

    while (1) {
        result = scanf_s("%lf", &value);
        if (result == 1) {
            while (getchar() != '\n');
            return value;
        }
        else {
            printf("Error! Enter a number like 1.5 or 0.01");
            while (getchar() != '\n');
        }
    }
}


int main() {
    int mode, func_choice, n_max, i, n_terms_used;
    double x, eps, result, reference, diff, previous;


    taylor_func taylor_functions[4] = {
        taylor_sin,
        taylor_cos,
        taylor_exp,
        taylor_arcsin
    };

    char* function_names[4] = { "sin", "cos", "exp", "arcsin" };
    double (*reference_functions[4])(double) = { sin, cos, exp, asin };


    printf("=== A program for calculating functions using Taylor series ===\n");

    while (1) {
        printf("=======================================================\n");
        printf("Please, select a mode\n");
        printf("1 - Single function calculation\n");
        printf("2 - Series of experiments\n");
        printf("3 - Exit the program\n");
        printf("Your choice: ");

        mode = get_int_input();

        if (mode == 3) {
            printf("Goodbye!\n");
            break;
        }
        else if (mode != 1 && mode != 2 && mode != 3) {
            printf("Error! Please, choose 1, 2 or 3\n");
            continue;
        }

        printf("Please, choose a function to calculate: \n");
        printf("1 - sin(x)\n");
        printf("2 - cos(x)\n");
        printf("3 - exp(x)\n");
        printf("4 - arcsin(x)\n");
        printf("Your choice: ");

        func_choice = get_int_input();

        if (func_choice < 1 || func_choice > 4) {
            printf("Error! Please, choose 1, 2, 3 or 4\n");
            continue;
        }

        printf("\nEnter the value of x: ");
        x = get_double_input();

        if (func_choice == 4) {
            if (x < -1.0 || x > 1.0) {
                printf("Warning! For arcsin(x) it must be -1 <= x <= 1\n");
                printf("x will be limited to the range [-1; 1]\n");
                if (x < -1.0) x = -1.0;
                if (x > 1) x = 1.0;
            }
        }

        if (mode == 1) {
            printf("\n--- Mode 1: Single function calculation ---\n");
            printf("Enter calculation accuracy (for example, 0.0001): ");

            eps = get_double_input();
            if (eps <= 0) {
                printf("Invalid accuracy value. Must be positive. Setting to 0.0001\n");
                eps = 0.0001;
            }

            printf("Enter maximum number of terms (from 1 to 1000): ");
            n_max = get_int_input();

            if (n_max < 1) {
                printf("Too few terms! Set to 1\n");
                n_max = 1;
            }
            if (n_max > 1000) {
                printf("Too many terms! Set to 1000\n");
                n_max = 1000;
            }

            reference = reference_functions[func_choice - 1](x);

            result = 0.0;
            n_terms_used = 0;
            previous = 0.0;

            for (i = 1; i <= n_max; i++) {
                result = taylor_functions[func_choice - 1](x, i);

                if (i > 1) {
                    if (fabs(result - previous) < eps) {
                        n_terms_used = i;
                        printf("Accuracy reached at %d term\n", i);
                        break;
                    }
                }
                previous = result;
            }
            if (n_terms_used == 0) {
                n_terms_used = n_max;
                printf("Accuracy not reached after %d terms\n", n_max);
            }
            diff = result - reference;

            printf("\n========== RESULTS ==========\n");
            printf("Function: ");


            printf("%s", function_names[func_choice - 1]);
            printf("(%.6f)\n", x);

            printf("Reference value: %.10f\n", reference);
            printf("Approximate value: %.10f\n", result);
            printf("Difference: %.10f\n", diff);
            printf("Terms used: %d out of %d\n", n_terms_used, n_max);
            printf("Accuracy: %.10f\n", eps);
        }
        else if (mode == 2) {
            printf("\n--- Mode 2: Series of experiment ---\n");
            printf("Enter number of experiments (from 1 to 25): ");

            n_max = get_int_input();
            if (n_max < 1) {
                printf("Too few experiments! Set to 1\n");
                n_max = 1;
            }
            if (n_max > 25) {
                printf("Too many experiments! Set to 25\n");
                n_max = 25;
            }
            reference = reference_functions[func_choice - 1](x);

            printf("\n============== EXPERIMENT RESULTS ==============\n");
            printf("Function: ");
            printf("%s", function_names[func_choice - 1]);
            printf("(%.6f)\n", x);

            printf("Reference value: %.10f\n\n", reference);
            printf("---------------------------------------------\n");
            printf("|  n |   Approximate value   |      Error    |\n");
            printf("|----|-----------------------|---------------|\n");

            for (i = 1; i <= n_max; i++) {
                result = taylor_functions[func_choice - 1](x, i);

                diff = result - reference;

                printf("|%4d|%20.10f |%18.10f|\n", i, result, diff);
            }
            printf("--------------------------------------------\n");


        }
    }
    return 0;
}