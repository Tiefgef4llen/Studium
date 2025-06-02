#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <unistd.h>
#include <time.h>

#define NUM_PRODUCERS 50
#define NUM_CONSUMERS 30
#define NUM_ITEMS_PER_PRODUCER 10000

// Knoten der verketteten Liste
typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

sem_t sem_items;      // Zählt, wie viele Items verfügbar sind
sem_t sem_slots;      // Zählt freie Slots (optional, hier unendlich)
sem_t sem_list;       // Mutex für Zugriff auf die Liste

atomic_int gl_prod = 0;   // Zähler für Producer-Summe
atomic_int gl_cons = 0;   // Zähler für Consumer-Summe

// Hilfsfunktionen
void list_append(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    sem_wait(&sem_list);
    if (tail) {
        tail->next = node;
        tail = node;
    } else {
        head = tail = node;
    }
    sem_post(&sem_list);
}

int list_remove() {
    sem_wait(&sem_list);
    if (!head) {
        sem_post(&sem_list);
        return -1;  // Sollte nicht passieren!
    }
    Node* node = head;
    int value = node->value;
    head = node->next;
    if (!head) tail = NULL;
    free(node);
    sem_post(&sem_list);
    return value;
}

// Producer-Thread
void* producer(void* arg) {
    unsigned int seed = pthread_self();
    for (int i = 0; i < NUM_ITEMS_PER_PRODUCER; i++) {
        int value = rand_r(&seed) % 1000;  // Zufallszahl
        list_append(value);
        atomic_fetch_add(&gl_prod, value);
        sem_post(&sem_items);  // Ein Item verfügbar machen
    }
    return NULL;
}

// Consumer-Thread
void* consumer(void* arg) {
    while (1) {
        if (sem_trywait(&sem_items) != 0) {
            // Wenn alle Producer fertig sind, kann Consumer beenden
            if (atomic_load(&gl_prod) == atomic_load(&gl_cons)) break;
            usleep(100); // Minimal warten, um nicht zu viel CPU zu ziehen
            continue;
        }
        int value = list_remove();
        atomic_fetch_add(&gl_cons, value);
    }
    return NULL;
}

// Hauptprogramm
int main() {
    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];

    sem_init(&sem_items, 0, 0);
    sem_init(&sem_list, 0, 1);

    // Producer starten
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, NULL);
    }
    // Consumer starten
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, NULL);
    }

    // Auf Producer warten
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }

    // Auf Consumer warten
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    // Ergebnis ausgeben
    printf("Producer-Summe: %d\n", gl_prod);
    printf("Consumer-Summe: %d\n", gl_cons);
    if (gl_prod == gl_cons) {
        printf("✅ Summen stimmen überein!\n");
    } else {
        printf("❌ Summen stimmen NICHT überein!\n");
    }

    sem_destroy(&sem_items);
    sem_destroy(&sem_list);
    return 0;
}
