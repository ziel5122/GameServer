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

  Position position;

  void get_position(Position player_position);
  void set_position(Position player_position);
};

#endif
