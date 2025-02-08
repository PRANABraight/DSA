#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL 0
#define SUSPICIOUS 1
#define MALICIOUS 2
#define MAX 1000

struct NetworkNode {
    int id;
    int status;
    int packetCount;
    int failedAttempts;
};

struct Queue {
    int *items;
    int front;
    int rear;
    int maxSize;
};

int *visited;
int **graph;
int vertices;
struct NetworkNode *nodes;
FILE *logFile;

int scanCount = 0;
struct {
    int nodeId;
    int type;  // 0 for BFS, 1 for DFS
    char status[20];
    int timestamp;
} scanResults[MAX];

struct Queue* createQueue(int size) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->items = (int *)malloc(size * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->maxSize = size;
    return q;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == q->maxSize - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (q->front == -1)
        return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

void freeQueue(struct Queue* q) {
    free(q->items);
    free(q);
}

void initializeNetworkNodes() {
    nodes = (struct NetworkNode *)malloc(vertices * sizeof(struct NetworkNode));
    visited = (int *)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        nodes[i].id = i;
        nodes[i].status = NORMAL;
        nodes[i].packetCount = 0;
        nodes[i].failedAttempts = 0;
        visited[i] = 0;
    }
}

int isNodeMalicious(int nodeId) {
    return (nodes[nodeId].packetCount > 1000 || nodes[nodeId].failedAttempts > 5);
}

void recordScanResult(int nodeId, int type, const char* status) {
    scanResults[scanCount].nodeId = nodeId;
    scanResults[scanCount].type = type;
    strcpy(scanResults[scanCount].status, status);
    scanResults[scanCount].timestamp = scanCount;
    scanCount++;
}

void BFS_IDS(int startVertex) {
    struct Queue* q = createQueue(vertices);
    int *parent = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[startVertex] = 1;
    enqueue(q, startVertex);

    fprintf(logFile, "\nBFS Intrusion Detection Scan Results:\n");

    printf("\nBFS Traversal Path: ");
    
    while (q->front != -1) {
        int currentVertex = dequeue(q);
        printf("%d -> ", currentVertex);

        if (isNodeMalicious(currentVertex)) {
            fprintf(logFile, "Alert! Suspicious activity detected at node %d\n", currentVertex);
            printf("\nMALICIOUS NODE DETECTED: %d (Packets: %d, Failed Attempts: %d)\n", 
                currentVertex, nodes[currentVertex].packetCount, 
                nodes[currentVertex].failedAttempts);
            recordScanResult(currentVertex, 0, "MALICIOUS");
            nodes[currentVertex].status = MALICIOUS;
        }

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = currentVertex;
                enqueue(q, i);

                if (nodes[currentVertex].status == MALICIOUS) {
                    nodes[i].status = SUSPICIOUS;
                    fprintf(logFile, "Warning: Node %d connected to malicious node %d\n", i, currentVertex);
                }
            }
        }
    }
    printf("end\n");
    freeQueue(q);
    free(parent);
}

void DFS_IDS(int vertex) {
    visited[vertex] = 1;
    printf("%d -> ", vertex);

    if (isNodeMalicious(vertex)) {
        fprintf(logFile, "Alert! Suspicious activity detected at node %d\n", vertex);
        printf("\nMALICIOUS NODE DETECTED: %d (Packets: %d, Failed Attempts: %d)\n", 
            vertex, nodes[vertex].packetCount, nodes[vertex].failedAttempts);
        recordScanResult(vertex, 1, "MALICIOUS");
        nodes[vertex].status = MALICIOUS;
    }

    for (int i = 0; i < vertices; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            if (nodes[vertex].status == MALICIOUS) {
                nodes[i].status = SUSPICIOUS;
                fprintf(logFile, "Warning: Node %d connected to malicious node %d\n", i, vertex);
            }
            DFS_IDS(i);
        }
    }
}

void freeGraph() {
    for (int i = 0; i < vertices; i++) {
        free(graph[i]);
    }
    free(graph);
}

