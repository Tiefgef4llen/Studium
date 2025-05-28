#include <iostream>
#include <future>
#include <vector>

long long iterations = 100000000;

int collatz_length(long long n) {
    int length = 0;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        length++;
    }
    return length;
}

std::pair<int, int> laengsteFolge(int start, int end) {
    int max_length = 0;
    int best_number = 0;

    for (int i = start; i < end; i++) {
        int length = collatz_length(i);
        if (length > max_length) {
            max_length = length;
            best_number = i;
        }
    }
    return {best_number, max_length};
}

int main() {
    int threadCnt = 10000;
    std::vector<std::future<std::pair<int, int>>> futures;

    for(int i = 0; i < threadCnt; i++) {
        int start = i * (iterations / threadCnt) + 1;
        int end = (i + 1) * (iterations / threadCnt);

        futures.emplace_back(std::async(std::launch::async, laengsteFolge , start, end));
    }

    int max_length = 0;
    int best_number = 0;

    for (auto& f : futures) {
        auto [local_best, local_max] = f.get(); // Ergebnis abrufen
        if (local_max > max_length) {
            max_length = local_max;
            best_number = local_best;
        }
    }

    std::cout << "Bester Startwert: " << best_number << std::endl;
    std::cout << "Länge der Folge: " << max_length << std::endl;

    return 0;

}

