#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <inttypes.h>
#include <time.h>
#include <stdatomic.h>

#define THREADS 12
uint64_t ITERATIONS = 100000000;

typedef struct int_b_e {

    struct timespec startTime;
    struct timespec endTime;
} structStartEnd;

long long startWert = 1;
int blockSize = 1;

uint64_t global_besterStart = 0;
int global_maxIterations = 0;
uint64_t global_summe = 0;

pthread_mutex_t globale_mutex = PTHREAD_MUTEX_INITIALIZER;


void *collatz(void *args) {
    // Längste Folge berechnen
    uint64_t maxX = 0;
    uint64_t maxCnt = 0;
    uint64_t threadIterations = 0;

    while(1) {
        long long begin = atomic_fetch_add(&startWert, blockSize);
        if(begin > ITERATIONS) break;

        //long long begin = atomic_load(&startWert);
        long long end = begin + blockSize;
        //atomic_fetch_add(&startWert, blockSize);
        

        //printf("Thread Begin %lld, End %lld\n", begin, end);
        for (uint64_t i = begin; i < begin + blockSize; i++) {
            int cnt = 0;
            uint64_t x = i;
            while(x > 1) {
                if((x % 2) == 0) {
                    x = x/2;
                } else {
                    x = 3 * x + 1;
                }
                cnt += 1;
                threadIterations++;
            }
            if(cnt > maxCnt) {
                maxCnt = cnt;
                maxX = i;
            }
        }
    }

    // Mutex
    pthread_mutex_lock(&globale_mutex);
    global_summe += threadIterations;
    if(maxCnt > global_maxIterations) {
        global_besterStart = maxX;
        global_maxIterations = maxCnt;
    }
    pthread_mutex_unlock(&globale_mutex);
    return NULL;
}

int main() {

    pthread_t threads[THREADS];

    int begin = 0;
    for(int i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, &collatz, NULL);
    }

    for(int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
        //printf("Thread: %d | MaxIterations: %ld | Iterationen dieses Threads: %ld | Dauer des Threads: %d.%09d \n", i, threadParams[i].maxX, threadParams[i].threadIterations, outs, outn);
    }

    printf("Längste Folge: %d  mit Startwert: %ld\n", global_maxIterations, global_besterStart);
    printf("Summe: %ld", global_summe);
    return 0;
}