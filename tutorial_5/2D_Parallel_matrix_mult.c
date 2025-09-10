#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

void parallel_2d_multiply(double **A, double *x, double *y, int n, int num_threads);
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
    printf("2D PARTITIONING PARALLEL MATRIX-VECTOR MULTIPLICATION\n");
    print_line('-', 70);

    max_threads = omp_get_max_threads();
    printf("Maximum available threads: %d\n", max_threads);

    printf("Enter number of threads to use (1-%d): ", max_threads);
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > max_threads) {
        printf("invalid number of threads. Using maximum available: %d\n", max_threads);
        num_threads = max_threads;
    }

    printf("\nChoose matrix option:\n");
    printf("1. Use sample matrix from file\n");
    printf("2. Enter custom matrix manually\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        read_matrix_from_file("sample_matrix.txt", &A, &x, &n);
        y = (double*)calloc(n, sizeof(double));
        printf("Loaded sample matrix from file (sample_matrix.txt).\n");
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
    printf("PERFORMING 2D PARALLEL MULTIPLICATION\n");
    print_line('-', 70);

    start_time = omp_get_wtime();
    parallel_2d_multiply(A, x, y, n, num_threads);
    end_time = omp_get_wtime();

    total_time = end_time - start_time;

    printf("\nResult vector y (%dx1):\n", n);
    print_vector(y, n);

    print_line('-', 70);
    printf("EXECUTION SUMMARY\n");
    print_line('-', 70);
    printf("Matrix size: %dx%d\n", n, n);
    printf("Number of threads used: %d\n", num_threads);
    printf("Partitioning method: 2D Block\n");
    printf("Total operations: %d multiplications, %d additions\n", n*n, n*(n-1));
    printf("Total execution time: %.6f seconds\n", total_time);
    print_line('-', 70);

    free_matrix(A, n);
    free(x);
    free(y);

    return 0;
}

void parallel_2d_multiply(double **A, double *x, double *y, int n, int num_threads) {
    omp_set_num_threads(num_threads);

    int grid_size = (int)sqrt(num_threads);
    while (num_threads % grid_size != 0 && grid_size > 1) {
        grid_size--;
    }
    int grid_rows = grid_size;
    int grid_cols = num_threads / grid_size;

    printf("Using 2D partitioning with %d threads\n", num_threads);
    printf("Grid arrangement: %dx%d (rows x cols)\n", grid_rows, grid_cols);

    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
    }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        int block_row = thread_id / grid_cols;
        int block_col = thread_id % grid_cols;

        int block_size_row = n / grid_rows;
        int extra_rows = n % grid_rows;
        int block_size_col = n / grid_cols;
        int extra_cols = n % grid_cols;

        int start_row, end_row, start_col, end_col;

        if (block_row < extra_rows) {
            start_row = block_row * (block_size_row + 1);
            end_row = start_row + block_size_row + 1;
        } else {
            start_row = block_row * block_size_row + extra_rows;
            end_row = start_row + block_size_row;
        }

        if (block_col < extra_cols) {
            start_col = block_col * (block_size_col + 1);
            end_col = start_col + block_size_col + 1;
        } else {
            start_col = block_col * block_size_col + extra_cols;
            end_col = start_col + block_size_col;
        }

        for (int i = start_row; i < end_row; i++) {
            double partial_sum = 0.0;
            for (int j = start_col; j < end_col; j++) {
                partial_sum += A[i][j] * x[j];
            }
            #pragma omp atomic
            y[i] += partial_sum;
        }
    }
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