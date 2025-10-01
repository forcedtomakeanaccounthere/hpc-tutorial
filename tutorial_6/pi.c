#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

int main() {
    int i, num_threads = 6;   // choose number of threads here
    double x, pi, sum = 0.0;
    double start_time, end_time;

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(num_threads);   // set number of threads

    start_time = omp_get_wtime();

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);   // now each thread has its own sum
    }

    pi = step * sum;

    end_time = omp_get_wtime();

    printf("Number of threads = %d\n", num_threads);
    printf("Approximated PI   = %.15f\n", pi);
    printf("Time taken        = %f seconds\n", end_time - start_time);

    return 0;
}
