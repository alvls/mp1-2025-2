#include <stdio.h>
#include <math.h>

int main() {
    double r1, r2, x1, y1, x2, y2, d;
    printf("napishite: x1 y1 r1 x2 y2 r2.(cherez probel and bez tochki)");
    scanf_s("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2);
    double sum = r1 + r2;
    double raz = abs(r1 - r2);
    d = pow((pow((x1 - x2), 2) + pow((y1 - y2), 2)), 0.5);
    if (d <= 0 && r1 == r2) {
        printf("okr sovpadaut"); // окр совпадают.
        return 0;
    }
    if (d > sum) {
        printf("net obshix tochek"); // ќкружности наход€тс€ вне друг друга.
        return 0;
    }
    if (d < raz) {
        printf("odna v drugoi bez tochek kasania"); //ќдна окружность полностью находитс€ внутри другой.
        return 0;
    }
    if (d == sum) {
        printf("1 tochka kasania snaryshnim sposobom"); //ќкружности касаютс€ в одной точке снаружи.
        return 0;
    }
    if (d == raz && d != 0) {
        printf("1 tochka kasania vnytrenim sposobom"); // ќдна окружность касаетс€ другой изнутри в одной точке.
        return 0;
    }
    if (d > raz && d < sum) {
        printf("esti 2 obshie tocki"); //” окружностей есть две общие точки.
        return 0;
    }
}