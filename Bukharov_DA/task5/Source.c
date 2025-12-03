#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>

struct file_info {
    char name[256];
    long size;
};

int get_files(char* path, struct file_info** files_ptr, int* capacity_ptr) {
    struct _finddata_t c_file;
    intptr_t hFile;
    int count = 0;
    char search_path[300];

    snprintf(search_path, sizeof(search_path), "%s\\*.*", path);

    if ((hFile = _findfirst(search_path, &c_file)) == -1L) {
        printf("No files found!\n");
        return 0;
    }

    do {
        if (count >= *capacity_ptr) {
            *capacity_ptr *= 2;
            files_ptr = (struct file_info*)realloc(*files_ptr, (*capacity_ptr) * sizeof(struct file_info));
            if (!*files_ptr) {
                printf("Memory reallocation failed\n");
                _findclose(hFile);
                return count;
            }
        }

        /*strncpy(files[count].name, c_file.name, 255);
        files[count].name[255] = '\0';
        files[count].size = c_file.size;*/
        strncpy((*files_ptr)[count].name, c_file.name, 255);
        (*files_ptr)[count].name[255] = '\0';
        (*files_ptr)[count].size = c_file.size;
        count++;

    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);
    return count;
}

void bubble_sort(struct file_info* files, int count, int asc) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (asc) {
                if (files[j].size > files[j + 1].size) {
                    struct file_info temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
            else {
                if (files[j].size < files[j + 1].size) {
                    struct file_info temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
    }
}

void selection_sort(struct file_info* files, int count, int asc) {
    for (int i = 0; i < count - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < count; j++) {
            if (asc) {
                if (files[j].size < files[idx].size) idx = j;
            }
            else {
                if (files[j].size > files[idx].size) idx = j;
            }
        }
        if (idx != i) {
            struct file_info temp = files[i];
            files[i] = files[idx];
            files[idx] = temp;
        }
    }
}

void insertion_sort(struct file_info* files, int count, int asc) {
    for (int i = 1; i < count; i++) {
        struct file_info key = files[i];
        int j = i - 1;

        if (asc) {
            while (j >= 0 && files[j].size > key.size) {
                files[j + 1] = files[j];
                j--;
            }
        }
        else {
            while (j >= 0 && files[j].size < key.size) {
                files[j + 1] = files[j];
                j--;
            }
        }
        files[j + 1] = key;
    }
}

void merge(struct file_info* files, int left, int mid, int right, int asc) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct file_info* L = (struct file_info*)malloc(n1 * sizeof(struct file_info));
    struct file_info* R = (struct file_info*)malloc(n2 * sizeof(struct file_info));

    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        return;
    }

    for (int i = 0; i < n1; i++) L[i] = files[left + i];
    for (int j = 0; j < n2; j++) R[j] = files[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (asc) {
            if (L[i].size <= R[j].size) {
                files[k++] = L[i++];
            }
            else {
                files[k++] = R[j++];
            }
        }
        else {
            if (L[i].size >= R[j].size) {
                files[k++] = L[i++];
            }
            else {
                files[k++] = R[j++];
            }
        }
    }

    while (i < n1) files[k++] = L[i++];
    while (j < n2) files[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(struct file_info* files, int left, int right, int asc) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(files, left, mid, asc);
        merge_sort(files, mid + 1, right, asc);
        merge(files, left, mid, right, asc);
    }
}

int partition(struct file_info* files, int low, int high, int asc) {
    long pivot = files[high].size;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (asc) {
            if (files[j].size <= pivot) {
                i++;
                struct file_info temp = files[i];
                files[i] = files[j];
                files[j] = temp;
            }
        }
        else {
            if (files[j].size >= pivot) {
                i++;
                struct file_info temp = files[i];
                files[i] = files[j];
                files[j] = temp;
            }
        }
    }

    struct file_info temp = files[i + 1];
    files[i + 1] = files[high];
    files[high] = temp;
    return i + 1;
}

void quick_sort(struct file_info* files, int low, int high, int asc) {
    if (low < high) {
        int pi = partition(files, low, high, asc);
        quick_sort(files, low, pi - 1, asc);
        quick_sort(files, pi + 1, high, asc);
    }
}


void shell_sort(struct file_info* files, int count, int asc) {
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            struct file_info temp = files[i];
            int j;

            if (asc) {
                for (j = i; j >= gap && files[j - gap].size > temp.size; j -= gap) {
                    files[j] = files[j - gap];
                }
            }
            else {
                for (j = i; j >= gap && files[j - gap].size < temp.size; j -= gap) {
                    files[j] = files[j - gap];
                }
            }
            files[j] = temp;
        }
    }
}


