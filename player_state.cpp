#include <mutex>

#include "player_state.h"

void PlayerState::get_position(Position player_position) {
  position_lock.lock();
  player_position = position;
  position_lock.unlock();
}

void PlayerState::set_position(Position player_position) {
  position_lock.lock();
  position = player_position;
  position_lock.unlock();
}
