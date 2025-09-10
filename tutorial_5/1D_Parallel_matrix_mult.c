#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void parallel_1d_multiply(double **A, double *x, double *y, int n, int num_threads);
double** allocate_matrix(int n);
void free_matrix(double **matrix, int n);
void print_matrix(double **matrix, int n);
void print_vector(double *vector, int n);
void get_user_input_matrix(double **A, double *x, int n);
void read_matrix_from_file(const char *filename, double ***A, double **x, int *n);

void print_line(char c, int count) {
    for (int i = 0; i < count; i++) {
        putchar(c);
    }
    putchar('\n');
}

int main() {
    int n, choice, num_threads, max_threads;
    double **A, *x, *y;
    double start_time, end_time, total_time;
    
    print_line('-', 70);
    printf("1D PARTITIONING (ROW-WISE) PARALLEL MATRIX-VECTOR MULTIPLICATION\n");
    print_line('-', 70);
    
    max_threads = omp_get_max_threads();
    printf("Maximum available threads: %d\n", max_threads);
    
    printf("Enter number of threads to use (1-%d): ", max_threads);
    scanf("%d", &num_threads);
    
    if (num_threads < 1 || num_threads > max_threads) {
        printf("Invalid number of threads. Using %d threads\n", max_threads);
        num_threads = max_threads;
    }
    
    printf("\nChoose matrix option:\n");
    printf("1. Use sample matrix from file\n");
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
    
    print_line('-', 70);
    printf("PERFORMING 1D PARALLEL MULTIPLICATION\n");
    print_line('-', 70);
    
    start_time = omp_get_wtime();
    parallel_1d_multiply(A, x, y, n, num_threads);
    end_time = omp_get_wtime();
    
    total_time = end_time - start_time;
    
    printf("\nResult vector y (%dx1):\n", n);
    print_vector(y, n);
    
    print_line('-', 70);
    printf("results :\n");
    print_line('-', 70);
    printf("Matrix size: %dx%d\n", n, n);
    printf("Number of threads used: %d\n", num_threads);
    printf("Partitioning method: 1D Row-wise\n");
    printf("Total operations: %d multiplications, %d additions\n", n*n, n*(n-1));
    printf("Total execution time: %.6f seconds\n", total_time);
    print_line('-', 70);
    
    free_matrix(A, n);
    free(x);
    free(y);
    
    return 0;
}

void parallel_1d_multiply(double **A, double *x, double *y, int n, int num_threads) {
    omp_set_num_threads(num_threads);

    printf("Using 1D partitioning with %d threads (OpenMP parallel for)\n", num_threads);
    printf("Each thread processes consecutive rows of the matrix automatically\n\n");

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }

    printf("\n1D parallel multiplication completed.\n");
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
