#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sequential_multiply(double **A, double *x, double *y, int n);
double** allocate_matrix(int n);
void free_matrix(double **matrix, int n);
void print_matrix(double **matrix, int n);
void print_vector(double *vector, int n);
void get_user_input_matrix(double **A, double *x, int n);
void print_line(char c, int count);
void read_matrix_from_file(const char *filename, double ***A, double **x, int *n);

int main() {
    int n, choice;
    double **A, *x, *y;
    clock_t start_time, end_time;
    double total_time;
    
    print_line('-', 60);
    printf("SEQUENTIAL MATRIX-VECTOR MULTIPLICATION\n");
    print_line('-', 60);
    
    printf("Choose matrix size:\n");
    printf("1. 6x6 matrix (from file)\n");
    printf("2. Custom size (manual input)\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        read_matrix_from_file("sample_matrix.txt", &A, &x, &n);
        y = (double*)calloc(n, sizeof(double));
        printf("Using sample matrix from file (sample_matrix.txt).\n");
    } else {
        printf("Enter matrix dimension n (for nxn matrix): ");
        scanf("%d", &n);

        A = allocate_matrix(n);
        x = (double*)malloc(n * sizeof(double));
        y = (double*)calloc(n, sizeof(double));

        get_user_input_matrix(A, x, n);
    }
    
    printf("\nMatrix A (%dx%d):\n", n, n);
    print_matrix(A, n);
    printf("\nVector x (%dx1):\n", n);
    print_vector(x, n);
    
    print_line('-', 60);
    printf("PERFORMING SEQUENTIAL MULTIPLICATION\n");
    print_line('-', 60);
    
    start_time = clock();
    sequential_multiply(A, x, y, n);
    end_time = clock();
    
    total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    printf("\nResult vector y (%dx1):\n", n);
    print_vector(y, n);
    
    print_line('-', 60);
    printf("EXECUTION SUMMARY\n");
    print_line('-', 60);
    printf("Matrix size: %dx%d\n", n, n);
    printf("Total operations: %d multiplications, %d additions\n", n*n, n*(n-1));
    printf("Total execution time: %.6f seconds\n", total_time);
    print_line('-', 60);
    
    free_matrix(A, n);
    free(x);
    free(y);
    
    return 0;
}

void sequential_multiply(double **A, double *x, double *y, int n) {
    printf("Processing matrix-vector multiplication sequentially...\n");
    
    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
        printf("Computed y[%d] = %.2f\n", i, y[i]);
    }
    
    printf("Sequential multiplication completed.\n");
}

double** allocate_matrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_vector(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        printf("%8.2f ", vector[i]);
    }
    printf("\n");
}

void get_user_input_matrix(double **A, double *x, int n) {
    printf("\nEnter the %dx%d matrix A (row by row, space-separated):\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("\nEnter the %dx1 vector x (space-separated):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }
}

void print_line(char c, int count) {
    for (int i = 0; i < count; i++) {
        putchar(c);
    }
    putchar('\n');
}

void read_matrix_from_file(const char *filename, double ***A, double **x, int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);

    *A = allocate_matrix(*n);
    *x = (double*)malloc((*n) * sizeof(double));

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%lf", &((*A)[i][j]));
        }
    }

    for (int i = 0; i < *n; i++) {
        fscanf(file, "%lf", &((*x)[i]));
    }

    fclose(file);
}
