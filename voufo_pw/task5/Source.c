#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>

typedef struct {
    char name[260];
    long size;
} FileInfo;

FileInfo files[5000];
int fileCount = 0;

void loadFiles(const char* path) {
    struct _finddata_t c_file;
    char mask[300];
    fileCount = 0;

    sprintf(mask, "%s\\.", path);

    intptr_t hFile = _findfirst(mask, &c_file);
    if (hFile == -1L) {
        printf("Directory not found.\n");
        return;
    }

    do {
        if (!(c_file.attrib & _A_SUBDIR)) {
            strcpy(files[fileCount].name, c_file.name);
            files[fileCount].size = c_file.size;
            fileCount++;
        }
    } while (_findnext(hFile, &c_file) == 0);

    _findclose(hFile);
}

void bubbleSort() {
    for (int i = 0; i < fileCount - 1; i++)
        for (int j = 0; j < fileCount - i - 1; j++)
            if (files[j].size > files[j + 1].size) {
                FileInfo temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
            }
}

void printFiles() {
    for (int i = 0; i < fileCount; i++)
        printf("%-30s %10ld bytes\n", files[i].name, files[i].size);
}

int main() {
    char path[260];
    int method;

    printf("Enter folder path: ");
    scanf("%s", path);

    loadFiles(path);

    if (fileCount == 0) {
        printf("No files.\n");
        return 0;
    }

    printf("Choose sort method:\n1 - Bubble sort\n");
    scanf("%d", &method);

    clock_t start = clock();

    if (method == 1) bubbleSort();

    clock_t end = clock();

    printFiles();
    printf("\nTime: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}