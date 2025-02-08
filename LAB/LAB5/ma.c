#include <stdio.h>
#include <string.h>

#define MAX 5

// Linear Search
int linearSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            printf("%d is found at index %d!!\n", key, i);
            return i;
        }
    }
    printf("Number %d not found.\n", key);
    return -1;
}

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

// Binary Search
int binarySearch(int arr[], int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            printf("%d is found at index %d!!\n", key, mid);
            return mid;
        }
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Number %d not found.\n", key);
    return -1;
}

// Bubble Sort
void bubbleSort(int arr[], int size) {
    int comparisons = 0;
    int swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
    printf("Bubble Sort - Comparisons: %d, Swaps: %d\n", comparisons, swaps);
}

// Insertion Sort
void insertionSort(int arr[], int size) {
    int comparisons = 0;
    int shifts = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }
        arr[j + 1] = key;
        comparisons++;
    }
    printf("Insertion Sort - Comparisons: %d, Shifts: %d\n", comparisons, shifts);
}

// Main Function
int main() {
    int arr[MAX]; //= {64, 34, 25, 12, 22};
    
    char *arrStr[MAX] = {"apple", "orange", "banana", "grape", "pear"};

    printf("Input arrays of size %d: ", MAX);
    scanf("%d", arr);
    
    int key = 25;
    char *keyStr = "banana";
    
    // Linear Search
    linearSearch(arr, MAX, key);
    linearSearchString(arrStr, MAX, keyStr);

    // Sentinel Search
    sentinelSearch(arr, MAX, key);

    // Binary Search
    bubbleSort(arr, MAX); // Sort before binary search
    binarySearch(arr, MAX, key);

    // Sorting
    bubbleSort(arr, MAX);
    insertionSort(arr, MAX);
    
    return 0;
}
