#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct QueueNode {
    int id;
    char eventType[MAX]; 
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

QueueNode* createNode(int id, const char* eventType) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->id = id;
    strncpy(newNode->eventType, eventType, MAX - 1);
    newNode->eventType[MAX - 1] = '\0'; 
    newNode->next = NULL;
    return newNode;
}

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, int id, const char* eventType) {
    QueueNode* newNode = createNode(id, eventType);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    QueueNode* temp = queue->front;
    int id = temp->id;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    printf("Dequeued: %d, %s\n", temp->id, temp->eventType);
    free(temp);
    return 0;
}

void peek(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front element: %d, %s\n", queue->front->id, queue->front->eventType);
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

void printQueue(Queue* queue) {
    QueueNode* temp = queue->front;
    while (temp) {
        printf("[%d, %s] -> ", temp->id, temp->eventType);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Queue* queue = createQueue();
    int choice, id;
    char eventType[MAX];

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Print Queue\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter id: ");
                scanf("%d", &id);
                printf("Enter status: ");
                scanf(" %[^\n]", eventType);  
                enqueue(queue, id, eventType);
                break;

            case 2:
                dequeue(queue);
                break;

            case 3:
                peek(queue);
                break;

            case 4:
                printf("Queue contents:\n");
                printQueue(queue);
                break;

            case 5:
                freeQueue(queue);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
