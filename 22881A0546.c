#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_NAME_LENGTH 50
#define MAX_ISBN_LENGTH 13

// Book structure
struct Book {
    char title[MAX_NAME_LENGTH];
    char author[MAX_NAME_LENGTH];
    char isbn[MAX_ISBN_LENGTH];
    int quantity;
};

// User structure
struct User {
    int user_id;
    char name[MAX_NAME_LENGTH];
};

// Function to display available books
void displayBooks(struct Book books[], int bookCount) {
    printf("Available Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, ISBN: %s, Quantity: %d\n",
               books[i].title, books[i].author, books[i].isbn, books[i].quantity);
    }
    printf("\n");
}

// Function to borrow a book
void borrowBook(struct User user, struct Book books[], int bookCount, const char *isbn) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0 && books[i].quantity > 0) {
            printf("Book '%s' borrowed by %s.\n", books[i].title, user.name);
            books[i].quantity--;
            return;
        }
    }
    printf("Book not available or ISBN not found.\n");
}

int main() {
    struct Book books[MAX_BOOKS];
    struct User users[MAX_USERS];

    int bookCount = 0;
    int userCount = 0;

    // Load data from a file (if available)
    FILE *file = fopen("library_data.txt", "r");
    if (file != NULL) {
        fread(&bookCount, sizeof(int), 1, file);
        fread(books, sizeof(struct Book), bookCount, file);

        fread(&userCount, sizeof(int), 1, file);
        fread(users, sizeof(struct User), userCount, file);

        fclose(file);
    }

    // Example data
    strcpy(books[bookCount].title, "Sample Book");
    strcpy(books[bookCount].author, "John Doe");
    strcpy(books[bookCount].isbn, "123456789");
    books[bookCount].quantity = 5;
    bookCount++;

    strcpy(books[bookCount].title, "Another Book");
    strcpy(books[bookCount].author, "Jane Smith");
    strcpy(books[bookCount].isbn, "987654321");
    books[bookCount].quantity = 3;
    bookCount++;

    strcpy(users[userCount].name, "Alice");
    users[userCount].user_id = 1;
    userCount++;

    // Main menu
    int choice;
    do {
        printf("Library Management System\n");
        printf("1. Display Available Books\n");
        printf("2. Borrow a Book\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks(books, bookCount);
                break;

            case 2:
                if (userCount > 0) {
                    int userId;
                    printf("Enter your user ID: ");
                    scanf("%d", &userId);

                    struct User currentUser;
                    for (int i = 0; i < userCount; i++) {
                        if (users[i].user_id == userId) {
                            currentUser = users[i];
                            break;
                        }
                    }

                    if (currentUser.user_id == userId) {
                        char isbn[MAX_ISBN_LENGTH];
                        printf("Enter the ISBN of the book you want to borrow: ");
                        scanf("%s", isbn);

                        borrowBook(currentUser, books, bookCount, isbn);
                    } else {
                        printf("User not found.\n");
                    }
                } else {
                    printf("No users in the system. Add users first.\n");
                }
                break;

            case 3:
                // Save data to a file before exiting
                file = fopen("library_data.txt", "w");
                if (file != NULL) {
                    fwrite(&bookCount, sizeof(int), 1, file);
                    fwrite(books, sizeof(struct Book), bookCount, file);

                    fwrite(&userCount, sizeof(int), 1, file);
                    fwrite(users, sizeof(struct User), userCount, file);

                    fclose(file);
                }
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}