void simulateNetworkActivity() {
    int numSimulations;
    printf("\nEnter number of network activities to simulate: ");
    scanf("%d", &numSimulations);

    for (int i = 0; i < numSimulations; i++) {
        int nodeId, activityType, value;
        printf("\nSimulation %d:\n", i + 1);
        printf("Enter node ID (0 to %d): ", vertices - 1);
        scanf("%d", &nodeId);

        if (nodeId < 0 || nodeId >= vertices) {
            printf("Invalid node ID. Skipping...\n");
            continue;
        }

        printf("Select activity type:\n");
        printf("1. Set packet count\n");
        printf("2. Set failed attempts\n");
        printf("Choice: ");
        scanf("%d", &activityType);

        printf("Enter value: ");
        scanf("%d", &value);

        if (value < 0) {
            printf("Invalid value. Skipping...\n");
            continue;
        }

        switch (activityType) {
            case 1:
                nodes[nodeId].packetCount = value;
                printf("Set packet count for Node %d to %d\n", nodeId, value);
                break;
            case 2:
                nodes[nodeId].failedAttempts = value;
                printf("Set failed attempts for Node %d to %d\n", nodeId, value);
                break;
            default:
                printf("Invalid activity type. Skipping...\n");
        }
    }
}

int main() {
    printf("Enter number of network nodes: ");
    scanf("%d", &vertices);

    // Allocate memory
    graph = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int *)malloc(vertices * sizeof(int));
    }

    printf("Enter the network connectivity matrix (0 for no connection, 1 for connection):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            do {
                scanf("%d", &graph[i][j]);
                if (graph[i][j] != 0 && graph[i][j] != 1) {
                    printf("Please enter only 0 or 1: ");
                }
            } while (graph[i][j] != 0 && graph[i][j] != 1);
        }
    }

    initializeNetworkNodes();

    simulateNetworkActivity();  // Replace the hard-coded simulation

    // log file
    logFile = fopen("scan_results.log", "w");
    if (!logFile) {
        printf("Error: Unable to open log file.\n");
        return 1;
    }

    fprintf(logFile, "Starting IDS scan from node 0...\n");

    printf("\n=== Starting Network Security Scan ===\n");
    
    printf("\nBFS-based IDS Scan:");
    BFS_IDS(0);

    for (int i = 0; i < vertices; i++) {
        visited[i] = 0; 
    }

    printf("\nDFS-based IDS Scan:");
    printf("\nDFS Traversal Path: ");
    DFS_IDS(0);
    printf("end\n");
    
    printf("\n=== Detailed Scan Results ===\n");
    for (int i = 0; i < scanCount; i++) {
        printf("Scan #%d: Node %d [%s] detected by %s\n",
            i + 1,
            scanResults[i].nodeId,
            scanResults[i].status,
            scanResults[i].type == 0 ? "BFS" : "DFS");
    }
    
    printf("\n=== Final Network Status ===\n");
    for (int i = 0; i < vertices; i++) {
        printf("Node %d:\n", i);
        printf("  Status: %s\n", 
            nodes[i].status == NORMAL ? "Normal" :
            nodes[i].status == SUSPICIOUS ? "Suspicious" : "Malicious");
        printf("  Packet Count: %d\n", nodes[i].packetCount);
        printf("  Failed Attempts: %d\n", nodes[i].failedAttempts);
    }

    fprintf(logFile, "\nFinal Network Status:\n");
    for (int i = 0; i < vertices; i++) {
        fprintf(logFile, "Node %d: %s\n", i,
                nodes[i].status == NORMAL ? "Normal" :
                nodes[i].status == SUSPICIOUS ? "Suspicious" : "Malicious");
    }

    fclose(logFile);

    // Free allocated memory
    freeGraph();
    free(nodes);
    free(visited);

    printf("Scan results saved to 'scan_results.log'.\n");
    return 0;
}
