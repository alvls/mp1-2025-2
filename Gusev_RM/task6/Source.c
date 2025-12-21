#include <locale.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897
typedef double (*ReducerFunc)(double);

double reduce_angle(double x) {
    double two_pi = 2 * PI;
    x = fmod(x, two_pi);
    if (x > PI) x -= two_pi;
    if (x < -PI) x += two_pi;
    return x;
}

double my_exp(double a, int b, double t, int rez, int exper) {
    double znach = 1.0;
    double sum = 1.0;

    if (rez == 1) {
        for (int i = 1; i <= b; i++) {
            znach = znach * a / i;
            sum = sum + znach;
            if (fabs(exp(a) - sum) <= t) {
                printf("Необходимая точность достигнута\n");
                printf("Вычисленное значение: %.15f\n", sum);
                printf("Эталонное значение:   %.15f\n", exp(a));
                printf("Разница:              %.15f\n", exp(a) - sum);
                return sum;
            }
        }
        printf("Ряд закончен (достигнут предел членов)\n");
        printf("Вычисленное значение: %.15f\n", sum);
        printf("Эталонное значение:   %.15f\n", exp(a));
        printf("Разница:              %.15f\n", exp(a) - sum);
        return sum;
    }

    if (rez == 2) {
        printf("Эталонное значение: %.15f\n", exp(a));
        printf("Количество слагаемых    вычисленная оценка    разница\n");
        printf("-------------------------------------------------------\n");

        for (int n = 1; n <= exper; n++) {
            sum = 1.0;
            znach = 1.0;
            for (int i = 1; i <= n; i++) {
                znach = znach * a / i;
                sum = sum + znach;
            }
            printf("       %2i                 %.15f     %.15f\n",
                n, sum, fabs(exp(a) - sum));
        }
        return 0;
    }

    return 0;
}


double my_sin(double a, int b, double t, int rez, int exper, ReducerFunc reducer) {
    a = reducer(a);

    if (rez == 1) {
        double znach = a;
        double sum = a;
        int sign = -1;
        int n = 3;

        for (int i = 2; i <= b; i += 2) {
            znach *= (a * a) / ((n - 1) * n);
            sum += sign * znach;
            sign *= -1;
            n += 2;

            if (fabs(sin(a) - sum) <= t) {
                printf("Необходимая точность достигнута\n");
                printf("Вычисленное значение: %.15f\n", sum);
                printf("Эталонное значение:   %.15f\n", sin(a));
                printf("Разница:              %.15f\n", sin(a) - sum);
                printf("Использовано членов:  %d\n", i / 2 + 1);
                return sum;
            }
        }

        printf("Ряд закончен (достигнут предел членов)\n");
        printf("Вычисленное значение: %.15f\n", sum);
        printf("Эталонное значение:   %.15f\n", sin(a));
        printf("Разница:              %.15f\n", sin(a) - sum);
        return sum;
    }

    if (rez == 2) {
        printf("Эталонное значение: %.15f\n", sin(a));
        printf("Количество слагаемых    вычисленная оценка    разница\n");
        printf("-------------------------------------------------------\n");

        for (int n_terms = 1; n_terms <= exper; n_terms++) {
            double znach = a;
            double sum = a;
            int sign = -1;
            int n = 3;

            for (int i = 2; i <= n_terms * 2; i += 2) {
                znach *= (a * a) / ((n - 1) * n);
                sum += sign * znach;
                sign *= -1;
                n += 2;
            }

            printf("       %2i                 %.15f     %.15f\n",
                n_terms, sum, fabs(sin(a) - sum));
        }
        return 0;
    }

    return 0;
}


double my_cos(double a, int b, double t, int rez, int exper, ReducerFunc reducer) {
    a = reducer(a);
    if (rez == 1) {
        double znach = 1;
        double sum = 1;
        int sign = -1;
        int n = 2;

        for (int i = 1; i <= b; i += 2) {
            znach *= (a * a) / ((n - 1) * n);
            sum += sign * znach;
            sign *= -1;
            n += 2;

            if (fabs(cos(a) - sum) <= t) {
                printf("Необходимая точность достигнута\n");
                printf("Вычисленное значение: %.15f\n", sum);
                printf("Эталонное значение:   %.15f\n", cos(a));
                printf("Разница:              %.15f\n", cos(a) - sum);
                printf("Использовано членов:  %d\n", (i + 1) / 2);
                return sum;
            }
        }

        printf("Ряд закончен (достигнут предел членов)\n");
        printf("Вычисленное значение: %.15f\n", sum);
        printf("Эталонное значение:   %.15f\n", cos(a));
        printf("Разница:              %.15f\n", cos(a) - sum);
        return sum;
    }

    if (rez == 2) {
        printf("Эталонное значение: %.15f\n", cos(a));
        printf("Количество слагаемых    вычисленная оценка    разница\n");
        printf("-------------------------------------------------------\n");

        for (int n_terms = 1; n_terms <= exper; n_terms++) {
            double znach = 1;
            double sum = 1;
            int sign = -1;
            int n = 2;

            for (int i = 1; i <= n_terms * 2 - 1; i += 2) {
                znach *= (a * a) / ((n - 1) * n);
                sum += sign * znach;
                sign *= -1;
                n += 2;
            }

            printf("       %2i                 %.15f     %.15f\n",
                n_terms, sum, fabs(cos(a) - sum));
        }
        return 0;
    }

    return 0;
}


