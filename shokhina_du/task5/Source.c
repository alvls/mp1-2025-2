#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <direct.h>
#include <windows.h>
#include <locale.h>
#include <ctype.h>

// структура для хранения информации о файле
typedef struct {
    char name[260];
    long size;
} fileinfo;

// функциb сортировки
void bubble_sort(fileinfo* files, int n, int ascending);
void selection_sort(fileinfo* files, int n, int ascending);
void insertion_sort(fileinfo* files, int n, int ascending);
void merge_sort(fileinfo* files, int left, int right, int ascending);
void quick_sort(fileinfo* files, int low, int high, int ascending);
void shell_sort(fileinfo* files, int n, int ascending);
void counting_sort(fileinfo* files, int n, int ascending);

// вспомогательные функции
void merge(fileinfo* files, int left, int mid, int right, int ascending);
int partition(fileinfo* files, int low, int high, int ascending);
void swap(fileinfo* a, fileinfo* b);
int get_max_size(fileinfo* files, int n);
int compare_files(const fileinfo* a, const fileinfo* b, int ascending);

// основные функции программы
int get_files_count(const char* path);
int load_files(const char* path, fileinfo* files);
void display_files(fileinfo* files, int count);
void clear_input_buffer();
void print_current_state(const char* path, int file_count);

int main() {
    setlocale(LC_ALL, "rus");

    char path[260] = "";
    fileinfo* files = NULL;
    int file_count = 0;
    int choice = 0;
    int sort_method = 1;
    int ascending = 1; // 1 - по возрастанию, 0 - по убыванию
    int first_run = 1;

    SetConsoleOutputCP(CP_UTF8);

    do {
        if (first_run) {
            printf("========== файловый менеджер ==========\n");
            first_run = 0;
        }

        printf("\nменю:\n");
        printf("1. указать путь к каталогу\n");
        printf("2. выбрать метод сортировки\n");
        printf("3. показать отсортированные файлы\n");
        printf("4. выход\n");
        printf("выберите действие: ");

        if (scanf_s("%d", &choice) != 1) {
            clear_input_buffer();
            printf("ошибка ввода! пожалуйста, введите число.\n");
            continue;
        }

        switch (choice) {
        case 1: {
            // ввод пути к каталогу
            printf("введите путь к каталогу: ");
            clear_input_buffer();
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = 0; // удаляем символ новой строки

            // проверка существования каталога
            if (_access(path, 0) != 0) {
                printf("ошибка: каталог не существует!\n");
                path[0] = '\0';
                file_count = 0;
                if (files) {
                    free(files);
                    files = NULL;
                }
                break;
            }

            // получаем количество файлов
            file_count = get_files_count(path);
            if (file_count == 0) {
                printf("в каталоге нет файлов или произошла ошибка!\n");
                if (files) {
                    free(files);
                    files = NULL;
                }
                break;
            }

            // выделяем память под файлы
            if (files) free(files);
            files = (fileinfo*)malloc(file_count * sizeof(fileinfo));
            if (!files) {
                printf("ошибка выделения памяти!\n");
                file_count = 0;
                break;
            }

            // загружаем информацию о файлах
            if (load_files(path, files) == 0) {
                printf("загружено %d файлов\n", file_count);
            }
            else {
                printf("ошибка загрузки файлов!\n");
                free(files);
                files = NULL;
                file_count = 0;
            }
            break;
        }

        case 2: {
            // выбор метода сортировки
            if (file_count == 0 || !files) {
                printf("сначала загрузите файлы из каталога!\n");
                break;
            }

            printf("\nметоды сортировки:\n");
            printf("1. пузырьком\n");
            printf("2. выбором\n");
            printf("3. вставками\n");
            printf("4. слиянием\n");
            printf("5. хоара\n");
            printf("6. шелла\n");
            printf("7. подсчетом\n");
            printf("выберите метод сортировки (1-7): ");

            if (scanf_s("%d", &sort_method) != 1 || sort_method < 1 || sort_method > 7) {
                printf("неверный выбор!\n");
                clear_input_buffer();
                break;
            }

            printf("порядок сортировки:\n");
            printf("1. по возрастанию размера\n");
            printf("2. по убыванию размера\n");
            printf("выберите порядок (1-2): ");

            int order_choice;
            if (scanf_s("%d", &order_choice) != 1) {
                printf("неверный выбор!\n");
                clear_input_buffer();
                break;
            }
            ascending = (order_choice == 1);

            printf("метод сортировки установлен: ");
            switch (sort_method) {
            case 1: printf("пузырьком, "); break;
            case 2: printf("выбором, "); break;
            case 3: printf("вставками, "); break;
            case 4: printf("слиянием, "); break;
            case 5: printf("хоара, "); break;
            case 6: printf("шелла, "); break;
            case 7: printf("подсчетом, "); break;
            }
            printf("%s\n", ascending ? "по возрастанию" : "по убыванию");
            break;
        }

        case 3: {
            // показ отсортированных файлов
            if (file_count == 0 || !files) {
                printf("сначала загрузите файлы из каталога!\n");
                break;
            }

            printf("\n");
            print_current_state(path, file_count);

            // создаем копию массива для сортировки
            fileinfo* files_copy = (fileinfo*)malloc(file_count * sizeof(fileinfo));
            if (!files_copy) {
                printf("ошибка выделения памяти!\n");
                break;
            }
            memcpy(files_copy, files, file_count * sizeof(fileinfo));

            // измеряем время сортировки
            clock_t start_time = clock();

            switch (sort_method) {
            case 1:
                bubble_sort(files_copy, file_count, ascending);
                break;
            case 2:
                selection_sort(files_copy, file_count, ascending);
                break;
            case 3:
                insertion_sort(files_copy, file_count, ascending);
                break;
            case 4:
                merge_sort(files_copy, 0, file_count - 1, ascending);
                break;
            case 5:
                quick_sort(files_copy, 0, file_count - 1, ascending);
                break;
            case 6:
                shell_sort(files_copy, file_count, ascending);
                break;
            case 7:
                counting_sort(files_copy, file_count, ascending);
                break;
            }

            clock_t end_time = clock();
            double sort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

            printf("метод сортировки: ");
            switch (sort_method) {
            case 1: printf("пузырьком"); break;
            case 2: printf("выбором"); break;
            case 3: printf("вставками"); break;
            case 4: printf("слиянием"); break;
            case 5: printf("хоара"); break;
            case 6: printf("шелла"); break;
            case 7: printf("подсчетом"); break;
            }
            printf(", порядок: %s\n", ascending ? "по возрастанию" : "по убыванию");
            printf("время сортировки: %.6f секунд\n\n", sort_time);

            // отображаем отсортированные файлы
            display_files(files_copy, file_count);

            free(files_copy);
            break;
        }

        case 4:
            printf("выход из программы...\n");
            break;

        default:
            printf("неверный выбор! пожалуйста, выберите от 1 до 4.\n");
            break;
        }

    } while (choice != 4);

    // освобождаем память
    if (files) free(files);

    return 0;
}

