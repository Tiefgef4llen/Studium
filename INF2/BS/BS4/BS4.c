#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <time.h>

#define NUM_PRODUCERS 50
#define NUM_CONSUMERS 30
#define ITEMS_PER_PRODUCER 10000

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* head = NULL;

// Semaphoren
sem_t sem_items;      // Anzahl verfügbarer Items
sem_t sem_list;       // Schutz für Zugriff auf Liste
sem_t sem_space;      // Freier Platz in der Liste

// Summenzähler
atomic_int gl_prod = 0;
atomic_int gl_cons = 0;
atomic_int list_length = 0;

// === Listenoperationen ===

// Einfügen am Anfang
void list_prepend(int value) {
    sem_wait(&sem_space);   // Platz reservieren
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;

    sem_wait(&sem_list);
    node->next = head;
    head = node;
    sem_post(&sem_list);
    if(list_length > 5) printf("Liste zu lang : %d\n",list_length);

    atomic_fetch_add(&list_length, 1);
}

// Entfernen vom Ende
int list_remove_tail() {
    sem_wait(&sem_list);
    if (!head) {
        sem_post(&sem_list);
        return -2;
    }

    Node* curr = head;
    Node* prev = NULL;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }

    int value = curr->value;
    if (prev) {
        prev->next = NULL;
    } else {
        head = NULL;
    }

    free(curr);
    sem_post(&sem_list);
    sem_post(&sem_space);  // Platz freigeben
    atomic_fetch_sub(&list_length, 1);
    return value;
}

void collatz(int x) {
    while(x > 1) {
        if((x % 2) == 0) {
            x = x/2;
        } else {
            x = 3 * x + 1;
        }
    }
}

void* producer(void* arg) {
    unsigned int seed = pthread_self();

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int value = rand_r(&seed) % 1000;
        collatz(value);
        list_prepend(value);
        //printf("[Producer %ld] Erzeugt: %d\n", (long)pthread_self(), value);
        atomic_fetch_add(&gl_prod, value);
        sem_post(&sem_items);  // Item verfügbar machen
    }
    return NULL;
}


void* consumer(void* arg) {
    while (1) {
        collatz(9999);
        sem_wait(&sem_items);  // Blockiert bis Item verfügbar

        int value = list_remove_tail();
        if (value == -1) {
            // Sonderwert: Produktion abgeschlossen
            break;
        }

        //printf("[Consumer %ld] Verbraucht: %d\n", (long)pthread_self(), value);
        atomic_fetch_add(&gl_cons, value);
    }
    return NULL;
}


int main() {
    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];

    // Semaphoren initialisieren
    sem_init(&sem_items, 0, 0);
    sem_init(&sem_list, 0, 1);
    sem_init(&sem_space, 0, 5);

    // Threads erzeugen
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, NULL);
    }

    // Auf Producer warten
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }

    // Consumer stoppen
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        list_prepend(-1);       // Sonderwert für Stop
        sem_post(&sem_items);   // Signal an Consumer
    }

    // Auf Consumer warten
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    // Ergebnis
    printf("\n--- Ergebnis ---\n");
    printf("Producer-Summe: %d\n", gl_prod);
    printf("Consumer-Summe: %d\n", gl_cons);
    printf("Listenlänge: %d\n", atomic_load(&list_length));



    // Semaphoren freigeben
    sem_destroy(&sem_items);
    sem_destroy(&sem_list);
    sem_destroy(&sem_space);

    return 0;
}
