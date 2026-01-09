#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define PI 3.14159265358979323846
#define MAX_TERMS 1000
#define MAX_EXPERIMENTS 25

// Прототипы функций
double taylor_sin(double x, int n, double epsilon, int* terms_used);
double taylor_cos(double x, int n, double epsilon, int* terms_used);
double taylor_exp(double x, int n, double epsilon, int* terms_used);
double taylor_sec(double x, int n, double epsilon, int* terms_used);
void mode_single(int func_choice, double x);
void mode_series(int func_choice, double x);

// Указатель на функцию расчета рядом Тейлора
typedef double (*taylor_func_ptr)(double, int, double, int*);

// Вспомогательная функция для вычисления факториала
long double factorial(int n) {
    long double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Функция для приведения угла к диапазону [-π, π]
double normalize_angle(double x) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    return x;
}

// Ряд Тейлора для sin(x)
double taylor_sin(double x, int n, double epsilon, int* terms_used) {
    x = normalize_angle(x);
    double sum = 0.0;
    double term;
    int i = 0;

    for (i = 0; i < n; i++) {
        term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        sum += term;

        if (fabs(term) < epsilon) {
            *terms_used = i + 1;
            return sum;
        }
    }

    *terms_used = n;
    return sum;
}

// Ряд Тейлора для cos(x)
double taylor_cos(double x, int n, double epsilon, int* terms_used) {
    x = normalize_angle(x);
    double sum = 0.0;
    double term;
    int i = 0;

    for (i = 0; i < n; i++) {
        term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        sum += term;

        if (fabs(term) < epsilon) {
            *terms_used = i + 1;
            return sum;
        }
    }

    *terms_used = n;
    return sum;
}

// Ряд Тейлора для exp(x)
double taylor_exp(double x, int n, double epsilon, int* terms_used) {
    double sum = 0.0;
    double term = 1.0; // Первый член ряда (x^0/0!)
    int i = 0;

    for (i = 0; i < n; i++) {
        if (i > 0) {
            term = pow(x, i) / factorial(i);
        }
        sum += term;

        if (fabs(term) < epsilon) {
            *terms_used = i + 1;
            return sum;
        }
    }

    *terms_used = n;
    return sum;
}

// Ряд Тейлора для sec(x) = 1/cos(x)
double taylor_sec(double x, int n, double epsilon, int* terms_used) {
    x = normalize_angle(x);

    // Для углов близких к π/2, cos(x) приближается к 0
    if (fabs(cos(x)) < 1e-10) {
        *terms_used = 0;
        return INFINITY;
    }

    // Разложение sec(x) через ряд Тейлора для cos(x) и обращение
    double cos_approx = taylor_cos(x, n, epsilon, terms_used);

    if (fabs(cos_approx) < 1e-10) {
        return INFINITY;
    }

    return 1.0 / cos_approx;
}

// Режим 1: Однократный расчет
void mode_single(int func_choice, double x) {
    int n;
    double epsilon;

    printf("Введите количество элементов ряда (1-1000): ");
    scanf_s("%d", &n);

    if (n < 1 || n > 1000) {
        printf("Некорректное количество элементов! Используется значение по умолчанию: 10\n");
        n = 10;
    }

    printf("Введите точность вычисления (>= 0.000001): ");
    scanf_s("%lf", &epsilon);

    if (epsilon < 0.000001) {
        printf("Некорректная точность! Используется значение по умолчанию: 0.000001\n");
        epsilon = 0.000001;
    }

    // Получение эталонного значения
    double reference;
    char* func_name;
    taylor_func_ptr taylor_func;

    switch (func_choice) {
    case 1:
        reference = sin(x);
        func_name = "sin(x)";
        taylor_func = taylor_sin;
        break;
    case 2:
        reference = cos(x);
        func_name = "cos(x)";
        taylor_func = taylor_cos;
        break;
    case 3:
        reference = exp(x);
        func_name = "exp(x)";
        taylor_func = taylor_exp;
        break;
    case 4:
        if (fabs(cos(x)) < 1e-10) {
            printf("Ошибка: cos(x) = 0, sec(x) не определена в этой точке!\n");
            return;
        }
        reference = 1.0 / cos(x);
        func_name = "sec(x)";
        taylor_func = taylor_sec;
        break;
    default:
        return;
    }

    // Вычисление рядом Тейлора
    int terms_used = 0;
    double approximation = taylor_func(x, n, epsilon, &terms_used);

    // Проверка на переполнение
    if (isinf(approximation)) {
        printf("\n=== Результаты расчета ===\n");
        printf("Функция: %s в точке x = %.6lf\n", func_name, x);
        printf("Результат: бесконечность (функция не определена в этой точке)\n");
        return;
    }

    // Вывод результатов
    printf("\n=== Результаты расчета ===\n");
    printf("Функция: %s в точке x = %.6lf\n", func_name, x);
    printf("Эталонное значение: %.10lf\n", reference);
    printf("Вычисленная оценка: %.10lf\n", approximation);
    printf("Разница: %.10lf\n", fabs(approximation - reference));
    printf("Количество использованных слагаемых: %d\n", terms_used);
}

