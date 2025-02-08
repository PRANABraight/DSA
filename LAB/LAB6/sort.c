#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int mergeComparisons = 0, mergeTransfers = 0;
int quickComparisons = 0, quickTransfers = 0;

// Struct
typedef struct {
    int id;    
    int value; 
} Data;

// Function prototypes
void generateData(Data data[], int n);
void writeToFile(Data data[], int n, const char* filename);
void readFromFile(Data data[], int* n, const char* filename);
void mergeSort(Data data[], int left, int right);
void merge(Data data[], int left, int mid, int right);
void quickSort(Data data[], int low, int high);
int partition(Data data[], int low, int high);
void radixSort(Data data[], int n);
void compareSorts();
void printData(Data data[], int n);
void menu();

// Main function
int main() {
    menu();
    return 0;
}

// Random data generator
void generateData(Data data[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        data[i].id = i + 1;
        data[i].value = rand() % 10; 
    }
}

// Write data to file
void writeToFile(Data data[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%d\n", data[i].id, data[i].value);
    }
    fclose(file);
}

// Read data from file
void readFromFile(Data data[], int* n, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fscanf(file, "%d,%d", &data[i].id, &data[i].value) == 2) {
        i++;
    }
    *n = i;
    fclose(file);
}

// Display data
void printData(Data data[], int n) {
    printf("ID\tAttack\tIntrusion Severity\n");
    for (int i = 0; i < n; i++) {
        printf("%d\tAttack%d\t\t%d\n", data[i].id, i + 1, data[i].value);
    }
}

// Merge Sort
void mergeSort(Data data[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

void merge(Data data[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Data leftArray[n1], rightArray[n2];
    for (int i = 0; i < n1; i++) {
        leftArray[i] = data[left + i];
        mergeTransfers++;
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = data[mid + 1 + j];
        mergeTransfers++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        mergeComparisons++;
        if (leftArray[i].value <= rightArray[j].value) {
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
        mergeTransfers++;
    }

    while (i < n1) {
        data[k] = leftArray[i];
        i++;
        k++;
        mergeTransfers++;
    }
    while (j < n2) {
        data[k] = rightArray[j];
        j++;
        k++;
        mergeTransfers++;
    }
}

// Quick Sort
void quickSort(Data data[], int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

int partition(Data data[], int low, int high) {
    Data pivot = data[high];
    quickTransfers++;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quickComparisons++;
        if (data[j].value < pivot.value) {
            i++;
            Data temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            quickTransfers += 3;
        }
    }

    Data temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    quickTransfers += 3;

    return i + 1;
}

// Radix Sort
void radixSort(Data data[], int n) {
    int max = data[0].value;
    for (int i = 1; i < n; i++) {
        if (data[i].value > max) {
            max = data[i].value;
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int count[10] = {0};
        Data output[n];

        for (int i = 0; i < n; i++) {
            count[(data[i].value / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int index = (data[i].value / exp) % 10;
            output[count[index] - 1] = data[i];
            count[index]--;
        }

        for (int i = 0; i < n; i++) {
            data[i] = output[i];
        }
    }
}

// Compare Sorting Algorithms
void compareSorts() {
    Data data[MAX], temp[MAX];
    int n = MAX;

    generateData(data, n);
    writeToFile(data, n, "unsorted_data.txt");

    readFromFile(temp, &n, "unsorted_data.txt");
    mergeSort(temp, 0, n - 1);
    writeToFile(temp, n, "merge_sorted_data.txt");
    printf("\nData after Merge Sort:\n");
    printData(temp, n);

    readFromFile(temp, &n, "unsorted_data.txt");
    quickSort(temp, 0, n - 1);
    writeToFile(temp, n, "quick_sorted_data.txt");
    printf("\nData after Quick Sort:\n");
    printData(temp, n);

    readFromFile(temp, &n, "unsorted_data.txt");
    radixSort(temp, n);
    writeToFile(temp, n, "radix_sorted_data.txt");
    printf("\nData after Radix Sort:\n");
    printData(temp, n);

    printf("\nComparison of Sorting Algorithms:\n");
    printf("Algorithm\tComparisons\tData Transfers\n");
    printf("Merge Sort\t%d\t\t%d\n", mergeComparisons, mergeTransfers);
    printf("Quick Sort\t%d\t\t%d\n", quickComparisons, quickTransfers);
    printf("Radix Sort\tN/A\t\tN/A\n");
}

// Menu
void menu() {
    int choice;
    Data data[MAX];
    int n;

    while (1) {
        printf("\n--- Sorting Algorithms Menu ---\n");
        printf("1. Generate Random Intrusions Data\n");
        printf("2. Display Intrusions Data\n");
        printf("3. Sort using Merge Sort\n");
        printf("4. Sort using Quick Sort\n");
        printf("5. Sort using Radix Sort\n");
        printf("6. Compare Sorting Algorithms\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateData(data, MAX);
                writeToFile(data, MAX, "unsorted_data.txt");
                printf("Random data generated and saved to 'unsorted_data.txt'.\n");
                break;
            case 2:
                readFromFile(data, &n, "unsorted_data.txt");
                printf("\nUnsorted Data:\n");
                printData(data, n);
                break;
            case 3:
                readFromFile(data, &n, "unsorted_data.txt");
                mergeSort(data, 0, n - 1);
                writeToFile(data, n, "merge_sorted_data.txt");
                printf("\nData sorted using Merge Sort:\n");
                printData(data, n);
                break;
            case 4:
                readFromFile(data, &n, "unsorted_data.txt");
                quickSort(data, 0, n - 1);
                writeToFile(data, n, "quick_sorted_data.txt");
                printf("\nData sorted using Quick Sort:\n");
                printData(data, n);
                break;
            case 5:
                readFromFile(data, &n, "unsorted_data.txt");
                radixSort(data, n);
                writeToFile(data, n, "radix_sorted_data.txt");
                printf("\nData sorted using Radix Sort:\n");
                printData(data, n);
                break;
            case 6:
                compareSorts();
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
