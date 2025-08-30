#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 512   // image size (N x N)

// Example Sobel operators
int Gx[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

int Gy[3][3] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};

int main() {
    int i, j, x, y;
    int **image, **output;

    // Allocate memory
    image = (int **)malloc(N * sizeof(int *));
    output = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        image[i] = (int *)malloc(N * sizeof(int));
        output[i] = (int *)malloc(N * sizeof(int));
    }

    // Fill image with dummy values
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            image[i][j] = rand() % 256;

    // ---------------- Sequential convolution ----------------
    clock_t start = clock();

    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            int sumX = 0, sumY = 0;
            for (x = -1; x <= 1; x++) {
                for (y = -1; y <= 1; y++) {
                    sumX += image[i + x][j + y] * Gx[x + 1][y + 1];
                    sumY += image[i + x][j + y] * Gy[x + 1][y + 1];
                }
            }
            output[i][j] = (int)(sqrt(sumX * sumX + sumY * sumY));
        }
    }

    clock_t end = clock();
    double T_seq = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential Time: %f seconds\n", T_seq);

    // Free memory
    for (i = 0; i < N; i++) {
        free(image[i]);
        free(output[i]);
    }
    free(image);
    free(output);

    return 0;
}