#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// struct
struct Node
{
    int id;
    char eventType[50];
    int severity;
    struct Node *next;
};


// insert
void insertAtEnd(struct Node **head, int id, char *eventType, int severity)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->eventType, eventType);
    newNode->severity = severity;
    newNode->next = NULL;


    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void insertAtPosition(struct Node **head, int position, int id, char *eventType, int severity)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->eventType, eventType);
    newNode->severity = severity;
    newNode->next = NULL;


    if (position == 0)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }


    // Traverse to node-1
    struct Node *temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }


    if (temp == NULL)
    {
        printf("Position out of range.\n");
        free(newNode);
        return;
    }


    newNode->next = temp->next;
    temp->next = newNode;
}



// delete
void deleteByid(struct Node **head, int id)
{
    struct Node *temp = *head;
    struct Node *prev = NULL;


    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        return;
    }


    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }


    if (temp == NULL)
        return;


    prev->next = temp->next;
    free(temp);
}


void deleteAtPosition(struct Node **head, int position)
{
    if (*head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    struct Node *temp = *head;


    if (position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }


    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }


    if (temp == NULL || temp->next == NULL)
    {
        printf("Position out of range.\n");
        return;
    }


    struct Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
}


// display
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("id: %d, Event: %s, Severity: %d -> ", node->id, node->eventType, node->severity);
        node = node->next;
    }
    printf("NULL\n");
}


// search
struct Node *searchByid(struct Node *head, int id)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


int main()
{
    struct Node *head = NULL;
    int choice, id, severity;
    char eventType[50];


    while (1)
    {
        printf("\n-----Menu-----\n");
        printf("1. Insert Log-id\n");
        printf("2. Delete Log-id\n");
        printf("3. Display Logs\n");
        printf("4. Search Log\n");
        printf("5. Insert Log-position\n");
        printf("6.Delete Log-position\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
        case 1:
            printf("Enter id: ");
            scanf("%d", &id);
            printf("Enter event type: ");
            scanf("%s", eventType);
            printf("Enter severity: ");
            scanf("%d", &severity);
            insertAtEnd(&head, id, eventType, severity);
            break;
        case 2:
            printf("Enter id of log to delete: ");
            scanf("%d", &id);
            deleteByid(&head, id);
            break;
        case 3:
            printf("Log Entries:\n");
            printList(head);
            break;
        case 4:
            printf("Enter id to search: ");
            scanf("%d", &id);
            struct Node *foundNode = searchByid(head, id);
            if (foundNode != NULL)
            {
                printf("Found Log - id: %d, Event: %s, Severity: %d\n",
                       foundNode->id, foundNode->eventType, foundNode->severity);
            }
            else
            {
                printf("Log with id %d not found.\n", id);
            }
            break;


        case 5:
            printf("Enter position to insert: ");
            int position;
            scanf("%d", &position);
            printf("Enter id: ");
            scanf("%d", &id);
            printf("Enter event type: ");
            scanf("%s", eventType);
            printf("Enter severity: ");
            scanf("%d", &severity);
            insertAtPosition(&head, position, id, eventType, severity);
            break;


        case 6:
            printf("Enter position to delete: ");
           
            scanf("%d", &position);
            deleteAtPosition(&head, position);
            break;


        case 7:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
