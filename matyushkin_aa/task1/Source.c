#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Ru");
    double DENSITY_DVP = 800, d;
    double DENSITY_DSP = 650;
    double DENSITY_WOOD = 600;  
    double height, width, depth;
    printf("Введите высоту шкафа (180-220 см): ");
    scanf_s("%lf", &height);
    printf("Введите ширину шкафа (80-120 см): ");
    scanf_s("%lf", &width);
    printf("Введите глубину шкафа (50-90 см): ");
    scanf_s("%lf", &depth);

    if (height < 180 || height > 220 || width < 80 || width > 120 || depth < 50 || depth > 90) {
        printf("Ошибка: размеры выходят за допустимые пределы.\n");
        return 1;
    }

    height /= 100;
    width /= 100;
    depth /= 100;

    double back_area = height * width;
    double back_volume = back_area * 0.005;
    double back_mass = back_volume * DENSITY_DVP;

    double side_area = height * depth;
    double side_volume = 2 * side_area * 0.015;
    double side_mass = side_volume * DENSITY_DSP;

    double lid_area = width * depth;
    double lid_volume = 2 * lid_area * 0.015;
    double lid_mass = lid_volume * DENSITY_DSP;

    double door_area = height * (width / 2);
    double door_volume = 2 * door_area * 0.01;
    double door_mass = door_volume * DENSITY_WOOD;

    int shelf_count = (int)(height * 100) / 40;
    double shelf_volume = shelf_count * width * depth * 0.015;
    double shelf_mass = shelf_volume * DENSITY_DSP;

    double total_mass = back_mass + side_mass + lid_mass + door_mass + shelf_mass;

    printf("\nМасса шкафа: %.2f кг\n", total_mass);
    printf("Детализация:\n");
    printf("- Задняя стенка: %.2f кг\n", back_mass);
    printf("- Боковины: %.2f кг\n", side_mass);
    printf("- Верхняя и нижняя крышки: %.2f кг\n", lid_mass);
    printf("- Двери: %.2f кг\n", door_mass);
    printf("- Полки (%d шт): %.2f кг\n", shelf_count, shelf_mass);

    scanf_s("%lf", &d);

    return 0;

}