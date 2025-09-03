#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 16
#define NUM_THREADS 4

int arr[N], prefix_sum[N];
int partial_sums[NUM_THREADS];

typedef struct {
    int tid;
    int start;
    int end;
} ThreadData;

void* compute_local_prefix(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int tid = data->tid;
    int start = data->start;
    int end = data->end;

    prefix_sum[start] = arr[start];
    for (int i = start + 1; i < end; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }

    // Save local total sum of this chunk
    partial_sums[tid] = prefix_sum[end - 1];

    printf("Thread %d computed local prefix sum for indices [%d..%d]\n", 
            tid, start, end - 1);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int chunk = N / NUM_THREADS;

    // Example input
    for (int i = 0; i < N; i++) arr[i] = i + 1;

    // ---------------- PHASE 1 ----------------
    printf("=== Phase 1: Local prefix sums ===\n");
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].tid = t;
        thread_data[t].start = t * chunk;
        thread_data[t].end = (t == NUM_THREADS - 1) ? N : (t + 1) * chunk;
        pthread_create(&threads[t], NULL, compute_local_prefix, &thread_data[t]);
    }
    for (int t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    printf("Computation done at parallel level 1 (local prefix sums)\n\n");

    // ---------------- PHASE 2 ----------------
    printf("=== Phase 2: Offset adjustment ===\n");
    for (int t = 1; t < NUM_THREADS; t++) {
        int offset = partial_sums[t - 1];
        partial_sums[t] += partial_sums[t - 1];

        for (int i = t * chunk; i < ((t == NUM_THREADS - 1) ? N : (t + 1) * chunk); i++) {
            prefix_sum[i] += offset;
        }

        printf("Chunk %d adjusted with offset %d\n", t, offset);
    }

    printf("Computation done at parallel level 2 (offset adjustment)\n\n");

    // ---------------- RESULT ----------------
    printf("Final Array:      ");
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    printf("\nFinal Prefix Sum: ");
    for (int i = 0; i < N; i++) printf("%d ", prefix_sum[i]);
    printf("\n");

    return 0;
}