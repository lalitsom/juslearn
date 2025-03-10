#include <time.h>
#include <pthread.h>
#include <unistd.h> 


void* worker(void* arg){
    while(1);
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