#include <stdio.h>
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <locale.h>
#include <string.h>

struct FileInfo {
    char name[200];
    time_t write_time;
    long size;
};

struct FileInfo* CollectFiles(char* path, int* file_count) {
    struct _finddata_t c_file;
    intptr_t hFile;
    int count = 0;
    int capacity = 100;

    struct FileInfo* files = (struct FileInfo*)malloc(capacity * sizeof(struct FileInfo));

    if ((hFile = _findfirst(path, &c_file)) == -1L) {
        free(files);
        return NULL;
    }

    do {
        if (count >= capacity) {
            capacity *= 2;
            files = (struct FileInfo*)realloc(files, capacity * sizeof(struct FileInfo));
        }

        strcpy_s(files[count].name, sizeof(files[count].name), c_file.name);
        files[count].write_time = c_file.time_write;
        files[count].size = c_file.size;

        count++;
    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);

    *file_count = count;
    return files;
}

void ShowFiles(struct FileInfo* files, int file_count, double time_used) {
    int count = 0;

    printf("\nСписок файлов:\n\n");
    printf("FILE         DATE %24c   SIZE\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');
    do {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &files[count].write_time);
        printf("%-12.12s %.24s  %10ld\n", files[count].name, buffer, files[count].size);
        count++;
    } while (count < file_count);

    printf("\nКоличество файлов: %d\n", file_count);
    printf("Время сортировки: %f секунд\n", time_used);
}

struct FileInfo* BubbleSort(struct FileInfo* files, int file_count) {
    for (int i = 0; i < file_count - 1; i++) {
        int isSorted = 1;

        for (int j = 0; j < file_count - i - 1; j++) {
            if (files[j].size > files[j + 1].size) {
                struct FileInfo temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
                isSorted = 0;
            }
        }

        if (isSorted) {
            break;
        }
    }

    return files;
}

struct FileInfo* SelectionSort(struct FileInfo* files, int file_count) {
    for (int i = 0; i < file_count - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < file_count; j++) {
            if (files[j].size < files[min_index].size) {
                min_index = j;
            }
        }

        if (min_index != i) {
            struct FileInfo temp = files[i];
            files[i] = files[min_index];
            files[min_index] = temp;
        }
    }

    return files;
}

struct FileInfo* InsertionSort(struct FileInfo* files, int file_count) {
    for (int i = 1; i < file_count; i++) {
        struct FileInfo current = files[i];
        int j = i - 1;

        while (j >= 0 && files[j].size > current.size) {
            files[j + 1] = files[j];
            j--;
        }

        files[j + 1] = current;
    }

    return files;
}

struct FileInfo* MergeSort(struct FileInfo* files, int file_count) {
    if (file_count <= 1) {
        return files;
    }

    int mid = file_count / 2;
    int left_count = mid;
    int right_count = file_count - mid;

    struct FileInfo* left = (struct FileInfo*)malloc(left_count * sizeof(struct FileInfo));
    struct FileInfo* right = (struct FileInfo*)malloc(right_count * sizeof(struct FileInfo));

    memcpy(left, files, left_count * sizeof(struct FileInfo));
    memcpy(right, files + mid, right_count * sizeof(struct FileInfo));

    MergeSort(left, left_count);
    MergeSort(right, right_count);

    int i = 0, j = 0, k = 0;
    while (i < left_count && j < right_count) {
        if (left[i].size <= right[j].size) {
            files[k++] = left[i++];
        }
        else {
            files[k++] = right[j++];
        }
    }

    while (i < left_count) {
        files[k++] = left[i++];
    }
    while (j < right_count) {
        files[k++] = right[j++];
    }

    free(left);
    free(right);

    return files;
}

struct FileInfo* QuickSort(struct FileInfo* files, int low, int high) {
    if (low < high) {
        long pivot = files[low].size;
        int i = low - 1;
        int j = high + 1;

        while (1) {
            do {
                i++;
            } while (files[i].size < pivot);

            do {
                j--;
            } while (files[j].size > pivot);

            if (i >= j) {
                break;
            }

            struct FileInfo temp = files[i];
            files[i] = files[j];
            files[j] = temp;
        }

        QuickSort(files, low, j);
        QuickSort(files, j + 1, high);
    }

    return files;
}

struct FileInfo* ShellSort(struct FileInfo* files, int file_count) {
    int gap = 1;
    while (gap < file_count / 3) {
        gap = gap * 3 + 1;
    }

