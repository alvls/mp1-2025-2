#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

typedef struct {
    char name[260];
    long size;
} FileInfo;

typedef struct {
    FileInfo* files;
    int count;
} FileList;

void bubbleSort(FileInfo* arr, int n, int ascending);
void selectionSort(FileInfo* arr, int n, int ascending);
void insertionSort(FileInfo* arr, int n, int ascending);
void mergeSort(FileInfo* arr, int left, int right, int ascending);
void quickSort(FileInfo* arr, int low, int high, int ascending);
void shellSort(FileInfo* arr, int n, int ascending);
void countingSort(FileInfo* arr, int n, int ascending);

FileList getFileList(const char* path);
void printFileList(FileList fileList);
void freeFileList(FileList* fileList);
void copyFileList(FileInfo* dest, FileInfo* src, int n);
void displayMenu();

int main() {
    setlocale(LC_ALL, "Ru_ru.UTF8");

    char path[260];
    FileList originalList;
    FileList sortedList;
    int choice, direction;
    clock_t start, end;
    double cpu_time_used;

    printf("========== ФАЙЛОВЫЙ МЕНЕДЖЕР С СОРТИРОВКОЙ ==========\n");

    printf("Введите путь к директории: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        printf("Ошибка ввода пути.\n");
        return 1;
    }

    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') {
        path[len - 1] = '\0';
    }

    originalList = getFileList(path);

    if (originalList.count == 0) {
        printf("В указанной директории нет файлов или директория не существует.\n");
        return 1;
    }

    sortedList.files = (FileInfo*)malloc(originalList.count * sizeof(FileInfo));
    if (sortedList.files == NULL) {
        printf("Ошибка выделения памяти.\n");
        freeFileList(&originalList);
        return 1;
    }
    sortedList.count = originalList.count;

    do {
        displayMenu();
        printf("Выберите действие: ");
        if (scanf_s("%d", &choice) != 1) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 0) {
            break;
        }

        if (choice == 8) {
            printf("Введите новый путь к директории: ");
            if (fgets(path, sizeof(path), stdin) == NULL) {
                printf("Ошибка ввода пути.\n");
                continue;
            }

            len = strlen(path);
            if (len > 0 && path[len - 1] == '\n') {
                path[len - 1] = '\0';
            }

            freeFileList(&originalList);
            free(sortedList.files);

            originalList = getFileList(path);

            if (originalList.count == 0) {
                printf("В указанной директории нет файлов или директория не существует.\n");
                break;
            }

            sortedList.files = (FileInfo*)malloc(originalList.count * sizeof(FileInfo));
            if (sortedList.files == NULL) {
                printf("Ошибка выделения памяти.\n");
                freeFileList(&originalList);
                return 1;
            }
            sortedList.count = originalList.count;

            printf("Директория успешно изменена.\n");
            continue;
        }

        if (choice < 1 || choice > 7) {
            printf("Неверный выбор. Попробуйте снова.\n");
            continue;
        }

        printf("Выберите направление сортировки:\n");
        printf("1. По возрастанию (от меньшего к большему)\n");
        printf("2. По убыванию (от большего к меньшему)\n");
        printf("Ваш выбор: ");
        if (scanf_s("%d", &direction) != 1) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (direction != 1 && direction != 2) {
            printf("Неверный выбор направления. Используется сортировка по возрастанию.\n");
            direction = 1;
        }

        copyFileList(sortedList.files, originalList.files, originalList.count);

        start = clock();

        switch (choice) {
        case 1:
            bubbleSort(sortedList.files, sortedList.count, direction == 1);
            break;
        case 2:
            selectionSort(sortedList.files, sortedList.count, direction == 1);
            break;
        case 3:
            insertionSort(sortedList.files, sortedList.count, direction == 1);
            break;
        case 4:
            mergeSort(sortedList.files, 0, sortedList.count - 1, direction == 1);
            break;
        case 5:
            quickSort(sortedList.files, 0, sortedList.count - 1, direction == 1);
            break;
        case 6:
            shellSort(sortedList.files, sortedList.count, direction == 1);
            break;
        case 7:
            countingSort(sortedList.files, sortedList.count, direction == 1);
            break;
        }

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\n========== РЕЗУЛЬТАТЫ СОРТИРОВКИ ==========\n");
        printf("Метод сортировки: ");
        switch (choice) {
        case 1: printf("Пузырьком"); break;
        case 2: printf("Выбором"); break;
        case 3: printf("Вставками"); break;
        case 4: printf("Слиянием"); break;
        case 5: printf("Хоара (быстрая)"); break;
        case 6: printf("Шелла"); break;
        case 7: printf("Подсчетом"); break;
        }
        printf("\nНаправление: %s\n", direction == 1 ? "по возрастанию" : "по убыванию");
        printf("Время сортировки: %.6f секунд\n\n", cpu_time_used);

        printFileList(sortedList);

    } while (choice != 0);

    freeFileList(&originalList);
    free(sortedList.files);

    printf("Программа завершена.\n");

    return 0;
}

void displayMenu() {
    printf("\n========== МЕНЮ СОРТИРОВКИ ==========\n");
    printf("1. Сортировка пузырьком\n");
    printf("2. Сортировка выбором\n");
    printf("3. Сортировка вставками\n");
    printf("4. Сортировка слиянием\n");
    printf("5. Сортировка Хоара (быстрая)\n");
    printf("6. Сортировка Шелла\n");
    printf("7. Сортировка подсчетом\n");
    printf("8. Сменить директорию\n");
    printf("0. Выход\n");
}

