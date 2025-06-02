#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <time.h>

#define CONSUMER 2
#define PRODUCER 2

// Synchronization primitives
sem_t sUsed;  // Number of occupied slots
sem_t sFree;  // Number of free slots
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// Atomic counters
atomic_int gl_prod = 0;    // Total number of produced elements
atomic_int gl_cons = 0;    // Total number of consumed elements
atomic_int listLength = 0; // Number of items currently in the list

typedef struct node {
    struct node* next;
    int data;
} node_t;

node_t* list = NULL;

node_t* addFront(node_t* anchor, int data) {
    node_t* newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = anchor;
    return newNode;
}

int removeEnd(node_t* anchor) {
    if (anchor == NULL) return -1;
    node_t* pNode = anchor;
    
    // In this simple implementation, we assume the list has at least one node.
    // Traverse until the second-to-last node.
    while (pNode->next->next != NULL) {
        pNode = pNode->next;
    }
    int ret = pNode->next->data;
    free(pNode->next);
    pNode->next = NULL;
    return ret;
}

void* producerFun(void* args) {
    for (int i = 0; i < 5; i++) {
        int data = rand() % 100;
        
        sem_wait(&sFree);         // Wait for a free slot
        pthread_mutex_lock(&mtx); // Enter critical section
        
        list = addFront(list, data);
        printf("{Producer %ld} Produced: %d\n", pthread_self(), data);
        atomic_fetch_add(&gl_prod, 1);
        atomic_fetch_add(&listLength, 1);
        
        pthread_mutex_unlock(&mtx); 
        sem_post(&sUsed);         // Signal that an item is available
    }
    return NULL;
}

void* consumerFun(void* args) {
    while (1) {
        // Set up a 1-second timeout waiting on sUsed.
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1; // wait up to one second
        
        if (sem_timedwait(&sUsed, &ts) != 0) {
            // A timeout occurred—check if we are done.
            pthread_mutex_lock(&mtx);
            // Terminate only if all producers are done and the list is empty.
            if (atomic_load(&gl_prod) == (5 * PRODUCER) && listLength == 0) {
                pthread_mutex_unlock(&mtx);
                break;
            }
            pthread_mutex_unlock(&mtx);
            continue;
        }
        
        pthread_mutex_lock(&mtx);
        // As a safeguard, check if there is an item.
        if (listLength > 0) {
            int removed = removeEnd(list);
            atomic_fetch_sub(&listLength, 1);
            atomic_fetch_add(&gl_cons, 1);
            printf("{Consumer %ld} Consumed: %d\n", pthread_self(), removed);
        }
        pthread_mutex_unlock(&mtx);
        sem_post(&sFree);  // Indicate a free slot is available
    }
    return NULL;
}

int main() {
    srand((unsigned) time(NULL));
    
    sem_init(&sUsed, 0, 0);
    sem_init(&sFree, 0, 1);
    
    pthread_t producer[PRODUCER];
    pthread_t consumer[CONSUMER];
    
    // Create producer threads
    for (int i = 0; i < PRODUCER; i++) {
        pthread_create(&producer[i], NULL, producerFun, NULL);
    }
    // Create consumer threads
    for (int i = 0; i < CONSUMER; i++) {
        pthread_create(&consumer[i], NULL, consumerFun, NULL);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < PRODUCER; i++) {
        pthread_join(producer[i], NULL);
    }
    for (int i = 0; i < CONSUMER; i++) {
        pthread_join(consumer[i], NULL);
    }
    
    printf("Final List Length: %d\n", listLength);
    printf("Total Produced:   %d\n", gl_prod);
    printf("Total Consumed:   %d\n", gl_cons);
    
    return 0;
}