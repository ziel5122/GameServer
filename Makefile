OBJS = server.o state.o
CC = g++
LFLAGS = -Wall
CFLAGS = $(LFLAGS) -c

game_server: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o game_server.exe

server: server.cc server.h socket.h
	$(CC) $(CFLAGS) server.cc
