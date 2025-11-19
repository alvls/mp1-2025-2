#include <stdio.h>
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");

    struct _finddata_t c_file;
    intptr_t hFile;
    char path[200] = "C:\\*.*";
    char sorting_method[20] = "Пузырьком";
    int count = 0;

    while (1) {
        printf("Текущий путь: %s\n", path);
        printf("Текущий метод сортировки: %s\n", sorting_method);
        printf("1 - Сменить путь\n");
        printf("2 - Сменить метод сортировки\n");
        printf("3 - Вывести файлы\n\n");

        
    }
}

void ShowFiles(char path[200] path) {
    if ((hFile = _findfirst(path, &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        printf("Listing of .c files\n\n");
        printf("FILE         DATE %24c   SIZE\n", ' ');
        printf("----         ---- %24c   ----\n", ' ');
        do {
            char buffer[30];
            ctime_s(buffer, _countof(buffer), &c_file.time_write);
            printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
            count++;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        printf("\ncount of files: %d", count);
    }
}