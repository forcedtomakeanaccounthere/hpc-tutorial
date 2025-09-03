#include <stdio.h>
#include <pthread.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep(1000 * (x))   // Sleep takes milliseconds
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)           // POSIX sleep
#endif

pthread_mutex_t lock1, lock2;

void *thread1_func(void *arg) {
    pthread_mutex_lock(&lock1);
    SLEEP(1);   // force overlap
    pthread_mutex_lock(&lock2);

    printf("Thread 1 executing\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void *thread2_func(void *arg) {
    pthread_mutex_lock(&lock2);
    SLEEP(1);   // force overlap
    pthread_mutex_lock(&lock1);

    printf("Thread 2 executing\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}