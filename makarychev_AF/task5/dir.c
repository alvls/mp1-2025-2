#include <stdio.h>
#include <dirent.h>
#include <locale.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/stat.h>
#include <string.h>
struct diR { char name[256]; unsigned int size; int mode; short size_dir;};
typedef struct diR direct;
void output(direct* cat, char mode[5],int size)
{
	printf("ИМЯ         ТИП %8c   РАЗМЕР\n", ' ');
	printf("---         --- %8c   ------\n", ' ');
	if (strcmp(mode, "LEFT") == 0)
	{
		for (int i = 0; i < size; i++)
		{
			printf("%-12.12s %.8s  %10ld\n",cat[i].name,cat[i].mode ? "DIR":"FILE",cat[i].size);
		}
	}
	else
	{
		for (int i = size-1; i >=0; i--)
		{
			printf("%-12.12s %.8s  %10ld\n", cat[i].name, cat[i].mode ? "DIR" : "FILE", cat[i].size);
		}
	}
}
direct* record(char directory[255])
{
	DIR* dir;
	char path[500];
	struct dirent* ent;
	struct stat info;
	int count = 0, size = 10;
	dir = opendir(directory);
	if (dir == NULL)
	{
		printf("ВВЕДЕНА НЕПРАВИЛЬНАЯ ДИРЕКТОРИЯ\n");
		return NULL;
	}
	direct* cat = malloc(size * sizeof(direct));
	while ((ent = readdir(dir)) != 0) {
		if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))
		{
			continue;
		}
		if (count >= size)
		{
			size *= 2;
			cat = realloc(cat, size * sizeof(direct));
		}
		memcpy(cat[count].name, ent->d_name, sizeof(cat[count].name) - 1);
		cat[count].name[sizeof(cat[count].name) - 1] = '\0';
		snprintf(path, sizeof(path), "%s/%s", directory, ent->d_name);
		stat(path, &info);
		cat[count].size = info.st_size;
		cat[count].mode = S_ISDIR(info.st_mode);
		count++;
	}
	cat[0].size_dir = count;
	closedir(dir);
	return cat;
}
void bubble(direct* cat, int size)
{
	direct temp;
	int ind;
	for (int i = 0; i < size; i++)
	{
		ind = 0;
		for (int j = 0 ; j < size - (i+1); j++)
		{
			if (cat[j].size > cat[j + 1].size)
			{
				temp = cat[j];
				cat[j] = cat[j + 1];
				cat[j + 1] = temp;
				ind++;
			}
		}
		if (ind == 0)
		{
			break;
		}
	}
	cat[0].size_dir = size;
}
void select(direct* cat, int size)
{
	direct temp;
	int min;
	for (int i = 0; i < size-1; i++)
	{
		min = i;
		for (int j = i + 1; j < size ; j++)
		{
			if (cat[j].size < cat[min].size)
			{
				min = j;
			}
		}
		if (min != i)
		{
			temp = cat[i];
			cat[i] = cat[min];
			cat[min] = temp;
		}
	}
	cat[0].size_dir = size;
}
void insert(direct* cat, int size)
{
	direct key;
	int j;
	for (int i = 1; i < size; i++)
	{
		key = cat[i];
		j = i - 1;
		while ((j >= 0) && (cat[j].size > key.size))
		{
			cat[j + 1] = cat[j];
			j--;
		}
		cat[j + 1] = key;
	}
	cat[0].size_dir = size;
}
void merge(direct* cat,int left,int mid,int right,direct*temp)
{
	int i = left;      
	int j = mid + 1;   
	int k = left;     
	while (i <= mid && j <= right) {
		if (cat[i].size <= cat[j].size) {
			temp[k++] = cat[i++];
		}
		else {
			temp[k++] = cat[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = cat[i++];
	}
	while (j <= right) {
		temp[k++] = cat[j++];
	}
	memcpy(cat, temp, sizeof(*cat) / sizeof(direct));
}
void mergeSort(direct* cat, int size)
{
	direct* temp = malloc(cat[0].size_dir * sizeof(direct));
	for (int curr_size = 1; curr_size < size; curr_size *= 2) {
		for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size) {
			int mid = left_start + curr_size - 1;
			if (mid >= size - 1) {
				continue;
			}
			int right_end = left_start + 2 * curr_size - 1;
			if (right_end >= size) {
				right_end = size - 1;
			}
			merge(cat, left_start, mid, right_end, temp);
		}
	}
	cat[0].size_dir = size;
	free(temp);
}
int sim(direct a, direct b)
{
	int res;
	if (a.size > b.size)
	{
		res = 1;
	}
	else if (a.size < b.size)
	{
		res = -1;
	}
	else
	{
		res = 0;
	}
	return res;
}
void SortShell(direct* cat, int size)
{
	direct temp;
	for (int s = size / 2; s > 0; s /= 2)
	{
		for (int i = s; i < size; ++i)
		{
			for (int j = i - s; (j >= 0) && (cat[j].size > cat[j + s].size); j -= s)
			{
				temp = cat[j];
				cat[j] = cat[j + 1];
				cat[j + 1] = temp;
			}
		}
	}
	cat[0].size_dir = size;
}
void Countsort(direct*cat,int size)
{
	unsigned int min_size = cat[0].size;
	unsigned int max_size = cat[0].size;
	double st, end;
	st = omp_get_wtime();
	for (int i = 1; i < size; i++) {
		if (cat[i].size < min_size)
		{
			min_size = cat[i].size;
		}
		if (cat[i].size > max_size)
		{
			max_size = cat[i].size;
		}
	}
	unsigned int range = max_size - min_size + 1;
	if (range > 10000000) { 
		printf("Диапазон значений слишком большой для сортировки подсчетом (%u).\n", range);
		printf("Рекомендуется использовать другую сортировку.\n");
		return;
	}
	int* count = (int*)calloc(range, sizeof(int));
	direct* output =malloc(size * sizeof(direct));
	for (int i = 0; i < size; i++) {
		count[cat[i].size - min_size]++;
	}
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}
	for (int i = size - 1; i >= 0; i--) {
		unsigned int index = cat[i].size - min_size;
		output[count[index] - 1] = cat[i];
		count[index]--;
	}
	memcpy(cat, output, size * sizeof(direct));
	free(count);
	free(output);
	cat[0].size_dir = size;
	end = omp_get_wtime();
	printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
}
void main()
{
	char* locale = setlocale(LC_ALL, "");
	int flag1 = 1, flag2, choise;
	double st, end;
	char directory[255] = "", mode_output[6] = "LEFT";
	direct* cat = ('1', 1);
	printf("Добро пожаловать в Лабароторную работу номер 5\n=========ПРОТОТИП ФАЙЛОВОГО МЕНЕДЖЕРА=========\n");
	do {
		flag2 = 1;
		printf("Для дальнейшей работы введите директорию\nДля завершения введите END\nВвод: ");
		scanf_s(" %s", directory, 255);
		if (strcmp(directory, "END") == 0)
		{
			break;
		}
		direct* cat = record(directory);
		if ((cat) != NULL)
		{
			printf("Директория введена верно\n");
		}
		else
		{
			continue;
		}
		do
		{
			printf("Выбирите действие:\n1.Вывести директорию\n2.Отсортировать директорию\n3.Ввернуться к вводу\nВаше действие: ");
			scanf_s(" %d", &choise);
			switch (choise)
			{
			case 1:
			{
				output(cat, mode_output, cat[0].size_dir);
				continue;
			}
			case 2:
			{
				printf("Сортировать:\n1.По возрастанию размера\n2.По убыванию размера\nВвод: ");
				scanf_s("%i", &choise);
				if (choise == 1)
				{
					strcpy_s(mode_output, 6, "LEFT");
				}
				else if (choise == 2)
				{
					strcpy_s(mode_output, 6, "RIGHT");
				}
				else
				{
					printf("Ошибка ввода\n");
					continue;
				}
				printf("Выбирите метод сортировки:\n1.пузырьком\n2.выбором\n3.вставками\n4.слиянием\n5.Хоара\n6.Шелла\n7.подсчетом\nВвод: ");
				scanf_s("%i", &choise);
				switch (choise)
				{
				case 1:
				{
					st = omp_get_wtime();
					bubble(cat, cat[0].size_dir);
					end = omp_get_wtime();
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 2:
				{
					st = omp_get_wtime();
					select(cat, cat[0].size_dir);
					end = omp_get_wtime();
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 3:
				{
					st = omp_get_wtime();
					insert(cat, cat[0].size_dir);
					end = omp_get_wtime();
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 4:
				{
					st = omp_get_wtime();
					mergeSort(cat, cat[0].size_dir);
					end = omp_get_wtime();
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 5:
				{
					int* p = malloc(sizeof(int));
					*p = cat[0].size_dir;
					st = omp_get_wtime();
					qsort(cat, cat[0].size_dir, sizeof(direct), sim);
					end = omp_get_wtime();
					cat[0].size_dir = *p;
					free(p);
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 6:
				{
					st = omp_get_wtime();
					SortShell(cat, cat[0].size_dir);
					end = omp_get_wtime();
					printf("Содержимое дириктории успешно отсортировано за %lf секунд\n", end - st);
					continue;
				}
				case 7:
				{
					Countsort(cat, cat[0].size_dir);
					continue;
				}
				default:
				{
					printf("Ошибка ввода\n");
					continue;
				}
				}
			}
			case 3:
			{
				flag2 = 0;
				continue;
			}
			default:
			{
				printf("Введена неправльная команда");
				continue;
			}
			}
		} while (flag2);
	} while (flag1);
	free(cat);
}