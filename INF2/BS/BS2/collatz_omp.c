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
    
   #pragma omp parallel
    {
        int localMaxIterations = 0;
        uint64_t localBesterStart = 0;

        // Paralleles for
        #pragma omp for
        for (int i = 1; i <= 100000000; i++) {
            int length = collatz(i);
            if (length > localMaxIterations) {
                localMaxIterations = length;
                localBesterStart = i;
            }
        }

        // globales udpaten (alle Threads greifen drauf zu)
        #pragma omp critical
        {
            if (localMaxIterations > maxIterations) {
                maxIterations = localMaxIterations;
                besterStartWert = localBesterStart;
            }
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