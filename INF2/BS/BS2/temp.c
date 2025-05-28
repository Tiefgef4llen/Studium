#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int n_threads = 10;
uint64_t searching_range = 100000000;

int globalLongestCollatz = 0;
uint64_t globalLongestCollatzN = 0;

struct timespec start, end;
double runtime;

void collatz() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint64_t y = 0;
    #pragma omp parallel for
    for (uint64_t i = 1; i <= searching_range; i++) {
        int count = 0;
        uint64_t z = i;
        while (z > 1) {
            if (z % 2 == 0) {
                z = z / 2;
            } else {
                z = 3 * z + 1;
            }
            count++;
        }
        if (globalLongestCollatz < count) {
            globalLongestCollatz = count;
            globalLongestCollatzN = i;
        }
        y++;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    runtime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Thread-Laufzeit = %2.6f Sekunden\n    Berechnungen dieses Threads: %llu\n", runtime, y);
}

int main() {
    clock_gettime(CLOCK_MONOTONIC, &start);
    collatz();

    clock_gettime(CLOCK_MONOTONIC, &end);
    runtime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Längste Collatz Folge hat eine Länge von %d bei Collatz(%llu) im Bereich von 1 bis %llu\n", globalLongestCollatz, globalLongestCollatzN, searching_range);
    printf("Die Laufzeit betrug %.6f Sekunden auf %d Thread(s)\n\n", runtime, n_threads);
}