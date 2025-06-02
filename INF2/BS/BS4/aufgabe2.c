#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdbool.h>


#define CONSUMER 5
#define PRODUCER 5

#define MAXVAL 50

//Semaphore -----
sem_t sUsed;        // Anzahl belegter Plätze
sem_t sFree;        // Anzahl freier Plätze
// Mutex 
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

atomic_int gl_prod = 0;
atomic_int gl_cons = 0;

atomic_bool productionDone = false;


//---

int listLength = 0;

typedef struct node {
    struct node* next;
    int data;
} node_t;

node_t* list;


node_t* addFront(node_t* anchor, int data) {
    node_t* newNode = malloc(sizeof(node_t));
    newNode->data = data;

    newNode->next = anchor;

    return newNode;
}

int removeEnd(node_t* anchor) {
    node_t* pNode = anchor;
    while(pNode->next->next != NULL) {
        pNode = pNode->next;
    }
    int ret = pNode->next->data;
    free(pNode->next);
    pNode->next = NULL;
    return ret;
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

void* producerFun(void* args) {
    for(int i = 0; i < MAXVAL; i++) {
        if(listLength > 5) printf("Liste zu groß, Länge: %d\n", listLength);

        // Wartezeit erzeugen mit Collatz Funktion
        int number = rand();
        collatz(number);

        int data = rand() % 100;
        
        sem_wait(&sFree);           // Nur weitermachen, wenn Platz frei ist (sFree != 0)
        pthread_mutex_lock(&mtx);   // Mutex locken

        list = addFront(list, data);
        printf("{Erzeuger: %ld} Erzeugt: %d\n", pthread_self(), data);
        atomic_fetch_add(&gl_prod, 1);
        listLength++;

        pthread_mutex_unlock(&mtx);
        sem_post(&sUsed);           // Used Anzahl um 1 erhöhen

        if (atomic_fetch_add(&gl_prod, 1) == (PRODUCER * MAXVAL) - 1) {
            atomic_store(&productionDone, true);
        }
    }
}

void* consumerFun(void* args) {
    while (true) {
        int number = rand();
        collatz(number);

        sem_wait(&sUsed);
        pthread_mutex_lock(&mtx);

        // Beenden, wenn Liste leer und Produktion abgeschlossen
        if (list->next == NULL && atomic_load(&productionDone)) {
            pthread_mutex_unlock(&mtx);
            sem_post(&sUsed);  // Andere wartende Threads entblocken
            break;  // Thread beendet sich
        }

        int removed = removeEnd(list);
        atomic_fetch_add(&gl_cons, 1);
        listLength--;
        printf("{Verbraucher: %ld} Verbraucht: %d\n", pthread_self(), removed);

        pthread_mutex_unlock(&mtx);
        sem_post(&sFree);
    }
}

int main () {
    srand(pthread_self());

    sem_init(&sUsed, 0, 0);
    sem_init(&sFree, 0, 100);

    list = malloc(sizeof(node_t));
    list->next = NULL;


    pthread_t producer[PRODUCER];
    pthread_t consumer[CONSUMER];

    // Threads erzeugen
    for(int i = 0; i < PRODUCER; i++) {
        pthread_create(&producer[i], NULL, &producerFun, NULL);
    }

    for(int i = 0; i < CONSUMER; i++) {
        pthread_create(&consumer[i], NULL, &consumerFun, NULL);
    }


    // Thread joinen
    for(int i = 0; i < PRODUCER; i++) {
        pthread_join(producer[i], NULL);
    }

    for(int i = 0; i < CONSUMER; i++) {
        pthread_join(consumer[i], NULL);
    }

    printf("Länge: %d\n", listLength);
    printf("Objekte erzeugt:   \t %d\n", gl_prod);
    printf("Objekte konsumiert: \t %d\n", gl_cons);


    return 0;
}