#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_FILES 1000

typedef struct {
    char name[260];
    time_t time_write;
    int size;
}filesinf;

void counting(filesinf files[], int size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    int max=-1;
    for (int i = 0; i < size; i++) {
        if (max < files1[i].size) {
            max = files1[i].size;
        }
    }
    int* count = (int*)malloc((max + 1) * sizeof(int));
    memset(count, 0,(max + 1)*sizeof(int));
    for (int i = 0; i < size; i++) {
        count[files1[i].size]++;
    }
    int a = 0;
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    if (chek == 1) {
        for (int i = 0; i < max + 1; i++) {
            for (int ii = 0; ii < count[i]; ii++) {
                for (int y = 0; y < size; y++) {
                    if (files1[y].size == i) {
                        temp[a++] = files1[y];
                        files1[y].size = -1;
                        break;
                    }
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = max; i >= 0; i--) {
            for (int ii = 0; ii < count[i]; ii++) {
                for (int y = 0; y < size; y++) {
                    if (files1[y].size == i) {
                        temp[a++] = files1[y];
                        files1[y].size = -1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < size; i++) {
        files1[i] = temp[i];
    }
    free(count);
    free(temp);
    clock_t end = clock();
    clock_t ticks = end - start;
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files1[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files1[i].name, buffer, files1[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
}

void shell(filesinf files[], int size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    if (chek == 1) {
        for (int i = size / 2; i > 0; i /= 2) {
            for (int ii = i; ii < size; ++ii) {
                for (int y = ii - i; y >= 0 && files1[y].size > files1[y + i].size; y -= i) {
                    filesinf temp;
                    temp = files1[y];
                    files1[y] = files1[y + i];
                    files1[y + i] = temp;
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = size / 2; i > 0; i /= 2) {
            for (int ii = i; ii < size; ++ii) {
                for (int y = ii - i; y >= 0 && files1[y].size < files1[y + i].size; y -= i) {
                    filesinf temp;
                    temp = files1[y];
                    files1[y] = files1[y + i];
                    files1[y + i] = temp;
                }
            }
        }
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files1[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files1[i].name, buffer, files1[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
}

void hoara1(filesinf arr[], int low, int high, int chek) {
    if (low >= high) return;
    int middle = low + (high - low) / 2;
    int opor = arr[middle].size;

    int i = low;
    int j = high;

    while (i <= j) {
        if (chek == 1) {
            while (arr[i].size < opor) {
                i++;
            }
            while (arr[j].size > opor) {
                j--;
            }
        }
        if (chek == 2) {
            while (arr[i].size > opor) i++;
            while (arr[j].size < opor) j--;
        }

        if (i <= j) {
            filesinf temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (low < j) {
        hoara1(arr, low, j, chek);
    }
    if (i < high) {
        hoara1(arr, i, high, chek);
    }
}

void hoara(filesinf files[], int size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    for (int i = 0; i < size; i++) {
        temp[i] = files1[i];
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    hoara1(temp, 0, size - 1, chek);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10d\n", temp[i].name, buffer, temp[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
    free(temp);
}

void merge1(filesinf arr[], int left, int mid, int right, int ascending) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    filesinf* L = (filesinf*)malloc(n1 * sizeof(filesinf));
    filesinf* R = (filesinf*)malloc(n2 * sizeof(filesinf));
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (ascending == 1) {
            if (L[i].size <= R[j].size) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        else {
            if (L[i].size >= R[j].size) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void merge2(filesinf arr[], int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge2(arr, left, mid, ascending);
        merge2(arr, mid + 1, right, ascending);
        merge1(arr, left, mid, right, ascending);
    }
}

void merge(filesinf files[], int size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    for (int i = 0; i < size; i++) {
        temp[i] = files1[i];
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    merge2(temp, 0, size - 1, chek);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", temp[i].name, buffer, temp[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
    free(temp);
}

void insert(filesinf files[], size_t size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    filesinf temp[MAX_FILES];
    for (int i = 0; i < size; i++) {
        strcpy(temp[i].name, files1[i].name);
        temp[i].size = files1[i].size;
        temp[i].time_write = files1[i].time_write;
    }
    if (chek == 1) { 
        for (int i = 1; i < size; i++) {
            filesinf key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j].size > key.size) {
                strcpy(temp[j + 1].name, temp[j].name);
                temp[j + 1].size = temp[j].size;
                temp[j + 1].time_write = temp[j].time_write;
                j--;
            }
            strcpy(temp[j + 1].name, key.name);
            temp[j + 1].size = key.size;
            temp[j + 1].time_write = key.time_write;
        }
    }
    if (chek == 2) { 
        for (int i = 1; i < size; i++) {
            filesinf key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j].size < key.size) {
                strcpy(temp[j + 1].name, temp[j].name);
                temp[j + 1].size = temp[j].size;
                temp[j + 1].time_write = temp[j].time_write;
                j--;
            }
            strcpy(temp[j + 1].name, key.name);
            temp[j + 1].size = key.size;
            temp[j + 1].time_write = key.time_write;
        }
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10d\n", temp[i].name, buffer, temp[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
}

void choice(filesinf files[], size_t size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    if (chek == 1) {
        for (int i = 0; i < size - 1; i++) {
            filesinf min;
            min.size = 10000000000000;
            for (int ii = i; ii < size; ii++) {
                filesinf temp;
                if (files1[ii].size <= min.size) {
                    min.size = files1[ii].size;
                    if (min.size != files1[i].size) {
                        strcpy(temp.name, files1[i].name);
                        temp.size = files1[i].size;
                        temp.time_write = files1[i].time_write;
                        strcpy(files1[i].name, files1[ii].name);
                        strcpy(files1[ii].name, temp.name);
                        files1[i].size = files1[ii].size;
                        files1[ii].size = temp.size;
                        files1[i].time_write = files1[ii].time_write;
                        files1[ii].time_write = temp.time_write;
                    }
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = 0; i < size - 1; i++) {
            filesinf max;
            max.size = -1;
            for (int ii = i; ii < size; ii++) {
                filesinf temp;
                if (files1[ii].size >= max.size) {
                    max.size = files1[ii].size;
                    if (max.size != files1[i].size) {
                        strcpy(temp.name, files1[i].name);
                        temp.size = files1[i].size;
                        temp.time_write = files1[i].time_write;
                        strcpy(files1[i].name, files1[ii].name);
                        strcpy(files1[ii].name, temp.name);
                        files1[i].size = files1[ii].size;
                        files1[ii].size = temp.size;
                        files1[i].time_write = files1[ii].time_write;
                        files1[ii].time_write = temp.time_write;

                    }
                }
            }
        }
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files1[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files1[i].name, buffer, files1[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0) {
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
}

void buble(filesinf files[], size_t size, char path[300], int chek) {
    filesinf files1[MAX_FILES];
    for (int i = 0; i < size; i++) {
        files1[i].size = files[i].size;
        files1[i].time_write = files[i].time_write;
        strcpy(files1[i].name, files[i].name);
    }
    clock_t start = clock();
    if (chek == 1) {
        for (int i = 1; i < size; i++) {
            for (int ii = size - 1; ii > i - 1; ii--) {
                if (files1[ii].size < files1[ii - 1].size) {
                    filesinf temp;
                    strcpy(temp.name, files1[ii].name);
                    temp.size = files1[ii].size;
                    temp.time_write = files1[ii].time_write;
                    strcpy(files1[ii].name, files1[ii - 1].name);
                    strcpy(files1[ii - 1].name, temp.name);
                    files1[ii].size = files1[ii - 1].size;
                    files1[ii].time_write = files1[ii - 1].time_write;
                    files1[ii - 1].size = temp.size;
                    files1[ii - 1].time_write = temp.time_write;
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = 1; i < size; i++) {
            for (int ii = size - 1; ii > i - 1; ii--) {
                if (files1[ii].size > files1[ii - 1].size) {
                    filesinf temp;
                    strcpy(temp.name, files1[ii].name);
                    temp.size = files1[ii].size;
                    temp.time_write = files1[ii].time_write;
                    strcpy(files1[ii].name, files1[ii - 1].name);
                    strcpy(files1[ii - 1].name, temp.name);
                    files1[ii].size = files1[ii - 1].size;
                    files1[ii].time_write = files1[ii - 1].time_write;
                    files1[ii - 1].size = temp.size;
                    files1[ii - 1].time_write = temp.time_write;
                }
            }
        }
    }
    clock_t end = clock();
    clock_t ticks = end - start;
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files1[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files1[i].name, buffer, files1[i].size);
    }
    if ((double)ticks / CLOCKS_PER_SEC * 1000 == 0){
        printf("Время слишком мало для точного измерения\n");
        printf("Повторите с большим объемом данных\n");
    }
    else {
        printf("Время сортировки: % .3f мс\n", (double)ticks / CLOCKS_PER_SEC * 1000);
    }
}
int main(void){
    setlocale(LC_ALL, "Rus");
    struct _finddata_t c_file;
    intptr_t hFile;
    char path[300];
    filesinf file[MAX_FILES];
    int count = 0;
    printf("Введите путь к директории: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        printf("Ошибка ввода!\n");
    }
    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') {
        path[len - 1] = '\0';
    }
    char search_path[300];
    sprintf(search_path, "%s\\*.*", path);
    if ((hFile = _findfirst(search_path, &c_file)) == -1L)
        printf("В директории нет файлов или директория не существует!\n");
    do {
        if (count < MAX_FILES) {
            strcpy(file[count].name, c_file.name);
            file[count].time_write = c_file.time_write;
            file[count].size = c_file.size;
            count++;
        }
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < count; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &file[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", file[i].name, buffer, file[i].size);
    }
    int chek1 = 0, chek2 = 0;
    while (chek2 == 0) {
        printf("Выберите метод сортировки:\n");
        printf("1-Пузырьком\n2-Выбором\n3-Вставками\n4-Слияние\n5-Хоара\n6-Шелл\n7-Подсчет\n");
        printf("8-Выход\n");
        printf("---> ");
        int metod = -1;
        scanf_s("%i", &metod);
        if (metod == 1){
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            buble(file, count, path, chek1);
        }
        if (metod == 2) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            choice(file, count, path, chek1);
        }
        if (metod == 3) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            insert(file, count, path, chek1);
        }
        if (metod == 4) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            merge(file, count, path, chek1);
        }
        if (metod == 5) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            hoara(file, count, path, chek1);
        }
        if (metod == 6) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            shell(file, count, path, chek1);
        }
        if (metod == 7) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            counting(file, count, path, chek1);
        }
        if (metod == 8) {
            break;
        }
    }
    system("pause");
}