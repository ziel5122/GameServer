#include <cstdlib>
#include <stdio.h>

#include "socket.h"

#define PORT 27015

struct Player {
  float x;
  float y;
  float z;
};

struct GameState {
  struct Player players[6] = {
    { 1.0f, 2.0f, 3.0f },
    { 1.0f, 2.0f, 3.0f },
    { 1.0f, 2.0f, 3.0f },
    { 1.0f, 2.0f, 3.0f },
    { 1.0f, 2.0f, 3.0f },
    { 1.0f, 2.0f, 3.0f }
  };
};

GameState game_state_to;
GameState game_state_from;
sockaddr_in from;
sockaddr_in to;

socklen_t from_length = sizeof(to);

int byte_length;
int bytes_read;
int bytes_sent;

char message_to[] = "dog";
char message_from[4];

int main() {
  if (InitializeSockets()) return 1;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  int sock2 = socket(AF_INET, SOCK_DGRAM, 0);

  if (BindSocket(sock, PORT)) return 1;
  if (BindSocket(sock2, PORT+1)) return 1;

  wchar_t address[16] = L"10.0.0.8";

  to.sin_family = AF_INET;
#if PLATFORM == PLATFORM_WINDOWS
  int error = InetPton(AF_INET, address, &to.sin_addr);
#else
  int error = inet_pton(AF_INET, "10.0.0.8", &to.sin_addr);
#endif
  to.sin_port = htons(PORT + 1);

  while (1) {
    bytes_sent = sendto(sock, &game_state_to, 72, 0, (sockaddr*)&to, from_length);
    bytes_read = recvfrom(sock2, (struct GameState*)&game_state_from, 72, 0, (sockaddr*)&from, &from_length);
    printf("%d\t%d\n", bytes_sent, bytes_read);
    printf("%f\n", game_state_from.players[0].y);
  }

  return 0;
}
