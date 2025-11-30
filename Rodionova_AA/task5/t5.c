#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <locale.h>
#include <stdlib.h>  
#include <string.h>
#include <io.h>  
#include <time.h>  
#include <omp.h> 

struct s 
{
    char name[256]; unsigned int size;
};
typedef struct s ifile;

void sp1(ifile* arr, int size)
{
    ifile t;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-(i+1); j++)
        {
            if(arr[j].size > arr[j + 1].size)
            {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}
void sp2(ifile* arr, int size)
{
    ifile t;
    int m;
    for (int i = 0; i < size-1; i++)
    {
        m = i;
        for (int j = i+1; j < size; j++)
        {
            if (arr[j].size < arr[m].size)
            {
                m = j;
            }
            if (m != i)
            {
                t = arr[i];
                arr[i] = arr[m];
                arr[m] = t;
            }
        }
    }
}
void sp3(ifile* arr, int size)
{
    ifile t;
    int j;
    for (int i = 1; i < size; i++)
    {
        t = arr[i];
        j = i - 1;
        while ((j >= 0) && (arr[j].size > t.size))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}
void sp4a(ifile* arr, int left, int m, int right, ifile* t)
{
    int i = left;
    int j = m + 1;
    int n = left;
    while (i <= m && j <= right) 
    {
        if (arr[i].size <= arr[j].size) 
        {
            t[n++] = arr[i++];
        }
        else 
        {
            t[n++] = arr[j++];
        }
    }
    while (i <= m) 
    {
        t[n++] = arr[i++];
    }
    while (j <= right) 
    {
        t[n++] = arr[j++];
    }
    for (int x = left; x <= right; x++) 
    {
        arr[x] = t[x];
    }
}
void sp4(ifile* arr, int size)
{
    ifile* t = malloc(size * sizeof(ifile));
    for (int curr_size = 1; curr_size < size; curr_size *= 2) 
    {
        for (int start = 0; start < size - 1; start += 2 * curr_size) 
        {
            int m = start + curr_size - 1;
            if (m >= size - 1) 
            {
                continue;
            }
            int end = start + 2 * curr_size - 1;
            if (end >= size) 
            {
                end = size - 1;
            }
            sp4a(arr, start, m, end, t);
        }
    }
    free(t);
}
int srav(ifile a, ifile b)
{
    int r;
    if (a.size > b.size)
    {
        r = 1;
    }
    else if (a.size < b.size)
    {
        r = -1;
    }
    else
    {
        r = 0;
    }
    return r;
}
void sp6(ifile* arr, int size)
{
    ifile t;
    for (int s = size / 2; s > 0; s /= 2)
    {
        for (int i = s; i < size; ++i)
        {
            for (int j = i - s; (j >= 0) && (arr[j].size > arr[j + s].size); j -= s)
            {
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
}
void sp7(ifile* arr, int size)
{
    unsigned int min_size = arr[0].size;
    unsigned int max_size = arr[0].size;
    double d, e;
    d = omp_get_wtime();
    for (int i = 1; i < size; i++) {
        if (arr[i].size < min_size)
        {
            min_size = arr[i].size;
        }
        if (arr[i].size > max_size)
        {
            max_size = arr[i].size;
        }
    }
    unsigned int range = max_size - min_size + 1;
    if (range > 10000000) {
        printf("превышение допустимого размера файлов (%u).\n", range);
        return;
    }
    int* count = (int*)calloc(range, sizeof(int));
    ifile* output = malloc(size * sizeof(ifile));
    for (int i = 0; i < size; i++) {
        count[arr[i].size - min_size]++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        unsigned int index = arr[i].size - min_size;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
    memcpy(arr, output, size * sizeof(ifile));
    free(count);
    free(output);
    e = omp_get_wtime();
    printf("сортировка завершена за время: %lf\n", e - d);
}
int main(void)
{
    struct _finddata_t c_file;
    char* locale = setlocale(LC_ALL, "");
    intptr_t hFile;
    char path[200];
    int a, size = 4, count = 0, b=0, c=0;
    double d, e;

    ifile* arr = malloc(size * sizeof(ifile));
    do
    {
        printf("выберите действие\n");
        printf("1 - ввести директорию \n");
        printf("2 - выбрать метод сортировки\n");
        printf("3 - вывести директорию\n");
        printf("4 - выход\n");
        scanf_s("%d", &a);
        switch (a)
        {
        case 1:
        {
            scanf_s("%s", path, 200);
            snprintf(path, sizeof(path), "%s/%s", path, "*.*");
            if ((hFile = _findfirst(path, &c_file)) == -1L)
            {
                printf("No files in current directory!\n");
                continue;
            }
            else
            {
                count = 0;
                do {

                    if (count >= size)
                    {
                        size *= 2;
                        arr = realloc(arr, size * sizeof(ifile));
                    }
                    memcpy(arr[count].name, c_file.name, sizeof(arr[count].name) - 1);
                    arr[count].name[sizeof(arr[count].name) - 1] = '\0';
                    arr[count].size = c_file.size;
                    count++;
                } while (_findnext(hFile, &c_file) == 0);
                _findclose(hFile);
            }
            continue;

        }
        case 2:
        {
            printf("выберите вариант сортировки\n");
            printf("1 - по возрастанию\n");
            printf("2 - по убыванию\n");
            scanf_s("%d", &b);
            printf("выберите метод сортировки\n");
            printf("1 - пузырьком\n");
            printf("2 - выбором\n");
            printf("3 - вставками\n");
            printf("4 - слиянием\n");
            printf("5 - Хоара\n");
            printf("6 - Шелла\n");
            printf("7 - подсчётом\n");
            scanf_s("%d", &c);
            switch (c)
            {
            case 1:
            {
                d = omp_get_wtime();
                sp1(arr, count);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 2:
            {
                d = omp_get_wtime();
                sp2(arr, count);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 3:
            {
                d = omp_get_wtime();
                sp3(arr, count);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 4:
            {
                d = omp_get_wtime();
                sp4(arr, count);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 5:
            {
                d = omp_get_wtime();
                qsort(arr, count, sizeof(ifile), srav);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 6:
            {
                d = omp_get_wtime();
                sp6(arr, count);
                e = omp_get_wtime();
                printf("сортировка завершена за время: %lf\n", e - d);
                continue;
            }
            case 7:
            {
                sp7(arr, count);
                continue;
            }
            default:
                break;
            }
        }
        case 3:
        {
            printf("FILE%24c   SIZE\n", ' ');
            printf("----%24c   ----\n", ' ');
            if (b == 1)
            {
                for (int i = 0; i < count; i++)
                {
                    printf("%-12.12s %.24s  %10ld\n", arr[i].name, " ", arr[i].size);
                }
            }
            else
            {
                for (int i = count-1; i >=0; i--)
                {
                    printf("%-12.12s %.24s  %10ld\n", arr[i].name, " ", arr[i].size);
                }
            }
            continue;
        }
        case 4:
        {
            break;
        }
        default:
            continue;
        }
    }while (1);
    free(arr);
}