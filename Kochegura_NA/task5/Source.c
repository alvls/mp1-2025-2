#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_NAME 100

struct FileInfo {
    char name[MAX_NAME];
    long size;
};

int get_files(char* path, struct FileInfo files[]) {
    char search_path[300];
    WIN32_FIND_DATA file_data;
    HANDLE hFind;
    int count = 0;

    sprintf(search_path, "%s\\*", path);

    hFind = FindFirstFile(search_path, &file_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error, cant open folder'%s'\n", path);
        return 0;
    }

    do {
        if (strcmp(file_data.cFileName, ".") == 0 ||
            strcmp(file_data.cFileName, "..") == 0) {
            continue;
        }

        if (!(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcpy(files[count].name, file_data.cFileName);
            files[count].size = file_data.nFileSizeLow;
            count++;

            if (count >= MAX_FILES) {
                printf("Error cant get more files (%d)\n", MAX_FILES);
                break;
            }
        }
    } while (FindNextFile(hFind, &file_data) != 0);

    FindClose(hFind);
    return count;
}

void bubble_sort(struct FileInfo files[], int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int need_swap = 0;
            if (ascending && files[j].size > files[j + 1].size) {
                need_swap = 1;
            }
            if (!ascending && files[j].size < files[j + 1].size) {
                need_swap = 1;
            }

            if (need_swap) {
                struct FileInfo temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
            }
        }
    }
}

void vibor_sort(struct FileInfo files[], int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        int extreme_index = i;
        for (int j = i + 1; j < n; j++) {
            if (ascending && files[j].size < files[extreme_index].size) {
                extreme_index = j;
            }
            if (!ascending && files[j].size > files[extreme_index].size) {
                extreme_index = j;
            }
        }
        struct FileInfo temp = files[i];
        files[i] = files[extreme_index];
        files[extreme_index] = temp;
    }
}

void vstavka_sort(struct FileInfo files[], int n, int ascending) {
    for (int i = 1; i < n; i++) {
        struct FileInfo key = files[i];
        int j = i - 1;

        while (j >= 0) {
            int condition = 0;
            if (ascending && files[j].size > key.size) {
                condition = 1;
            }
            if (!ascending && files[j].size < key.size) {
                condition = 1;
            }

            if (condition) {
                files[j + 1] = files[j];
                j--;
            }
            else {
                break;
            }
        }
        files[j + 1] = key;
    }
}

void merge(struct FileInfo files[], int left, int mid, int right, int ascending) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct FileInfo* L = (struct FileInfo*)malloc(n1 * sizeof(struct FileInfo));
    struct FileInfo* R = (struct FileInfo*)malloc(n2 * sizeof(struct FileInfo));

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

void merge_sort_recursive(struct FileInfo files[], int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_recursive(files, left, mid, ascending);
        merge_sort_recursive(files, mid + 1, right, ascending);
        merge(files, left, mid, right, ascending);
    }
}

void merge_sort(struct FileInfo files[], int n, int ascending) {
    merge_sort_recursive(files, 0, n - 1, ascending);
}

int partition(struct FileInfo files[], int low, int high, int ascending) {
    long pivot = files[high].size;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if ((ascending && files[j].size <= pivot) ||
            (!ascending && files[j].size >= pivot)) {
            i++;
            struct FileInfo temp = files[i];
            files[i] = files[j];
            files[j] = temp;
        }
    }

    struct FileInfo temp = files[i + 1];
    files[i + 1] = files[high];
    files[high] = temp;

    return i + 1;
}

void quick_sort_recursive(struct FileInfo files[], int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(files, low, high, ascending);
        quick_sort_recursive(files, low, pi - 1, ascending);
        quick_sort_recursive(files, pi + 1, high, ascending);
    }
}

void quick_sort(struct FileInfo files[], int n, int ascending) {
    quick_sort_recursive(files, 0, n - 1, ascending);
}

void shell_sort(struct FileInfo files[], int n, int ascending) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            struct FileInfo temp = files[i];
            int j;

            for (j = i; j >= gap; j -= gap) {
                int condition = 0;
                if (ascending && files[j - gap].size > temp.size) {
                    condition = 1;
                }
                if (!ascending && files[j - gap].size < temp.size) {
                    condition = 1;
                }

                if (condition) {
                    files[j] = files[j - gap];
                }
                else {
                    break;
                }
            }
            files[j] = temp;
        }
    }
}

