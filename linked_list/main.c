
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Book {
    char title[100];
    float price;
    int pages;
    char language[30];
    float weight;
    int year;
    struct Book *next;
} Book;

Book* createBook(
    const char *title,
    float price,
    int pages,
    const char *language,
    float weight,
    int year
) {
    Book *book = malloc(sizeof(Book));

    if (book == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    snprintf(book->title, sizeof(book->title), "%s", title);
    book->price = price;
    book->pages = pages;
    snprintf(book->language, sizeof(book->language), "%s", language);
    book->weight = weight;
    book->year = year;
    book->next = NULL;

    return book;
}

void appendBook(Book **head, Book *newBook) {
    if (*head == NULL) {
        *head = newBook;
        return;
    }

    Book *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newBook;
}

void printBooks(const Book *head) {
    const Book *current = head;
    int number = 1;

    printf("HARRY POTTER BOOKS\n\n");

    while (current != NULL) {
        printf("Book #%d\n", number++);
        printf("Title: %s\n", current->title);
        printf("Price: %.2f EUR\n", current->price);
        printf("Pages: %d\n", current->pages);
        printf("Language: %s\n", current->language);
        printf("Weight: %.2f kg\n", current->weight);
        printf("Publication year: %d\n", current->year);
        printf("----------------------------------------\n");

        current = current->next;
    }
}

void freeBooks(Book *head) {
    while (head != NULL) {
        Book *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    setlocale(LC_ALL, "");

    Book *head = NULL;

    appendBook(&head, createBook(
        "Harry Potter and the Philosopher's Stone",
        12.99, 223, "English", 0.35, 1997
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Chamber of Secrets",
        13.99, 251, "English", 0.38, 1998
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Prisoner of Azkaban",
        14.99, 317, "English", 0.45, 1999
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Goblet of Fire",
        16.99, 636, "English", 0.75, 2000
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Order of the Phoenix",
        18.99, 766, "English", 0.90, 2003
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Half-Blood Prince",
        17.99, 607, "English", 0.70, 2005
    ));

    appendBook(&head, createBook(
        "Harry Potter and the Deathly Hallows",
        19.99, 607, "English", 0.72, 2007
    ));

    printBooks(head);
    freeBooks(head);

    return 0;
}
