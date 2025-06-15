#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <time.h>
#include <unistd.h>

#define NUM_PRODUCERS 50
#define NUM_CONSUMERS 30
#define ITEMS_PER_PRODUCER 10000
#define MAX_LIST_SIZE 5

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

int get_list_length() {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Einfügen am Anfang
void list_prepend(int value) {
    sem_wait(&sem_space);  // Platz reservieren

    Node* node = malloc(sizeof(Node));
    node->value = value;

    sem_wait(&sem_list);
    node->next = head;
    head = node;

    // Listenlänge prüfen
    int length = get_list_length();
    if (length > MAX_LIST_SIZE) {
        printf("Listenlänge überschreitet %d: %d\n", MAX_LIST_SIZE, length);
    }

    sem_post(&sem_list);

    sem_post(&sem_items);  // Item verfügbar machen
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
    return value;
}

void collatz(int x) {
    while (x > 1) {
        x = (x % 2 == 0) ? x / 2 : 3 * x + 1;
    }
}

// Producer-Thread
void* producer(void* arg) {
    unsigned int seed = pthread_self();

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int value = rand_r(&seed) % 1000;
        collatz(value);
        list_prepend(value);
        atomic_fetch_add(&gl_prod, value);
    }
    return NULL;
}

// Consumer-Thread
void* consumer(void* arg) {
    while (1) {
        collatz(9999);
        sem_wait(&sem_items);  // Blockiert bis Item verfügbar

        int value = list_remove_tail();
        if (value == -1) {
            break;  // Stop-Signal
        }

        if (value >= 0) {
            atomic_fetch_add(&gl_cons, value);
        }
    }
    return NULL;
}

int main() {
    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];

    // Semaphoren initialisieren
    sem_init(&sem_items, 0, 0);
    sem_init(&sem_list, 0, 1);
    sem_init(&sem_space, 0, MAX_LIST_SIZE);

    // Threads starten
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

    // Stop-Signale senden
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        list_prepend(-1);
    }

    // Auf Consumer warten
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    // Ausgabe
    printf("\n--- Ergebnis ---\n");
    printf("Producer-Summe: %d\n", gl_prod);
    printf("Consumer-Summe: %d\n", gl_cons);

    // Cleanup
    sem_destroy(&sem_items);
    sem_destroy(&sem_list);
    sem_destroy(&sem_space);

    return 0;
}
