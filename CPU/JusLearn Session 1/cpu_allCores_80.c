#include <time.h>
#include <pthread.h>
#include <unistd.h> 


void* worker(void* arg){
    struct timespec start, now, sleep_time;

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        do {
            clock_gettime(CLOCK_MONOTONIC, &now);
        } while (((now.tv_sec - start.tv_sec) * 1000) + 
                 ((now.tv_nsec - start.tv_nsec) / 1000000) < 80);

        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = 20 * 1000000L;
        nanosleep(&sleep_time, NULL);
    }
}

int main() {
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    pthread_t threads[num_cores];

    for (int i = 0; i < num_cores; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < num_cores; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}