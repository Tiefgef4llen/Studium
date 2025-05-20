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
        int local_max_length = 0;
        uint64_t local_best_number = 0;

        // Paralleles for (nowait auf nummer sicher)
        #pragma omp for nowait
        for (int i = 1; i <= 100000000; i++) {
            int length = collatz(i);
            if (length > local_max_length) {
                local_max_length = length;
                local_best_number = i;
            }
        }

        // globales udpaten (alle Threads greifen drauf zu)
        #pragma omp critical
        {
            if (local_max_length > maxIterations) {
                maxIterations = local_max_length;
                besterStartWert = local_best_number;
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