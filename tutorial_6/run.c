#include <stdio.h>
#include <omp.h>

#define N 20
#define M 10

// A sample function f(i)
int f(int i) {
    return i % 5;  // some simple computation
}

int main() {
    int v[M];
    int indices[N];

    // initialize arrays
    for (int i = 0; i < M; i++) v[i] = 0;
    for (int i = 0; i < N; i++) indices[i] = i % M;

    printf("=== Version 1: Parallel without critical ===\n");
    #pragma omp parallel for default(none) shared(v, indices)
    for (int i = 0; i < N; i++) {
        v[indices[i]] += f(i);
    }

    for (int i = 0; i < M; i++) {
        printf("v[%d] = %d\n", i, v[i]);
    }

    // Reset v for version 2
    for (int i = 0; i < M; i++) v[i] = 0;

    printf("\n=== Version 2: Parallel with critical ===\n");
    #pragma omp parallel for default(none) shared(v, indices)
    for (int i = 0; i < N; i++) {
        #pragma omp critical
        v[indices[i]] += f(i);
    }

    for (int i = 0; i < M; i++) {
        printf("v[%d] = %d\n", i, v[i]);
    }

    return 0;
}