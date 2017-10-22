include makefile.rules

all: server client

server:
	$(CC) $(FLAGS) -o server server.c

client:
	$(CC) $(FLAGS) -o client client.c

clean:
	rm -f server client
