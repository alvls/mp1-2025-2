#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <string.h>

//структура для хранения информации о файле
typedef struct {
    char name[_MAX_FNAME];
    long size;
} FileInfo;

//прототипы функций сортировки
void bubble_sort(FileInfo* files, int count, int ascending);
void selection_sort(FileInfo* files, int count, int ascending);
void insertion_sort(FileInfo* files, int count, int ascending);
void merge_sort(FileInfo* files, int left, int right, int ascending);
void quick_sort(FileInfo* files, int low, int high, int ascending);//Хоара
void shell_sort(FileInfo* files, int count, int ascending);
void counting_sort(FileInfo* files, int count, int ascending);

//вспомогательные функции
void merge(FileInfo* files, int left, int mid, int right, int ascending);
int partition(FileInfo* files, int low, int high, int ascending);
void swap_files(FileInfo* a, FileInfo* b);
int read_directory(const char* path, FileInfo** files);
void print_files(FileInfo* files, int count);
void clear_input_buffer();

int main() {
    char path[1024];
    FileInfo* files = NULL;
    int file_count = 0;
    int choice, sort_choice, order_choice;
    clock_t start_time, end_time;
    double sort_time;

    printf("=== File Manager with Sorting ===\n\n");

    do {
        printf("Enter directory path: ");
        if (fgets(path, sizeof(path), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }
        path[strcspn(path, "\n")] = 0; //удаление символа новой строки
        file_count = read_directory(path, &files);

        if (file_count <= 0) {
            printf("No files found or error reading directory. Try again.\n\n");
            continue;
        }

        //меню выбора сортировки
        do {
            printf("\n=== Sorting Menu ===\n");
            printf("1. Bubble Sort\n");
            printf("2. Selection Sort\n");
            printf("3. Insertion Sort\n");
            printf("4. Merge Sort\n");
            printf("5. Quick Sort\n");
            printf("6. Shell Sort\n");
            printf("7. Counting Sort\n");
            printf("8. Change directory\n");
            printf("9. Exit\n");
            printf("Choose sorting method (1-9): ");

            if (scanf("%d", &sort_choice) != 1) {
                printf("Invalid input.\n");
                clear_input_buffer();
                continue;
            }
            clear_input_buffer();

            if (sort_choice == 8) break;
            if (sort_choice == 9) {
                free(files);
                return 0;
            }

            if (sort_choice < 1 || sort_choice > 7) {
                printf("Invalid choice. Please try again.\n");
                continue;
            }

            printf("\nSorting order:\n"); //выбор порядка сортировки
            printf("1. Ascending (smallest first)\n");
            printf("2. Descending (largest first)\n");
            printf("Choose order (1-2): ");

            if (scanf("%d", &order_choice) != 1 || (order_choice != 1 && order_choice != 2)) {
                printf("Invalid input. Using ascending order.\n");
                order_choice = 1;
            }
            clear_input_buffer();

            //копия массива для сортировки
            FileInfo* files_to_sort = malloc(file_count * sizeof(FileInfo));
            memcpy(files_to_sort, files, file_count * sizeof(FileInfo));

            //сортировка, замер времени
            printf("\nSorting...\n");
            start_time = clock();

            switch (sort_choice) {
            case 1:
                bubble_sort(files_to_sort, file_count, order_choice == 1);
                break;
            case 2:
                selection_sort(files_to_sort, file_count, order_choice == 1);
                break;
            case 3:
                insertion_sort(files_to_sort, file_count, order_choice == 1);
                break;
            case 4:
                merge_sort(files_to_sort, 0, file_count - 1, order_choice == 1);
                break;
            case 5:
                quick_sort(files_to_sort, 0, file_count - 1, order_choice == 1);
                break;
            case 6:
                shell_sort(files_to_sort, file_count, order_choice == 1);
                break;
            case 7:
                counting_sort(files_to_sort, file_count, order_choice == 1);
                break;
            }

            end_time = clock();
            sort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            //вывод результатов
            printf("\n=== Sorted Files ===\n");
            printf("%-30s %15s\n", "Filename", "Size (bytes)");
            printf("%-30s %15s\n", "--------", "------------");
            print_files(files_to_sort, file_count);
            printf("\nSorting time: %.6f seconds\n", sort_time);

            free(files_to_sort);

            printf("\nPress Enter to continue...");
            getchar();

        } while (1);

        free(files);
        files = NULL;

    } while (1);

    return 0;
}

//функция для чтения файлов из директории
int read_directory(const char* path, FileInfo** files) {
    struct _finddata_t file_info;
    intptr_t file_handle;
    char search_path[1024];
    int count = 0;
    int capacity = 100;

    //создание пути для поиска
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    //выделение памяти для начального массива
    *files = malloc(capacity * sizeof(FileInfo));
    if (*files == NULL) {
        return -1;
    }

    //поиск первого файла
    if ((file_handle = _findfirst(search_path, &file_info)) == -1L) {
        free(*files);
        *files = NULL;
        return -1;
    }

    do {
        if (file_info.attrib & _A_SUBDIR) {
            continue;
        }

        //увеличение массива при необходимости
        if (count >= capacity) {
            capacity *= 2;
            FileInfo* temp = realloc(*files, capacity * sizeof(FileInfo));
            if (temp == NULL) {
                free(*files);
                _findclose(file_handle);
                return -1;
            }
            *files = temp;
        }

        //сохранение информации о файле
        strncpy((*files)[count].name, file_info.name, _MAX_FNAME);
        (*files)[count].size = file_info.size;
        count++;

    } while (_findnext(file_handle, &file_info) == 0);

    _findclose(file_handle);
    return count;
}

//функция для вывода списка файлов
void print_files(FileInfo* files, int count) {
    for (int i = 0; i < count; i++) {
        printf("%-30s %15ld\n", files[i].name, files[i].size);
    }
}

//очистка буфера ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//обмен двух элементов массива
void swap_files(FileInfo* a, FileInfo* b) {
    FileInfo temp = *a;
    *a = *b;
    *b = temp;
}

//сортировка пузырьком
void bubble_sort(FileInfo* files, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((ascending && files[j].size > files[j + 1].size) ||
                (!ascending && files[j].size < files[j + 1].size)) {
                swap_files(&files[j], &files[j + 1]);
            }
        }
    }
}

