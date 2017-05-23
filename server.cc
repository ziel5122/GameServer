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

  DataPacket* data_packet = new DataPacket();
  data_packet = player_state_to->GetDataPacket();
  int data_packet_size = sizeof(*data_packet);
  bytes_sent = sendto(sock, (void*)data_packet, data_packet_size, 0,
   (sockaddr*)&to, from_length);
  if (bytes_sent <= 0) {
    printf("send failed\n");
    return 1;
  }

  DataPacket* data_packet_from;
  char* temp = new char;
  bytes_read = recvfrom(sock2, temp,
   data_packet_size, 0, (sockaddr*)&from, &from_length);
  if (bytes_read <= 0) {
    printf("read failed\n");
    return 1;
  }
  printf("%d\t%d\n", bytes_sent, bytes_read);

  game_state.player1 = player_state_from;
  player_state_from = new PlayerState();
  printf("%f\n", game_state.player1->position->x);
  player_state_to->position->x = 69.0;
  printf("%f\n", game_state.player1->position->x);
  /*
  bytes_sent = sendto(sock, (void*)player_state_to, sizeof(*player_state_to),
   0, (sockaddr*)&to, from_length);
  bytes_read = recvfrom(sock2, (struct PlayerState*)player_state_from,
   sizeof(*player_state_from), 0, (sockaddr*)&from, &from_length);
  printf("%f\n", game_state.player1->position->x);
  */
  return 0;
}
