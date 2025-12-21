#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double taylor_sin(double x, int max_terms, double* terms_used, double epsilon);
double taylor_cos(double x, int max_terms, double* terms_used, double epsilon);
double taylor_exp(double x, int max_terms, double* terms_used, double epsilon);
double taylor_sqrt(double x, int max_terms, double* terms_used, double epsilon);
double reference_znachenie(int func_choice, double x);
void single_calculation(int func_choice, double x, double epsilon, int n);
void series_experiment(int func_choice, double x, int nmax);

int main() {
    int mode, function_choice;
    double x, epsilon;
    int n, nmax;

    printf("=== FUNCTION CALCULATOR WITH TAYLOR SERIES ===\n\n");

    printf("Select mode:\n");
    printf("1 - One-time calculation of a function at a given point\n");
    printf("2 - Serial experiment\n");
    scanf_s("%d", &mode);

    printf("\nAvailable functions:\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - exp(x)\n");
    printf("4 - sqrt(1+x - sqrt(1+x))\n");
    scanf_s("%d", &function_choice);
    if (function_choice < 1 || function_choice > 4) {
        printf("Error unknow choise!\n");
        return 1;
    }
    printf("Enter x: ");
    scanf_s("%lf", &x);
    if (function_choice == 4) {
        if (x < 0) {
            printf("Error: for sqrt(1+x - sqrt(1+x)) x must be >= 0!\n");
            printf("If x < 0, 1+x < sqrt(1+x), sqrt will be < 0.\n");
            return 1;
        }
    }
    if (mode == 1) {
        printf("Enter tochnosty vichislenya (in 0.000001 and bigger): ");
        scanf_s("%lf", &epsilon);
        if (epsilon < 0.000001) {
            printf("Error: tochnosty must be not smaller than 0.000001!\n");
            return 1;
        }
        printf("Enter max count N (in 1 to 1000): ");
        scanf_s("%d", &n);
        if (n < 1 || n > 1000) {
            printf("Error: N must be in 1 to 1000!\n");
            return 1;
        }
        single_calculation(function_choice, x, epsilon, n);
    }
    else if (mode == 2) {
        printf("Enter experiment count NMax (in 1 to 25): ");
        scanf_s("%d", &nmax);
        if (nmax < 1 || nmax > 25) {
            printf("Error: NMax must be in 1 to 25!\n");
            return 1;
        }
        series_experiment(function_choice, x, nmax);
    }
    else {
        printf("Error: unknow mode!\n");
        return 1;
    }
    return 0;
}

double taylor_sin(double x, int max_terms, double* terms_used, double epsilon) {
    double result = 0.0;
    double term;
    int sign = 1;
    double x_reduced = x;
    while (x_reduced > M_PI) x_reduced -= 2 * M_PI;
    while (x_reduced < -M_PI) x_reduced += 2 * M_PI;
    term = x_reduced;
    for (int i = 1; i <= max_terms; i++) {
        result += sign * term;

        if (i > 1 && fabs(term) < epsilon) {
            *terms_used = i;
            return result;
        }     
        term *= x_reduced * x_reduced / ((2 * i) * (2 * i + 1));
        sign *= -1;
    }
    *terms_used = max_terms;
    return result;
}
double taylor_cos(double x, int max_terms, double* terms_used, double epsilon) {
    double result = 0.0;
    double term = 1.0;
    int sign = 1;
    double x_reduced = x;
    while (x_reduced > M_PI) x_reduced -= 2 * M_PI;
    while (x_reduced < -M_PI) x_reduced += 2 * M_PI;

    for (int i = 0; i < max_terms; i++) {
        result += sign * term;
        if (i > 0 && fabs(term) < epsilon) {
            *terms_used = i + 1;
            return result;
        }
        term *= x_reduced * x_reduced / ((2 * i + 1) * (2 * i + 2));
        sign *= -1;
    }
    *terms_used = max_terms;
    return result;
}
double taylor_exp(double x, int max_terms, double* terms_used, double epsilon) {
    double result = 0.0;
    double term = 1.0;
    for (int i = 0; i < max_terms; i++) {
        result += term;
        if (i > 0 && fabs(term) < epsilon) {
            *terms_used = i + 1;
            return result;
        }
        term *= x / (i + 1);
    }
    *terms_used = max_terms;
    return result;
}
double taylor_sqrt(double x, int max_terms, double* terms_used, double epsilon) {
    if (x == 0) {
        *terms_used = 1;
        return 0.0;
    }
    double a_coeffs[] = {
        0.5,        
        1.0 / 8.0,    
        -1.0 / 16.0,  
        5.0 / 128.0,  
        -7.0 / 256.0, 
        21.0 / 1024.0 
    };
    int num_coeffs = 6;
    double a = 0.0;
    double x_power = x;

    int terms_to_use = (max_terms < num_coeffs) ? max_terms : num_coeffs;

    for (int i = 0; i < terms_to_use; i++) {
        a += a_coeffs[i] * x_power;
        x_power *= x;
    }
    double result = sqrt(a);
    *terms_used = (terms_to_use < max_terms) ? terms_to_use : max_terms;
    return result;
}
double taylor_sqrt2(double x, int max_terms, double* terms_used, double epsilon) {
    if (x == 0) {
        *terms_used = 1;
        return 0.0;
    }
    double coeffs[] = {
        1.0,                 
        -1.0 / 4.0,         
        13.0 / 96.0,            
        -17.0 / 192.0,          
        629.0 / 9216.0,          
        -437.0 / 6144.0         
    };
    int num_coeffs = 6;
    double result = 0.0;
    double x_power = 1.0;  
    double sqrt_x = sqrt(x);
    double sqrt_2 = sqrt(2.0);
    for (int n = 0; n < max_terms && n < num_coeffs; n++) {
        double term;
        if (n == 0) {
            term = sqrt_x / sqrt_2;
        }
        else {
            x_power *= x;
            term = (sqrt_x / sqrt_2) * coeffs[n] * x_power;
        }
        result += term;

        if (n > 0 && fabs(term) < epsilon) {
            *terms_used = n + 1;
            return result;
        }
    }
    *terms_used = (max_terms < num_coeffs) ? max_terms : num_coeffs;
    return result;
}
double reference_znachenie(int func_choice, double x) {
    switch (func_choice) {
    case 1: return sin(x);
    case 2: return cos(x);
    case 3: return exp(x);
    case 4: {
        double sqrt_val = sqrt(1.0 + x);
        double under_sqrt = 1.0 + x - sqrt_val;
        if (under_sqrt < 0 && under_sqrt > -1e-15) {
            under_sqrt = 0.0;
        }
        return sqrt(under_sqrt);
    }
    default: return 0.0;
    }
}

