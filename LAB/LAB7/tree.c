#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char intrusionRule[50]; 
    struct TreeNode* left;  
    struct TreeNode* right; 
} TreeNode;


TreeNode* createNode(const char* rule);
TreeNode* insertNode(TreeNode* root, const char* rule, TreeNode* target, char direction);
TreeNode* insertNodeCLI(TreeNode* root);
TreeNode* deleteRoot(TreeNode* root);
void preorderTraversal(TreeNode* root);
void inorderTraversal(TreeNode* root);
void postorderTraversal(TreeNode* root);
void levelOrderTraversal(TreeNode* root);
int height(TreeNode* root);
void printLevel(TreeNode* root, int level);
TreeNode* constructFromInPre(char in[][50], char pre[][50], int start, int end, int* preIndex);
TreeNode* constructFromInPost(char in[][50], char post[][50], int start, int end, int* postIndex);
int search(char arr[][50], int start, int end, const char* value);
void freeTree(TreeNode* root);


int main() {
    TreeNode* root = NULL;
    int choice;

    do {
        printf("\n--- Intrusion Detection System Menu ---\n");
        printf("1. Insert Signatures\n");
        printf("2. Delete Root Signatures\n");
        printf("3. Preorder Traversal\n");
        printf("4. Inorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Level Order Traversal\n");
        printf("7. Construct from Inorder and Preorder\n");
        printf("8. Construct from Inorder and Postorder\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = insertNodeCLI(root);
                break;
            case 2:
                root = deleteRoot(root);
                break;
            case 3:
                printf("Preorder Traversal of Rules:\n");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Inorder Traversal of Rules:\n");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder Traversal of Rules:\n");
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Level Order Traversal of Rules:\n");
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 7: {
                int n;
                printf("Enter the number of nodes in the tree: ");
                scanf("%d", &n);

                char in[n][50];
                char pre[n][50];

                printf("Enter the Inorder traversal (space-separated):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%s", in[i]);
                }

                printf("Enter the Preorder traversal (space-separated):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%s", pre[i]);
                }

                int preIndex = 0;
                root = constructFromInPre(in, pre, 0, n - 1, &preIndex);
                printf("Tree constructed from Inorder and Preorder.\n");
                break;
            }
            case 9: {
                int n;
                printf("Enter the number of nodes in the tree: ");
                scanf("%d", &n);

                char in[n][50];
                char post[n][50];

                printf("Enter the Inorder traversal (space-separated):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%s", in[i]);
                }

                printf("Enter the Postorder traversal (space-separated):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%s", post[i]);
                }

                int postIndex = n - 1;
                root = constructFromInPost(in, post, 0, n - 1, &postIndex);
                printf("Tree constructed from Inorder and Postorder.\n");
                break;
            }
            case 0:
                printf("Exiting...\n");
                freeTree(root);
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

TreeNode* createNode(const char* rule) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->intrusionRule, rule);
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertNodeCLI(TreeNode* root) {
    char rule[50];
    char direction;

    if (root == NULL) {
        printf("Enter the intrusion rule for the root node: ");
        scanf(" %[^\n]s", rule);
        return createNode(rule); 
    }

    printf("Enter the intrusion rule to insert: ");
    scanf(" %[^\n]s", rule);
    printf("Do you want to add it to the (L)eft or (R)ight of the root? ");
    scanf(" %c", &direction);

    if (direction == 'L' || direction == 'l') {
        root->left = insertNode(root->left, rule, root, direction);
    } else if (direction == 'R' || direction == 'r') {
        root->right = insertNode(root->right, rule, root, direction);
    } else {
        printf("Invalid direction! Please use 'L' or 'R'.\n");
    }

    return root;
}

TreeNode* insertNode(TreeNode* root, const char* rule, TreeNode* target, char direction) {
    if (root == NULL) {
        return createNode(rule);
    }

    if (direction == 'L' || direction == 'l') {
        if (root->left == NULL) {
            root->left = createNode(rule);
        } else {
            root->left = insertNode(root->left, rule, root->left, direction);
        }
    } else if (direction == 'R' || direction == 'r') {
        if (root->right == NULL) {
            root->right = createNode(rule);
        } else {
            root->right = insertNode(root->right, rule, root->right, direction);
        }
    }

    return root;
}


TreeNode* deleteRoot(TreeNode* root) {
    if (root == NULL) {
        printf("The tree is empty!\n");
        return NULL;
    }
    TreeNode* temp = root;
    root = root->left ? root->left : root->right;
    free(temp);
    printf("Root rule deleted successfully.\n");
    return root;
}


void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%s ", root->intrusionRule);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s ", root->intrusionRule);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%s ", root->intrusionRule);
    }
}


void levelOrderTraversal(TreeNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
    }
}

void printLevel(TreeNode* root, int level) {
    if (root == NULL) return;
    if (level == 1) printf("%s ", root->intrusionRule);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

int height(TreeNode* root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

TreeNode* constructFromInPre(char in[][50], char pre[][50], int start, int end, int* preIndex) {
    if (start > end) return NULL;

    TreeNode* node = createNode(pre[*preIndex]);
    (*preIndex)++;

    if (start == end) return node;

    int inIndex = search(in, start, end, node->intrusionRule);
    node->left = constructFromInPre(in, pre, start, inIndex - 1, preIndex);
    node->right = constructFromInPre(in, pre, inIndex + 1, end, preIndex);

    return node;
}

TreeNode* constructFromInPost(char in[][50], char post[][50], int start, int end, int* postIndex) {
    if (start > end) return NULL;

    TreeNode* node = createNode(post[*postIndex]);
    (*postIndex)--;

    if (start == end) return node;

    int inIndex = search(in, start, end, node->intrusionRule);
    node->right = constructFromInPost(in, post, inIndex + 1, end, postIndex);
    node->left = constructFromInPost(in, post, start, inIndex - 1, postIndex);

    return node;
}


int search(char arr[][50], int start, int end, const char* value) {
    for (int i = start; i <= end; i++) {
        if (strcmp(arr[i], value) == 0)
            return i;
    }
    return -1;
}


void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
