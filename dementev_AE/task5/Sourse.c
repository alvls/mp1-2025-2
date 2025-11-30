#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

typedef struct {
    char nm[260];
    unsigned long sz;
} FD;

void bs(FD* a, int n);
void ss(FD* a, int n);
void is(FD* a, int n);
void ms(FD* a, int l, int r);
void qs(FD* a, int l, int h);
void sh(FD* a, int n);
void cs(FD* a, int n);

void sw(FD* a, FD* b);
void mg(FD* a, int l, int m, int r);
int pt(FD* a, int l, int h);
void pf(FD* a, int n);
void cl();

void sw(FD* a, FD* b) {
    FD t = *a;
    *a = *b;
    *b = t;
}

void pf(FD* a, int n) {
    printf("%-30s | %10s\n", "Имя файла", "Размер");
    for (int i = 0; i < n; i++) {
        if (i < 50 || i > n - 10)
            printf("%-30.30s  %10lu\n", a[i].nm, a[i].sz);
        else if (i == 50)
            printf("...\n");
    }
}

void cl() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void bs(FD* a, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j].sz > a[j + 1].sz)
                sw(&a[j], &a[j + 1]);
}

void ss(FD* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int mi = i;
        for (int j = i + 1; j < n; j++)
            if (a[j].sz < a[mi].sz)
                mi = j;
        sw(&a[mi], &a[i]);
    }
}

void is(FD* a, int n) {
    for (int i = 1; i < n; i++) {
        FD k = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].sz > k.sz) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = k;
    }
}

void mg(FD* a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    FD* L = (FD*)malloc(n1 * sizeof(FD));
    FD* R = (FD*)malloc(n2 * sizeof(FD));
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].sz <= R[j].sz) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    free(L);
    free(R);
}

void ms(FD* a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        ms(a, l, m);
        ms(a, m + 1, r);
        mg(a, l, m, r);
    }
}

int pt(FD* a, int l, int h) {
    unsigned long p = a[(h + l) / 2].sz;
    int i = l - 1;
    int j = h + 1;
    while (1) {
        do { i++; } while (a[i].sz < p);
        do { j--; } while (a[j].sz > p);
        if (i >= j) return j;
        sw(&a[i], &a[j]);
    }
}

void qs(FD* a, int l, int h) {
    if (l < h) {
        int pi = pt(a, l, h);
        qs(a, l, pi);
        qs(a, pi + 1, h);
    }
}

void sh(FD* a, int n) {
    for (int g = n / 2; g > 0; g /= 2) {
        for (int i = g; i < n; i++) {
            FD t = a[i];
            int j;
            for (j = i; j >= g && a[j - g].sz > t.sz; j -= g)
                a[j] = a[j - g];
            a[j] = t;
        }
    }
}

void cs(FD* a, int n) {
    if (n == 0) return;
    unsigned long mx = a[0].sz;
    unsigned long mn = a[0].sz;
    for (int i = 1; i < n; i++) {
        if (a[i].sz > mx) mx = a[i].sz;
        if (a[i].sz < mn) mn = a[i].sz;
    }
    unsigned long r = mx - mn + 1;
    if (r > 50000000) {
        printf("Слишком большой диапазон\n");
        return;
    }
    int* cnt = (int*)calloc(r, sizeof(int));
    FD* out = (FD*)malloc(n * sizeof(FD));
    if (!cnt || !out) {
        printf("Недостаточно памяти\n");
        free(cnt);
        free(out);
        return;
    }
    for (int i = 0; i < n; i++)
        cnt[a[i].sz - mn]++;
    for (int i = 1; i < r; i++)
        cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        out[cnt[a[i].sz - mn] - 1] = a[i];
        cnt[a[i].sz - mn]--;
    }
    for (int i = 0; i < n; i++)
        a[i] = out[i];
    free(cnt);
    free(out);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    char p[200];
    char sp[250];
    struct _finddata_t fi;
    intptr_t fh;

    while (1) {
        printf("Введите путь: ");
        gets(p);

        strcpy(sp, p);
        if (p[strlen(p) - 1] != '\\') strcat(sp, "\\");
        strcat(sp, "*.*");
        fh = _findfirst(sp, &fi);
        if (fh == -1L) {
            printf("Ошибка пути\n");
            continue;
        }

        int fc = 0;
        do {
            if (!(fi.attrib & _A_SUBDIR)) fc++;
        } while (_findnext(fh, &fi) == 0);
        _findclose(fh);

        if (fc == 0) {
            printf("Нет файлов\n");
            continue;
        }

        FD* fs = (FD*)malloc(fc * sizeof(FD));
        fh = _findfirst(sp, &fi);
        int ci = 0;
        do {
            if (!(fi.attrib & _A_SUBDIR)) {
                strcpy(fs[ci].nm, fi.name);
                fs[ci].sz = fi.size;
                ci++;
            }
        } while (_findnext(fh, &fi) == 0);
        _findclose(fh);

        printf("Файлов: %d\n", fc);

        int ch;
        while (1) {
            printf("\n1. Пузырек\n2. Выбор\n3. Вставка\n4. Слияние\n");
            printf("5. Быстрая\n6. Шелл\n7. Подсчет\n0. Выход\n");

            if (scanf("%d", &ch) != 1) {
                printf("Ошибка ввода\n");
                cl();
                continue;
            }
            cl();

            if (ch == 0) break;
            if (ch < 1 || ch > 7) {
                printf("Неверный выбор\n");
                continue;
            }

            FD* sf = (FD*)malloc(fc * sizeof(FD));
            memcpy(sf, fs, fc * sizeof(FD));

            LARGE_INTEGER st, en, fr;
            QueryPerformanceFrequency(&fr);
            QueryPerformanceCounter(&st);

            switch (ch) {
            case 1: bs(sf, fc); break;
            case 2: ss(sf, fc); break;
            case 3: is(sf, fc); break;
            case 4: ms(sf, 0, fc - 1); break;
            case 5: qs(sf, 0, fc - 1); break;
            case 6: sh(sf, fc); break;
            case 7: cs(sf, fc); break;
            }

            QueryPerformanceCounter(&en);
            double tm = (double)(en.QuadPart - st.QuadPart) / fr.QuadPart;

            pf(sf, fc);
            printf("Время: %.6f сек\n", tm);

            free(sf);
        }

        free(fs);
    }
    return 0;
}