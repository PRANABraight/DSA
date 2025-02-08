#include <stdio.h>

int main() {
    int N, M, n, m;

    printf("Give number of rows N for first matrix: ");
    scanf("%d", &N);
    printf("Give number of columns M for first matrix: ");
    scanf("%d", &M);

    printf("Give number of rows n for second matrix: ");
    scanf("%d", &n);
    printf("Give number of columns m for second matrix: ");
    scanf("%d", &m);

    int arr[N][M];
    int arr1[n][m];  
    int arr2[n][m];  

    // Input elements of first matrix
    printf("Input the %d elements of the first matrix:\n", N * M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // Input elements of second matrix 
    if (N == n && M == m) {
        printf("Input the %d elements of the second matrix (for addition/subtraction):\n", N * M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &arr1[i][j]);
            }
        }
    } else {
        printf("Addition and subtraction cannot be performed since the dimensions do not match.\n");
    }

    // Input elements of third matrix 
    if (M == n) {
        printf("Input the %d elements of the third matrix (for multiplication):\n", n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &arr2[i][j]);
            }
        }
    } else {
        printf("Matrix multiplication is not possible because the number of columns in the first matrix is not equal to the number of rows in the second matrix.\n");
    }

    int rowsum[N];   
    int colsum[M];  
    int sum[N][M];         
    int sub[N][M];         
    int mult[N][m]; 

    int choice;

    while (1) {  
        printf("\nChoose option\n");
        printf("1. Row Sum\n");
        printf("2. Column Sum\n");
        printf("3. Matrix Addition\n");
        printf("4. Matrix Subtraction\n");
        printf("5. Matrix Multiplication\n");
        printf("6. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Row sum
                for (int i = 0; i < N; i++) {
                    rowsum[i] = 0;  
                    for (int j = 0; j < M; j++) {
                        rowsum[i] += arr[i][j];
                    }
                    printf("Row %d sum: %d\n", i + 1, rowsum[i]);
                }
                break;

            case 2:
                // Column sum
                for (int j = 0; j < M; j++) {
                    colsum[j] = 0;  
                    for (int i = 0; i < N; i++) { 
                        colsum[j] += arr[i][j];
                    }
                    printf("Column %d sum: %d\n", j + 1, colsum[j]);
                }
                break;

            case 3:
                // Matrix addition
                if (N == n && M == m) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            sum[i][j] = arr[i][j] + arr1[i][j];
                        }
                    }
                    printf("Matrix Sum:\n");
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            printf("%d ", sum[i][j]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("Matrix addition cannot be performed due to incompatible dimensions.\n");
                }
                break;

            case 4:
                // Matrix subtraction
                if (N == n && M == m) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            sub[i][j] = arr[i][j] - arr1[i][j];
                        }
                    }
                    printf("Matrix Subtraction:\n");
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            printf("%d ", sub[i][j]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("Matrix subtraction cannot be performed due to incompatible dimensions.\n");
                }
                break;

            case 5:
                // Matrix multiplication
                if (M == n) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < m; j++) {
                            mult[i][j] = 0; 
                            for (int k = 0; k < M; k++) {
                                mult[i][j] += arr[i][k] * arr2[k][j];
                            }
                        }
                    }
                    printf("Matrix Multiplication:\n");
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < m; j++) {
                            printf("%d ", mult[i][j]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("Matrix multiplication cannot be performed due to incompatible dimensions.\n");
                }
                break;

            case 6:
                // Exit the program
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Enter a valid choice.\n");
        }
    }

    return 0;
}
