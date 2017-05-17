#ifndef SOCKET_H
#define SOCKET_H

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
  #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
  #define PLATFORM PLATFORM_MAC
#else
  #define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
  #include <winsock2.h>

  WSADATA wsa_data;
#elif PLATFORM == PLATFORM_UNIX || PLATFORM == PLATFORM_MAC
  #include <netinet/in.h>
#endif

struct sockaddr_in server;

int error;
int sock;

int BindSocket(uint port) {
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  error = bind(sock, (struct sockaddr*)&server, sizeof(server));
  if (error == -1) {
    printf("Bind failed with error: %d\n", error);
    return 1;
  }
  return 0;
}

int CreateSocket() {
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    printf("Could not create socket: %d\n", sock);
    return 1;
  }
  return 0;
}

int InitializeSockets() {
#if PLATFORM == PLATFORM_WINDOWS
  error = return WSAStartup(MAKEWORD(2, 2), &wsa_data);
  if (error != 0) {
    printf("WSAStartup failed with error: %d\n", error);
    return return 1;
  }
#endif
  return 0;
}

ReceiveBytes() {

}

SendBytes() {
  
}

#endif
