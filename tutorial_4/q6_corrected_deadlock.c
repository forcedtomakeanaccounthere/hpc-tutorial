#include <stdio.h>
#include <pthread.h>

//with corrected locking order, prevents circular wait/deadlock

pthread_mutex_t lock1, lock2;

void *thread1_func(void *arg) {
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);

    printf("Thread 1 executing\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void *thread2_func(void *arg) {
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);

    printf("Thread 2 executing\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
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