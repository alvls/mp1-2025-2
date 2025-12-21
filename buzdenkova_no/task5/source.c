#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

typedef struct {
    char name[260];
    unsigned long size;
} FileData;

void bubbleSort(FileData* arr, int n);
void selectionSort(FileData* arr, int n);
void insertionSort(FileData* arr, int n);
void mergeSort(FileData* arr, int l, int r);
void quickSortHoare(FileData* arr, int low, int high);
void shellSort(FileData* arr, int n);
void countingSort(FileData* arr, int n);

void swap(FileData* a, FileData* b);
void merge(FileData* arr, int l, int m, int r);
int partitionHoare(FileData* arr, int low, int high);
void printFiles(FileData* arr, int n);
void clearInputBuffer();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    char path[200];
    char searchPath[250];
    struct _finddata_t c_file;
    intptr_t hFile;

    while (1) {
        printf("\n============================================\n");
        printf("ФАЙЛОВЫЙ МЕНЕДЖЕР (ПРОТОТИП)\n");
        printf("============================================\n");

        while (1) {
            printf("Введите путь до каталога (например, C:\\Windows): ");
            gets(path);

            strcpy(searchPath, path);
            if (path[strlen(path) - 1] != '\\') strcat(searchPath, "\\");
            strcat(searchPath, "*.*");

            hFile = _findfirst(searchPath, &c_file);
            if (hFile == -1L) {
                printf("ОШИБКА: Каталог не найден или путь неверен. Попробуйте снова.\n");
            }
            else {
                break;
            }
        }

        FileData* files = NULL;
        int count = 0;
        int capacity = 10;
        files = (FileData*)malloc(capacity * sizeof(FileData));

        do {
            if (!(c_file.attrib & _A_SUBDIR)) {
                if (count >= capacity) {
                    capacity *= 2;
                    files = (FileData*)realloc(files, capacity * sizeof(FileData));
                }
                strcpy(files[count].name, c_file.name);
                files[count].size = c_file.size;
                count++;
            }
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);

        if (count == 0) {
            printf("В данном каталоге нет файлов.\n");
            free(files);
            continue;
        }

        printf("Найдено файлов: %d\n", count);

        int choice = 0;
        while (1) {
            // Внутри цикла выбора метода сортировки, добавим пункт выхода
            printf("\nВыберите метод сортировки:\n");
            printf("1. Пузырьком (Bubble Sort)\n");
            printf("2. Выбором (Selection Sort)\n");
            printf("3. Вставками (Insertion Sort)\n");
            printf("4. Слиянием (Merge Sort)\n");
            printf("5. Хоара (Quick Sort)\n");
            printf("6. Шелла (Shell Sort)\n");
            printf("7. Подсчетом (Counting Sort)\n");
            printf("0. Выход из программы\n"); // добавляем пункт выхода
            printf("Ваш выбор: ");

            if (scanf("%d", &choice) != 1) {
                printf("Неверный ввод! Введите число.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();

            if (choice == 0) {
                printf("Завершение работы программы.\n");
                return 0; // завершение программы
            }
            if (choice < 1 || choice > 7) {
                printf("Неверный выбор сортировки!\n");
                continue;
            }


            FileData* sortedFiles = (FileData*)malloc(count * sizeof(FileData));
            memcpy(sortedFiles, files, count * sizeof(FileData));


            LARGE_INTEGER start, end, frequency;
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);

            switch (choice) {
            case 1: bubbleSort(sortedFiles, count); break;
            case 2: selectionSort(sortedFiles, count); break;
            case 3: insertionSort(sortedFiles, count); break;
            case 4: mergeSort(sortedFiles, 0, count - 1); break;
            case 5: quickSortHoare(sortedFiles, 0, count - 1); break;
            case 6: shellSort(sortedFiles, count); break;
            case 7: countingSort(sortedFiles, count); break;
            }

            QueryPerformanceCounter(&end);
            double time_spent = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

            printf("\n--- Результаты сортировки ---\n");
            printFiles(sortedFiles, count);
            printf("Время сортировки: %.10f сек.\n", time_spent);

            free(sortedFiles);
        }

        free(files);
    }
    return 0;
}


void swap(FileData* a, FileData* b) {
    FileData temp = *a;
    *a = *b;
    *b = temp;
}

void printFiles(FileData* arr, int n) {
    printf("%-30s | %10s\n", "Имя файла", "Размер (байт)");
    printf("----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (i < 50 || i > n - 10)
            printf("%-30.30s | %10lu\n", arr[i].name, arr[i].size);
        else if (i == 50)
            printf("... (список скрыт) ...\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void bubbleSort(FileData* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].size > arr[j + 1].size)
                swap(&arr[j], &arr[j + 1]);
}

void selectionSort(FileData* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].size < arr[min_idx].size)
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void insertionSort(FileData* arr, int n) {
    for (int i = 1; i < n; i++) {
        FileData key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].size > key.size) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(FileData* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    FileData* L = (FileData*)malloc(n1 * sizeof(FileData));
    FileData* R = (FileData*)malloc(n2 * sizeof(FileData));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].size <= R[j].size) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(FileData* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partitionHoare(FileData* arr, int low, int high) {
    unsigned long pivot = arr[(high + low) / 2].size;
    int i = low - 1;
    int j = high + 1;
    while (1) {
        do { i++; } while (arr[i].size < pivot);
        do { j--; } while (arr[j].size > pivot);
        if (i >= j) return j;
        swap(&arr[i], &arr[j]);
    }
}

void quickSortHoare(FileData* arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

void shellSort(FileData* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            FileData temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].size > temp.size; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void countingSort(FileData* arr, int n) {
    if (n == 0) return;

    unsigned long max = arr[0].size;
    unsigned long min = arr[0].size;

    for (int i = 1; i < n; i++) {
        if (arr[i].size > max) max = arr[i].size;
        if (arr[i].size < min) min = arr[i].size;
    }

    unsigned long range = max - min + 1;

    if (range > 50000000) {
        printf("ОШИБКА: Диапазон размеров файлов слишком велик для сортировки подсчетом.\n");
        return;
    }

    int* count = (int*)calloc(range, sizeof(int));
    FileData* output = (FileData*)malloc(n * sizeof(FileData));

    if (!count || !output) {
        printf("ОШИБКА: Нехватка памяти для сортировки подсчетом.\n");
        free(count);
        free(output);
        return;
    }

    for (int i = 0; i < n; i++)
        count[arr[i].size - min]++;

    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].size - min] - 1] = arr[i];
        count[arr[i].size - min]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}