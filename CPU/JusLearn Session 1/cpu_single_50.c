#include <mach/mach_time.h>
#include <time.h>
#include <stdint.h>

uint64_t get_time_ns() {
    static mach_timebase_info_data_t timebase = {0};
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    return mach_absolute_time() * timebase.numer / timebase.denom;
}

int main() {
    uint64_t busy_time = 100000000ULL;  
    uint64_t sleep_time = 100000000ULL; 
    uint64_t start;
    uint64_t now = get_time_ns();

    while (1) {
        start = get_time_ns();
        uint64_t target_busy_end = start + busy_time;
        uint64_t target_sleep_end = target_busy_end + sleep_time;

        while (now < target_busy_end) {
            now = get_time_ns();
        }

        now = get_time_ns();
        if (now < target_sleep_end) {
            uint64_t sleep_duration_ns = target_sleep_end - now;
            struct timespec ts;
            ts.tv_sec  = sleep_duration_ns / 1000000000ULL;
            ts.tv_nsec = sleep_duration_ns % 1000000000ULL;
            nanosleep(&ts, NULL);
        }
    }
    return 0;
}
