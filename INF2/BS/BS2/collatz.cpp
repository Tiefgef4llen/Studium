#include <iostream>
#include <thread>

int collatz(long long start, long long end) {
    int maxRet = 0;
    int besterStart = 0;
    if(start == 0) start = 1;
        //printf("Thread Begin %ld, End %ld\n", startEnd->begin, startEnd->end);
    for(long long i = start; i < end; i++) {
        int cnt = 0;
        long long x = i;
        while(x > 1) {
            if((x % 2) == 0) {
                x = x/2;
            } else {
                x = 3 * x + 1;
            }
            cnt += 1;
        }
    }

  
    return maxRet;
}

int main() {
    long long iterations = 100000000;

    // THREADS
    int threadCnt = 12;
    std::thread threads[threadCnt];
    for(int i = 0; i < threadCnt; i++) {
        threads[i] = std::thread(collatz, i * (iterations/threadCnt), (i + 1)*(iterations/threadCnt));
        std::cout << "Started thread with: " << i * (iterations/threadCnt) << " | " << (i + 1)*(iterations/threadCnt) << std::endl;
    }
    
    for(int i = 0; i < threadCnt; i++) {
        threads[i].join();
    }
}