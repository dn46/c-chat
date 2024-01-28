#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>


int main(void) {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    bind(server_socket, (struct sockaddr *) &address, sizeof(address));

    listen(server_socket, 10);

    int client_socket = accept(server_socket, NULL, NULL);

    //getting input from user
    struct pollfd fds[2] = { // two structures so we listen to any messages coming from the client
        {
            0,
            POLLIN, //if there's data to be read
            0
        },
        {
            client_socket,
            POLLIN,
            0
        }
    };

    for (;;) {
        char buffer[256] = { 0 };

        poll(fds, 2, 50000); // in miliseconds

        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);
            send(client_socket, buffer, 255, 0);
        } else if (fds[1].revents & POLLIN) { // if this is true, it means there's something to be read from the client
            if (recv(client_socket, buffer, 255, 0) == 0) {
                return 0;
            }
            
            printf("%s\n", buffer);
        }
    }

    return 0;
}