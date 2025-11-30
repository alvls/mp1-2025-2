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
    int max=-1;
    for (int i = 0; i < size; i++) {
        if (max < files[i].size) {
            max = files[i].size;
        }
    }
    int* count = (int*)malloc((max + 1) * sizeof(int));
    memset(count, 0,(max + 1)*sizeof(int));
    for (int i = 0; i < size; i++) {
        count[files[i].size]++;
    }
    int a = 0;
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    if (chek == 1) {
        for (int i = 0; i < max + 1; i++) {
            for (int ii = 0; ii < count[i]; ii++) {
                for (int y = 0; y < size; y++) {
                    if (files[y].size == i) {
                        temp[a++] = files[y];
                        files[y].size = -1;
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
                    if (files[y].size == i) {
                        temp[a++] = files[y];
                        files[y].size = -1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < size; i++) {
        files[i] = temp[i];
    }
    free(count);
    free(temp);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files[i].name, buffer, files[i].size);
    }
}

void shell(filesinf files[], int size, char path[300], int chek) {
    if (chek == 1) {
        for (int i = size / 2; i > 0; i /= 2) {
            for (int ii = i; ii < size; ++ii) {
                for (int y = ii - i; y >= 0 && files[y].size > files[y + i].size; y -= i) {
                    filesinf temp;
                    temp = files[y];
                    files[y] = files[y + i];
                    files[y + i] = temp;
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = size / 2; i > 0; i /= 2) {
            for (int ii = i; ii < size; ++ii) {
                for (int y = ii - i; y >= 0 && files[y].size < files[y + i].size; y -= i) {
                    filesinf temp;
                    temp = files[y];
                    files[y] = files[y + i];
                    files[y + i] = temp;
                }
            }
        }
    }
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files[i].name, buffer, files[i].size);
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
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    for (int i = 0; i < size; i++) {
        temp[i] = files[i];
    }
    hoara1(temp, 0, size - 1, chek);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10d\n", temp[i].name, buffer, temp[i].size);
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
    filesinf* temp = (filesinf*)malloc(size * sizeof(filesinf));
    for (int i = 0; i < size; i++) {
        temp[i] = files[i];
    }
    merge2(temp, 0, size - 1, chek);
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", temp[i].name, buffer, temp[i].size);
    }
    free(temp);
}

void insert(filesinf files[], size_t size, char path[300], int chek) {
    filesinf temp[MAX_FILES];
    for (int i = 0; i < size; i++) {
        strcpy(temp[i].name, files[i].name);
        temp[i].size = files[i].size;
        temp[i].time_write = files[i].time_write;
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
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &temp[i].time_write);
        printf("%-12.12s %.24s  %10d\n", temp[i].name, buffer, temp[i].size);
    }
}

void choice(filesinf files[], size_t size, char path[300], int chek) {
    if (chek == 1) {
        for (int i = 0; i < size - 1; i++) {
            filesinf min;
            min.size = 10000000000000;
            for (int ii = i + 1; ii < size; ii++) {
                filesinf temp;
                if (files[ii].size <= min.size) {
                    min.size = files[ii].size;
                    if (min.size != files[i].size) {
                        strcpy(temp.name, files[i].name);
                        temp.size = files[i].size;
                        temp.time_write = files[i].time_write;
                        strcpy(files[i].name, files[ii].name);
                        strcpy(files[ii].name, temp.name);
                        files[i].size = files[ii].size;
                        files[ii].size = temp.size;
                        files[i].time_write = files[ii].time_write;
                        files[ii].time_write = temp.time_write;
                    }
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = 0; i < size - 1; i++) {
        filesinf max;
        max.size = -1;
        for (int ii = i + 1; ii < size; ii++) {
            filesinf temp;
            if (files[ii].size > max.size) {
                max.size = files[ii].size;
                if (max.size != files[i].size) {
                    strcpy(temp.name, files[i].name);
                    temp.size = files[i].size;
                    temp.time_write = files[i].time_write;
                    strcpy(files[i].name, files[ii].name);
                    strcpy(files[ii].name, temp.name);
                    files[i].size = files[ii].size;
                    files[ii].size = temp.size;
                    files[i].time_write = files[ii].time_write;
                    files[ii].time_write = temp.time_write;
     
                    }
                }
            }
        }
    }
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files[i].name, buffer, files[i].size);
    }
}

void buble(filesinf files[], size_t size, char path[300],int chek) {
    if (chek==1){
        for (int i = 1; i < size; i++) {
            for (int ii = size - 1; ii > i-1; ii--) {
                if (files[ii].size < files[ii - 1].size) {
                    filesinf temp;
                    strcpy(temp.name, files[ii].name);
                    temp.size = files[ii].size;
                    temp.time_write = files[ii].time_write;
                    strcpy(files[ii].name, files[ii - 1].name);
                    strcpy(files[ii - 1].name, temp.name);
                    files[ii].size = files[ii - 1].size;
                    files[ii].time_write = files[ii - 1].time_write;
                    files[ii - 1].size = temp.size;
                    files[ii - 1].time_write = temp.time_write;
                }
            }
        }
    }
    if (chek == 2) {
        for (int i = 1; i < size; i++) {
            for (int ii = size - 1; ii > i-1; ii--) {
                if (files[ii].size > files[ii - 1].size) {
                    filesinf temp;
                    strcpy(temp.name, files[ii].name);
                    temp.size = files[ii].size;
                    temp.time_write = files[ii].time_write;
                    strcpy(files[ii].name, files[ii - 1].name);
                    strcpy(files[ii - 1].name, temp.name);
                    files[ii].size = files[ii - 1].size;
                    files[ii].time_write = files[ii - 1].time_write;
                    files[ii - 1].size = temp.size;
                    files[ii - 1].time_write = temp.time_write;
                }
            }
        }
    }
    printf("\nСписок файлов в: %s\n\n", path);
    printf("ФАЙЛ         ДАТА %24c   РАЗМЕР\n", ' ');
    printf("----         ---- %24c   ------\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files[i].time_write);
        printf("%-12.12s %.24s  %10ld\n", files[i].name, buffer, files[i].size);
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
        printf("---> ");
        int metod = -1;
        scanf_s("%i", &metod);
        if (metod == 1){
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            buble(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 2) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            choice(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 3) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            insert(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 4) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            merge(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 5) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            hoara(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 6) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            shell(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
        if (metod == 7) {
            printf("Как отсотировать массив\n ");
            printf("1 - по возрастанию\n ");
            printf("2 - по убыванию\n ");
            printf("---> ");
            scanf_s("%i", &chek1);
            clock_t start = clock();
            counting(file, count, path, chek1);
            clock_t end = clock();
            double seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Время сортировки: %f\n", seconds);
        }
    }
    system("pause");
}