// функции для вывода информации

void print_current_state(const char* path, int file_count) {
    printf("текущий каталог: %s\n", path);
    printf("количество файлов: %d\n", file_count);
}

// функции сортировки

void bubble_sort(fileinfo* files, int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare_files(&files[j], &files[j + 1], ascending) > 0) {
                swap(&files[j], &files[j + 1]);
            }
        }
    }
}

void selection_sort(fileinfo* files, int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (compare_files(&files[j], &files[min_idx], ascending) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&files[i], &files[min_idx]);
        }
    }
}

void insertion_sort(fileinfo* files, int n, int ascending) {
    for (int i = 1; i < n; i++) {
        fileinfo key = files[i];
        int j = i - 1;

        while (j >= 0 && compare_files(&files[j], &key, ascending) > 0) {
            files[j + 1] = files[j];
            j = j - 1;
        }
        files[j + 1] = key;
    }
}

void merge_sort(fileinfo* files, int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(files, left, mid, ascending);
        merge_sort(files, mid + 1, right, ascending);

        merge(files, left, mid, right, ascending);
    }
}

void merge(fileinfo* files, int left, int mid, int right, int ascending) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    fileinfo* L = (fileinfo*)malloc(n1 * sizeof(fileinfo));
    fileinfo* R = (fileinfo*)malloc(n2 * sizeof(fileinfo));

    for (i = 0; i < n1; i++)
        L[i] = files[left + i];
    for (j = 0; j < n2; j++)
        R[j] = files[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (compare_files(&L[i], &R[j], ascending) <= 0) {
            files[k] = L[i];
            i++;
        }
        else {
            files[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        files[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        files[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void quick_sort(fileinfo* files, int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(files, low, high, ascending);

        quick_sort(files, low, pi - 1, ascending);
        quick_sort(files, pi + 1, high, ascending);
    }
}

int partition(fileinfo* files, int low, int high, int ascending) {
    fileinfo pivot = files[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compare_files(&files[j], &pivot, ascending) <= 0) {
            i++;
            swap(&files[i], &files[j]);
        }
    }
    swap(&files[i + 1], &files[high]);
    return (i + 1);
}

void shell_sort(fileinfo* files, int n, int ascending) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            fileinfo temp = files[i];
            int j;

            for (j = i; j >= gap && compare_files(&files[j - gap], &temp, ascending) > 0; j -= gap) {
                files[j] = files[j - gap];
            }
            files[j] = temp;
        }
    }
}

