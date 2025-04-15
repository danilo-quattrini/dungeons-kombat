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