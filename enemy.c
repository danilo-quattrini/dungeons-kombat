#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <stdbool.h>
#define FIELD_SIZE 61
#define ENEMY_MIN_STRENGTH 5
#define ENEMY_MAX_STRENGTH 25
#define NUM_ENEMIES 10
char enemySymbols[NUM_ENEMIES] = {'$', '%', '&', '#', '@', 'Y', '?', '^', '!', 'X'};
int enemyPositions[NUM_ENEMIES];
int enemyStrengths[NUM_ENEMIES];

// Funzione per randomizzare la forza dei nemici
void randomizeEnemyStrengths() {
  for (int i = 0; i < NUM_ENEMIES; i++) {
      enemyStrengths[i] = ENEMY_MIN_STRENGTH + rand() % (ENEMY_MAX_STRENGTH - ENEMY_MIN_STRENGTH + 1); // Genera forza casuale per ogni nemico
  }
}
// We are going to initialize the position to each enemy
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
// Funzione per stampare le informazioni dei nemici
void seeEnemies() {
  printf("\n");
  printf("+-------+--------+----------+\n");
  printf("| Enemy | Power  | Position |\n");
  printf("+-------+--------+----------+\n");
  for (int i = 0; i < NUM_ENEMIES; i++) {
      printf("|   %c   |   %2d   |    %2d    |\n", enemySymbols[i], enemyStrengths[i], enemyPositions[i]);
  }
  printf("+-------+--------+----------+\n");
}