#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <mutex>

struct Position {
  float x;
  float y;
  float z;
};

struct PlayerState {
  std::mutex position_lock;

  Position* position;

  void get_position(Position* &player_position) {
    position_lock.lock();
    player_position = position;
    printf("getting position\n");
    position_lock.unlock();
  }

  void print_position() {
    printf("Position:\n");
    printf("\tx: %f\n", position->x);
    printf("\ty: %f\n", position->y);
    printf("\tz: %f\n", position->z);
  }

  void set_position(Position* player_position) {
    position_lock.lock();
    position = player_position;
    printf("setting position\n");
    position_lock.unlock();
  }
};

#endif
