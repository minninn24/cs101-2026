#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_COUNT 6
#define TITLE_LEN 128

typedef struct Books {
    int id;
    int price;
    char title[TITLE_LEN];
} book_t;

int total_price(const book_t *books, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += (books + i)->price;
    }
    return sum;
}

void list_books(const book_t *books, int count) {
    printf("%-4s %-7s %s\n", "Id", "Price", "Title");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        const book_t *b = books + i;
        printf("%-4d %-7d %s\n", b->id, b->price, b->title);
    }
}

int main(void) {
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300,  "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550,  "Killers of the Flower Moon"},
        {5, 870,  "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    FILE *fp = fopen("Book.bin", "wb");
    if (fp == NULL) {
        printf("無法建立 Book.bin\n");
        return 1;
    }

    size_t written = fwrite(books, sizeof(book_t), BOOK_COUNT, fp);
    fclose(fp);

    if (written != BOOK_COUNT) {
        printf("寫入 Book.bin 發生錯誤\n");
        return 1;
    }

    list_books(books, BOOK_COUNT);
    int total = total_price(books, BOOK_COUNT);
    printf("------------------------------------------------------------\n");
    printf("Total Price: %d\n", total);

    return 0;
}