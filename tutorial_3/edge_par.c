#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define N 512

int main() {
    // Allocate arrays on heap
    int (*image)[N] = malloc(sizeof(int[N][N]));
    int (*output)[N] = malloc(sizeof(int[N][N]));

    if (!image || !output) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize image
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            image[i][j] = (i + j) % 256;
        }
    }

    double start_time = omp_get_wtime();

    // Parallel computation (Sobel-like filter)
    #pragma omp parallel for collapse(2)
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            int gx = -image[i-1][j-1] - 2*image[i][j-1] - image[i+1][j-1]
                     + image[i-1][j+1] + 2*image[i][j+1] + image[i+1][j+1];

            int gy = -image[i-1][j-1] - 2*image[i-1][j] - image[i-1][j+1]
                     + image[i+1][j-1] + 2*image[i+1][j] + image[i+1][j+1];

            output[i][j] = abs(gx) + abs(gy);
        }
    }

    double end_time = omp_get_wtime();

    printf("Parallel execution time: %f seconds\n", end_time - start_time);

    free(image);
    free(output);

    return 0;
}