// Режим 2: Серийный эксперимент
void mode_series(int func_choice, double x) {
    int n_max;

    printf("Введите количество экспериментов (1-25): ");
    scanf_s("%d", &n_max);

    if (n_max < 1 || n_max > 25) {
        printf("Некорректное количество экспериментов! Используется значение по умолчанию: 10\n");
        n_max = 10;
    }

    // Получение эталонного значения
    double reference;
    char* func_name;
    taylor_func_ptr taylor_func;

    switch (func_choice) {
    case 1:
        reference = sin(x);
        func_name = "sin(x)";
        taylor_func = taylor_sin;
        break;
    case 2:
        reference = cos(x);
        func_name = "cos(x)";
        taylor_func = taylor_cos;
        break;
    case 3:
        reference = exp(x);
        func_name = "exp(x)";
        taylor_func = taylor_exp;
        break;
    case 4:
        if (fabs(cos(x)) < 1e-10) {
            printf("Ошибка: cos(x) = 0, sec(x) не определена в этой точке!\n");
            return;
        }
        reference = 1.0 / cos(x);
        func_name = "sec(x)";
        taylor_func = taylor_sec;
        break;
    default:
        return;
    }

    // Вывод заголовка
    printf("\n=== Серийный эксперимент ===\n");
    printf("Функция: %s в точке x = %.6lf\n", func_name, x);
    printf("Эталонное значение: %.10lf\n\n", reference);

    // Заголовок таблицы
    printf("%-10s %-20s %-20s\n", "Слагаемые", "Приближение", "Разница");
    printf("----------------------------------------------------------\n");

    // Проведение экспериментов
    for (int n = 1; n <= n_max; n++) {
        int terms_used;
        double approximation = taylor_func(x, n, 0.0, &terms_used);
        double difference;

        if (isinf(approximation)) {
            printf("%-10d %-20s %-20s\n", n, "бесконечность", "бесконечность");
        }
        else {
            difference = fabs(approximation - reference);
            printf("%-10d %-20.10lf %-20.10lf\n", n, approximation, difference);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int mode, choice;

    printf("=== Калькулятор функций через ряд Тейлора ===\n\n");

    do {
        printf("Выберите режим работы:\n");
        printf("1 - Однократный расчет функции\n");
        printf("2 - Серийный эксперимент\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &mode);

        if (mode == 0) {
            printf("Выход из программы.\n");
            break;
        }

        printf("\nВыберите функцию:\n");
        printf("1 - sin(x)\n");
        printf("2 - cos(x)\n");
        printf("3 - exp(x)\n");
        printf("4 - sec(x)\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &choice);

        if (choice < 1 || choice > 4) {
            printf("Неверный выбор функции!\n\n");
            continue;
        }

        double x;
        printf("Введите точку x: ");
        scanf_s("%lf", &x);

        switch (mode) {
        case 1:
            mode_single(choice, x);
            break;
        case 2:
            mode_series(choice, x);
            break;
        default:
            printf("Неверный режим!\n");
        }

        printf("\n");

    } while (1);

    return 0;
}