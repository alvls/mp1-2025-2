#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 Task 6: Taylor series calculator
 sin(x), cos(x), exp(x), tan(x) (tan computed as sin/cos)
 Modes:
  - Mode 1: compute with epsilon and max terms N
  - Mode 2: experiment table for 1..Nmax terms
*/

// function pointer type: (x, eps, pointer-to-used-terms, maxTerms)
typedef double (FuncPointer)(double, double, int, int);

/* Prototypes */
double taylor_sin(double x, double eps, int *used, int N);
double taylor_cos(double x, double eps, int *used, int N);
double taylor_exp(double x, double eps, int *used, int N);
double taylor_tan(double x, double eps, int *used, int N);

void mode1(FuncPointer f, double (*exact)(double));
void mode2(FuncPointer f, double (*exact)(double));

/* ------------------ Taylor implementations ------------------ */

double taylor_sin(double x, double eps, int *used, int N) {
    if (N < 1) { *used = 0; return 0.0; }
    double term = x;           // first term x^(2*0+1)/(2*0+1)! = x
    double sum = term;
    *used = 1;
    int n = 1;
    // iterate while term magnitude > eps and we haven't used N terms
    while (fabs(term) > eps && *used < N) {
        // recurrence: next term = term * ( - x^2 / ((2n)*(2n+1)) )
        term *= - (x * x) / ((2.0 * n) * (2.0 * n + 1.0));
        sum += term;
        (*used)++;
        n++;
    }
    return sum;
}

double taylor_cos(double x, double eps, int *used, int N) {
    if (N < 1) { *used = 0; return 0.0; }
    double term = 1.0;         // first term 1
    double sum = term;
    *used = 1;
    int n = 1;
    while (fabs(term) > eps && *used < N) {
        // recurrence: next term = term * ( - x^2 / ((2n-1)*(2n)) )
        term *= - (x * x) / ((2.0 * n - 1.0) * (2.0 * n));
        sum += term;
        (*used)++;
        n++;
    }
    return sum;
}

double taylor_exp(double x, double eps, int *used, int N) {
    if (N < 1) { *used = 0; return 0.0; }
    double term = 1.0;         // first term 1
    double sum = term;
    *used = 1;
    int n = 1;
    while (fabs(term) > eps && *used < N) {
        term *= x / (double)n; // recurrence term *= x/n
        sum += term;
        (*used)++;
        n++;
    }
    return sum;
}

/* Compute tan(x) via sin and cos Taylor approximations.
   We compute sin and cos up to N terms total (split not equal but we add used counts).
   If cosine is too close to zero we report NAN.
*/
double taylor_tan(double x, double eps, int *used, int N) {
    if (N < 1) { *used = 0; return NAN; }

    // To be conservative, compute sin and cos each using up to N terms (this duplicates work but stays simple)
    int used_s = 0, used_c = 0;
    double s = taylor_sin(x, eps, &used_s, N);
    double c = taylor_cos(x, eps, &used_c, N);

    *used = used_s + used_c;
    if (fabs(c) < 1e-14) {
        // cos too small -> tan undefined or huge; return NAN
        return NAN;
    }
    return s / c;
}

/* ------------------ Modes ------------------ */

void mode1(FuncPointer f, double (*exact)(double)) {
    double x, eps;
    int N;
    int used;

    printf("Enter x (radians): ");
    if (scanf("%lf", &x) != 1) { printf("Bad input\n"); return; }

    printf("Enter precision epsilon (e.g. 1e-8): ");
    if (scanf("%lf", &eps) != 1) { printf("Bad input\n"); return; }
    if (eps <= 0.0) { printf("Epsilon must be positive.\n"); return; }

    printf("Enter max number of terms N (1..1000): ");
    if (scanf("%d", &N) != 1) { printf("Bad input\n"); return; }
    if (N < 1) { printf("N must be >= 1\n"); return; }
    if (N > 1000) N = 1000;

    double approx = f(x, eps, &used, N);
    double realv = exact(x);

    printf("\n=== RESULT MODE 1 ===\n");
    printf("Exact value:       %.15lf\n", realv);
    printf("Taylor approx:     %.15lf\n", approx);
    printf("Absolute error:    %.15lf\n", fabs(realv - approx));
    printf("Terms used (approx): %d\n", used);
}

void mode2(FuncPointer f, double (*exact)(double)) {
    double x;
    int Nmax;
    int used;

    printf("Enter x (radians): ");
    if (scanf("%lf", &x) != 1) { printf("Bad input\n"); return; }

    printf("Enter number of experiments Nmax (1..25): ");
    if (scanf("%d", &Nmax) != 1) { printf("Bad input\n"); return; }
    if (Nmax < 1) { printf("Nmax must be >= 1\n"); return; }
    if (Nmax > 1000) Nmax = 1000;

    double realv = exact(x);

    printf("\n=== RESULT MODE 2 ===\n");
    printf("Exact value = %.15lf\n\n", realv);
    printf("%5s | %-25s | %s\n", "Terms", "Approximation", "Abs Error");
    printf("---------------------------------------------------------------\n");

    for (int n = 1; n <= Nmax; ++n) {
        double approx = f(x, 1e-15, &used, n); // give very small eps, limit by n
        double err = fabs(realv - approx);
        printf("%5d | %-25.15lf | %.15lf\n", n, approx, err);
    }
}

/* ------------------ main ------------------ */

int main(void) {
    int funcChoice;
    int mode;
    FuncPointer f = NULL;
    double (*exact)(double) = NULL;

    printf("Choose function:\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - exp(x)\n");
    printf("4 - tan(x)  (unique)\n");
    printf("Your choice: ");
    if (scanf("%d", &funcChoice) != 1) { printf("Bad input\n"); return 1; }

    switch (funcChoice) {
        case 1:
            f = taylor_sin; exact = sin; break;
        case 2:
            f = taylor_cos; exact = cos; break;
        case 3:
            f = taylor_exp; exact = exp; break;
        case 4:
            f = taylor_tan; exact = tan; break;
        default:
            printf("Invalid choice\n"); return 1;
    }

    printf("Choose mode:\n1 - one calculation (epsilon + N)\n2 - series experiment (1..Nmax)\nYour choice: ");
    if (scanf("%d", &mode) != 1) { printf("Bad input\n"); return 1; }

    if (mode == 1) mode1(f, exact);
    else if (mode == 2) mode2(f, exact);
    else printf("Invalid mode\n");

    return 0;
}