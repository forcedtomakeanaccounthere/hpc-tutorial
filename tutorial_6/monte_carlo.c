#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double monteCarloPi(long long n) {
    long long insideCircle = 0;
    for (long long i = 0; i < n; i++) {
        double x = (double)rand() / RAND_MAX; // [0,1]
        double y = (double)rand() / RAND_MAX; // [0,1]
        
        // Scale to [-1,1]
        x = 2.0 * x - 1.0;
        y = 2.0 * y - 1.0;
        
        if (x*x + y*y <= 1.0) {
            insideCircle++;
        }
    }
    return 4.0 * (double)insideCircle / (double)n;
}

int main() {
    srand(time(NULL));

    long long sampleSizes[] = {10, 100, 10000, 1000000, 10000000, 100000000};
    int nSizes = sizeof(sampleSizes) / sizeof(sampleSizes[0]);

    printf("SampleSize, PiEstimate, Error\n");
    for (int i = 0; i < nSizes; i++) {
        long long n = sampleSizes[i];
        double piEstimate = monteCarloPi(n);
        double error = fabs(M_PI - piEstimate);
        printf("%lld, %.10f, %.10f\n", n, piEstimate, error);
    }

    return 0;
}