void counting_sort(struct FileInfo files[], int n, int ascending) {
    if (n == 0) return;

    long max_size = files[0].size;
    for (int i = 1; i < n; i++) {
        if (files[i].size > max_size) {
            max_size = files[i].size;
        }
    }

    int* count = (int*)calloc(max_size + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        count[files[i].size]++;
    }

    if (!ascending) {
        for (int i = 0; i <= max_size / 2; i++) {
            int temp = count[i];
            count[i] = count[max_size - i];
            count[max_size - i] = temp;
        }
    }
    int index = 0;
    for (int i = 0; i <= max_size; i++) {
        while (count[i] > 0) {
            for (int j = 0; j < n; j++) {
                if (files[j].size == i) {
                    struct FileInfo temp = files[index];
                    files[index] = files[j];
                    files[j] = temp;
                    index++;
                    count[i]--;
                    break;
                }
            }
        }
    }

    free(count);
}

void show_files(struct FileInfo files[], int count, char PP[300]) {
    printf("------------------------------------------\n");
    printf("Listing of files DIRECTORY * %s * \n\n", PP);
    printf("------------------------------------------\n");
    printf("%-30s %s\n", "File name", "Size");
    printf("------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-30s %ld bytes\n", files[i].name, files[i].size);
    }
    printf("------------------------------------------\n");
    printf("File count: [ %d ]\n", count);
    printf("------------------------------------------\n");
}

void perform_sort(struct FileInfo files[], int count, int method, int order, char DD[300]) {
    clock_t start, end;
    double time_used;

    struct FileInfo temp_files[MAX_FILES];
    for (int i = 0; i < count; i++) {
        temp_files[i] = files[i];
    }

    printf("\nSorted method by ... ");
    start = clock();

    switch (method) {
    case 1:
        printf("(Bubble)");
        bubble_sort(temp_files, count, order);
        break;
    case 2:
        printf("(Vibor)");
        vibor_sort(temp_files, count, order);
        break;
    case 3:
        printf("(Vstavka)");
        vstavka_sort(temp_files, count, order);
        break;
    case 4:
        printf("(Sliyanie)");
        merge_sort(temp_files, count, order);
        break;
    case 5:
        printf("(Hoara)");
        quick_sort(temp_files, count, order);
        break;
    case 6:
        printf("(Shella)");
        shell_sort(temp_files, count, order);
        break;
    case 7:
        printf("(Podshet)");
        counting_sort(temp_files, count, order);
        break;
    }

    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf(" End by %.6f sec\n", time_used);
    show_files(temp_files, count, DD);
}

int main() {
    char path[300];
    struct FileInfo files[MAX_FILES];
    int file_count = 0;
    int choice, sort_method, sort_order;

    printf("=== file mahager ===\n");

    while (1) {
        printf("******************************************\n");
        printf("\nMenu:\n");
        printf("1. Select Dir\n");
        printf("2. Select sorted type\n");
        printf("3. Show files\n");
        printf("4. Exit\n");
        printf("******************************************\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter path: (Example: C:\\temp) ");
            getchar();
            fgets(path, sizeof(path), stdin);
            if (path[strlen(path) - 1] == '\n') {
                path[strlen(path) - 1] = '\0';
            }

            file_count = get_files(path, files);
            if (file_count > 0) {
                printf("# In folder %s - system found %d files #\n", path, file_count);
            }
            else {
                printf("Files is 0\n");
            }
            break;

        case 2:
            if (file_count == 0) {
                printf("Select dir first\n");
                break;
            }
            printf("\nSorted type:\n");
            printf("1. Bubble\n");
            printf("2. Choise\n");
            printf("3. Vstavki\n");
            printf("4. Sliyanie\n");
            printf("5. Hoara\n");
            printf("6. Shella\n");
            printf("7. Podshet\n");
            printf("Sellect type (1-7): ");
            scanf("%d", &sort_method);

            if (sort_method < 1 || sort_method > 7) {
                printf("Error  - Ne verniy Vibor!\n");
                break;
            }

            printf("Sorted order:\n");
            printf("1. up\n");
            printf("2. down\n");
            printf("sellect (1-2): ");
            scanf("%d", &sort_order);

            if (sort_order != 1 && sort_order != 2) {
                printf("Error - Ne verniy Vibor!\n");
                break;
            }

            perform_sort(files, file_count, sort_method, sort_order == 1, path);
            break;

        case 3:
            if (file_count == 0) {
                printf("sellect dir\n");
            }
            else {
                show_files(files, file_count, path);
            }
            break;

        case 4:
            printf("Exit\n");
            return 0;

        default:
            printf("Error.\n");
        }
    }

    return 0;
}