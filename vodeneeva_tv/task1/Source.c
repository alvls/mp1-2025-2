#include <stdio.h>
#include <math.h>

int main() 
{
    float t_zs = 0.5, t_b = 1.5, t_k = 1.5, t_d = 1;
    int p_dsp = 700, p_dvp = 800, p_d = 650;
    int height, width, depth;
    printf("Введите высоту (от 180см до 220см), ширину (от 80см до 120см) и глубину шкафа (от 50см до 90см) в см (значения вводите через пробел): "); 
    scanf("%d %d %d", &height, &width, &depth);
    printf("Размеры шкафа: \tвысота: %dсм \tширина: %dсм \tглубина: %dсм\n", height, width, depth );
    printf("\n");
    if (height < 180 || height > 220){
        printf("Введено некорректное значение для высоты!\n");
        return 0;
    }
    if (width < 80 || width > 120){
        printf("Введено некорректное значение для ширины!\n");
        return 0;
    }
    if (depth < 50 || depth > 90){
        printf("Введено некорректное значение для глубины!\n");
        return 0;
    }
    double weight_zs =  height * width * p_dvp * t_zs;
    double weight_b = p_dsp * height * depth * t_b;
    double weight_k = p_dsp * width * depth * t_k;
    double weight_d = p_d * width * height * t_d;
    int count_p = height / (40 + t_k);
    double weight_p = p_dsp * t_d * width * depth * count_p;
    double weight = ((weight_zs + 2 * weight_b +  2 * weight_k + weight_d + weight_p) / 1000000);
    printf("Масса шкафа: \t %.2f кг\n", weight);

    return 0;
}
