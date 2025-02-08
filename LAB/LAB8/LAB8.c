#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Structure definition
typedef struct Node {
    int data; 
    int frequency;
    time_t lastDetected;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(int data);
Node* insertNode(Node* root, int data);
int searchNode(Node* root, int key);
Node* findMin(Node* root);
Node* deleteNode(Node* root, int key);
int calculateHeight(Node* root);
int countNodes(Node* root);
void logIntrusion(int signature);
void checkAnomalies(Node* root, int timeWindow, int frequencyThreshold);
void inOrderTraversal(Node* root);
void preOrderTraversal(Node* root);
void postOrderTraversal(Node* root);

// Add this global variable at the top with other declarations
static int anomaliesFound = 0;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->frequency = 1;
    newNode->lastDetected = time(NULL);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data == root->data) {
        root->frequency++;
        root->lastDetected = time(NULL);
    }
    else if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int searchNode(Node* root, int key) {
    if (root == NULL)
        return 0; 

    if (key == root->data)
        return 1; 

    if (key < root->data)
        return searchNode(root->left, key);
    else
        return searchNode(root->right, key);
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}


Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


int calculateHeight(Node* root) {
    if (root == NULL)
        return -1;

    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void logIntrusion(int signature) {
    printf("Intrusion Detected: Signature %d\n", signature);
}

void checkAnomalies(Node* root, int timeWindow, int frequencyThreshold) {
    if (root == NULL)
        return;

    time_t currentTime = time(NULL);
    double timeDifference = difftime(currentTime, root->lastDetected);

    if (timeDifference <= timeWindow && root->frequency > frequencyThreshold) {
        printf("ANOMALY DETECTED: Signature %d\n", root->data);
        printf("- Frequency: %d occurrences\n", root->frequency);
        printf("- Time window: %.1f seconds ago\n", timeDifference);
        printf("- Threshold exceeded: %d (limit: %d)\n", 
               root->frequency, frequencyThreshold);
        printf("----------------------------------------\n");
        anomaliesFound = 1;
    }

    checkAnomalies(root->left, timeWindow, frequencyThreshold);
    checkAnomalies(root->right, timeWindow, frequencyThreshold);
}

void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}


void postOrderTraversal(Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

//main 
int main() {
    Node* root = NULL;
    int choice, input;

    do {
        printf("\n--- Intrusion Detection System BST ---\n");
        printf("1. Insert Intrusion Signature\n");
        printf("2. Search for a Signature\n");
        printf("3. Delete a Signature\n");
        printf("4. Display In-Order Traversal\n");
        printf("5. Display Pre-Order Traversal\n");
        printf("6. Display Post-Order Traversal\n");
        printf("7. Calculate Height of BST\n");
        printf("8. Count Total Nodes\n");
        printf("9. Log Intrusion (Simulate)\n");
        printf("10. Check Anomalies\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the intrusion signature to insert: ");
            scanf("%d", &input);
            root = insertNode(root, input);
            printf("Signature '%d' inserted successfully.\n", input);
            break;
        case 2:
            printf("Enter the intrusion signature to search: ");
            scanf("%d", &input);
            if (searchNode(root, input))
                printf("Signature '%d' found in the BST.\n", input);
            else
                printf("Signature '%d' not found in the BST.\n", input);
            break;
        case 3:
            printf("Enter the intrusion signature to delete: ");
            scanf("%d", &input);
            root = deleteNode(root, input);
            printf("Signature '%d' deleted successfully (if it existed).\n", input);
            break;
        case 4:
            printf("In-Order Traversal: ");
            inOrderTraversal(root);
            printf("\n");
            break;
        case 5:
            printf("Pre-Order Traversal: ");
            preOrderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Post-Order Traversal: ");
            postOrderTraversal(root);
            printf("\n");
            break;
        case 7:
            printf("Height of the BST: %d\n", calculateHeight(root));
            break;
        case 8:
            printf("Total number of nodes: %d\n", countNodes(root));
            break;
        case 9:
            printf("Enter the intrusion signature to log: ");
            scanf("%d", &input);
            root = insertNode(root, input);  // Updated to track frequency
            logIntrusion(input);
            break;
        case 10:
            printf("Checking for anomalies (threshold: 3 occurrences in 60 seconds)...\n");
            anomaliesFound = 0;  // Reset the flag
            checkAnomalies(root, 60, 3);
            if (!anomaliesFound) {
                printf("No anomalies detected in the current time window.\n");
            }
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
