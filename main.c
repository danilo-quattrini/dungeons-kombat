#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> 
#define FIELD_SIZE 61
#include "enemy.c"
#include "player.c"
// Tutte le variabili globali
int restoreStrenghtTimes = 3;
// Funzioni utilizzate nel gioco
void initializePlayerPosition(); // Inizializza la posizione del giocatore
void randomizeEnemyStrengths(); // Randomizza la forza dei nemici
void spawnEnemies(); // Posiziona i nemici su posizioni casuali dispari
void seePlayer(); // Mostra le informazioni del giocatore
void gameField(); // Stampa il campo da gioco con nemici e giocatore
void seeEnemies(); // Mostra le informazioni dei nemici
void jumpTurn(); // Il player salta in una nuova posizione nel campo
void restoreStrenght(); // Il player si potrà riposare e recuperare la forza (lo può fare un massimo di 3 volte)
void startGame(); // Fase effettiva del gioco
bool checkFreeSpace(int); // Controllo se c'è spazio libero dove andrà il player
bool playerDied(); // Controlla se il giocatore è ancora in vita o no

int main() {
    srand(time(0)); // Inizializza il generatore di numeri casuali
    initializePlayerPosition(); // Posiziona il giocatore in una posizione casuale
    randomizeEnemyStrengths();  // Randomizza la forza dei nemici
    spawnEnemies();// Posiziona i nemici su posizioni casuali dispari
    seePlayer();
    seeEnemies();
    gameField();
    return 0;
}

void jumpTurn(){
    bool enemyFound = true; // Flag per controllare se il giocatore è stato trovato
    playerPosition = 1 + rand() % (FIELD_SIZE / 2) * 2; // Genera una posizione casuale dispari tra 1 e 59
    for(int i = 0; i < NUM_ENEMIES; i++){
        if(playerPosition == enemyPositions[i]){
           enemyFound = true; 
           playerPosition = 1 + rand() % (FIELD_SIZE / 2) * 2;
        }else{
            enemyFound = false; // Imposta il flag a true se il nemico è trovato
        }
    }
    if(!enemyFound){
        playerStrength--; // Riduce la forza del giocatore di 1
        printf("Il tuo turno è saltato!\n");
        printf("Posizione del Player '*' è: %d\t Strength: %d\n", playerPosition, playerStrength);
    }
}

void restoreStrenght(){
    if(restoreStrenghtTimes != 0){
        int enemyStrenghtAvarage = 0;
        int enemyMaxStrenght = ENEMY_MIN_STRENGTH - 1; // Initialize to a value lower than the minimum possible strength
        int enemyMinStrenght = ENEMY_MAX_STRENGTH + 1; // Initialize to a value higher than the maximum possible strength
        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            if(enemyStrengths[i] > 0){
                if(enemyMaxStrenght < enemyStrengths[i] ){
                    enemyMaxStrenght = enemyStrengths[i];
                }
                if(enemyMinStrenght > enemyStrengths[i]){
                    enemyMinStrenght = enemyStrengths[i];
                }
            }
        }
        enemyStrenghtAvarage = (enemyMaxStrenght + enemyMinStrenght) / 2;
        playerStrength += enemyStrenghtAvarage;
        printf("Forza attuale del giocatore: %d\n", playerStrength);
        restoreStrenghtTimes--;
        printf("Hai ancora %d volte/a per riposare\n", restoreStrenghtTimes);
    }else{
        printf("Non puoi più recuperare la forza!!\n");
    }
    
}

// Funzione per stampare il campo da gioco con nemici e giocatore
void gameField(){

    bool enemyFound = false; // Flag per controllare se il giocatore è stato trovato
    seePlayer();
    // Stampa la linea del campo da gioco
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
        // Controllo se * si trova in posizione giusta
        if (!enemyFound && i != playerPosition) {
                printf(" "); // Stampa uno spazio vuoto se non ci sono nemici o il giocatore
        }else if (i == playerPosition) {
            printf("%c", PLAYER_SYMBOL); // Stampa il simbolo del giocatore
        }
    }

    // Stampa linea del campo da gioco
    printf("\n"); // Stampa una nuova linea
    for(int i = 0; i < FIELD_SIZE; i++){
        printf("-"); // Stampa la linea orizzontale
  
    }
    seeEnemies();
}
void startGame(){
    int movementChoice;
    printf("Dove vuoi attaccare? 1/0 (1 = D e 0 = S)\n");
    printf("=>");
    scanf("%d", &movementChoice);
    switch (movementChoice)
    {
        case 1:
            playerPosition++;
            for (int i = 0; i < NUM_ENEMIES; i++) {
                if (!checkFreeSpace(i)) {
                    if (enemyStrengths[i] > playerStrength) {
                        playerPosition--;
                        printf("Il nemico è troppo forte per te!!\n");
                    } else if(enemyStrengths[i] <= playerStrength){
                        sleep(1); // Pause for 1 second
                        int gameDice = rand() % 2; // Genera un numero casuale tra 0 e 1
                        printf("%d\n", gameDice);
                        sleep(1);
                        if (gameDice == 0) {
                            printf("Hai sconfitto il nemico %c!\n", enemySymbols[i]);
                            playerStrength += enemyStrengths[i]; // Aggiungi la forza del nemico al giocatore
                            if (playerStrength > 2 * ENEMY_MAX_STRENGTH) { // Controlla se supera 2 volte la forza massima dei nemici
                                playerStrength = 2 * ENEMY_MAX_STRENGTH; // Limita la forza del giocatore
                            }
                            enemyStrengths[i] = 0; // Elimina il nemico
                            enemyPositions[i] = -1; // Rimuove il nemico dal campo
                            
                        } else {
                            printf("Il nemico %c ti ha sconfitto!\n", enemySymbols[i]);
                            playerPosition--;
                            playerStrength -= enemyStrengths[i];
                        }
                    }
                    break;
                }
            }
           
            break;
        case 0:
            playerPosition--;
            for (int i = 0; i < NUM_ENEMIES; i++) {
                if (!checkFreeSpace(i)) {
                    if (enemyStrengths[i] > playerStrength) {
                        playerPosition++;
                        printf("Il nemico è troppo forte per te\n");
                    } else if(enemyStrengths[i] <= playerStrength){
                        printf("Lancio dado: ");
                        sleep(1);
                        int gameDice = rand() % 2; // Genera un numero casuale tra 0 e 1
                        printf("%d\n", gameDice);
                        sleep(1);
                        if (gameDice == 0) {
                            printf("Hai sconfitto il nemico %c!\n", enemySymbols[i]);
                            playerStrength += enemyStrengths[i]; // Aggiungi la forza del nemico al giocatore
                            if (playerStrength > 2 * ENEMY_MAX_STRENGTH) { // Controlla se supera 2 volte la forza massima dei nemici
                                playerStrength = 2 * ENEMY_MAX_STRENGTH; // Limita la forza del giocatore
                            }
                            enemyStrengths[i] = 0; // Elimina il nemico
                            enemyPositions[i] = -1; // Rimuove il nemico dal campo
                            
                        } else {
                            printf("Il nemico %c ti ha sconfitto!\n", enemySymbols[i]);
                            playerPosition++;
                            playerStrength -= enemyStrengths[i];
                        }
                    }
                    break;
                }
            }    
            break;
            default:
                printf("Inserisci la corretta posizione");
                break;
    }
}

// Funzione che controlla se ci sono nemici o no
bool checkFreeSpace(int i){
    bool state = true;
    if (playerPosition == enemyPositions[i]) {
        state = false;
        printf("La posizione è occupata %d\n", state);
    }
    return state;
}
