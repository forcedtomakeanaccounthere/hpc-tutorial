
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000  // 1 million elements

// QuickSort recursive function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Inline partition logic
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = (i + 1);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int *arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));

    // Fill array with random integers
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    // Measure execution time
    clock_t start, end;
    start = clock();

    quickSort(arr, 0, SIZE - 1);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("QuickSort of %d elements took %.2f seconds.\n", SIZE, time_taken);

    free(arr);
    return 0;
}