#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[35];
    char status[25]; 
    struct Book *next;
};

// insert
void insertAtEnd(struct Book **head, int id, char *title, char* status) {
    struct Book *temp = *head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Error!! Book ID must be unique.\n");
            return;
        }
        temp = temp->next;
    }

    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));
    if (id > 0) { //positve
        newBook->id = id;
        strcpy(newBook->title, title);
        strcpy(newBook->status, status);
        newBook->next = NULL;

        if (*head == NULL) {
            *head = newBook;
        } else {
            struct Book *temp = *head;
            while (temp->next != NULL) {   
                temp = temp->next;
            }
            temp->next = newBook;
        }
    } 

    else {
        printf("Error: Invalid ID.\n");
    }
}


void printList(struct Book *book) {
    while (book != NULL) {
        printf("[id: %d, Title: %s, Status: %s] -> ", book->id, book->title, book->status);
        book = book->next;
    }
    printf("NULL\n");
}

void count(struct Book *head) {
    int a = 0, i = 0, r = 0, l = 0;
    if (head == NULL) {
        printf("Empty node\n");
        return;
    }

    struct Book *temp = head;
    while (temp != NULL) {   
        
        if (strcmp(temp->status, "available") == 0) {
            a++;
        } 
        
        else if (strcmp(temp->status, "issued") == 0) {
            i++;
        } 
        else if (strcmp(temp->status, "reserved") == 0) {
            r++;
        } 
        else if (strcmp(temp->status, "lost") == 0) {
            l++;
        }
        temp = temp->next;
    }
    printf("The number of books with status\n Available: %d \n Issued: %d \n Reserved: %d \n Lost: %d \n", a, i, r, l);
}

// delete
void deleteByid(struct Book **head, int id) {
    struct Book *temp = *head;
    struct Book *prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        return;
    }


    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;+
    
    }


    if (temp == NULL)
        return;

    prev->next = temp->next;
    free(temp);
}

int main() {
    struct Book *head = NULL;
    int choice;

    insertAtEnd(&head, 1, "The Great Gatsby", "available");
    insertAtEnd(&head, 2, "The Stranger", "issued");
    insertAtEnd(&head, 3, "1984", "reserved");
    insertAtEnd(&head, 4, "Alchemist", "lost");

    while(1){
    printf("----------Menu---------\n");
    printf("1. Add new Book\n");
    printf("2. Display all books\n");
    printf("3. Count books by status\n");
    printf("4. Delete by ID\n");
    printf("5. Exit\n");
    printf("------------------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            int id;
            char title[35], status[25];
            printf("Enter id: ");
            scanf("%d", &id);
            printf("Enter title: ");
            scanf(" %[^\n]%*c", title);
            printf("Enter status: ");
            scanf(" %[^\n]%*c", status);

            insertAtEnd(&head, id, title, status);
            break;
        }
        case 2:
            // Print 
            printList(head);
            break;
        case 3:
            // Count 
            count(head);
            break;
        case 4: {
            // Delete-id
            int id;
            printf("Enter id to delete: ");
            scanf("%d", &id);
            deleteByid(&head, id);
            break;
        }
        case 5:
            // Exit 
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid Input\n");
            break;
    }

    }

    return 0;
}
