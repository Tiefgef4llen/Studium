#include <stdio.h>
#include <pthread.h>

int testePrimzahl(int x) {
    for(int i = 2; i < x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int main() {
    int r = 0;
    for(int i = 2; i < 1000000; i++) {
        r = testePrimzahl(i);
    }
    return 0;
}