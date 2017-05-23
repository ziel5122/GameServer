#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <mutex>

struct Position {
  float x;
  float y;
  float z;
};

struct DataPacket {
  Position position;
  Position potato_position;
};

struct PlayerState {
  std::mutex position_lock;

  Position* position;
  Position* potato_position;

  unsigned char index;

  DataPacket* GetDataPacket() {
    DataPacket* data_packet = new DataPacket();
    data_packet->position = *position;
    data_packet->potato_position = *potato_position;
    return data_packet;
  }

  unsigned char GetIndex() {
    return index;
  }

  void PrintPosition() {
    printf("Position:\n");
    printf("\tx: %f\n", position->x);
    printf("\ty: %f\n", position->y);
    printf("\tz: %f\n", position->z);
  }

  Position* pGetPosition() {
    position_lock.lock();
    Position* player_position = position;
    position_lock.unlock();
    return player_position;
  }

  void pSetPosition(Position* player_position) {
    position_lock.lock();
    position = player_position;
    position_lock.unlock();
  }
};

#endif
