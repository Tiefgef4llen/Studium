#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<long long, int> collatz_cache; // Cache für bereits berechnete Folgenlängen

int collatz_length(long long n) {
    if (n == 1) return 1;
    if (collatz_cache.count(n)) return collatz_cache[n]; // Falls bereits berechnet

    int length = (n % 2 == 0) ? 1 + collatz_length(n / 2) : 1 + collatz_length(3 * n + 1);
    
    collatz_cache[n] = length; // Speichern der berechneten Länge
    return length;
}

int main() {
    int max_length = 0;
    int best_number = 0;

    for (int i = 1; i <= 100000000; i++) {
        int length = collatz_length(i);
        if (length > max_length) {
            max_length = length;
            best_number = i;
        }
    }

    cout << "Zahl mit der längsten Collatz-Folge zwischen 0 und 10000: " << best_number << endl;
    cout << "Länge der Folge: " << max_length << endl;

    return 0;
}