#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <windows.h>

#define MAX_PATH_LENGTH 256
#define MAX_FILES 1000

typedef struct {
    char name[260];
    long size;
} FileInfo;

void bubble_sort(FileInfo* files, int count, int ascending);
void selection_sort(FileInfo* files, int count, int ascending);
void insertion_sort(FileInfo* files, int count, int ascending);
void merge_sort(FileInfo* files, int left, int right, int ascending);
void quick_sort(FileInfo* files, int low, int high, int ascending);
void shell_sort(FileInfo* files, int count, int ascending);
void counting_sort(FileInfo* files, int count, int ascending);
void merge(FileInfo* files, int left, int mid, int right, int ascending);
int partition(FileInfo* files, int low, int high, int ascending);
void copy_files(FileInfo* dest, FileInfo* src, int count);
void display_files(FileInfo* files, int count);
int read_directory(const char* path, FileInfo* files);

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    char path[MAX_PATH_LENGTH];
    FileInfo files[MAX_FILES];
    FileInfo sorted_files[MAX_FILES];
    int file_count = 0;
    int choice;
    int sort_method;
    int ascending;
    clock_t start, end;
    double time_taken;
    
    printf("=== ФАЙЛОВЫЙ МЕНЕДЖЕР СОРТИРОВКИ ===\n\n");
    
    printf("Введите путь к директории: ");
    fgets(path, MAX_PATH_LENGTH, stdin);
    path[strcspn(path, "\n")] = 0; 
    
    file_count = read_directory(path, files);
    if (file_count == 0) {
        printf("В директории нет файлов или путь указан неверно!\n");
        system("pause");
        return 1;
    }
    
    printf("Найдено файлов: %d\n\n", file_count);
    
    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Ввести новый путь к директории\n");
        printf("2. Выбрать метод сортировки\n");
        printf("3. Показать отсортированные файлы\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                printf("Введите путь к директории: ");
                fgets(path, MAX_PATH_LENGTH, stdin);
                path[strcspn(path, "\n")] = 0;
                file_count = read_directory(path, files);
                if (file_count == 0) {
                    printf("В директории нет файлов или путь указан неверно!\n");
                } else {
                    printf("Найдено файлов: %d\n", file_count);
                }
                break;
                
            case 2:
                printf("\n=== ВЫБОР МЕТОДА СОРТИРОВКИ ===\n");
                printf("1. Пузырьком\n");
                printf("2. Выбором\n");
                printf("3. Вставками\n");
                printf("4. Слиянием\n");
                printf("5. Хоара (быстрая)\n");
                printf("6. Шелла\n");
                printf("7. Подсчетом\n");
                printf("Выберите метод (1-7): ");
                scanf("%d", &sort_method);
                
                printf("Выберите порядок сортировки:\n");
                printf("1. По возрастанию\n");
                printf("2. По убыванию\n");
                printf("Выберите (1-2): ");
                scanf("%d", &ascending);
                ascending = (ascending == 1) ? 1 : 0;
                break;
                
            case 3:
                if (file_count == 0) {
                    printf("Нет файлов для сортировки!\n");
                    break;
                }
                
                if (sort_method < 1 || sort_method > 7) {
                    printf("Сначала выберите метод сортировки!\n");
                    break;
                }
             
                copy_files(sorted_files, files, file_count);
                
                printf("\n=== ОТСОРТИРОВАННЫЙ СПИСОК ФАЙЛОВ ===\n");
                start = clock();
                
                switch (sort_method) {
                    case 1:
                        bubble_sort(sorted_files, file_count, ascending);
                        printf("Метод: Пузырьком, ");
                        break;
                    case 2:
                        selection_sort(sorted_files, file_count, ascending);
                        printf("Метод: Выбором, ");
                        break;
                    case 3:
                        insertion_sort(sorted_files, file_count, ascending);
                        printf("Метод: Вставками, ");
                        break;
                    case 4:
                        merge_sort(sorted_files, 0, file_count - 1, ascending);
                        printf("Метод: Слиянием, ");
                        break;
                    case 5:
                        quick_sort(sorted_files, 0, file_count - 1, ascending);
                        printf("Метод: Хоара (быстрая), ");
                        break;
                    case 6:
                        shell_sort(sorted_files, file_count, ascending);
                        printf("Метод: Шелла, ");
                        break;
                    case 7:
                        counting_sort(sorted_files, file_count, ascending);
                        printf("Метод: Подсчетом, ");
                        break;
                }
                
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("Порядок: %s\n", ascending ? "по возрастанию" : "по убыванию");
                printf("Время сортировки: %.6f секунд\n\n", time_taken);
                
                display_files(sorted_files, file_count);
                break;
                
            case 4:
                printf("Выход из программы...\n");
                break;
                
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
        
    } while (choice != 4);
    
    system("pause");
    return 0;
}

int read_directory(const char* path, FileInfo* files) {
    struct _finddata_t c_file;
    intptr_t hFile;
    char search_path[MAX_PATH_LENGTH];
    int count = 0;
    
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    
    if ((hFile = _findfirst(search_path, &c_file)) == -1L) {
        return 0;
    }
    
    do {
        if (!(c_file.attrib & _A_SUBDIR)) {
            strncpy(files[count].name, c_file.name, 259);
            files[count].name[259] = '\0';
            files[count].size = c_file.size;
            count++;
            
            if (count >= MAX_FILES) {
                printf("Достигнут максимальный лимит файлов (%d)\n", MAX_FILES);
                break;
            }
        }
    } while (_findnext(hFile, &c_file) == 0);
    
    _findclose(hFile);
    return count;
}

