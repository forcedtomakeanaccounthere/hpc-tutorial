#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8   // Limit maximum parallelism

typedef struct {
    int *arr;
    int left;
    int right;
    int depth;
} ThreadData;

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void *merge_sort(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int l = data->left, r = data->right;

    printf("Thread (depth %d) sorting subarray from %d to %d\n",
           data->depth, l, r);

    if (l < r) {
        int m = l + (r - l) / 2;

        pthread_t tid;
        ThreadData left_data = {data->arr, l, m, data->depth + 1};
        ThreadData right_data = {data->arr, m + 1, r, data->depth + 1};

        int created = 0;
        // Spawn new thread for left half if depth < MAX_THREADS
        if (data->depth < MAX_THREADS) {
            pthread_create(&tid, NULL, merge_sort, &left_data);
            merge_sort(&right_data);
            pthread_join(tid, NULL);
            created = 1;
        } else {
            merge_sort(&left_data);
            merge_sort(&right_data);
        }

        merge(data->arr, l, m, r);

        printf("Thread (depth %d) merged subarray from %d to %d\n",
               data->depth, l, r);
    }
    return NULL;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    ThreadData data = {arr, 0, n - 1, 0};
    merge_sort(&data);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}