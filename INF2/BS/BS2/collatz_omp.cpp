#include <iostream>
#include <omp.h>


int collatz_length(long long n) {
    int length = 0;
    while(n > 1) {
        if((n % 2) == 0) {
            n = n/2;
        } else {
            n = 3 * n + 1;
        }
        length += 1;
    }
    return length;
}

int main() {
    int max_length = 0;
    int best_number = 0;

    // Anzahl Threads setzen
    omp_set_num_threads(omp_get_max_threads());
    std::cout << "Verwende Threads: " << omp_get_max_threads() << std::endl;

    #pragma omp parallel
    {
        int local_max_length = 0;
        int local_best_number = 0;

        // Paralleles for (nowait auf nummer sicher)
        #pragma omp for nowait
        for (int i = 1; i <= 100000000; i++) {
            int length = collatz_length(i);
            if (length > local_max_length) {
                local_max_length = length;
                local_best_number = i;
            }
        }

        // globales udpaten (alle Threads greifen drauf zu)
        #pragma omp critical
        {
            if (local_max_length > max_length) {
                max_length = local_max_length;
                best_number = local_best_number;
            }
        }
    }

    std::cout << "Zahl mit der längsten Collatz-Folge zwischen 0 und 100000000: " << best_number << std::endl;
    std::cout << "Länge der Folge: " << max_length << std::endl;

    return 0;
}