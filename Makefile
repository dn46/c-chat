CC=gcc
CFLAGS=-I.

all: chat-client chat-server

chat-client: chat-client.c
	$(CC) -o chat-client chat-client.c $(CFLAGS)

chat-server: chat-server.c
	$(CC) -o chat-server chat-server.c $(CFLAGS)

clean:
	rm -f chat-client chat-server