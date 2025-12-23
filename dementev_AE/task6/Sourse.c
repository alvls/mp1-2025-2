#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double taylor_sin(double x, int n);
double taylor_cos(double x, int n);
double taylor_exp(double x, int n);
double taylor_ln1px(double x, int n);
double get_reference_value(int func_choice, double x);
double calculate_n_terms(int func_choice, double x, int n);
double calculate_with_precision(int func_choice, double x, double epsilon, int max_terms, int* actual_terms);
void print_menu();
void mode_single();
void mode_series();

int main() {
    setlocale(LC_ALL, "Russian");
    int mode;

    printf("Программа вычисления функций через ряды Тейлора\n");
    printf("==============================================\n");
    printf("Разработано для функций: sin(x), cos(x), exp(x), ln(1+x)\n");

    do {
        print_menu();
        printf("Выберите режим (1-3): ");
        scanf_s("%d", &mode);
        clear_input_buffer();

        switch (mode) {
        case 1:
            mode_single();
            break;
        case 2:
            mode_series();
            break;
        case 3:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Ошибка: некорректный режим. Попробуйте снова.\n");
        }
    } while (mode != 3);

    return 0;
}

double normalize_angle(double x) {
    while (x > M_PI) {
        x -= 2 * M_PI;
    }
    while (x < -M_PI) {
        x += 2 * M_PI;
    }
    return x;
}

double taylor_sin(double x, int n) {
    double result = 0.0;
    double term = x;

    x = normalize_angle(x);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            term = x;
        }
        else {
            term = term * (-x * x) / ((2 * i) * (2 * i + 1));
        }
        result += term;
    }
    return result;
}

double taylor_cos(double x, int n) {
    double result = 0.0;
    double term = 1.0;

    x = normalize_angle(x);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            term = 1.0;
        }
        else {
            term = term * (-x * x) / ((2 * i - 1) * (2 * i));
        }
        result += term;
    }
    return result;
}

double taylor_exp(double x, int n) {
    double result = 0.0;
    double term = 1.0;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            term = 1.0;
        }
        else {
            term = term * x / i;
        }
        result += term;
    }
    return result;
}

double taylor_ln1px(double x, int n) {
    double result = 0.0;
    double term = x;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            term = x;
        }
        else {
            term = term * (-x) * i / (i + 1);
        }
        result += term;
    }
    return result;
}

double get_reference_value(int func_choice, double x) {
    switch (func_choice) {
    case 1: return sin(x);
    case 2: return cos(x);
    case 3: return exp(x);
    case 4: return log(1.0 + x);
    default: return 0.0;
    }
}

double calculate_n_terms(int func_choice, double x, int n) {
    switch (func_choice) {
    case 1: return taylor_sin(x, n);
    case 2: return taylor_cos(x, n);
    case 3: return taylor_exp(x, n);
    case 4: return taylor_ln1px(x, n);
    default: return 0.0;
    }
}

double calculate_with_precision(int func_choice, double x, double epsilon, int max_terms, int* actual_terms) {
    double result = 0.0;
    double term = 0.0;
    double prev_result = 0.0;
    int i;

    *actual_terms = 0;

    for (i = 0; i < max_terms; i++) {
        switch (func_choice) {
        case 1:  // sin(x)
            if (i == 0) {
                x = normalize_angle(x);
                term = x;
            }
            else {
                term = term * (-x * x) / ((2 * i) * (2 * i + 1));
            }
            break;
        case 2:  // cos(x)
            if (i == 0) {
                x = normalize_angle(x);
                term = 1.0;
            }
            else {
                term = term * (-x * x) / ((2 * i - 1) * (2 * i));
            }
            break;
        case 3:  // exp(x)
            if (i == 0) {
                term = 1.0;
            }
            else {
                term = term * x / i;
            }
            break;
        case 4:  // ln(1+x)
            if (i == 0) {
                term = x;
            }
            else {
                term = term * (-x) * i / (i + 1);
            }
            break;
        }

        prev_result = result;
        result += term;
        (*actual_terms)++;

        if (i > 0 && fabs(term) < epsilon) {
            break;
        }
    }

    return result;
}

void print_menu() {
    printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
    printf("1. Однократный расчет функции\n");
    printf("2. Серийный эксперимент\n");
    printf("3. Выход\n");
}