void counting_sort(struct file_info* files, int count, int asc) {
    if (count <= 0) return;

    long max_size = files[0].size;
    for (int i = 1; i < count; i++) {
        if (files[i].size > max_size) max_size = files[i].size;
    }

    int* count_arr = (int*)calloc(max_size + 1, sizeof(int));
    if (!count_arr) return;

    for (int i = 0; i < count; i++) {
        count_arr[files[i].size]++;
    }

    struct file_info* output = (struct file_info*)malloc(count * sizeof(struct file_info));
    if (!output) {
        free(count_arr);
        return;
    }

    if (asc) {
        int index = 0;
        for (long i = 0; i <= max_size; i++) {
            while (count_arr[i] > 0) {
                for (int j = 0; j < count; j++) {
                    if (files[j].size == i) {
                        output[index++] = files[j];
                        count_arr[i]--;
                        break;
                    }
                }
            }
        }
    }
    else {
        int index = 0;
        for (long i = max_size; i >= 0; i--) {
            while (count_arr[i] > 0) {
                for (int j = 0; j < count; j++) {
                    if (files[j].size == i) {
                        output[index++] = files[j];
                        count_arr[i]--;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        files[i] = output[i];
    }

    free(count_arr);
    free(output);
}

void show_menu() {
    printf("\n=== FILE MANAGER ===\n");
    printf("1 - Enter folder path\n");
    printf("2 - Show files\n");
    printf("3 - Bubble sort\n");
    printf("4 - Selection sort\n");
    printf("5 - Insertion sort\n");
    printf("6 - Merge sort\n");
    printf("7 - Quick sort (Hoare)\n");
    printf("8 - Shell sort\n");
    printf("9 - Counting sort\n");
    printf("10 - Exit\n");
    printf("Your choice: ");
}

void show_files_list(struct file_info* files, int count, char* sort_name, double time) {
    if (count <= 0) {
        printf("No files to display\n");
        return;
    }

    printf("\n--- %s ---\n", sort_name);
    printf("Time: %.6f seconds\n", time);
    printf("FILE               SIZE\n");
    printf("----               ----\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s %10ld\n", files[i].name, files[i].size);
    }
    printf("Total files: %d\n", count);
}

int main() {
    struct file_info* files = NULL;
    struct file_info* original_files = NULL; 
    int capacity = 100; 
    char folder_path[256] = ".";
    int file_count = 0;
    int choice;
    int sort_dir;

    printf("FILE MANAGER PROGRAM\n");
    printf("====================\n");

    files = (struct file_info*)malloc(capacity * sizeof(struct file_info));
    original_files = (struct file_info*)malloc(capacity * sizeof(struct file_info));

    if (!files || !original_files) {
        printf("Memory error\n");
        return 1;
    }

    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            printf("Enter folder path: ");
            if (scanf("%255s", folder_path) != 1) {
                printf("Invalid path!\n");
                continue;
            }

            file_count = get_files(folder_path, &files, &capacity);
            if (file_count > 0) {
                original_files = (struct file_info*)realloc(original_files, file_count * sizeof(struct file_info));
                memcpy(original_files, files, sizeof(struct file_info) * file_count);
                printf("Loaded %d files\n", file_count);
            }
            else {
                printf("No files found!\n");
            }

        }
        else if (choice == 2) {
            if (file_count > 0) {
                printf("\n--- Files in folder ---\n");
                for (int i = 0; i < file_count; i++) {
                    printf("%-20s %10ld\n", original_files[i].name, original_files[i].size);
                }
                printf("Total files: %d\n", file_count);
            }
            else {
                printf("No files loaded!\n");
            }

        }
        else if (choice >= 3 && choice <= 9) {
            if (file_count == 0) {
                printf("Load files first!\n");
                continue;
            }

            printf("Sort direction:\n");
            printf("1 - Ascending\n");
            printf("2 - Descending\n");
            printf("Your choice: ");
            if (scanf("%d", &sort_dir) != 1 || (sort_dir != 1 && sort_dir != 2)) {
                printf("Invalid choice!\n");
                continue;
            }

            memcpy(files, original_files, sizeof(struct file_info) * file_count);

            clock_t start = clock();

            switch (choice) {
            case 3:
                bubble_sort(files, file_count, sort_dir == 1);
                break;
            case 4:
                selection_sort(files, file_count, sort_dir == 1);
                break;
            case 5:
                insertion_sort(files, file_count, sort_dir == 1);
                break;
            case 6:
                merge_sort(files, 0, file_count - 1, sort_dir == 1);
                break;
            case 7:
                quick_sort(files, 0, file_count - 1, sort_dir == 1);
                break;
            case 8:
                shell_sort(files, file_count, sort_dir == 1);
                break;
            case 9:
                counting_sort(files, file_count, sort_dir == 1);
                break;
            }

            clock_t end = clock();
            double time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            char* sort_names[] = {
                "", "", "",
                "Bubble Sort",
                "Selection Sort",
                "Insertion Sort",
                "Merge Sort",
                "Quick Sort (Hoare)",
                "Shell Sort",
                "Counting Sort"
            };

            show_files_list(files, file_count, sort_names[choice], time_used);

        }
        else if (choice == 10) {
            printf("Goodbye!\n");
            break;

        }
        else {
            printf("Invalid choice!\n");
        }
    }
    free(files);
    free(original_files);

    return 0;
}