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
int restoreStrenghtTimes = 3;
// Funzioni utilizzate nel gioco
void initializePlayerPosition(); // Inizializza la posizione del giocatore
void randomizeEnemyStrengths(); // Randomizza la forza dei nemici
void spawnEnemies(); // Posiziona i nemici su posizioni casuali dispari
void seePlayer(); // Mostra le informazioni del giocatore
void gameField(); // Stampa il campo da gioco con nemici e giocatore
int displayMenu(); // Mostra il menu del gioco
void seeEnemies(); // Mostra le informazioni dei nemici
void jumpTurn(); // Il player salta in una nuova posizione nel campo
void restoreStrenght(); // Il player si potrà riposare e recuperare la forza (lo può fare un massimo di 3 volte)
void startGame(); // Fase effettiva del gioco
bool checkFreeSpace(int); // Controllo se c'è spazio libero dove andrà il player
void initializePlayerPosition() {
    bool validPosition;
    do {
        validPosition = true;
        playerPosition = 1 + rand() % (FIELD_SIZE / 2) * 2; // Genera una posizione casuale dispari tra 1 e 59
        for (int i = 0; i < NUM_ENEMIES; i++) {
            if (playerPosition == enemyPositions[i]) { // Controlla se la posizione del giocatore coincide con quella di un nemico
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);
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

// Abilità del player nel gioco
void seePlayer() {
    printf("\n");
    printf("Player simbolo: %c\n", PLAYER_SYMBOL);
    printf("Forza del Player: %d\n", playerStrength);
    printf("Posizione del Player: %d\n", playerPosition);
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
// Funzione per stampare le informazioni dei nemici
void seeEnemies() {
    printf("\n");
    printf("Nemico\tForza\tPosizione\n");
    for (int i = 0; i < NUM_ENEMIES; i++) {
        printf("%c\t", enemySymbols[i]);
        printf("%d\t", enemyStrengths[i]);
        printf("%d\n", enemyPositions[i]);
    }
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
                        printf("Il nemico è troppo forte per te\n");
                    } else {
                        printf("Hai sconfitto il nemico %c!\n", enemySymbols[i]);
                        enemyStrengths[i] = 0; // Elimina il nemico
                        enemyPositions[i] = -1; // Rimuove il nemico dal campo
                        playerStrength--; // Riduce la forza del giocator
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
                    } else {
                        printf("Hai sconfitto il nemico %c!\n", enemySymbols[i]);
                        enemyStrengths[i] = 0; // Elimina il nemico
                        enemyPositions[i] = -1; // Rimuove il nemico dal campo
                        playerStrength--; // Riduce la forza del giocatore
                    }
                    break;
                }
            }     
           
            break;
        default:
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
        printf("5 - Gioca\n");
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
            if(playerStrength != 0){
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
                            seeEnemies(); // Mostra le informazioni dei nemici
                            break;
                        case 3:
                        jumpTurn(); // Il player salta in una nuova posizione nel campo
                        break;
                        case 4: 
                            restoreStrenght(); // Il player può recuperare la forza degl'enemy
                            break;
                        case 5:
                            startGame();
                            break;
                        default:
                            printf("Scelta non valida!\n");
                }
            } else{
                printf("Hai perso!!\n");
                return 0;
            }
        }while(choice!=0);

    return 0;
}