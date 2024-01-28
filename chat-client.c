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

    connect(server_socket, (struct sockaddr *) &address, sizeof(address));

    int client_socket = accept(server_socket, NULL, NULL);

    //getting input from user
    struct pollfd fds[2] = { // two structures so we listen to any messages coming from the client
        {
            0,
            POLLIN, //if there's data to be read
            0
        },
        {
            server_socket,
            POLLIN,
            0
        }
    };

    for (;;) {
        char buffer[256] = { 0 };

        poll(fds, 2, 50000); // in miliseconds

        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);
            send(server_socket, buffer, 255, 0);
        } else if (fds[1].revents & POLLIN) { // if this is true, it means there's something to be read from the client
            if (recv(server_socket, buffer, 255, 0) == 0) {
                return 0;
            }
            
            printf("%s\n", buffer);
        }
    }

    return 0;
}