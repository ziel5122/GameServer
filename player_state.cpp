#include <mutex>

#include "player_state.h"

void PlayerState::get_position() {
  position_lock.lock();
  printf("getting position\n");
  position_lock.unlock();
}

void PlayerState::print_position() {
  printf("Position:\n");
  printf("\tx: %f\n", position.x);
  printf("\ty: %f\n", position.y);
  printf("\tz: %f\n", position.z);
}

void PlayerState::set_position() {
  position_lock.lock();
  printf("setting position\n");
  position_lock.unlock();
}