void mode_single() {
    int func_choice;
    double x, epsilon;
    int n_max;
    int actual_terms;
    double reference, approximation, difference;

    printf("\n=== ОДНОКРАТНЫЙ РАСЧЕТ ===\n");
    printf("Выберите функцию:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. ln(1+x)\n");
    printf("Ваш выбор (1-4): ");
    scanf_s("%d", &func_choice);
    clear_input_buffer();

    if (func_choice < 1 || func_choice > 4) {
        printf("Ошибка: некорректный выбор функции.\n");
        return;
    }

    printf("Введите x: ");
    scanf_s("%lf", &x);
    clear_input_buffer();

    if (func_choice == 4 && x <= -1.0) {
        printf("Ошибка: для ln(1+x) требуется x > -1\n");
        return;
    }

    printf("Введите точность (>= 0.000001): ");
    scanf_s("%lf", &epsilon);
    clear_input_buffer();

    if (epsilon < 1e-6) {
        printf("Ошибка: точность должна быть >= 0.000001\n");
        printf("Будет использовано минимальное значение: 0.000001\n");
        epsilon = 1e-6;
    }

    printf("Введите максимальное количество слагаемых (1-1000): ");
    scanf_s("%d", &n_max);
    clear_input_buffer();

    if (n_max < 1 || n_max > 1000) {
        printf("Ошибка: количество слагаемых должно быть от 1 до 1000\n");
        if (n_max < 1) n_max = 1;
        if (n_max > 1000) n_max = 1000;
        printf("Будет использовано значение: %d\n", n_max);
    }

    reference = get_reference_value(func_choice, x);

    approximation = calculate_with_precision(func_choice, x, epsilon, n_max, &actual_terms);
    difference = approximation - reference;

    printf("\n=== РЕЗУЛЬТАТЫ РАСЧЕТА ===\n");
    printf("Функция: ");
    switch (func_choice) {
    case 1: printf("sin(%.6f)\n", x); break;
    case 2: printf("cos(%.6f)\n", x); break;
    case 3: printf("exp(%.6f)\n", x); break;
    case 4: printf("ln(1+%.6f)\n", x); break;
    }
    printf("Точность: %.6f\n", epsilon);
    printf("Макс. слагаемых: %d\n", n_max);
    printf("---------------------------------\n");
    printf("Эталонное значение:    % .10f\n", reference);
    printf("Вычисленное значение:  % .10f\n", approximation);
    printf("Разница:               % .10e\n", difference);
    printf("Количество слагаемых:  %d\n", actual_terms);

    if (actual_terms == n_max) {
        printf("Примечание: достигнуто максимальное количество слагаемых\n");
    }
}

void mode_series() {
    int func_choice;
    double x;
    int n_max;
    double reference;

    printf("\n=== СЕРИЙНЫЙ ЭКСПЕРИМЕНТ ===\n");
    printf("Выберите функцию:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. ln(1+x)\n");
    printf("Ваш выбор (1-4): ");
    scanf_s("%d", &func_choice);
    clear_input_buffer();

    if (func_choice < 1 || func_choice > 4) {
        printf("Ошибка: некорректный выбор функции.\n");
        return;
    }

    printf("Введите x: ");
    scanf_s("%lf", &x);
    clear_input_buffer();

    if (func_choice == 4 && x <= -1.0) {
        printf("Ошибка: для ln(1+x) требуется x > -1\n");
        return;
    }

    printf("Введите количество экспериментов (1-25): ");
    scanf_s("%d", &n_max);
    clear_input_buffer();

    if (n_max < 1 || n_max > 25) {
        printf("Ошибка: количество экспериментов должно быть от 1 до 25\n");
        if (n_max < 1) n_max = 1;
        if (n_max > 25) n_max = 25;
        printf("Будет использовано значение: %d\n", n_max);
    }

    reference = get_reference_value(func_choice, x);

    printf("\n=== РЕЗУЛЬТАТЫ СЕРИЙНОГО ЭКСПЕРИМЕНТА ===\n");
    printf("Функция: ");
    switch (func_choice) {
    case 1: printf("sin(%.6f)\n", x); break;
    case 2: printf("cos(%.6f)\n", x); break;
    case 3: printf("exp(%.6f)\n", x); break;
    case 4: printf("ln(1+%.6f)\n", x); break;
    }
    printf("Эталонное значение: %.10f\n\n", reference);
    printf("+-----+----------------------+----------------------+\n");
    printf("|  N  |    Приближение       |      Разница         |\n");
    printf("+-----+----------------------+----------------------+\n");

    for (int n = 1; n <= n_max; n++) {
        double approximation = calculate_n_terms(func_choice, x, n);
        double difference = approximation - reference;
        printf("|%4d | % .10e | % .10e |\n", n, approximation, difference);

        if (n % 5 == 0 && n != n_max) {
            printf("+-----+----------------------+----------------------+\n");
        }
    }

    printf("+-----+----------------------+----------------------+\n");
}