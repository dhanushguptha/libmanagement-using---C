#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    int book_id;
    char title[100];
    char author[100];
    int is_issued;
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
} Library;

void initializeLibrary(Library *library) {
    library->count = 0;
}

void addBook(Library *library, int book_id, const char *title, const char *author) {
    if (library->count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }
    library->books[library->count].book_id = book_id;
    strcpy(library->books[library->count].title, title);
    strcpy(library->books[library->count].author, author);
    library->books[library->count].is_issued = 0;
    library->count++;
    printf("Book added successfully: %s\n", title);
}

void removeBook(Library *library, int book_id) {
    int i;
    for (i = 0; i < library->count; i++) {
        if (library->books[i].book_id == book_id) {
            for (int j = i; j < library->count - 1; j++) {
                library->books[j] = library->books[j + 1];
            }
            library->count--;
            printf("Book removed successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void issueBook(Library *library, int book_id) {
    for (int i = 0; i < library->count; i++) {
        if (library->books[i].book_id == book_id) {
            if (library->books[i].is_issued) {
                printf("Book is already issued.\n");
            } else {
                library->books[i].is_issued = 1;
                printf("Book issued successfully: %s\n", library->books[i].title);
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void returnBook(Library *library, int book_id) {
    for (int i = 0; i < library->count; i++) {
        if (library->books[i].book_id == book_id) {
            if (!library->books[i].is_issued) {
                printf("Book was not issued.\n");
            } else {
                library->books[i].is_issued = 0;
                printf("Book returned successfully: %s\n", library->books[i].title);
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void displayBooks(Library *library) {
    if (library->count == 0) {
        printf("No books in the library.\n");
        return;
    }
    for (int i = 0; i < library->count; i++) {
        Book *book = &library->books[i];
        printf("Book ID: %d, Title: %s, Author: %s, Issued: %s\n", 
               book->book_id, book->title, book->author, book->is_issued ? "Yes" : "No");
    }
}

int main() {
    Library library;
    initializeLibrary(&library);

    while (1) {
        printf("\n========= Library Management System =========\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Display Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            int book_id;
            char title[100], author[100];
            printf("Enter Book ID: ");
            scanf("%d", &book_id);
            getchar(); // Consume newline character
            printf("Enter Book Title: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0; // Remove newline character
            printf("Enter Book Author: ");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = 0; // Remove newline character
            addBook(&library, book_id, title, author);

        } else if (choice == 2) {
            int book_id;
            printf("Enter Book ID to remove: ");
            scanf("%d", &book_id);
            removeBook(&library, book_id);

        } else if (choice == 3) {
            int book_id;
            printf("Enter Book ID to issue: ");
            scanf("%d", &book_id);
            issueBook(&library, book_id);

        } else if (choice == 4) {
            int book_id;
            printf("Enter Book ID to return: ");
            scanf("%d", &book_id);
            returnBook(&library, book_id);

        } else if (choice == 5) {
            displayBooks(&library);

        } else if (choice == 6) {
            printf("Exiting the system. Goodbye!\n");
            break;

        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
