#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");

	float pDVP = 0.85f, // ïëîòíîñòè â ã/ñì^3 
		pDSP = 0.7f,
		pWood = 0.55f;
		float mass_of_back_wall, mass_of_walls, mass_of_covers,
			mass_of_doors, mass_of_shelves, mass; 
	int h, w, d, n;

	printf("Ââåäèòå âûñîòó øêàôà â äèàïàçîíå îò 180 äî 220 ñì, øèðèíó â äèàïàçîíå îò 80 äî 120 ñì, ãëóáèíó â äèàïàçîíå îò 50 äî 90 ñì\n");
	scanf_s("%d %d %d", &h, &w, &d);
	
	while (h > 220 || h < 180 || w < 80 || w > 120 || d < 50 || d > 90) {
		printf("Âû íåïðàâèëüíî ââåëè ðàçìåðû øêàôà. Ïîïðîáóéòå åùå ðàç\n");
		scanf_s("%d %d %d", &h, &w, &d);
	}
	

	while (h > 220 || h < 180 || w < 80 || w > 120 || d < 50 || d > 90) {
		printf("Âû ââåëè íåïðàâèëüíûå ðàçìåðû øêàôà. Ïîïðîáóéòå åùå ðàç: ");
		scanf_s("%d %d %d", &h, &w, &d);
	}

	n = h / 40;
	mass_of_back_wall = h * w * 0.5 * pDVP;
	mass_of_walls = 2 * h * d * 1.5 * pDSP;
	mass_of_covers = 2 * w * d * 1.5 * pDSP;
	mass_of_doors = h * w * 1 * pWood;
	mass_of_shelves = n * (w - 3) * d * 1.5 * pDSP;
	mass = (mass_of_back_wall + mass_of_walls + mass_of_covers + mass_of_doors + mass_of_shelves) / 1000;
	printf("Âåñ âñåãî øêàôà: %f êã\n", mass);

	system("pause");
}