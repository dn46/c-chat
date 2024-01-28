# Chat Server

This is a simple chat server written in C. It uses the socket API to communicate over the internet, and the poll API to handle multiple connections.

## Compilation

To compile the chat server, you need to have GCC installed on your system. You can compile the server using the provided Makefile:

```
make
```

## Usage

To start the server, simply run the compiled executable:

```
./chat-server
```

Afterwards, start the client by running the other compiled executable:

```
./chat-client
```

The server will listen for incoming connections on port 9999.