    while (gap > 0) {
        for (int i = gap; i < file_count; i++) {
            struct FileInfo temp = files[i];
            int j;

            for (j = i; j >= gap && files[j - gap].size > temp.size; j -= gap) {
                files[j] = files[j - gap];
            }

            files[j] = temp;
        }

        gap /= 3;
    }

    return files;
}

struct FileInfo* CountingSort(struct FileInfo* files, int file_count) {
    long min_size = files[0].size;
    long max_size = files[0].size;
    for (int i = 1; i < file_count; i++) {
        if (files[i].size < min_size) {
            min_size = files[i].size;
        }
        if (files[i].size > max_size) {
            max_size = files[i].size;
        }
    }

    int range = max_size - min_size + 1;
    int* count = (int*)calloc(range, sizeof(int));
    if (count == NULL) {
        return NULL;
    }

    for (int i = 0; i < file_count; i++) {
        count[files[i].size - min_size]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    struct FileInfo* output = (struct FileInfo*)malloc(file_count * sizeof(struct FileInfo));
    if (output == NULL) {
        free(count);
        return NULL;
    }

    for (int i = file_count - 1; i >= 0; i--) {
        int pos = files[i].size - min_size;
        count[pos]--;
        output[count[pos]] = files[i];
    }

    for (int i = 0; i < file_count; i++) {
        files[i] = output[i];
    }

    free(count);
    free(output);

    return files;
}

struct FileInfo* Sort(struct FileInfo* files, char sorting_method, int file_count, char ascending, double* time_used) {
    if (file_count <= 1) {
        return files;
    }

    struct FileInfo* sorted;

    clock_t start = clock();

    if (sorting_method == 0) {
        sorted = BubbleSort(files, file_count);
    }
    else if (sorting_method == 1) {
        sorted = SelectionSort(files, file_count);
    }
    else if (sorting_method == 2) {
        sorted = InsertionSort(files, file_count);
    }
    else if (sorting_method == 3) {
        sorted = MergeSort(files, file_count);
    }
    else if (sorting_method == 4) {
        sorted = QuickSort(files, 0, file_count - 1);
    }
    else if (sorting_method == 5) {
        sorted = ShellSort(files, file_count);
    }
    else if (sorting_method == 6) {
        sorted = CountingSort(files, file_count);
    }
    else
        sorted = NULL;

    clock_t end = clock();
    *time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (!ascending) {
        for (int i = 0; i < file_count / 2; i++) {
            struct FileInfo temp = sorted[i];
            sorted[i] = sorted[file_count - i - 1];
            sorted[file_count - i - 1] = temp;
        }
    }

    return sorted;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    char path[200] = "C:\\*.*";
    char sorting_method = 0;
    char* sorting_method_convert[] = { "Пузырьком", "Выбором", "Вставками", "Слиянием", "Хоара", "Шелла", "Подсчетом"};
    char ascending = 1;
    char* ascending_convert[] = {"Убывание", "Возрастание"};

    while (1) {
        char input[8];

        printf("\nТекущий путь: %s\n", path);
        printf("Текущий метод сортировки: %s %s\n", sorting_method_convert[sorting_method], ascending_convert[ascending]);
        printf("1 - Сменить путь\n");
        printf("2 - Сменить метод сортировки\n");
        printf("3 - Указать возрастание/убывание\n");
        printf("4 - Вывести файлы\n\n");

        scanf_s("%s", input, sizeof(input));
        
        if (strcmp(input, "1") == 0) {
            printf("\nВведите путь:\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = '\0';
        }
        else if (strcmp(input, "2") == 0) {
            printf("\nВведите метод: (0 - Пузырьком, 1 - Выбором, 2 - Вставками, 3 - Слиянием, 4 - Хоара, 5 - Шелла, 6 - Подсчетом)\n\n");
            scanf_s("%d", &sorting_method);
        }
        else if (strcmp(input, "3") == 0) {
            printf("\n0 - убывание, 1 - возрастание:\n");
            scanf_s("%d", &ascending);
        }
        else if (strcmp(input, "4") == 0) {
            int file_count = 0;
            double time_used = 0;

            struct FileInfo* files = CollectFiles(path, &file_count);

            if (!files) {
                printf("\nНет файлов в папке!\n");
                continue;
            }

            Sort(files, sorting_method, file_count, ascending, &time_used);

            if (!files) {
                printf("\nВы указали какой-то странный метод сортировки!\n");
                continue;
            }

            ShowFiles(files, file_count, time_used);

            free(files);
        }
    }
}