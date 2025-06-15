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
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    printf("Shared memory object opened with fd: %d\n", fd);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    void *shm_base = mmap(NULL, sizeof(struct sync) + sizeof(struct payload), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Shared memory mapped at address: %p\n", shm_base);

    struct sync *sync_obj = (struct sync *)shm_base;
    struct payload *payload_obj = (struct payload *)((void *)sync_obj + sizeof(struct sync));
    for (int i = 0; i < 5; i++) {
        sem_wait(&sync_obj->newWork);

        payload_obj->result = 1;
        for (int j = 0; j < payload_obj->exponent; j++) {
            payload_obj->result *= payload_obj->zahl;
        }

        sem_post(&sync_obj->newResult);
    }

    return 0;
}