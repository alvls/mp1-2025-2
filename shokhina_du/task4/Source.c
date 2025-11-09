#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

// скидки или их отсутствие (0)
int skidki[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };

// cтруктура для товаров
typedef struct {
    int shtrihcod[4];
    char name[20];
    int price;
    int skidka;
} Product;

// структура чека
typedef struct {
    int price_skidka;
    int count;
} Check;

// функция для сравнения штрих-кодов
int sravnenie(int cod1[4], int cod2[4]) {
    for (int i = 0; i < 4; i++) {
        if (cod1[i] != cod2[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    // список продуктов 
    Product products[] = {
        // последний элемент - одна из скидок 
        {{5, 6, 7, 2}, "Молоко", 85, skidki[rand() % 11]},
        {{1, 5, 9, 4}, "Кефир", 90, skidki[rand() % 11]},
        {{9, 0, 1, 2}, "Сыр", 200, skidki[rand() % 11]},
        {{3, 3, 4, 0}, "Колбаса", 260, skidki[rand() % 11]},
        {{8, 5, 1, 7}, "Хлеб", 45, skidki[rand() % 11]},
        {{6, 7, 7, 2}, "Яйца", 120, skidki[rand() % 11]},
        {{4, 0, 8, 9}, "Картофель", 100, skidki[rand() % 11]},
        {{6, 6, 9, 4}, "Огурцы", 130, skidki[rand() % 11]},
        {{3, 2, 0, 5}, "Помидоры", 140, skidki[rand() % 11]},
        {{1, 1, 1, 9}, "Кофе", 450, skidki[rand() % 11]},
        {{9, 5, 2, 2}, "Чай", 180, skidki[rand() % 11]}
    };

    // сам чек
    Check check[] = {
        // 3ий элемент - цена со скидкой
        {products[0].price * (100 - products[0].skidka) / 100, 0},
        {products[1].price * (100 - products[1].skidka) / 100, 0},
        {products[2].price * (100 - products[2].skidka) / 100, 0},
        {products[3].price * (100 - products[3].skidka) / 100, 0},
        {products[4].price * (100 - products[4].skidka) / 100, 0},
        {products[5].price * (100 - products[5].skidka) / 100, 0},
        {products[6].price * (100 - products[6].skidka) / 100, 0},
        {products[7].price * (100 - products[7].skidka) / 100, 0},
        {products[8].price * (100 - products[8].skidka) / 100, 0},
        {products[9].price * (100 - products[9].skidka) / 100, 0},
        {products[10].price * (100 - products[10].skidka) / 100, 0}
    };

    printf("Добро пожаловать в «Электронную кассу»!\n");
    printf("--------------------------------------------------------------------------------------------------");
    printf("\nВот список продуктов, доступные в нашем магазине : \n");
    printf("= Продукт   \t\tСтоимость (руб.)\tСкидка (проц.)\t\tШтрих-код\n");
    for (int i = 0; i < 11; i++) {
        printf("- %s   \t\t%d\t\t\t%d\t\t\t", products[i].name, products[i].price,
            products[i].skidka);
        for (int j = 0; j < 4; j++)
            printf("%d", products[i].shtrihcod[j]);
        printf("\n");
    }

    int chek[1000];
    printf("--------------------------------------------------------------------------------------------------");
    printf("\nВведите штрих-коды товаров, которые хотите «приобрести» (введите 0, если товары «закончились»):\n");
    int flag;
    int found_any_product = 0; // флаг для отслеживания найденных товаров
    int wrong_shtrih = 0; // счетчик неверных штрих-кодов

    while (1) {
        scanf_s("%d", &flag);
        if (flag == 0)
            break;

        int shtrih[4];
        for (int i = 0; i < 4; i++) {
            shtrih[4 - i - 1] = flag % 10;
            flag /= 10;
        }

        int product_found = 0; // флаг для отслеживания найденного товара
        for (int i = 0; i < 11; i++) {
            if (sravnenie(products[i].shtrihcod, shtrih)) {
                check[i].count++;
                product_found = 1;
                found_any_product = 1;
                break;
            }
        }

        // Если товар не найден
        if (!product_found) {
            printf("Товар со штрих-кодом ");
            for (int j = 0; j < 4; j++) {
                printf("%d", shtrih[j]);
            }
            printf(" не найден! Пожалуйста, проверьте правильность ввода!\n");
            wrong_shtrih++;
        }
    }

    // Проверка, был ли введен хотя бы один товар
    if (!found_any_product) {
        printf("--------------------------------------------------------------------------------------------------\n");
        if (wrong_shtrih > 0) {
            printf("Ни один из введенных штрих-кодов не соответствует товарам в магазине.\n");
            printf("Пожалуйста, проверьте правильность ввода штрих-кодов и попробуйте снова.\n");
        }
        else {
            printf("Вы не «купили» ни одного товара?\n");
        }
        printf("--------------------------------------------------------------------------------------------------\n");

        getchar();
        getchar();
        return 0;
    }

    printf("--------------------------------------------------------------------------------------------------");
    printf("\nКассовый чек:\n");
    printf("= Продукт   \tСтоимость (руб.)\tСтоимость с учётом скидки\tКоличество\tОбщая стоимость (руб.)\n");
    int sum = 0;
    int items_count = 0; // счетчик позиций в чеке

    for (int i = 0; i < 11; i++) {
        if (check[i].count) {
            printf("- %s   \t%d\t\t\t%d\t\t\t\t%d\t\t%d\n", products[i].name, products[i].price, check[i].price_skidka,
                check[i].count, check[i].price_skidka * check[i].count);
            sum += check[i].price_skidka * check[i].count;
            items_count++;
        }
    }

    // Вывод информации о неверных штрих-кодах
    if (wrong_shtrih > 0) {
        printf("\nПримечание: %d штрих-код(ов) не было распознано.\n", wrong_shtrih);
    }

    printf("--------------------------------------------------------------------------------------------------");
    printf("\nИТОГО: %d руб.", sum);

    getchar();
    getchar();
    return 0;
}