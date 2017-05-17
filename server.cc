#include <stdio.h>

#include "socket.h"

#define PORT 27015

struct GameState = {
  int x,
  int y,
};

int main() {
  if (InitializeSockets()) return 1;
  if (CreateSocket()) return 1;
  if (BindSocket(PORT)) return 1;

  while (1) {

  }

  return 0;
}
