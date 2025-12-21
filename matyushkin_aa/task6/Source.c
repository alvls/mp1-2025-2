#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

#define EPS_MIN 0.000001
#define MAX_TERMS 1000
#define MAX_EXPERIMENTS 25

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef double (*MathFunc)(double, double, int, int*);

double sin_series(double x, double epsilon, int max_terms, int* terms_used);
double cos_series(double x, double epsilon, int max_terms, int* terms_used);
double exp_series(double x, double epsilon, int max_terms, int* terms_used);
double ctg_series(double x, double epsilon, int max_terms, int* terms_used);

double sin_exact(double x);
double cos_exact(double x);
double exp_exact(double x);
double ctg_exact(double x);

void single_calculation();
void series_experiment();
void print_menu();

void setRussianLocale() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
}

int main() {
    setRussianLocale();

    int choice;

    do {
        print_menu();
        printf("Выберите режим работы (0 - выход): ");
        (void)scanf("%d", &choice);

        switch (choice) {
        case 1:
            single_calculation();
            break;
        case 2:
            series_experiment();
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}

double sin_series(double x, double epsilon, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term;
    int sign = 1;

    *terms_used = 0;

    x = fmod(x, 2 * M_PI);
    if (x > M_PI) x -= 2 * M_PI;
    if (x < -M_PI) x += 2 * M_PI;

    term = x;

    for (int i = 1; i <= max_terms; i++) {
        sum += sign * term;
        (*terms_used)++;

        if (fabs(term) < epsilon && i > 1) {
            break;
        }

        term *= x * x / ((2 * i) * (2 * i + 1));
        sign = -sign;
    }

    return sum;
}

double cos_series(double x, double epsilon, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = 1.0;
    int sign = 1;

    *terms_used = 0;

    x = fmod(x, 2 * M_PI);
    if (x > M_PI) x -= 2 * M_PI;
    if (x < -M_PI) x += 2 * M_PI;

    term = 1.0;
    sum = term;
    (*terms_used)++;

    for (int i = 1; i < max_terms; i++) {
        if (fabs(term) < epsilon && i > 1) {
            break;
        }

        term *= x * x / ((2 * i - 1) * (2 * i));
        term *= -1;
        sum += term;
        (*terms_used)++;
    }

    return sum;
}

double exp_series(double x, double epsilon, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = 1.0;

    *terms_used = 0;

    sum = term;
    (*terms_used)++;

    for (int i = 1; i < max_terms; i++) {
        if (fabs(term) < epsilon && i > 1) {
            break;
        }

        term *= x / i;
        sum += term;
        (*terms_used)++;
    }

    return sum;
}

double ctg_series(double x, double epsilon, int max_terms, int* terms_used) {
    x = fmod(x, 2 * M_PI);
    if (x > M_PI) x -= 2 * M_PI;
    if (x < -M_PI) x += 2 * M_PI;

    if (fabs(x) < EPS_MIN || fabs(fabs(x) - M_PI) < EPS_MIN) {
        printf("Ошибка: ряд для ctg(x) расходится вблизи 0 и π*n\n");
        *terms_used = 0;
        return NAN;
    }

    double sum = 0.0;
    double x_squared = x * x;
    double term;

    sum = 1.0 / x;
    *terms_used = 1;

    double coefficients[] = {
        -1.0 / 3.0,
        -1.0 / 45.0,
        -2.0 / 945.0,
        -1.0 / 4725.0,
        -2.0 / 93555.0,
        -1382.0 / 638512875.0
    };

    double x_power = x;

    for (int i = 0; i < max_terms - 1 && i < 6; i++) {
        term = coefficients[i] * x_power;

        if (fabs(term) < epsilon && i > 0) {
            break;
        }

        sum += term;
        (*terms_used)++;

       
        x_power *= x_squared;
    }

    return sum;
}

double sin_exact(double x) {
    return sin(x);
}

double cos_exact(double x) {
    return cos(x);
}

double exp_exact(double x) {
    return exp(x);
}

double ctg_exact(double x) {
    if (fabs(sin(x)) < EPS_MIN) {
        return NAN;
    }
    return cos(x) / sin(x);
}

void single_calculation() {
    int func_choice, n;
    double x, epsilon;
    double exact_value, approx_value, difference;
    int terms_used;

    printf("\n=== РЕЖИМ 1: ОДНОКРАТНЫЙ РАСЧЕТ ===\n");
    printf("Выберите функцию:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. ctg(x)\n");
    printf("Ваш выбор: ");
    (void)scanf("%d", &func_choice);

    if (func_choice < 1 || func_choice > 4) {
        printf("Неверный выбор функции.\n");
        return;
    }

    printf("Введите значение x: ");
    (void)scanf("%lf", &x);

    printf("Введите точность расчета (>= %.6f): ", EPS_MIN);
    (void)scanf("%lf", &epsilon);

    if (epsilon < EPS_MIN) {
        printf("Точность слишком мала. Установлено минимальное значение: %.6f\n", EPS_MIN);
        epsilon = EPS_MIN;
    }

    printf("Введите максимальное количество слагаемых N (1-%d): ", MAX_TERMS);
    (void)scanf("%d", &n);

    if (n < 1 || n > MAX_TERMS) {
        printf("Недопустимое количество слагаемых. Установлено: %d\n", MAX_TERMS);
        n = MAX_TERMS;
    }

    MathFunc series_func;
    double (*exact_func)(double);

    switch (func_choice) {
    case 1:
        series_func = sin_series;
        exact_func = sin_exact;
        break;
    case 2:
        series_func = cos_series;
        exact_func = cos_exact;
        break;
    case 3:
        series_func = exp_series;
        exact_func = exp_exact;
        break;
    case 4:
        series_func = ctg_series;
        exact_func = ctg_exact;
        break;
    default:
        return;
    }

    exact_value = exact_func(x);
    approx_value = series_func(x, epsilon, n, &terms_used);

    if (isnan(exact_value) || isnan(approx_value)) {
        printf("Ошибка: функция не определена для данного x.\n");
        return;
    }

    difference = fabs(exact_value - approx_value);

    printf("\n=== РЕЗУЛЬТАТЫ ===\n");
    printf("Функция: ");
    switch (func_choice) {
    case 1: printf("sin(x)"); break;
    case 2: printf("cos(x)"); break;
    case 3: printf("exp(x)"); break;
    case 4: printf("ctg(x)"); break;
    }
    printf(" при x = %.6f\n", x);
    printf("Эталонное значение: %.10f\n", exact_value);
    printf("Вычисленное значение: %.10f\n", approx_value);
    printf("Разница: %.10f\n", difference);
    printf("Количество использованных слагаемых: %d\n", terms_used);
    printf("Заданная точность: %.6f\n", epsilon);
}

void series_experiment() {
    int func_choice, n_max;
    double x;
    double exact_value;

    printf("\n=== РЕЖИМ 2: СЕРИЙНЫЙ ЭКСПЕРИМЕНТ ===\n");
    printf("Выберите функцию:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. ctg(x)\n");
    printf("Ваш выбор: ");
    (void)scanf("%d", &func_choice);

    if (func_choice < 1 || func_choice > 4) {
        printf("Неверный выбор функции.\n");
        return;
    }

    printf("Введите значение x: ");
    (void)scanf("%lf", &x);

    printf("Введите количество экспериментов NMax (1-%d): ", MAX_EXPERIMENTS);
    (void)scanf("%d", &n_max);

    if (n_max < 1 || n_max > MAX_EXPERIMENTS) {
        printf("Недопустимое количество экспериментов. Установлено: %d\n", MAX_EXPERIMENTS);
        n_max = MAX_EXPERIMENTS;
    }

    MathFunc series_func;
    double (*exact_func)(double);
    const char* func_name;

    switch (func_choice) {
    case 1:
        series_func = sin_series;
        exact_func = sin_exact;
        func_name = "sin(x)";
        break;
    case 2:
        series_func = cos_series;
        exact_func = cos_exact;
        func_name = "cos(x)";
        break;
    case 3:
        series_func = exp_series;
        exact_func = exp_exact;
        func_name = "exp(x)";
        break;
    case 4:
        series_func = ctg_series;
        exact_func = ctg_exact;
        func_name = "ctg(x)";
        break;
    default:
        return;
    }


    exact_value = exact_func(x);

    if (isnan(exact_value)) {
        printf("Ошибка: функция не определена для данного x.\n");
        return;
    }


    printf("\n=== РЕЗУЛЬТАТЫ ДЛЯ %s при x = %.4f ===\n", func_name, x);
    printf("Эталонное значение: %.10f\n\n", exact_value);
    printf("%-10s %-25s %-25s\n",
        "Слагаемых", "Приближенное значение", "Разница");
    printf("------------------------------------------------------------\n");

    for (int n = 1; n <= n_max; n++) {
        int terms_used;
        double approx_value;

        approx_value = series_func(x, 1e-15, n, &terms_used);

        if (!isnan(approx_value)) {
            double difference = fabs(exact_value - approx_value);
            printf("%-10d %-25.10f %-25.10f\n",
                n, approx_value, difference);
        }
    }
}

void print_menu() {
    printf("\n==============================\n");
    printf("    КАЛЬКУЛЯТОР ФУНКЦИЙ\n");
    printf("==============================\n");
    printf("1. Однократный расчет\n");
    printf("2. Серийный эксперимент\n");
    printf("0. Выход\n");
    printf("==============================\n");
}