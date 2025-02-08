#include <stdio.h>
#include <string.h>
#include<stdlib.h>

// Linear Search
int linear(int arr[], int size, int a) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == a) {
            printf("%d is found at index %d\n", a, i);
            return i;
        }
    }
    printf("Number %d was not found.\n", a);
    return -1;
}

// String Linear Search
int linearSearchString(char *arr[], int size, char *key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], key) == 0) {
            printf("%s is found at index %d!!\n", key, i);
            return i;
        }
    }
    printf("String %s not found.\n", key);
    return -1;
}

// Sentinel Search
int sentinelSearch(int arr[], int size, int key) {
    int last = arr[size - 1];
    arr[size - 1] = key;
    int i = 0;
    while (arr[i] != key) {
        i++;
    }
    arr[size - 1] = last;
    if (i < size - 1 || arr[size - 1] == key) {
        printf("%d is found at index %d!!\n", key, i);
        return i;
    }
    printf("Number %d not found.\n", key);
    return -1;
}

// String Sentinel Search
int sentinelSearchString(char *arr[], int size, char *key) {
    char *last = arr[size - 1];
    arr[size - 1] = key;
    int i = 0;
    while (strcmp(arr[i], key) != 0) {
        i++;
    }
    arr[size - 1] = last;
    if (i < size - 1 || strcmp(arr[size - 1], key) == 0) {
        printf("%s is found at index %d!!\n", key, i);
        return i;
    }
    printf("String %s not found.\n", key);
    return -1;
}

// Binary Search
int binary(int arr[], int size, int a) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == a) {
            printf("%d found at index %d\n", a, mid);
            return mid;
        }
        if (arr[mid] < a) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Number %d not found.\n", a);
    return -1;
}

// Bubble Sort
void bubble(int arr[], int size) {
    int comparisons = 0;
    int shifts = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                shifts++;
            }
        }
    }
    printf("Array sorted using Bubble Sort.\nComapaisions: %d\n Swaps: %d\n",&comparisons, &shifts);
}

// Insertion Sort
void insertion(int arr[], int size) {
    int comparisons = 0;
    int shifts = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }
        arr[j + 1] = key;
    }
    printf("Array sorted using Insertion Sort.\nComapaisions: %d\n Swaps: %d\n",&comparisons, &shifts);
}

int main() {
    int choice, searchKey, size, sortChoice;
    char keyString[50];

    printf("Choose data type:\n");
    printf("1. Integer Array\n");
    printf("2. String Array\n");
    printf("Enter your choice: ");
    int dataTypeChoice;
    scanf("%d", &dataTypeChoice);

    if (dataTypeChoice == 1) {
        // Integer Array Option
        printf("Enter the size of the integer array: ");
        scanf("%d", &size);
        int arr[size];
        printf("Enter elements of the array:\n");
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        while (1) {
            printf("\nInteger Array Menu:\n");
            printf("1. Linear Search\n");
            printf("2. Sentinel Search\n");
            printf("3. Binary Search\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter number to search: ");
                    scanf("%d", &searchKey);
                    linear(arr, size, searchKey);
                    break;
                case 2:
                    printf("Enter number to search: ");
                    scanf("%d", &searchKey);
                    sentinelSearch(arr, size, searchKey);
                    break;
                case 3:
                    printf("Binary Search requires a sorted array.\n");
                    printf("Choose sorting method:\n");
                    printf("1. Bubble Sort\n");
                    printf("2. Insertion Sort\n");
                    printf("Enter your choice: ");
                    scanf("%d", &sortChoice);
                    if (sortChoice == 1) {
                        bubble(arr, size);
                    } else if (sortChoice == 2) {
                        insertion(arr, size);
                    } else {
                        printf("Invalid sorting choice.\n");
                        continue;
                    }
                    printf("Enter number to search: ");
                    scanf("%d", &searchKey);
                    binary(arr, size, searchKey);
                    break;
                case 4:
                    printf("Exiting integer search menu.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else if (dataTypeChoice == 2) {
        // String Array Option
        printf("Enter the size of the string array: ");
        scanf("%d", &size);
        char *arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = malloc(50 * sizeof(char));
            if (!arr[i]) { 
                printf("Memory allocation failed.\n");
                return 1;
            }
            printf("Enter string %d: ", i + 1);
            scanf("%s", arr[i]);
        }

        while (1) {
            printf("\nString Array Menu:\n");
            printf("1. Linear Search\n");
            printf("2. Sentinel Search\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter string to search: ");
                    scanf("%s", keyString);
                    linearSearchString(arr, size, keyString);
                    break;
                case 2:
                    printf("Enter string to search: ");
                    scanf("%s", keyString);
                    sentinelSearchString(arr, size, keyString);
                    break;
                case 3:
                    printf("Exiting string search menu.\n");
                    for (int i = 0; i < size; i++) {
                        free(arr[i]);
                    }
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid data type choice.\n");
    }

    return 0;
}