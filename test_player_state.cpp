#include <stdio.h>

#include "player_state.h"

int main() {
  PlayerState player_state;
  player_state.position.x = 1.0f;
  player_state.position.y = 2.0f;
  player_state.position.z = 3.0f;

  printf("%f\n", player_state.position.x);
  printf("%f\n", player_state.position.y);
  printf("%f\n", player_state.position.z);
  printf("%d\n", &player_state);
}
