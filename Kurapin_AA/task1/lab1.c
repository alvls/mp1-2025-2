#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");

    double height, width, depth;
    double chipboard_density = 650, fiberboard_density = 800, wood_density = 800;

    printf("Введите высоту, ширину, глубину: ");
    scanf_s("%lf %lf %lf", &height, &width, &depth);

    height /= 100;
    width /= 100;
    depth /= 100;

    double backdoor_mass = fiberboard_density * (height * width * 0.005);
    double sidedoors_mass = 2 * chipboard_density * (height * depth * 0.015);
    double ends_mass = 2 * chipboard_density * (depth * width * 0.015);
    double doors_mass = wood_density * (height * width * 0.01);

    int shelves_count = (int)ceil(height / 0.4) - 1;
    double shelves_mass = shelves_count * chipboard_density * ((width - 0.03) * (depth - 0.015) * 0.015);
    
    double wardrobe_mass = backdoor_mass + sidedoors_mass + ends_mass + doors_mass + shelves_mass;

    printf("Масса шкафа: %lf кг\n", wardrobe_mass);

    system("pause");

	return 0;
}