void single_calculation(int func_choice, double x, double epsilon, int n) {
    double (*taylor_func)(double, int, double*, double);
    char* func_name;

    switch (func_choice) {
    case 1:
        taylor_func = taylor_sin;
        func_name = "sin(x)";
        break;
    case 2:
        taylor_func = taylor_cos;
        func_name = "cos(x)";
        break;
    case 3:
        taylor_func = taylor_exp;
        func_name = "exp(x)";
        break;
    case 4:
        taylor_func = taylor_sqrt2;
        func_name = "sqrt(1+x - sqrt(1+x))";
        break;
    default:
        return;
    }
    printf("\n=== CALCULATION RESULTS ===\n");
    printf("Function: %s\n", func_name);
    printf("Point x = %.6f\n", x);
    printf("Tochnosty epsilon = %.10f\n", epsilon);
    printf("Max elements count N = %d\n\n", n);
    double reference = reference_znachenie(func_choice, x);
    printf("reference_znachenie: %.10f\n", reference);

    double terms_used = 0;
    double approximation = taylor_func(x, n, &terms_used, epsilon);

    printf("Approximate znachenie: %.10f\n", approximation);
    printf("Difference znacheniy: %.10f\n", fabs(approximation - reference));
    printf("count used n: %.0f\n", terms_used);

    if (terms_used == n && fabs(approximation - reference) > epsilon) {
        printf("\nWarning: the specified accuracy is not reached for %d terms!\n", n);
    }
    int v;
    scanf_s("%d", &v);
}
void series_experiment(int func_choice, double x, int nmax) {
    double (*taylor_func)(double, int, double*, double);
    char* func_name;
    switch (func_choice) {
    case 1:
        taylor_func = taylor_sin;
        func_name = "sin(x)";
        break;
    case 2:
        taylor_func = taylor_cos;
        func_name = "cos(x)";
        break;
    case 3:
        taylor_func = taylor_exp;
        func_name = "exp(x)";
        break;
    case 4:
        taylor_func = taylor_sqrt2;
        func_name = "sqrt(1+x - sqrt(1+x))";
        break;
    default:
        return;
    }
    printf("\n=== THE RESULTS OF THE SERIAL EXPERIMENT ===\n");
    printf("Function: %s\n", func_name);
    printf("Point x = %.6f\n", x);
    printf("Expirement count NMax = %d\n\n", nmax);
    double reference = reference_znachenie(func_choice, x);
    printf("The reference znachenie: %.10f\n\n", reference);
    printf("+------+------------------------+------------------------+\n");
    printf("|  N   |  Approximate znachenie |   Difference znacheniy |\n");
    printf("+------+------------------------+------------------------+\n");
    for (int n = 1; n <= nmax; n++) {
        double terms_used = 0;
        double approximation = taylor_func(x, n, &terms_used, 1e-100);
        double difference = fabs(approximation - reference);

        printf("| %4d | %22.10f | %22.10f |\n", n, approximation, difference);
    }
    printf("+------+------------------------+------------------------+\n");
    int g;
    scanf_s("%d", &g);
}