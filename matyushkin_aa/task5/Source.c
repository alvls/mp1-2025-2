#include <stdio.h>
#include <time.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>
#include <inttypes.h>

#define _parse_ans if (*ans == 'Y' || *ans == 'y') { continue; } else { is_broken = 1; break; }
#define _is_broken if (is_broken) continue;

#define BASE_DYNAMIC_SIZE 10
#define DEFAULT_INPUT_SIZE 5
#define DIRPATH_BUF_SIZE 100
#define MAX_CFILE_BUF_SIZE 200

void format_print(struct _finddata_t* c_files, const uint64_t size, const uint64_t sort_time);

uint64_t partition(struct _finddata_t* arr, uint64_t low, uint64_t high, uint8_t compare_parameter);
void quick_sort_recursive(struct _finddata_t* arr, uint64_t low, uint64_t high, uint8_t compare_parameter);
void merge(struct _finddata_t* arr, uint64_t left, uint64_t mid, uint64_t right, uint8_t compare_parameter);
void merge_sort_recursive(struct _finddata_t* arr, uint64_t left, uint64_t right, uint8_t compare_parameter);

ULONGLONG selection_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG bubble_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG insertion_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG shell_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG quick_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG merge_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);
ULONGLONG counting_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter);


const uint8_t* opcode[] = { "!h\0", "!s\0", "!e\0" };

