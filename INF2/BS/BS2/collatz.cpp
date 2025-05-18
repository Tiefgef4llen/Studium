#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx; // Mutex for thread-safe access to global variables
int max_length = 0;
int best_number = 0;


void collatz(long long start, long long end) {
    int maxRet = 0;
    int besterStart = 0;
    if(start == 0) start = 1;
    for(long long i = start; i < end; i++) {
        int cnt = 0;
        while(i > 1) {
            if((i % 2) == 0) {
                i = i/2;
            } else {
                i = 3 * i + 1;
            }
            cnt += 1;
        }
        if(cnt > maxRet) {
            maxRet = cnt;
            besterStart = i;
        }
    }
    // Synchronize global variables using mutex
    std::lock_guard<std::mutex> guard(mtx);
    if (maxRet > max_length) {
        max_length = maxRet;
        best_number = besterStart;
    }

}

int main() {
    long long iterations = 100000000;

    std::vector<std::pair<int, int>> ergebnise;

    int num_threads = std::thread::hardware_concurrency(); // Get available threads
    std::vector<std::thread> threads;
    int range_per_thread = 10000 / num_threads;

    for (int i = 0; i < num_threads; i++) {
        int start = i * range_per_thread + 1;
        int end = (i == num_threads - 1) ? 10000 : (i + 1) * range_per_thread;
        threads.emplace_back(collatz, start, end);
    }

    for (auto& t : threads) {
        t.join(); // Wait for all threads to complete
    }

    /*
    // THREADS
    int threadCnt = 12;
    std::thread threads[threadCnt];
    for(int i = 0; i < threadCnt; i++) {
        threads[i] = std::thread(collatz, i * (iterations/threadCnt), (i + 1)*(iterations/threadCnt), &ergebnise);
        //std::cout << "Started thread with: " << i * (iterations/threadCnt) << " | " << (i + 1)*(iterations/threadCnt) << std::endl;
    }
    
    for(int i = 0; i < threadCnt; i++) {
        threads[i].join();
    }

    int maxIterations = 0;
    int besterStart = 0;

    for(const auto& e : ergebnise) {
        if(e.first > maxIterations) {
            maxIterations = e.first;
            besterStart = e.second;
        }
    }
    */
    std::cout << " Meiste Iterations: " << max_length << " Mit Startwert: " << best_number << std::endl;
}