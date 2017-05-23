#include <cstdlib>
#include <stdio.h>

#include "player_state.h"
#include "socket.h"

#define PORT 27015

struct GameState {
  PlayerState* player1;
};

GameState game_state;
PlayerState* player_state_to;
PlayerState* player_state_from;

sockaddr_in from;
sockaddr_in to;

socklen_t from_length = sizeof(to);

int byte_length;
int bytes_read;
int bytes_sent;

int main() {
  if (InitializeSockets()) return 1;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  int sock2 = socket(AF_INET, SOCK_DGRAM, 0);

  if (BindSocket(sock, PORT)) return 1;
  if (BindSocket(sock2, PORT+1)) return 1;

  wchar_t address[16] = L"0.0.0.0";

  to.sin_family = AF_INET;\

#if PLATFORM == PLATFORM_WINDOWS
  int error = InetPton(AF_INET, address, &to.sin_addr);
#else
  int error = inet_pton(AF_INET, "0.0.0.0", &to.sin_addr);
#endif

  to.sin_port = htons(PORT + 1);

  game_state = GameState();

  player_state_to = new PlayerState();
  player_state_to->position = new Position();
  player_state_to->position->x = 6.0f;
  player_state_to->potato_position = new Position();

  player_state_from = new PlayerState();

  DataPacket* data_packet = player_state_to->GetDataPacket();
  int data_packet_size = sizeof(*data_packet);
  bytes_sent = sendto(sock, (void*)data_packet, data_packet_size, 0,
                      (sockaddr*)&to, from_length);
  if (bytes_sent <= 0) {
    printf("send failed\n");
    return 1;
  }

  DataPacket* data_packet_from;
  char* temp = new char;
  bytes_read = recvfrom(sock2, temp, data_packet_size, 0, (sockaddr*)&from,
                        &from_length);
  if (bytes_read <= 0) {
    printf("read failed\n");
    return 1;
  }

  printf("%d\t%d\n", bytes_sent, bytes_read);

  data_packet_from = (struct DataPacket*)temp;
  Position position = data_packet_from->position;
  printf("%f\n", position.x);


  player_state_to->position->x = 16.0f;
  data_packet = player_state_to->GetDataPacket();
  bytes_sent = sendto(sock, (void*)data_packet, data_packet_size, 0,
                      (sockaddr*)&to, from_length);
  if (bytes_sent <= 0) {
    printf("send failed\n");
    return 1;
  }

  temp = new char;
  bytes_read = recvfrom(sock2, temp, data_packet_size, 0, (sockaddr*)&from,
                        &from_length);
  if (bytes_read <= 0) {
    printf("read failed\n");
    return 1;
  }

  data_packet_from = (struct DataPacket*)temp;
  Position* pos = &data_packet_from->position;
  printf("%f\n", pos->x);

  return 0;
}