void counting_sort(fileinfo* files, int n, int ascending) {
    if (n == 0) return;

    int max_size = get_max_size(files, n);

    int* count = (int*)calloc(max_size + 1, sizeof(int));
    if (!count) return;

    for (int i = 0; i < n; i++) {
        count[files[i].size]++;
    }

    if (!ascending) {
        for (int i = max_size - 1; i >= 0; i--) {
            count[i] += count[i + 1];
        }
    }
    else {
        for (int i = 1; i <= max_size; i++) {
            count[i] += count[i - 1];
        }
    }

    fileinfo* output = (fileinfo*)malloc(n * sizeof(fileinfo));
    if (!output) {
        free(count);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        long size = files[i].size;
        int index = count[size] - 1;
        output[index] = files[i];
        count[size]--;
    }

    for (int i = 0; i < n; i++) {
        files[i] = output[i];
    }

    free(count);
    free(output);
}

// вспомогательные функции

int compare_files(const fileinfo* a, const fileinfo* b, int ascending) {
    if (ascending) {
        return (a->size > b->size) - (a->size < b->size);
    }
    else {
        return (b->size > a->size) - (b->size < a->size);
    }
}

void swap(fileinfo* a, fileinfo* b) {
    fileinfo temp = *a;
    *a = *b;
    *b = temp;
}

int get_max_size(fileinfo* files, int n) {
    int max = files[0].size;
    for (int i = 1; i < n; i++) {
        if (files[i].size > max) {
            max = files[i].size;
        }
    }
    return max;
}

// функции работы с файловой системой

int get_files_count(const char* path) {
    struct _finddata_t c_file;
    intptr_t hFile;
    char search_path[300];
    int count = 0;

    // создаем путь для поиска
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    if ((hFile = _findfirst(search_path, &c_file)) == -1L) {
        return 0;
    }

    do {
        // пропускаем директории
        if (!(c_file.attrib & _A_SUBDIR)) {
            count++;
        }
    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);
    return count;
}

int load_files(const char* path, fileinfo* files) {
    struct _finddata_t c_file;
    intptr_t hFile;
    char search_path[300];
    int index = 0;

    // создаем путь для поиска
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    if ((hFile = _findfirst(search_path, &c_file)) == -1L) {
        return -1;
    }

    do {
        // загружаем только файлы (не директории)
        if (!(c_file.attrib & _A_SUBDIR)) {
            strncpy(files[index].name, c_file.name, sizeof(files[index].name) - 1);
            files[index].name[sizeof(files[index].name) - 1] = '\0';
            files[index].size = c_file.size;
            index++;
        }
    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);
    return 0;
}

void display_files(fileinfo* files, int count) {
    if (count == 0) {
        printf("нет файлов для отображения.\n");
        return;
    }

    printf("%-40s %15s\n", "имя файла", "размер (байт)");
    printf("%-40s %15s\n", "----------------------------------------", "---------------");

    for (int i = 0; i < count; i++) {
        printf("%-40s %15ld\n", files[i].name, files[i].size);
    }
    printf("\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
