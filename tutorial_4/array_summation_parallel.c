#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 16
#define N 100000000  

long long *arr;
long long sum[MAX_THREADS]; // partial sums

typedef struct {
    int start;
    int end;
    int thread_id;
} ThreadData;

void* sum_array(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    long long local_sum = 0;
    
    for (int i = data->start; i < data->end; i++) {
        local_sum += arr[i];
    }
    
    sum[data->thread_id] = local_sum;
    pthread_exit(NULL);
}

double Time_T(int threads) {
    pthread_t thread[threads];
    ThreadData thread_data[threads];

    // reset partial sums
    for (int i = 0; i < threads; i++) sum[i] = 0;

    clock_t start_time = clock();

    int chunk_size = N / threads;
    for (int i = 0; i < threads; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == threads - 1) ? N : (i + 1) * chunk_size;
        thread_data[i].thread_id = i;
        pthread_create(&thread[i], NULL, sum_array, (void*)&thread_data[i]);
    }

    // Join threads and compute final sum
    long long final_sum = 0;
    for (int i = 0; i < threads; i++) {
        pthread_join(thread[i], NULL);
        final_sum += sum[i];
    }

    clock_t end_time = clock();
    double elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Optional: verify correctness
    // printf("Final sum = %lld\n", final_sum);

    return elapsed;
}

int main() {
    // Allocate memory for array once
    arr = (long long*)malloc(N * sizeof(long long));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize array
    for (int i = 0; i < N; i++) {
        arr[i] = 1;
    }

    // Test with 1 to MAX_THREADS
    for (int t = 1; t <= MAX_THREADS; t++) {
        double time = Time_T(t);
        printf("Threads = %d, Time = %lf sec\n", t, time);
    }

    free(arr);
    return 0;
}