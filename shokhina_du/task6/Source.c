#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define PI 3.14159265358979323846

void print_menu();
void print_functions();
void mode_single();
void mode_series();

double taylor_sin(double x, double eps, int max_terms, int* terms_used);
double taylor_cos(double x, double eps, int max_terms, int* terms_used);
double taylor_exp(double x, double eps, int max_terms, int* terms_used);
double taylor_arsh(double x, double eps, int max_terms, int* terms_used);

double taylor_approximation(int func_id, double x, double eps, int max_terms, int* terms_used);
double get_reference_value(int func_id, double x);

int main() {
    setlocale(LC_ALL, "rus");

    int mode;

    printf("=========== Калькулятор функций по ряду Тейлора ===========\n");

    do {
        print_menu();
        scanf_s("%d", &mode);

        switch (mode) {
        case 1:
            mode_single();
            break;
        case 2:
            mode_series();
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (mode != 0);

    return 0;
}

void print_menu() {
    printf("\n---------------------------\n");
    printf("Выберите режим работы:\n");
    printf("1 - Однократный расчет функции\n");
    printf("2 - Серийный эксперимент\n");
    printf("0 - Выход\n");
    printf("Ваш выбор: ");
}

void print_functions() {
    printf("Доступные функции:\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - exp(x)\n");
    printf("4 - arsh(x)\n");
    printf("Ваш выбор: ");
}

// функции расчета рядов Тейлора:

double taylor_sin(double x, double eps, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = x;

    // приводим x к диапазону [-п, п] 
    double x_reduced = x;
    while (x_reduced > PI) x_reduced -= 2 * PI;
    while (x_reduced < -PI) x_reduced += 2 * PI;

    term = x_reduced;

    for (int i = 1; i <= max_terms; i++) {
        sum += term;

        if (fabs(term) < eps) {
            *terms_used = i;
            return sum;
        }
        term = -term * x_reduced * x_reduced / ((2 * i) * (2 * i + 1));
    }
    *terms_used = max_terms;
    return sum;
}

double taylor_cos(double x, double eps, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = 1.0;

    // приводим x к диапазону [-п, п]
    double x_reduced = x;
    while (x_reduced > PI) x_reduced -= 2 * PI;
    while (x_reduced < -PI) x_reduced += 2 * PI;

    term = 1.0;

    for (int i = 0; i < max_terms; i++) {
        sum += term;

        if (fabs(term) < eps) {
            *terms_used = i + 1;
            return sum;
        }
        term = -term * x_reduced * x_reduced / ((2 * i + 1) * (2 * i + 2));
    }
    *terms_used = max_terms;
    return sum;
}

// ряд тейлора для exp(x) = 1 + x + x^2/2! + x^3/3! + ...
double taylor_exp(double x, double eps, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = 1.0;

    term = 1.0;

    for (int i = 0; i < max_terms; i++) {
        sum += term;

        if (fabs(term) < eps) {
            *terms_used = i + 1;
            return sum;
        }
        term = term * x / (i + 1);
    }
    *terms_used = max_terms;
    return sum;
}

double taylor_arsh(double x, double eps, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term = x;

    if (fabs(x) >= 1.0) {
        *terms_used = 1;
        return log(x + sqrt(x * x + 1));
    }

    term = x;
    double x_sq = x * x;
    double coeff = 1.0;

    for (int i = 0; i < max_terms; i++) {
        sum += term;

        if (fabs(term) < eps) {
            *terms_used = i + 1;
            return sum;
        }
        coeff = coeff * (2.0 * i + 1) / (2.0 * i + 2);
        term = -term * x_sq * coeff * (2.0 * i + 1) / (2.0 * i + 3);
    }
    *terms_used = max_terms;
    return sum;
}

// выбор функции
double taylor_approximation(int func_id, double x, double eps, int max_terms, int* terms_used) {
    switch (func_id) {
    case 1:
        return taylor_sin(x, eps, max_terms, terms_used);
    case 2:
        return taylor_cos(x, eps, max_terms, terms_used);
    case 3:
        return taylor_exp(x, eps, max_terms, terms_used);
    case 4:
        return taylor_arsh(x, eps, max_terms, terms_used);
    default:
        *terms_used = 0;
        return 0.0;
    }
}

// получение эталонного значения через стандартные функции С
double get_reference_value(int func_id, double x) {
    switch (func_id) {
    case 1:
        return sin(x);
    case 2:
        return cos(x);
    case 3:
        return exp(x);
    case 4:
        return asinh(x); 
    default:
        return 0.0;
    }
}

// режим 1: однократный расчет 
void mode_single() {
    int func_choice, n;
    double x, eps;
    double reference, approximation;
    int terms_used;

    printf("\n--- Режим 1: Однократный расчет ---\n");
    print_functions();
    scanf_s("%d", &func_choice);

    if (func_choice < 1 || func_choice > 4) {
        printf("Неверный выбор функции.\n");
        return;
    }

    printf("Введите x: ");
    scanf_s("%lf", &x);

    printf("Введите точность (>= 0.000001): ");
    scanf_s("%lf", &eps);

    if (eps < 0.000001) {
        printf("Точность слишком мала. Установлено минимальное значение 0.000001\n");
        eps = 0.000001;
    }

    printf("Введите максимальное количество слагаемых N (1-1000): ");
    scanf_s("%d", &n);

    if (n < 1 || n > 1000) {
        printf("Некорректное N. Установлено значение 100\n");
        n = 100;
    }

    reference = get_reference_value(func_choice, x);
    approximation = taylor_approximation(func_choice, x, eps, n, &terms_used);

    printf("\n=========== РЕЗУЛЬТАТЫ ===========\n");
    printf("Функция: ");
    switch (func_choice) {
    case 1: printf("sin(x)\n"); break;
    case 2: printf("cos(x)\n"); break;
    case 3: printf("exp(x)\n"); break;
    case 4: printf("arsh(x)\n"); break;
    }
    printf("x = %lf\n", x);
    printf("Эталонное значение: %.12lf\n", reference);
    printf("Приближенное значение: %.12lf\n", approximation);
    printf("Разница: %.12lf\n", fabs(approximation - reference));
    printf("Использовано слагаемых: %d из %d\n", terms_used, n);

    if (terms_used == n) {
        printf("Достигнуто максимальное количество слагаемых.\n");
    }
    else {
        printf("Достигнута заданная точность.\n");
    }
}

// режим 2: серийный эксперимент
void mode_series() {
    int func_choice, n_max;
    double x;
    double reference;

    printf("\n--- Режим 2: Серийный эксперимент ---\n");
    print_functions();
    scanf_s("%d", &func_choice);

    if (func_choice < 1 || func_choice > 4) {
        printf("Неверный выбор функции.\n");
        return;
    }

    printf("Введите x: ");
    scanf_s("%lf", &x);

    printf("Введите количество экспериментов NMax (1-25): ");
    scanf_s("%d", &n_max);

    if (n_max < 1 || n_max > 25) {
        printf("Некорректное NMax. Установлено значение 10\n");
        n_max = 10;
    }

    reference = get_reference_value(func_choice, x);

    printf("\n=========== РЕЗУЛЬТАТЫ ===========\n");
    printf("Функция: ");
    switch (func_choice) {
    case 1: printf("sin(x)\n"); break;
    case 2: printf("cos(x)\n"); break;
    case 3: printf("exp(x)\n"); break;
    case 4: printf("arsh(x)\n"); break;
    }
    printf("x = %lf\n", x);
    printf("Эталонное значение: %.12lf\n\n", reference);

    printf("+------+--------------------+--------------------+\n");
    printf("|  N   |   Приближение      |     Разница        |\n");
    printf("+------+--------------------+--------------------+\n");

    // выполняем серию экспериментов
    for (int n = 1; n <= n_max; n++) {
        int terms_used;
        double eps = 1e-100; // очень маленькая точность, чтобы использовать все N слагаемых
        double approximation = taylor_approximation(func_choice, x, eps, n, &terms_used);
        double difference = fabs(approximation - reference);

        printf("| %4d | %18.12lf | %18.12lf |\n",
            n, approximation, difference);
    }

    printf("+------+--------------------+--------------------+\n");
}