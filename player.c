#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <stdbool.h>
int playerStrength;
int playerPosition;
#define PLAYER_SYMBOL '*'
#define PLAYER_MIN_STRENGTH 10
#define PLAYER_MAX_STRENGTH 20

// Abilità del player nel gioco
void seePlayer() {
  printf("\n");
  printf("+-------+--------+----------+\n");
  printf("| Player| Power  | Position |\n");
  printf("+-------+--------+----------+\n");
  printf("|   %c   |   %2d   |    %2d    |\n", PLAYER_SYMBOL, playerStrength, playerPosition);
  printf("+-------+--------+----------+\n");
}
// Controlla se il giocatore può ancora giocare o no
bool playerDied(){
  bool isDied = false;
  if(playerStrength == 0) isDied = true;
  return isDied;
}

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
