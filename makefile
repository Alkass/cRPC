include makefile.rules

all: server client

server:
	$(BUILD) -o server server.c

client:
	$(BUILD) -o client client.c

clean:
	rm -f server client