int main() {
    printf("==== PROTOTYPE OF FILE MANAGER ====\n\n[i] Type '!h' to get manual\n\n");

    while (1) {
        printf("> ");

        uint8_t mode[20];
        memset(mode, 0, 20);

        fgets(mode, 20, stdin);
        mode[strlen(mode) - 1] = 0;

        if (!(*mode)) continue;

        if (!memcmp(mode, *opcode, 3)) {
            printf("Manual :\n\t[i] Type '!s' to start process\n\t[i] Type '!e' to exit \n\t[!] Be careful : if you make an mistake at field, you'll probably do process at begin\n\t[!] Attention : you should write correctly command, otherwise you can be faced with undefined behaviour\n");
            continue;
        }

        else if (!memcmp(mode, *(opcode + 2), 3)) {
            printf("[i] Process finished\n");
            exit(0);
        }

        else if (!memcmp(mode, *(opcode + 1), 3)) {
            uint8_t dirpath[DIRPATH_BUF_SIZE];

            struct _finddata_t* c_files;
            uint64_t current_struct_index = 0;

            intptr_t sd = 0;
            uint8_t is_broken = 0;
            uint8_t output_mode[DEFAULT_INPUT_SIZE];
            uint8_t sort_type[DEFAULT_INPUT_SIZE];
            uint8_t ans[DEFAULT_INPUT_SIZE];
            int32_t fcount = -1;

            memset(dirpath, 0, 20);

            while (1) {
                printf("Enter path to directory : ");
                fgets(dirpath, DIRPATH_BUF_SIZE, stdin);

                if (*dirpath == 0xA) continue;

                dirpath[strlen(dirpath) - 1] = 0;

                if (_access(dirpath, 0) != 0) {
                    printf("[-] Cannot find : %s\nTry again? [Y/n] : ", dirpath);
                    fgets(ans, 5, stdin);
                    memset(dirpath, 0, strlen(dirpath));
                    _parse_ans;
                }

                break;
            }

            _is_broken;

            while (1) {
                printf("Select output mode : \n\t'u' - from large files to small\n\t'd' - from small files to large\n> ");
                fgets(output_mode, DEFAULT_INPUT_SIZE, stdin);

                if (*output_mode != 'u' && *output_mode != 'd') {
                    printf("[-] Unexpected mode selector\nTry again? [Y/n] : ");
                    fgets(ans, DEFAULT_INPUT_SIZE, stdin);
                    _parse_ans;
                }

                break;
            }

            _is_broken;

            while (1) {
                printf("Select sort-type : \n\
                    \t'1' - selection sort\n\
                    \t'2' - bubble sort\n\
                    \t'3' - insertion sort\n\
                    \t'4' - shell sort\n\
                    \t'5' - quick sort\n\
                    \t'6' - merge sort\n\
                    \t'7' - counting sort\n> ");

                fgets(sort_type, DEFAULT_INPUT_SIZE, stdin);

                if (*sort_type < '1' || *sort_type > '7') {
                    printf("[-] Unexpected sort selector\nTry again? [Y/n] : ");
                    fgets(ans, DEFAULT_INPUT_SIZE, stdin);
                    _parse_ans;
                }

                break;
            }

            _is_broken;

            while (1) {
                uint8_t input[DEFAULT_INPUT_SIZE];

                printf("Enter how much files you want to watch :\n\t'0' - all\n\t<VAL> - 'val' greater or equal files\n> ");
                fgets(input, DEFAULT_INPUT_SIZE, stdin);
                if (sscanf_s(input, "%d", &fcount) <= 0) {
                    printf("[-] Incorrect format\nTry again? [Y/n] : ");
                    fgets(ans, DEFAULT_INPUT_SIZE, stdin);
                    _parse_ans;
                }

                if (fcount < 0) {
                    printf("[-] Files count must be positive\nTry again? [Y/n] : ");
                    fgets(ans, DEFAULT_INPUT_SIZE, stdin);
                    _parse_ans;
                }

                if (fcount > MAX_CFILE_BUF_SIZE) {
                    printf("[-] So large value of files count\nTry again? [Y/n] : ");
                    fgets(ans, DEFAULT_INPUT_SIZE, stdin);
                    _parse_ans;
                }

                break;
            }

            _is_broken;

            uint8_t checked_files = 0;

            uint8_t search_path[DIRPATH_BUF_SIZE];
            snprintf(search_path, sizeof(search_path), "%s\\*.*", dirpath);

            if (fcount > 0) {
                c_files = (struct _finddata_t*)calloc(fcount, sizeof(struct _finddata_t));
                uint64_t local_counter = 0;

                struct _finddata_t current_file;
                memset(&current_file, 0, sizeof(struct _finddata_t));

                if ((sd = _findfirst(search_path, &current_file)) == -1L) {
                    printf("[-] Directory is empty. You returned to the main menu\n");
                    free(c_files);
                    continue;
                }
                else {
                    do {
                        if (!strcmp(current_file.name, ".") || !strcmp(current_file.name, "..") || current_file.attrib & _A_SUBDIR) {
                            continue;
                        }

                        c_files[current_struct_index++] = current_file;
                        ++local_counter;
                    } while (!_findnext(sd, &current_file) && local_counter < fcount);
                }

                if (local_counter < fcount) {
                    c_files = (struct _finddata_t*)realloc(c_files, local_counter * sizeof(struct _finddata_t));
                    if (!local_counter) free(c_files);
                    fcount = local_counter;
                }
            }
            else {
                uint64_t c_files_capacity = BASE_DYNAMIC_SIZE;

                c_files = (struct _finddata_t*)calloc(c_files_capacity, sizeof(struct _finddata_t));

                struct _finddata_t current_file;
                memset(&current_file, 0, sizeof(struct _finddata_t));

                if ((sd = _findfirst(search_path, &current_file)) == -1L) {
                    printf("[-] Directory is empty. You returned to the main menu\n");
                    free(c_files);
                    continue;
                }
                else {
                    do {
                        if (!strcmp(current_file.name, ".") || !strcmp(current_file.name, "..") || current_file.attrib & _A_SUBDIR) {
                            continue;
                        }

                        if (current_struct_index == c_files_capacity) {
                            c_files_capacity *= 2;
                            c_files = (struct _finddata_t*)realloc(c_files, c_files_capacity * sizeof(struct _finddata_t));
                        }

                        c_files[current_struct_index++] = current_file;
                    } while (!_findnext(sd, &current_file));
                }

                c_files = (struct _finddata_t*)realloc(c_files, current_struct_index * sizeof(struct _finddata_t));
                fcount = current_struct_index;
            }

            _findclose(sd);

            ULONGLONG sort_time = 0;

            if (fcount > 1) {
                switch (*sort_type) {
                case '1': {  // Selection sort
                    if (*output_mode == 'u') {
                        sort_time = selection_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = selection_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '2': {  // Bubble sort
                    if (*output_mode == 'u') {
                        sort_time = bubble_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = bubble_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '3': {  // Insertion sort
                    if (*output_mode == 'u') {
                        sort_time = insertion_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = insertion_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '4': {  // Shell sort
                    if (*output_mode == 'u') {
                        sort_time = shell_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = shell_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '5': {  // Quick sort
                    if (*output_mode == 'u') {
                        sort_time = quick_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = quick_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '6': {  // Merge sort
                    if (*output_mode == 'u') {
                        sort_time = merge_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = merge_sort(c_files, fcount, 1);
                    }
                    break;
                }

                case '7': {  // Counting sort
                    if (*output_mode == 'u') {
                        sort_time = counting_sort(c_files, fcount, 0);
                    }
                    else if (*output_mode == 'd') {
                        sort_time = counting_sort(c_files, fcount, 1);
                    }
                    break;
                }
                }
            }

            format_print(c_files, fcount, sort_time);
            free(c_files);
        }

        else {
            printf("[-] Unexpected token : %s\n", mode);
            continue;
        }
    }

    return 0;
}

void format_print(struct _finddata_t* c_files, const uint64_t size, const uint64_t sort_time) {
    printf("Listing of .c files\n\n");
    printf("FILE         DATE %24c   SIZE\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');

    for (uint64_t i = 0; i < size; ++i) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &(c_files[i]).time_write);
        printf("%-12.12s %.24s  %10ld\n", (c_files[i]).name, buffer, (uint64_t)(c_files[i]).size);
    }

    if (!sort_time)
        printf("Sorted by : >1 ms\n");
    else {
        printf("Sorted by : %d ms\n", sort_time);
    }
}

void swap(struct _finddata_t* c_files_i, struct _finddata_t* c_files_j) {
    struct _finddata_t temp = *c_files_i;
    *c_files_i = *c_files_j;
    *c_files_j = temp;
}

ULONGLONG selection_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    for (uint64_t i = 0; i < size; ++i) {
        for (uint64_t j = i + 1; j < size; ++j) {
            if (compare_parameter) {
                if (c_files[i].size > c_files[j].size) {
                    swap(&c_files[i], &c_files[j]);
                }
            }
            else {
                if (c_files[i].size < c_files[j].size) {
                    swap(&c_files[i], &c_files[j]);
                }
            }
        }
    }

    return GetTickCount64() - begin;
}

ULONGLONG bubble_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    for (uint64_t i = 0; i < size - 1; ++i) {
        for (uint64_t j = 0; j < size - i - 1; ++j) {
            if (compare_parameter) {
                if (c_files[j].size > c_files[j + 1].size) {
                    swap(&c_files[j], &c_files[j + 1]);
                }
            }
            else {
                if (c_files[j].size < c_files[j + 1].size) {
                    swap(&c_files[j], &c_files[j + 1]);
                }
            }
        }
    }

    return GetTickCount64() - begin;
}

ULONGLONG insertion_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    for (uint64_t i = 1; i < size; ++i) {
        struct _finddata_t key = c_files[i];
        int64_t j = i - 1;

        if (compare_parameter) {  // Если не 0
            while (j >= 0 && c_files[j].size > key.size) {
                c_files[j + 1] = c_files[j];
                j--;
            }
        }
        else {  // Если 0
            while (j >= 0 && c_files[j].size < key.size) {
                c_files[j + 1] = c_files[j];
                j--;
            }
        }

        c_files[j + 1] = key;
    }

    return GetTickCount64() - begin;
}

ULONGLONG shell_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    // Последовательность Кнута
    uint64_t gap = 1;
    while (gap < size / 3) {
        gap = gap * 3 + 1;
    }

    while (gap > 0) {
        for (uint64_t i = gap; i < size; ++i) {
            struct _finddata_t temp = c_files[i];
            uint64_t j = i;

            if (compare_parameter) {  // Если не 0
                while (j >= gap && c_files[j - gap].size > temp.size) {
                    c_files[j] = c_files[j - gap];
                    j -= gap;
                }
            }
            else {  // Если 0
                while (j >= gap && c_files[j - gap].size < temp.size) {
                    c_files[j] = c_files[j - gap];
                    j -= gap;
                }
            }

            c_files[j] = temp;
        }

        gap /= 3;
    }

    return GetTickCount64() - begin;
}

// Вспомогательная функция для разделения
uint64_t partition(struct _finddata_t* arr, uint64_t low, uint64_t high, uint8_t compare_parameter) {
    uint64_t pivot = arr[high].size;
    uint64_t i = low - 1;

    for (uint64_t j = low; j < high; ++j) {
        if (compare_parameter) {  // Если не 0
            if (arr[j].size <= pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        else {  // Если 0
            if (arr[j].size >= pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Рекурсивная функция
void quick_sort_recursive(struct _finddata_t* arr, uint64_t low, uint64_t high, uint8_t compare_parameter) {
    if (low < high) {
        uint64_t pi = partition(arr, low, high, compare_parameter);

        if (pi > 0) {
            quick_sort_recursive(arr, low, pi - 1, compare_parameter);
        }
        quick_sort_recursive(arr, pi + 1, high, compare_parameter);
    }
}

// Основная функция
ULONGLONG quick_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    quick_sort_recursive(c_files, 0, size - 1, compare_parameter);

    return GetTickCount64() - begin;
}

// Функция слияния двух подмассивов
void merge(struct _finddata_t* arr, uint64_t left, uint64_t mid, uint64_t right, uint8_t compare_parameter) {
    uint64_t n1 = mid - left + 1;
    uint64_t n2 = right - mid;

    // Создаем временные массивы
    struct _finddata_t* L = (struct _finddata_t*)malloc(n1 * sizeof(struct _finddata_t));
    struct _finddata_t* R = (struct _finddata_t*)malloc(n2 * sizeof(struct _finddata_t));

    // Копируем данные во временные массивы
    for (uint64_t i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (uint64_t j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Слияние временных массивов обратно в arr[left..right]
    uint64_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compare_parameter) {  // Если не 0
            if (L[i].size <= R[j].size) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        else {  // Если 0
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

    // Копируем оставшиеся элементы L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Рекурсивная функция сортировки слиянием
void merge_sort_recursive(struct _finddata_t* arr, uint64_t left, uint64_t right, uint8_t compare_parameter) {
    if (left < right) {
        uint64_t mid = left + (right - left) / 2;

        merge_sort_recursive(arr, left, mid, compare_parameter);
        merge_sort_recursive(arr, mid + 1, right, compare_parameter);
        merge(arr, left, mid, right, compare_parameter);
    }
}

// Основная функция
ULONGLONG merge_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    merge_sort_recursive(c_files, 0, size - 1, compare_parameter);

    return GetTickCount64() - begin;
}

ULONGLONG counting_sort(struct _finddata_t* c_files, const uint64_t size, const uint8_t compare_parameter) {
    ULONGLONG begin = GetTickCount64();

    if (size == 0) return GetTickCount64() - begin;

    // Находим максимальный и минимальный размер
    uint64_t max_size = c_files[0].size;
    uint64_t min_size = c_files[0].size;

    for (uint64_t i = 1; i < size; ++i) {
        if (c_files[i].size > max_size) max_size = c_files[i].size;
        if (c_files[i].size < min_size) min_size = c_files[i].size;
    }

    uint64_t range = max_size - min_size + 1;

    // Создаем массив для подсчета
    uint64_t* count = (uint64_t*)calloc(range, sizeof(uint64_t));
    struct _finddata_t* output = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));

    // Подсчитываем количество каждого размера
    for (uint64_t i = 0; i < size; ++i) {
        count[c_files[i].size - min_size]++;
    }

    if (compare_parameter) {  // Если не 0 (по возрастанию)
        // Преобразуем count в префиксную сумму
        for (uint64_t i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        // Строим выходной массив
        for (int64_t i = size - 1; i >= 0; --i) {
            uint64_t index = c_files[i].size - min_size;
            output[count[index] - 1] = c_files[i];
            count[index]--;
        }
    }
    else {  // Если 0 (по убыванию)
        // Для убывающего порядка нужно инвертировать
        // Преобразуем count в префиксную сумму с конца
        for (uint64_t i = range - 1; i > 0; --i) {
            count[i - 1] += count[i];
        }

        // Строим выходной массив
        for (uint64_t i = 0; i < size; ++i) {
            uint64_t index = c_files[i].size - min_size;
            output[size - count[index]] = c_files[i];
            count[index]--;
        }
    }

    // Копируем отсортированный массив обратно
    for (uint64_t i = 0; i < size; ++i) {
        c_files[i] = output[i];
    }

    free(count);
    free(output);

    return GetTickCount64() - begin;
}