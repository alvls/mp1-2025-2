#include <stdio.h>
#include <math.h>
#include <locale.h>

#define MAX_TERMS 1000

// Типы указателей на функции
typedef double (*RefFunc)(double);
typedef double (*TaylorFunc)(double, double, int, int*);

// Эталонные функции 
double ref_sin(double x) { return sin(x); }
double ref_cos(double x) { return cos(x); }
double ref_exp(double x) { return exp(x); }
double ref_arsinh(double x) { return asinh(x); }

//синус sin(x)
double taylor_sin(double x, double eps, int N, int* used)
{
    double term = x;
    double sum = term;
    int n = 1;

    while (fabs(term) > eps && n < N) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }
    *used = n;
    return sum;
}

// косинус cos(x)
double taylor_cos(double x, double eps, int N, int* used)
{
    double term = 1.0;
    double sum = term;
    int n = 1;

    while (fabs(term) > eps && n < N) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    }
    *used = n;
    return sum;
}

// экспонента exp(x)
double taylor_exp(double x, double eps, int N, int* used)
{
    double term = 1.0;
    double sum = term;
    int n = 1;

    while (fabs(term) > eps && n < N) {
        term *= x / n;
        sum += term;
        n++;
    }
    *used = n;
    return sum;
}

// arsinh(x)
double taylor_arsinh(double x, double eps, int N, int* used)
{
    double term = x;
    double sum = term;
    int n = 1;

    while (fabs(term) > eps && n < N) {
        term *= -x * x * (2 * n - 1) * (2 * n - 1)
            / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }
    *used = n;
    return sum;
}

// Главная программа
int main()
{
    char* locale = setlocale(LC_ALL, "");
    RefFunc ref_funcs[] = {
        ref_sin, ref_cos, ref_exp, ref_arsinh
    };

    TaylorFunc taylor_funcs[] = {
        taylor_sin, taylor_cos, taylor_exp, taylor_arsinh
    };

    const char* names[] = {
        "sin(x)", "cos(x)", "exp(x)", "arsinh(x)"
    };

    int mode;
    printf("Выберите режим:\n");
    printf("1 - Однократный расчет\n");
    printf("2 - Серийный эксперимент\n");
    scanf_s("%d", &mode);

    int f;
    printf("\nВыберите функцию:\n");
    printf("0 - sin(x)\n");
    printf("1 - cos(x)\n");
    printf("2 - exp(x)\n");
    printf("3 - arsinh(x)\n");
    scanf_s("%d", &f);

    double x;
    printf("\nВведите x: ");
    scanf_s("%lf", &x);

    double ref = ref_funcs[f](x);

    if (mode == 1) {
        double eps;
        int N, used;

        printf("Введите точность (>= 0.000001): ");
        scanf_s("%lf", &eps);

        printf("Введите число слагаемых (1..1000): ");
        scanf_s("%d", &N);

        double approx = taylor_funcs[f](x, eps, N, &used);

        printf("\nФункция: %s\n", names[f]);
        printf("Эталонное значение (полученное с помощью встроенной функции):      %.10lf\n", ref);
        printf("Приближенное значение:  %.10lf\n", approx);
        printf("Разница:                %.10lf\n", fabs(ref - approx));
        printf("Использовано слагаемых: %d\n", used);
    }
    else if (mode == 2) {
        int NMax;
        printf("Введите число экспериментов (от 1 до 25): ");
        scanf_s("%d", &NMax);

        printf("\nФункция: %s\n", names[f]);
        printf("Эталонное значение (получено с помощью встроенной функции): %.10lf\n\n", ref);
        printf("N\tЗначение\t\tРазница\n");

        for (int i = 1; i <= NMax; i++) {
            int used;
            double approx = taylor_funcs[f](x, 0.0, i, &used);
            printf("%d\t%.10lf\t%.10lf\n",
                i, approx, fabs(ref - approx));
        }
    }
    else {
        printf("Неверный режим.\n");
    }

    return 0;
}
