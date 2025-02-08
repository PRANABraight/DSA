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