double nat_ln(double a, int b, double t, int rez, int exper) {
    if (a <= 0) {
        printf("Ошибка: ln(x) определен для x > 0\n");
        return 0;
    }

    double x = a;

    int count = 0;
    while (a <= 0.5 || a > 2) {
        if (a <= 0.5) {
            a *= 2.0;
            count--;
        }
        if (a > 2) {
            a /= 2.0;
            count++;
        }
    }

    if (rez == 1) {
        double znach = a - 1.0;
        double sum = 0.0;
        int sign = 1;

        for (int i = 1; i <= b; i++) {
            sum += sign * znach / i;
            znach *= (a-1);
            sign = -sign;

            if (fabs(log(x) - (sum + count * 0.6931471805599453)) <= t) {
                printf("Необходимая точность достигнута\n");
                double result = sum + count * 0.6931471805599453;
                printf("Вычисленное значение: %.15f\n", result);
                printf("Эталонное значение:   %.15f\n", log(x));
                printf("Разница:              %.15f\n", log(x) - result);
                printf("Использовано членов:  %d\n", i);
                return result;
            }
        }

        double result = sum + count * 0.6931471805599453;
        printf("Ряд закончен (достигнут предел членов)\n");
        printf("Вычисленное значение: %.15f\n", result);
        printf("Эталонное значение:   %.15f\n", log(x));
        printf("Разница:              %.15f\n", log(x) - result);
        return result;
    }

    if (rez == 2) {
        printf("Эталонное значение: %.15f\n", log(x));
        printf("Количество слагаемых    вычисленная оценка    разница\n");
        printf("-------------------------------------------------------\n");

        for (int n_terms = 1; n_terms <= exper; n_terms++) {

            double znach = a - 1.0;
            double sum = 0.0;
            int sign = 1;

            for (int i = 1; i <= n_terms; i++) {
                sum += sign * znach / i;
                znach *= (a-1);
                sign = -sign;
            }

            double result = sum + count * 0.6931471805599453;
            printf("       %2i                 %.15f     %.15f\n",
                n_terms, result, fabs(log(x) - result));
        }
        return 0;
    }

    return 0;
}

int main() {
    setlocale(LC_ALL, "rus");
    ReducerFunc my_reducer = reduce_angle;

    float a = 0.f, t = 0.f;
    int b = 0;
    int rez0 = 0;
    int fn = 0;
    int exper = 0;

    printf("Выберите режим:\n");
    printf("1 - Вычисление с заданной точностью\n");
    printf("2 - Эксперимент (таблица зависимости от количества членов)\n");
    scanf_s("%i", &rez0);

    printf("Выберите функцию:\n");
    printf("1 - exp(x)\n");
    printf("2 - sin(x)\n");
    printf("3 - cos(x)\n");
    printf("4 - ln(x)\n");
    scanf_s("%i", &fn);

    printf("Введите x: ");
    scanf_s("%f", &a);

    if (rez0 == 1) {
        printf("Введите максимальное количество членов ряда: ");
        scanf_s("%d", &b);

        printf("Задайте точность: ");
        scanf_s("%f", &t);

        if (fn == 1) {
            double result = my_exp(a, b, t, rez0, exper);
        }
        else if (fn == 2) {
            double result = my_sin(a, b, t, rez0, exper, my_reducer);
        }
        else if (fn == 3) {
            double result = my_cos(a, b, t, rez0, exper, my_reducer);
        }
        else if (fn == 4) {
            double result = nat_ln(a, b, t, rez0, exper);
        }
        else {
            printf("Неверный выбор функции\n");
        }
    }

    if (rez0 == 2) {
        printf("Введите количество экспериментов (максимальное количество членов): ");
        scanf_s("%d", &exper);

        if (fn == 1) {
            double result = my_exp(a, b, t, rez0, exper);
        }
        else if (fn == 2) {
            double result = my_sin(a, b, t, rez0, exper, my_reducer);
        }
        else if (fn == 3) {
            double result = my_cos(a, b, t, rez0, exper, my_reducer);
        }
        else if (fn == 4) {
            double result = nat_ln(a, b, t, rez0, exper);
        }
        else {
            printf("Неверный выбор функции\n");
        }
    }

    system("pause");
    return 0;
}