void display_files(FileInfo* files, int count) {
    printf("%-40s %-15s\n", "Имя файла", "Размер (байт)");
    printf("---------------------------------------- ---------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-40s %-15ld\n", files[i].name, files[i].size);
    }
}

void copy_files(FileInfo* dest, FileInfo* src, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}

void bubble_sort(FileInfo* files, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            
            if (ascending) {
                swap = (files[j].size > files[j + 1].size);
            } else {
                swap = (files[j].size < files[j + 1].size);
            }
            
            if (swap) {
                FileInfo temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
            }
        }
    }
}

void selection_sort(FileInfo* files, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (ascending) {
                if (files[j].size < files[min_idx].size) {
                    min_idx = j;
                }
            } else {
                if (files[j].size > files[min_idx].size) {
                    min_idx = j;
                }
            }
        }
        
        if (min_idx != i) {
            FileInfo temp = files[i];
            files[i] = files[min_idx];
            files[min_idx] = temp;
        }
    }
}

void insertion_sort(FileInfo* files, int count, int ascending) {
    for (int i = 1; i < count; i++) {
        FileInfo key = files[i];
        int j = i - 1;
        
        if (ascending) {
            while (j >= 0 && files[j].size > key.size) {
                files[j + 1] = files[j];
                j--;
            }
        } else {
            while (j >= 0 && files[j].size < key.size) {
                files[j + 1] = files[j];
                j--;
            }
        }
        
        files[j + 1] = key;
    }
}

void merge_sort(FileInfo* files, int left, int right, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(files, left, mid, ascending);
        merge_sort(files, mid + 1, right, ascending);
        merge(files, left, mid, right, ascending);
    }
}

void merge(FileInfo* files, int left, int mid, int right, int ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    FileInfo* L = (FileInfo*)malloc(n1 * sizeof(FileInfo));
    FileInfo* R = (FileInfo*)malloc(n2 * sizeof(FileInfo));
    
    for (int i = 0; i < n1; i++)
        L[i] = files[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = files[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (ascending) {
            if (L[i].size <= R[j].size) {
                files[k] = L[i];
                i++;
            } else {
                files[k] = R[j];
                j++;
            }
        } else {
            if (L[i].size >= R[j].size) {
                files[k] = L[i];
                i++;
            } else {
                files[k] = R[j];
                j++;
            }
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

void quick_sort(FileInfo* files, int low, int high, int ascending) {
    if (low < high) {
        int pi = partition(files, low, high, ascending);
        quick_sort(files, low, pi - 1, ascending);
        quick_sort(files, pi + 1, high, ascending);
    }
}

int partition(FileInfo* files, int low, int high, int ascending) {
    long pivot = files[high].size;
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (ascending) {
            if (files[j].size <= pivot) {
                i++;
                FileInfo temp = files[i];
                files[i] = files[j];
                files[j] = temp;
            }
        } else {
            if (files[j].size >= pivot) {
                i++;
                FileInfo temp = files[i];
                files[i] = files[j];
                files[j] = temp;
            }
        }
    }
    
    FileInfo temp = files[i + 1];
    files[i + 1] = files[high];
    files[high] = temp;
    
    return (i + 1);
}

void shell_sort(FileInfo* files, int count, int ascending) {
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            FileInfo temp = files[i];
            int j;
            
            if (ascending) {
                for (j = i; j >= gap && files[j - gap].size > temp.size; j -= gap) {
                    files[j] = files[j - gap];
                }
            } else {
                for (j = i; j >= gap && files[j - gap].size < temp.size; j -= gap) {
                    files[j] = files[j - gap];
                }
            }
            
            files[j] = temp;
        }
    }
}

void counting_sort(FileInfo* files, int count, int ascending) {
    if (count == 0) return;
    
    long max_size = files[0].size;
    for (int i = 1; i < count; i++) {
        if (files[i].size > max_size) {
            max_size = files[i].size;
        }
    }
    
    int* count_arr = (int*)calloc(max_size + 1, sizeof(int));
    if (!count_arr) {
        printf("Ошибка выделения памяти для сортировки подсчетом!\n");
        return;
    }
 
    for (int i = 0; i < count; i++) {
        count_arr[files[i].size]++;
    }

    if (ascending) {
        for (int i = 1; i <= max_size; i++) {
            count_arr[i] += count_arr[i - 1];
        }
    } else {
        for (int i = max_size - 1; i >= 0; i--) {
            count_arr[i] += count_arr[i + 1];
        }
    }

    FileInfo* output = (FileInfo*)malloc(count * sizeof(FileInfo));
    if (!output) {
        free(count_arr);
        printf("Ошибка выделения памяти для сортировки подсчетом!\n");
        return;
    }

    for (int i = count - 1; i >= 0; i--) {
        output[count_arr[files[i].size] - 1] = files[i];
        count_arr[files[i].size]--;
    }
  
    for (int i = 0; i < count; i++) {
        files[i] = output[i];
    }
    
    free(count_arr);
    free(output);
}