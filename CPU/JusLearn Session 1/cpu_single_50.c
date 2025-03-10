#include <time.h>

int main() {
    struct timespec start, now, sleep_time;

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        do {
            clock_gettime(CLOCK_MONOTONIC, &now);
        } while (((now.tv_sec - start.tv_sec) * 1000) + 
                 ((now.tv_nsec - start.tv_nsec) / 1000000) < 100);

        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = 100 * 1000000L;
        nanosleep(&sleep_time, NULL);
    }

    return 0;
}
