#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


#define PLAYER_COUNT 2

typedef struct {
    int id;
    int score;
    int round_points;
} player_t;

// Globale Variablen
player_t players[PLAYER_COUNT];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_player_done[PLAYER_COUNT];
sem_t sem_bank_continue;

sem_t player_turn, player_fertig;

int runde = 0;
bool RundeFertig = false;
bool SpielFetig = false;

int karteZiehen() {
    return rand() % 11 + 1;
}


void* bank_worker(void* arg) {
    printf("Bank is running.\n");

    while(!SpielFetig) {
        printf("Bank: Runde %d\n", runde);

        // Semaphore für die Anzahl an Spielern freigeben
        // => Spieler fangen an
        for(int i = 0; i < PLAYER_COUNT; i++) {
            sem_post(&player_turn);
        }

        // Warten bis alle Spieler fertig sind
        // => Spieler müssen ihre Semaphore up()
        for(int i = 0; i < PLAYER_COUNT; i++) {
            sem_wait(&sem_player_done[i]);
        }

        printf("\n");

        pthread_mutex_lock(&mtx);

        // Ergebnisse der Spieler auslesen
        int ergebnisse[PLAYER_COUNT];
        for(int i = 0; i < PLAYER_COUNT; i++) {
            if(players[i].round_points > 21) ergebnisse[i] = -1;
            else {
                ergebnisse[i] = players[i].round_points;
            }
            printf("Spieler %d: %d\n", i, ergebnisse[i]);
        }
        
        // Besten Wert auslesen
        int max = -1;
        int besterSpieler = -1;
        for(int i = 0; i < PLAYER_COUNT; i++) {
            if(ergebnisse[i] > max) {
                max = ergebnisse[i];
                besterSpieler = i;
            }
        }

        // Anzahl bestimmen gewinner
        int anz = 0;
 
        for (int i = 0; i < PLAYER_COUNT; i++) {
            if (ergebnisse[i] == max && max != -1) {
                anz++;
            }
        }

        if(anz > 1) printf("Unentschieden\n");
        else {
            if (besterSpieler != -1) {
                players[besterSpieler].score++;
                printf("Spieler %d hat gewonnen mit %d,  Gesamt: %d\n", besterSpieler, max, players[besterSpieler].score);
            } else {
                printf("Niemand gewinnt die Runde.\n");
            }
        }


        // Check ob Spiel vorbei
        for(int i = 0; i < PLAYER_COUNT; i++) {
            if(players[i].score > 2) {
                printf("Vorbei. Gewinner ist Spieler %d\n", i);
                SpielFetig = true;
            }
        }

        runde++;
        if (runde >= 50 && !SpielFetig) {
            printf("50 Runden vorbei. Unentschieden.\n");
            SpielFetig = true;
        }
        pthread_mutex_unlock(&mtx);

        sleep(1);


        for(int i = 0; i < PLAYER_COUNT; i++) {
            sem_post(&sem_bank_continue);
        }

        // Falls Spiel vorbei  Spieler entblocken
        if (SpielFetig) {
            for (int i = 0; i < PLAYER_COUNT; i++) {
                sem_post(&player_turn);
            }
        }

    }

    return NULL;
}

void* player_worker(void* arg) {
    player_t* player = (player_t*)arg;

    while (1) {
        sem_wait(&player_turn); // warte auf Startfreigabe
        if (SpielFetig) break;

        pthread_mutex_lock(&mtx);
        player->round_points = 0;
        pthread_mutex_unlock(&mtx);

        while (1) {
            int val = karteZiehen();

            pthread_mutex_lock(&mtx);
            player->round_points += val;
            printf("Player %d: Karte gezogen: %d, Punkte in dieser Runde: %d\n",
                   player->id, val, player->round_points);

            if (player->round_points > 17) {
                pthread_mutex_unlock(&mtx);
                break;
            }

            pthread_mutex_unlock(&mtx);
        }

        sem_post(&sem_player_done[player->id]); // signalisiere Bank
        // !!!! Hier schlafen, sonst verbraucht 1 Thread das semaphor alleine
        sleep(1);
        sem_wait(&sem_bank_continue);           // warte auf nächste Rundenerlaubnis
    }

    return NULL;
}

int main() {
    pthread_t bank;
    pthread_t player[PLAYER_COUNT];

    sem_init(&player_turn, 0, 0);
    sem_init(&sem_bank_continue, 0, 0);
    for(int i = 0; i < PLAYER_COUNT; i++) {
       sem_init(&sem_player_done[i], 0, 0);
    }

    for(int i = 0; i < PLAYER_COUNT; i++) {
        players[i].id = i;
        players[i].score = 0;
        players[i].round_points = 0;

    }

    pthread_create(&bank, NULL, bank_worker, NULL);

    for(int i = 0; i < PLAYER_COUNT; i++) {
        pthread_create(&player[i], NULL, player_worker, &players[i]);
    }


    pthread_join(bank, NULL);
    
    for(int i = 0; i < PLAYER_COUNT; i++) {
        pthread_join(player[i], NULL);
    }

    sem_destroy(&player_turn);
    sem_destroy(&sem_bank_continue);
    for(int i = 0; i < PLAYER_COUNT; i++) {
       sem_destroy(&sem_player_done[i]);
    }
    return 0;
}