//сортировка выбором
void selection_sort(FileInfo* files, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        int extreme_index = i;
        for (int j = i + 1; j < count; j++) {
            if ((ascending && files[j].size < files[extreme_index].size) ||
                (!ascending && files[j].size > files[extreme_index].size)) {
                extreme_index = j;
            }
        }
        if (extreme_index != i) {
            swap_files(&files[i], &files[extreme_index]);
        }
    }
}

//сортировка вставками
void insertion_sort(FileInfo* files, int count, int ascending) {
    for (int i = 1; i < count; i++) {
        FileInfo key = files[i];
        int j = i - 1;

        while (j >= 0 && ((ascending && files[j].size > key.size) ||
            (!ascending && files[j].size < key.size))) {
            files[j + 1] = files[j];
            j--;
        }
        files[j + 1] = key;
    }
}

//вспомогательная функция для сортировки слиянием
void merge(FileInfo* files, int left, int mid, int right, int ascending) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    FileInfo* L = malloc(n1 * sizeof(FileInfo));
    FileInfo* R = malloc(n2 * sizeof(FileInfo));

    for (i = 0; i < n1; i++)
        L[i] = files[left + i];
    for (j = 0; j < n2; j++)
        R[j] = files[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if ((ascending && L[i].size <= R[j].size) ||
            (!ascending && L[i].size >= R[j].size)) {
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

//сортировка слиянием
void merge_sort(FileInfo* files, int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(files, left, mid, ascending);
        merge_sort(files, mid + 1, right, ascending);
        merge(files, left, mid, right, ascending);
    }
}

//вспомогательная функция для быстрой сортировки
int partition(FileInfo* files, int low, int high, int ascending) {
    long pivot = files[high].size;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if ((ascending && files[j].size <= pivot) ||
            (!ascending && files[j].size >= pivot)) {
            i++;
            swap_files(&files[i], &files[j]);
        }
    }
    swap_files(&files[i + 1], &files[high]);
    return (i + 1);
}

//быстрая сортировка (Хоара)
void quick_sort(FileInfo* files, int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(files, low, high, ascending);
        quick_sort(files, low, pi - 1, ascending);
        quick_sort(files, pi + 1, high, ascending);
    }
}

//сортировка Шелла
void shell_sort(FileInfo* files, int count, int ascending) {
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            FileInfo temp = files[i];
            int j;
            for (j = i; j >= gap &&
                ((ascending && files[j - gap].size > temp.size) ||
                    (!ascending && files[j - gap].size < temp.size)); j -= gap) {
                files[j] = files[j - gap];
            }
            files[j] = temp;
        }
    }
}

//сортировка подсчетом
void counting_sort(FileInfo* files, int count, int ascending) {
    if (count == 0) return;
    long max_size = files[0].size;
    for (int i = 1; i < count; i++) {
        if (files[i].size > max_size) {
            max_size = files[i].size;
        }
    }

    // Создание массива для подсчета
    int* count_array = calloc(max_size + 1, sizeof(int));
    if (count_array == NULL) return;
    for (int i = 0; i < count; i++) {
        count_array[files[i].size]++;
    }

    // Преобразование count_array для хранения позиций
    if (ascending) {
        for (int i = 1; i <= max_size; i++) {
            count_array[i] += count_array[i - 1];
        }
    }
    else {
        for (int i = max_size - 1; i >= 0; i--) {
            count_array[i] += count_array[i + 1];
        }
    }

    //временный массив для результата
    FileInfo* output = malloc(count * sizeof(FileInfo));
    if (output == NULL) {
        free(count_array);
        return;
    }

    // создание отсортированного массива
    for (int i = count - 1; i >= 0; i--) {
        output[count_array[files[i].size] - 1] = files[i];
        count_array[files[i].size]--;
    }
    memcpy(files, output, count * sizeof(FileInfo));

    free(count_array);
    free(output);
}
//Как же сложно...