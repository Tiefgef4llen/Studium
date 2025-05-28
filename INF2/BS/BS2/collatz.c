#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <inttypes.h>
#include <time.h>

#define THREADS 12
uint64_t ITERATIONS = 100000000;

typedef struct int_b_e {
    uint64_t begin;
    uint64_t end;
    uint64_t maxX;
    uint64_t maxIterations;
    uint64_t threadIterations;
    struct timespec startTime;
    struct timespec endTime;
} structStartEnd;


void *collatz(void *args) {
    // Argument in den richtigen Typ casten
    structStartEnd* startEnd = (structStartEnd*)args;
    clock_gettime(CLOCK_REALTIME, &startEnd->startTime);

    // Längste Folge berechnen
    uint64_t maxX = 0;
    uint64_t maxCnt = 0;
    uint64_t threadIterations = 0;

    if(startEnd->begin == 0) startEnd->begin = 1;

    //printf("Thread Begin %ld, End %ld\n", startEnd->begin, startEnd->end);
    for (uint64_t i = startEnd->begin; i < startEnd->end; i++) {
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

    startEnd->maxX = maxX;
    startEnd->threadIterations = threadIterations;
    startEnd->maxIterations = maxCnt;

    clock_gettime(CLOCK_REALTIME, &startEnd->endTime);
    return NULL;
}

int main() {

    pthread_t threads[THREADS];
    structStartEnd threadParams[THREADS];


    int begin = 0;
    for(int i = 0; i < THREADS; i++) {
        threadParams[i].begin = (ITERATIONS / THREADS) * i; 
        threadParams[i].end = (ITERATIONS / THREADS) * (i + 1);
        pthread_create(&threads[i], NULL, &collatz, &threadParams[i]);
    }

    uint64_t longest = 0;
    uint64_t longestInt = 0;
    for(int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
        if(threadParams[i].maxIterations > longest) {
            longest = threadParams[i].maxIterations;
            longestInt = threadParams[i].maxX;
        }
        int outs = threadParams[i].endTime.tv_sec - threadParams[i].startTime.tv_sec;
        int outn = threadParams[i].endTime.tv_nsec - threadParams[i].startTime.tv_nsec;
        if(outn < 0) {
            outn += 1000000000;
            outs--;
        }

        printf("Thread: %d | MaxIterations: %ld | Iterationen dieses Threads: %ld | Dauer des Threads: %d.%09d \n", i, threadParams[i].maxX, threadParams[i].threadIterations, outs, outn);
    }

    printf("Längste Folge: %ld  mit Startwert: %ld\n", longest, longestInt);
    return 0;
}