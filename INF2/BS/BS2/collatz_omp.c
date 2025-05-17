#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <inttypes.h>
#include <omp.h>

uint64_t ITERATIONS = 100000000;


uint64_t collatz(uint64_t number) {
    uint64_t iterationCount = 0;
    while(number > 1) {
            if((number % 2) == 0) {
                number = number/2;
            } else {
                number = 3 * number + 1;
            }
            iterationCount += 1;
        }
    return iterationCount;
}

int main() {

    uint64_t nextNumber = 1;
    uint64_t maxIterations = 0;
    uint64_t besterStartWert = 0;
    
    #pragma omp parallel for
    for (uint64_t i = 1; i <= ITERATIONS; i++) {
        //printf("%d\n", omp_get_num_threads()); // Ausgabe ist 12
        uint64_t iter_tmp = collatz(i);
        #pragma omp critical
        {
            if (iter_tmp > maxIterations) {
                maxIterations = iter_tmp;
                besterStartWert = i;
            }
            //printf("Thread %d: Zahl: %ld, Länge: %ld\n", omp_get_thread_num(), i, iter_tmp);       
        }
    }

    /*
    #pragma omp for private(local) private(maxIterations) private(besterStartWert)
    for(int i = 1; i < ITERATIONS; i++) {
        #pragma omp critical
        local = nextNumber++;
        uint64_t iter_tmp = collatz(nextNumber);
        if(iter_tmp > maxIterations) {
            maxIterations = iter_tmp;
            besterStartWert = nextNumber;
            
        }
        //nextNumber++;
    }
        */

    printf("Längste Folge: %ld  mit Startwert: %ld\n", maxIterations, besterStartWert);
    return 0;
}