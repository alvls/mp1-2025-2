#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

#define EPS_MIN 0.000001
#define NMAX_SINGLE 1000
#define NMAX_SERIES 25

typedef double (*FuncTaylor)(double x, int n, double eps, int *terms_used);

double sin_taylor(double x, int n, double eps, int *terms_used) {
    double term = x; 
    double sum = term;
    int k = 1;
    for (; k < n; ++k) {
        term = -term * x * x / ((2*k)*(2*k+1));
        sum += term;
        if (fabs(term) < eps) break;
    }
    *terms_used = k;
    return sum;
}

double cos_taylor(double x, int n, double eps, int *terms_used) {
    double term = 1.0; 
    double sum = term;
    int k = 1;
    for (; k < n; ++k) {
        term = -term * x * x / ((2*k-1)*(2*k));
        sum += term;
        if (fabs(term) < eps) break;
    }
    *terms_used = k;
    return sum;
}

double exp_taylor(double x, int n, double eps, int *terms_used) {
    double term = 1.0;
    double sum = term;
    int k = 1;
    for (; k < n; ++k) {
        term = term * x / k;
        sum += term;
        if (fabs(term) < eps) break;
    }
    *terms_used = k;
    return sum;
}

double arcsin_taylor(double x, int n, double eps, int *terms_used) {
    if (x < -1 || x > 1) {
        *terms_used = 0;
        return NAN;
    }

    double term = x;  
    double sum = term;
    int k;
    for (k = 1; k < n; ++k) {
        double numerator = (2*k - 1)*(2*k -1) * x * x;
        double denominator = (2*k)*(2*k + 1);
        term = term * numerator / denominator;
        sum += term;
        if (fabs(term) < eps) break;
    }
    *terms_used = k;
    return sum;
}

typedef struct {
    const char *name;
    FuncTaylor func_taylor;
    double (*func_math)(double);
} FuncInfo;

double arcsin_wrapper(double x) {
    return asin(x);
}

int choose_function() {
    printf("Выберите функцию для вычисления:\n");
    printf("1) sin(x)\n");
    printf("2) cos(x)\n");
    printf("3) exp(x)\n");
    printf("4) arcsin(x)\n");
    printf("Введите номер функции: ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 4) {
        printf("Некорректный выбор.\n");
        return -1;
    }
    return choice - 1;
}

void print_menu() {
    printf("Выберите режим работы:\n");
    printf("1) Однократный расчет функции в заданной точке\n");
    printf("2) Серийный эксперимент\n");
    printf("0) Выход\n");
    printf("Ваш выбор: ");
}

int main() {
    setlocale(LC_ALL, "rus");
    FuncInfo funcs[4] = {
        {"sin(x)", sin_taylor, sin},
        {"cos(x)", cos_taylor, cos},
        {"exp(x)", exp_taylor, exp},
        {"arcsin(x)", arcsin_taylor, asin}
    };

    int mode;
    do {
        print_menu();
        if (scanf("%d", &mode) != 1) {
            printf("Ошибка ввода.\n");
            break;
        }
        if (mode == 0) break;
        if (mode != 1 && mode != 2) {
            printf("Неверный режим. Попробуйте снова.\n");
            continue;
        }
        int func_index = choose_function();
        if (func_index == -1) continue;
        double x;
        printf("Введите точку x: ");
        if (scanf("%lf", &x) != 1) {
            printf("Ошибка ввода x.\n");
            continue;
        }
        if (func_index == 3) { 
            if (x < -1.0 || x > 1.0) {
                printf("Ошибка: x вне области определения arcsin(x) [-1..1].\n");
                continue;
            }
        }

        if (mode == 1) {
            double eps;
            int N;
            printf("Введите точность вычисления (>= 0.000001): ");
            if (scanf("%lf", &eps) != 1 || eps < EPS_MIN) {
                printf("Некорректная точность.\n");
                continue;
            }
            printf("Введите число слагаемых ряда N (1 .. %d): ", NMAX_SINGLE);
            if (scanf("%d", &N) != 1 || N < 1 || N > NMAX_SINGLE) {
                printf("Некорректное число слагаемых.\n");
                continue;
            }
            int terms_used = 0;
            double calc_value = funcs[func_index].func_taylor(x, N, eps, &terms_used);
            double ref_value = funcs[func_index].func_math(x);
            double diff = fabs(calc_value - ref_value);

            printf("Результаты вычислений:\n");
            printf("Эталонное значение (math.h): %.15f\n", ref_value);
            printf("Вычисленное значение: %.15f\n", calc_value);
            printf("Разница: %.15f\n", diff);
            printf("Вычислено слагаемых: %d\n", terms_used);

        } else {
            int NMax;
            printf("Введите количество экспериментов NMax (1 .. %d): ", NMAX_SERIES);
            if (scanf("%d", &NMax) != 1 || NMax < 1 || NMax > NMAX_SERIES) {
                printf("Некорректное количество экспериментов.\n");
                continue;
            }
            double ref_value = funcs[func_index].func_math(x);
            printf("Эталонное значение (math.h): %.15f\n", ref_value);
            printf(" N | Вычисленное значение | Разница\n");
            printf("-----------------------------------------\n");
            for (int i = 1; i <= NMax; ++i) {
                int terms_used = 0;
                double eps = EPS_MIN;
                double val = funcs[func_index].func_taylor(x, i, eps, &terms_used);
                double diff = fabs(val - ref_value);
                printf("%2d | %20.15f | %10.5e\n", i, val, diff);
            }
        }
        printf("\n");

    } while (1);
    printf("Программа завершена.\n");
    return 0;
}