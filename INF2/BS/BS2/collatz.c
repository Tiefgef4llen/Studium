#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <inttypes.h>

#define THREADS 16
uint64_t ITERATIONS = 100000000;

typedef uint64_t ull_t;

typedef struct int_b_e {
    ull_t begin;
    ull_t end;
    ull_t maxX;
    ull_t maxIterations;
    ull_t threadIterations;
} structStartEnd;


void *collatz(void *args) {
    // Argument in den richtigen Typ casten
    structStartEnd* startEnd = (structStartEnd*)args;

    // Längste Folge berechnen
    ull_t maxX = 0;
    ull_t maxCnt = 0;
    ull_t threadIterations = 0;

    if(startEnd->begin == 0) startEnd->begin = 1;

    //printf("Thread Begin %ld, End %ld\n", startEnd->begin, startEnd->end);
    for(ull_t i = startEnd->begin; i < startEnd->end; i++) {
        int cnt = 0;
        ull_t x = i;
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
        //printf("Thread: %d | MaxX: %ld | Iterationen dieses Threads: %ld\n", i, threadParams[i].maxX, threadParams[i].threadIterations);
    }

    printf("Längste Folge: %ld  mit Startwert: %ld\n", longest, longestInt);
    return 0;
}