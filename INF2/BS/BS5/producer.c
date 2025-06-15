#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_NAME "/sharedMemory"

struct sync {
    sem_t newWork;
    sem_t newResult;
    void *payloadOffset;
};

struct payload {
    int zahl;
    int exponent;
    int result;
};

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(struct sync) + sizeof(struct payload));

    void *shm_base = mmap(NULL, sizeof(struct sync) + sizeof(struct payload), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    struct sync *sync_obj = (struct sync *)shm_base;
    struct payload *payload_obj = (struct payload *)((void *)sync_obj + sizeof(struct sync));

    sync_obj->payloadOffset = payload_obj;

    sem_init(&sync_obj->newWork, 1, 0);
    sem_init(&sync_obj->newResult, 1, 0);

    for (int i = 0; i < 5; i++) {
        payload_obj->zahl = i + 2;
        payload_obj->exponent = i + 1;
        printf("Sending: %d^%d\n", payload_obj->zahl, payload_obj->exponent);

        sem_post(&sync_obj->newWork);
        sem_wait(&sync_obj->newResult);

        printf("Result received: %d^%d = %d\n", payload_obj->zahl, payload_obj->exponent, payload_obj->result);
    }

    sem_destroy(&sync_obj->newWork);
    sem_destroy(&sync_obj->newResult);
    shm_unlink(SHM_NAME);
    return 0;
}