FileList getFileList(const char* path) {
    FileList fileList = { NULL, 0 };
    struct _finddata_t c_file;
    intptr_t hFile;
    char searchPath[520];

    _snprintf(searchPath, sizeof(searchPath), "%s\\*.*", path);

    if ((hFile = _findfirst(searchPath, &c_file)) == -1L) {
        return fileList;
    }

    int count = 0;
    do {
        if (!(c_file.attrib & _A_SUBDIR)) {
            count++;
        }
    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);

    if (count == 0) {
        return fileList;
    }

    fileList.files = (FileInfo*)malloc(count * sizeof(FileInfo));
    if (!fileList.files) {
        fileList.count = 0;
        return fileList;
    }

    hFile = _findfirst(searchPath, &c_file);
    int index = 0;
    do {
        if (!(c_file.attrib & _A_SUBDIR)) {
            strncpy(fileList.files[index].name, c_file.name, 259);
            fileList.files[index].name[259] = '\0';
            fileList.files[index].size = c_file.size;
            index++;
        }
    } while (_findnext(hFile, &c_file) == 0 && index < count);

    _findclose(hFile);
    fileList.count = count;

    return fileList;
}

void printFileList(FileList fileList) {
    printf("%-40s %15s\n", "Имя файла", "Размер (байт)");
    printf("%-40s %15s\n", "---------", "-------------");

    for (int i = 0; i < fileList.count; i++) {
        printf("%-40s %15ld\n", fileList.files[i].name, fileList.files[i].size);
    }

    printf("\nВсего файлов: %d\n", fileList.count);
}

void freeFileList(FileList* fileList) {
    if (fileList->files) {
        free(fileList->files);
        fileList->files = NULL;
        fileList->count = 0;
    }
}

void copyFileList(FileInfo* dest, FileInfo* src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void bubbleSort(FileInfo* arr, int n, int ascending) {
    int i, j;
    FileInfo temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (ascending) {
                if (arr[j].size > arr[j + 1].size) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
            else {
                if (arr[j].size < arr[j + 1].size) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void selectionSort(FileInfo* arr, int n, int ascending) {
    int i, j, min_max_idx;
    FileInfo temp;

    for (i = 0; i < n - 1; i++) {
        min_max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (ascending) {
                if (arr[j].size < arr[min_max_idx].size) {
                    min_max_idx = j;
                }
            }
            else {
                if (arr[j].size > arr[min_max_idx].size) {
                    min_max_idx = j;
                }
            }
        }

        temp = arr[min_max_idx];
        arr[min_max_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(FileInfo* arr, int n, int ascending) {
    int i, j;
    FileInfo key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        if (ascending) {
            while (j >= 0 && arr[j].size > key.size) {
                arr[j + 1] = arr[j];
                j--;
            }
        }
        else {
            while (j >= 0 && arr[j].size < key.size) {
                arr[j + 1] = arr[j];
                j--;
            }
        }

        arr[j + 1] = key;
    }
}

void merge(FileInfo* arr, int left, int mid, int right, int ascending) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    FileInfo* L = (FileInfo*)malloc(n1 * sizeof(FileInfo));
    FileInfo* R = (FileInfo*)malloc(n2 * sizeof(FileInfo));

    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        return;
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (ascending) {
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

void mergeSort(FileInfo* arr, int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, ascending);
        mergeSort(arr, mid + 1, right, ascending);
        merge(arr, left, mid, right, ascending);
    }
}

int partition(FileInfo* arr, int low, int high, int ascending) {
    FileInfo pivot = arr[high];
    FileInfo temp;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (ascending) {
            if (arr[j].size <= pivot.size) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        else {
            if (arr[j].size >= pivot.size) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(FileInfo* arr, int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, ascending);

        quickSort(arr, low, pi - 1, ascending);
        quickSort(arr, pi + 1, high, ascending);
    }
}

void shellSort(FileInfo* arr, int n, int ascending) {
    int gap, i, j;
    FileInfo temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];

            if (ascending) {
                for (j = i; j >= gap && arr[j - gap].size > temp.size; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            }
            else {
                for (j = i; j >= gap && arr[j - gap].size < temp.size; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            }

            arr[j] = temp;
        }
    }
}

void countingSort(FileInfo* arr, int n, int ascending) {
    if (n <= 0) return;

    long max = arr[0].size;
    long min = arr[0].size;
    for (int i = 1; i < n; i++) {
        if (arr[i].size > max) max = arr[i].size;
        if (arr[i].size < min) min = arr[i].size;
    }

    long range = max - min + 1;

    long* count = (long*)calloc(range, sizeof(long));
    if (!count) return;

    for (int i = 0; i < n; i++) {
        count[arr[i].size - min]++;
    }

    if (ascending) {
        for (long i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
    }
    else {
        for (long i = range - 2; i >= 0; i--) {
            count[i] += count[i + 1];
        }
    }

    FileInfo* output = (FileInfo*)malloc(n * sizeof(FileInfo));
    if (!output) {
        free(count);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].size - min] - 1] = arr[i];
        count[arr[i].size - min]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count); //@#$$@$@
    free(output);
}