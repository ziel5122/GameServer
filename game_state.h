#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <mutex>

struct PlayerState {
  float x;
  float y;
  float z;

  PlayerState();
  
}

struct GameState {


  GameState();
  GameState(unsigned char num_players);
  ~GameState();
}

#endif
