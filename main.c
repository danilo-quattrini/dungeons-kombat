#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIELD_SIZE 61
#define PLAYER_SYMBOL '*'
#define PLAYER_MIN_STRENGTH 10
#define PLAYER_MAX_STRENGTH 20
#define ENEMY_MIN_STRENGTH 5
#define ENEMY_MAX_STRENGTH 25
#define NUM_ENEMIES 10

// Tutte le variabili globali
char enemySymbols[NUM_ENEMIES] = {'$', '%', '&', '#', '@', 'Y', '?', '^', '!', 'X'};
int enemyPositions[NUM_ENEMIES];
int enemyStrengths[NUM_ENEMIES];
int playerStrength;
int playerPosition;


void initializePlayerPosition() {
    playerPosition = 1 + rand() % (FIELD_SIZE / 2) * 2; // Genera una posizione casuale dispari tra 1 e 59
    playerStrength = PLAYER_MIN_STRENGTH + rand() % (PLAYER_MAX_STRENGTH - PLAYER_MIN_STRENGTH + 1); // Genera una forza casuale tra 10 e 20
}

// Funzione per randomizzare la forza dei nemici
void randomizeEnemyStrengths() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemyStrengths[i] = ENEMY_MIN_STRENGTH + rand() % (ENEMY_MAX_STRENGTH - ENEMY_MIN_STRENGTH + 1); // Genera forza casuale per ogni nemico
    }
}

void spawnEnemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int position;
        bool validPosition = true;
        do {
            position = 1 + rand() % (FIELD_SIZE / 2) * 2; // Genera una posizione casuale dispari tra 1 e 59
            validPosition = true; // Resetta la validità della posizione
            for (int j = 0; j < i; j++) {
                if (enemyPositions[j] == position) { // Controlla se la posizione è già occupata da un altro nemico
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition);
        enemyPositions[i] = position; // Assegna la posizione al nemico
    }

}

void seePlayer() {
    printf("\n");
    printf("Player simbolo: %c\n", PLAYER_SYMBOL);
    printf("Forza del Player: %d\n", playerStrength);
    printf("Posizione del Player: %d\n", playerPosition);
}

// Funzione per stampare il campo da gioco con nemici e giocatore
void gameField(){

    bool enemyFound = false; // Flag per controllare se il giocatore è stato trovato
    // Stampa la linea del campo da gioco
    printf("The Dungeon:\n");
    for(int i = 0; i < FIELD_SIZE; i++){
        printf("-"); // Stampa la linea orizzontale
    }

    printf("\n"); // Stampa una nuova linea
    for (int i = 0; i < FIELD_SIZE; i++) {
        // Stampa il simbolo nella posizione in cui si trova
        enemyFound = false; // Resetta il flag per ogni iterazione
        for (int j = 0; j < NUM_ENEMIES; j++) {
            if (i == enemyPositions[j]) {
                printf("%c", enemySymbols[j]); // Stampa il simbolo del nemico
                enemyFound = true; // Imposta il flag a true se il nemico è trovato
                break;
            }
        }
        if (!enemyFound) {
            if (i == playerPosition) {
                printf("%c", PLAYER_SYMBOL); // Stampa il simbolo del giocatore
            } else {
                printf(" "); // Stampa uno spazio vuoto se non ci sono nemici o il giocatore
            }
        }
    }

    // Stampa linea del campo da gioco
    printf("\n"); // Stampa una nuova linea
    for(int i = 0; i < FIELD_SIZE; i++){
        printf("-"); // Stampa la linea orizzontale
  
    }
}
int displayMenu() {
    int menuChoice;
    // Stampa il menu e richiede all'utente di inserire una scelta
    do {
        printf("\nMenu:\n");
        printf("0 - Abbandona\n");
        printf("1 - Vedi Player\n");
        printf("2 - Vedi Enemy\n");
        printf("3 - Salta\n");
        printf("4 - Riposa\n");
        printf("5- Gioca\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &menuChoice);
    } while (menuChoice<0 || menuChoice>5);
    return menuChoice;
}
   


int main() {
    int choice;
    srand(time(0)); // Inizializza il generatore di numeri casuali
    initializePlayerPosition(); // Posiziona il giocatore in una posizione casuale
    randomizeEnemyStrengths();  // Randomizza la forza dei nemici
    spawnEnemies();// Posiziona i nemici su posizioni casuali dispari
    do{
        gameField(); // Stampa il campo da gioco con nemici e giocatore
        choice=displayMenu(); // Mostra il menu del gioco
        switch (choice){
                case 0:
                    printf("Hai abbandonato il gioco.\n");
                    break;
                case 1:
                    seePlayer(); // Mostra le informazioni del giocatore
                    break;
                case 2:

                    break;
                default:
                    printf("Scelta non valida!\n");
        }
    }while(choice!=0);
    return 0;
}