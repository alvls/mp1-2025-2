#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");

    double height, width, depth;
    double chipboard_density, fiberboard_density, wood_density;

    printf("������� ������, ������, �������: ");
    scanf_s("%lf %lf %lf", &height, &width, &depth);

    printf("������� ��������� ���, ���, ������: ");
    scanf_s("%lf %lf %lf", &chipboard_density, &fiberboard_density, &wood_density);

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

    printf("����� �����: %lf", wardrobe_mass);

    system("pause");

	return 0;
}