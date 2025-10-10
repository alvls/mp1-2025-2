#include <stdio.h>
#include <math.h>

int main() {
    float density_dsp = 650.0;  
    float density_dvp = 800.0;    
    float density_wood = 500.0; 
    
    float h, w, d;
    
    printf("Введите высоту шкафа h (1.8 - 2.2 м): ");
    scanf("%f", &h);
    
    printf("Введите ширину шкафа w (0.8 - 1.2 м): ");
    scanf("%f", &w);
    
    printf("Введите глубину шкафа d (0.5 - 0.9 м): ");
    scanf("%f", &d);
    
    float thickness_dvp = 0.005; 
    float thickness_dsp = 0.015;    
    float thickness_doors = 0.01;  
    

    float area_back = h * w; 
    float volume_back = area_back * thickness_dvp;
    float mass_back = volume_back * density_dvp;
    
  
    float area_side = h * d;  
    float volume_sides = 2 * area_side * thickness_dsp;
    float mass_sides = volume_sides * density_dsp;
    
    float area_lid = w * d;  
    float volume_lids = 2 * area_lid * thickness_dsp;
    float mass_lids = volume_lids * density_dsp;
    

    float area_one_door = h * (w / 2); 
    float volume_doors = 2 * area_one_door * thickness_doors;
    float mass_doors = volume_doors * density_wood;
    
 
    float shelf_spacing = 0.4; 
    int num_shelves = (int)(h / shelf_spacing) - 1; 
    
    float area_shelf = w * d;  
    float volume_shelves = num_shelves * area_shelf * thickness_dsp;
    float mass_shelves = volume_shelves * density_dsp;
  
    float total_mass = mass_back + mass_sides + mass_lids + mass_doors + mass_shelves;
    printf("Задняя стенка: %.2f кг\n", mass_back);
    printf("Боковины: %.2f кг\n", mass_sides);
    printf("Верх/низ: %.2f кг\n", mass_lids);
    printf("Двери: %.2f кг\n", mass_doors);
    printf("Полки (%d шт): %.2f кг\n", num_shelves, mass_shelves);
    printf("Общая масса: %.2f кг\n", total_mass);
    
    return 0;
}