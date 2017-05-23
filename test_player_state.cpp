#include <stdio.h>

#include "player_state.h"

void dumb_function() { }

int main() {
  PlayerState player_state;
  player_state.position->x = 1.0f;
  player_state.position->y = 2.0f;
  player_state.position->z = 3.0f;

  Position* position = new Position();

  player_state.get_position(position);
  player_state.print_position();
  player_state.set_position(position);

  printf("\t%f\n", position->x);
  printf("\t%f\n", position->y);
  printf("\t%f\n", position->z);
}
