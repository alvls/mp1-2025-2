#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <stdio.h>

#define PI 3.14159265358979323846

double t_sin(double x, double precision, int N, int* N_used, int N_min) {
    x = fmod(x, PI * 2);
    if (x > PI)
        x -= 2 * PI;
    if (x > PI / 2)
        x = PI - x;
    else if (x < PI / 2)
        x = -PI - x;

    double sum = (double)x;
    double increment = (double)x;
    int n_used = 1;

    for (int i = 1; i < N * 2 - 1; i+= 2) {
        if (fabs(increment) < precision && n_used >= N_min) {
            *N_used = n_used;
            return sum;
        }

        increment *= -x * x / ((i + 1) * (i + 2));

        sum += increment;
        n_used++;

    }

    *N_used = n_used;
    return sum;
}

double t_cos(double x, double precision, int N, int* N_used, int N_min) {
    x = fmod(x, PI * 2);
    if (x > PI)
        x = 2 * PI - x;
    
    double sum = 1;
    double increment = 1;
    int n_used = 1;

    for (int i = 1; i < N * 2 - 1; i += 2) {
        if (fabs(increment) < precision && n_used >= N_min) {
            *N_used = n_used;
            return sum;
        }

        increment *= -x * x / ((i) * (i + 1));

        sum += increment;
        n_used++;

    }

    *N_used = n_used;
    return sum;
}

double t_exp(double x, double precision, int N, int* N_used, int N_min) {
    double sum = 1;
    double increment = 1;
    int n_used = 1;

    for (int i = 1; i < N; i++) {
        if (fabs(increment) < precision && n_used >= N_min) {
            *N_used = n_used;
            return sum;
        }

        increment *= x / i;

        sum += increment;
        n_used++;

    }

    *N_used = n_used;
    return sum;
}

double t_unique(double x, double precision, int N, int* N_used, int N_min) {
    if (x < -1) {
        printf("x должен быть >= -1\n");
        return -1;
    }
        
    if (x <= 1) {
        double sum = 1;
        double increment = 1;
        int n_used = 1;

        for (int i = 1; i < N; i++) {
            if (fabs(increment) < precision && n_used >= N_min) {
                *N_used = n_used;
                return sum;
            }

            increment *= x * (1.5 - i) / i;

            sum += increment;
            n_used++;

        }

        *N_used = n_used;
        return sum;
    }

    // ряд маклорена для sqrt(1+x) расходится при x > 1. ряд тейлора с изменяющимся х0 требует также вычисления корней.
    // воспользуюсь разложением sqrt(1+x) = sqrt(x) * sqrt(1 + 1/x), где второе гарантированно сходится в ряде маклорена
    // для подсчета sqrt(x) воспользуюсь методом Ньютона

    double sum = 1;
    double increment = 1;
    int n_used = 1;

    for (int i = 1; i < N; i++) {
        if (fabs(increment) < precision) {
            break;
        }

        increment *= (1.5 - i) / (i * x);

        sum += increment;
        n_used++;

    }


    double root = 1;
    double root_previous = -1000;
    
    while (fabs(root - root_previous) >= precision) {
        root_previous = root;

        root = (root + x / root) / 2;
    }

    *N_used = n_used;
    return root * sum;

}

int main() {
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");

    while (1) {
        char input[100];

        printf("\n1 - Однократный рассчет\n");
        printf("2 - Серийный эксперимент\n");

        scanf_s("%s", input, sizeof(input));

        if (strcmp(input, "1") == 0) {

            printf("\nВведите функцию [sin, cos, exp, unique (1 + x)^1/2]:\n");
            char func[10];
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(func, sizeof(func), stdin);
            func[strcspn(func, "\n")] = '\0';

            printf("\nВведите точку х, в которой будет вычисляться:\n");
            double x;
            scanf_s("%lf", &x);
            while ((c = getchar()) != '\n' && c != EOF);

            printf("\nВведите точность вычисления (от 0.000001 и больше):\n");
            double precision;
            scanf_s("%lf", &precision);
            while ((c = getchar()) != '\n' && c != EOF);

            printf("\nВведите числа элементов многочлена Тейлора:\n");
            int N;
            scanf_s("%d", &N);
            while ((c = getchar()) != '\n' && c != EOF);

            int N_used = 0;
            double value;
            double reference_value;

            if (strcmp(func, "sin") == 0) {
                value = t_sin(x, precision, N, &N_used, 1);
                reference_value = sin(x);
            }
            else if (strcmp(func, "cos") == 0) {
                value = t_cos(x, precision, N, &N_used, 1);
                reference_value = cos(x);
            }
            else if (strcmp(func, "exp") == 0) {
                value = t_exp(x, precision, N, &N_used, 1);
                reference_value = exp(x);
            }
            else if (strcmp(func, "unique") == 0) {
                value = t_unique(x, precision, N, &N_used, 1);
                reference_value = sqrt(1 + x);
            }
            else {
                printf("Плохая функция!\n");
                continue;
            }

            printf("Эталонное значение функции: %fl\n", reference_value);
            printf("Вычисленное значение функции: %f\n", value);
            printf("Разница между значениями: %fl\n", fabs(value - reference_value));
            printf("Количество посчитанных слагаемых: %d\n", N_used);

        }
        else if (strcmp(input, "2") == 0) {
            printf("\nВведите функцию [sin, cos, exp, unique (1 + x)^1/2]:\n");
            char func[10];
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(func, sizeof(func), stdin);
            func[strcspn(func, "\n")] = '\0';

            printf("\nВведите точку х, в которой будет вычисляться:\n");
            double x;
            scanf_s("%lf", &x);
            while ((c = getchar()) != '\n' && c != EOF);

            printf("\nВведите точность вычисления (от 0.000001 и больше):\n");
            double precision;
            scanf_s("%lf", &precision);
            while ((c = getchar()) != '\n' && c != EOF);

            printf("\nВведите числа экспериментов: (от 1 до 25)\n");
            int N;
            scanf_s("%d", &N);
            while ((c = getchar()) != '\n' && c != EOF);

            double values[25];
            double reference_value;
            int N_used = 0;

            if (strcmp(func, "sin") == 0) {
                for (int n = 1; n <= N; n++) {
                    values[n - 1] = t_sin(x, precision, n, &N_used, n);
                }
                reference_value = sin(x);
            }
            else if (strcmp(func, "cos") == 0) {
                for (int n = 1; n <= N; n++) {
                    values[n - 1] = t_cos(x, precision, n, &N_used, n);
                }
                reference_value = cos(x);
            }
            else if (strcmp(func, "exp") == 0) {
                for (int n = 1; n <= N; n++) {
                    values[n - 1] = t_exp(x, precision, n, &N_used, n);
                }
                reference_value = exp(x);
            }
            else if (strcmp(func, "unique") == 0) {
                for (int n = 1; n <= N; n++) {
                    values[n - 1] = t_unique(x, precision, n, &N_used, n);
                }
                reference_value = sqrt(1 + x);
            }
            else {
                printf("Плохая функция!\n");
                continue;
            }

            printf("Эталонное значение функции: %fl\n", reference_value);

            printf("+------+--------------------+--------------------+\n");
            printf("|  N   |   Приближение      |     Разница        |\n");
            printf("+------+--------------------+--------------------+\n");

            for (int n = 1; n <= N; n++) {

                printf("| %4d | %18.12lf | %18.12lf |\n",
                    n, values[n-1], fabs(values[n-1] - reference_value));
            }

            printf("+------+--------------------+--------------------+\n");
        }
    }

    return 0;
}