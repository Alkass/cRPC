all: server client

server:
  g++ -Wall -Werror -o server server.cpp

client:
  g++ -Wall -Werror -o client client.cpp
