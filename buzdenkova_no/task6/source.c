#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef double (*MathFunc)(double);

double ref_sin(double x) { return sin(x); }
double ref_cos(double x) { return cos(x); }
double ref_exp(double x) { return exp(x); }
double ref_cosh(double x) { return cosh(x); }

double taylor_sin(double x, int N, double eps, int* used)
{
    double term = x, sum = term;
    *used = 1;

    for (int n = 1; n < N; n++) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        (*used)++;
        if (fabs(term) < eps) break;
    }
    return sum;
}

double taylor_cos(double x, int N, double eps, int* used)
{
    double term = 1.0, sum = term;
    *used = 1;

    for (int n = 1; n < N; n++) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        (*used)++;
        if (fabs(term) < eps) break;
    }
    return sum;
}

double taylor_exp(double x, int N, double eps, int* used)
{
    double term = 1.0, sum = term;
    *used = 1;

    for (int n = 1; n < N; n++) {
        term *= x / n;
        sum += term;
        (*used)++;
        if (fabs(term) < eps) break;
    }
    return sum;
}

double taylor_cosh(double x, int N, double eps, int* used)
{
    double term = 1.0, sum = term;
    *used = 1;

    for (int n = 1; n < N; n++) {
        term *= x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        (*used)++;
        if (fabs(term) < eps) break;
    }
    return sum;
}

void print_func_menu(void)
{
    printf("0 - Выход\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - exp(x)\n");
    printf("4 - ch(x)\n");
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    int mode;
    printf("Выберите режим работы:\n");
    printf("0 - Выход\n");
    printf("1 - Однократный расчет\n");
    printf("2 - Серийный эксперимент\n");
    scanf("%d", &mode);

    if (mode == 0) {
        printf("Выход из программы.\n");
        return 0;
    }

    print_func_menu();

    int choice;
    scanf("%d", &choice);

    if (choice == 0) {
        printf("Выход из программы.\n");
        return 0;
    }

    MathFunc ref_func = NULL;
    double (*taylor_func)(double, int, double, int*) = NULL;

    switch (choice) {
    case 1: ref_func = ref_sin;  taylor_func = taylor_sin;  break;
    case 2: ref_func = ref_cos;  taylor_func = taylor_cos;  break;
    case 3: ref_func = ref_exp;  taylor_func = taylor_exp;  break;
    case 4: ref_func = ref_cosh; taylor_func = taylor_cosh; break;
    default:
        printf("Неверный выбор функции.\n");
        return 1;
    }

    double x;
    printf("Введите x: ");
    scanf("%lf", &x);

    double ref = ref_func(x);

    if (mode == 1) {
        double eps;
        int N;

        printf("Введите точность (>= 0.000001): ");
        scanf("%lf", &eps);
        printf("Введите число слагаемых (1..1000): ");
        scanf("%d", &N);

        int used = 0;
        double approx = taylor_func(x, N, eps, &used);

        printf("\nЭталонное значение: %.10lf\n", ref);
        printf("Вычисленное значение: %.10lf\n", approx);
        printf("Разница: %.10lf\n", fabs(ref - approx));
        printf("Количество слагаемых: %d\n", used);
    }
    else if (mode == 2) {
        int NMax;
        printf("Введите число экспериментов (1..25): ");
        scanf("%d", &NMax);

        printf("\nЭталонное значение: %.10lf\n", ref);
        printf("--------------------------------------------------\n");
        printf("| Слагаемые | Оценка значения | Разница |\n");
        printf("--------------------------------------------------\n");

        for (int i = 1; i <= NMax; i++) {
            int used = 0;
            double approx = taylor_func(x, i, 0.0, &used);
            printf("| %9d | %15.8lf | %8.2e |\n",
                i, approx, fabs(ref - approx));
        }

        printf("--------------------------------------------------\n");
    }
    else {
        printf("Неверный режим.\n");
    }

    return 0;
}