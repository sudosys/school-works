#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main(int argc, char** argv) {

    printf ("Client Starting...\n");

    int cli_socket;
    struct sockaddr_in srv_address;
    char buffer[BUFFER_SIZE];
    bzero(&srv_address, sizeof(srv_address));

    printf ("Enter something for the server to echo back: ");

    scanf("%s", buffer);
 
    srv_address.sin_family = AF_INET;
    srv_address.sin_port = htons(PORT);
    srv_address.sin_addr.s_addr = inet_addr(argv[1]);

    if ((cli_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed! Aborting...");
        exit(EXIT_FAILURE);
    }

    printf ("Socket created, connecting to server\n");
    
    if ((connect(cli_socket, (struct sockaddr*) &srv_address, sizeof(srv_address))) < 0) {
        perror("Connection to the server failed! Aborting...");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server, writing to socket\n");

    write(cli_socket, buffer, sizeof(buffer));

    printf("Now reading from socket\n");

    read(cli_socket, buffer, sizeof(buffer));

    printf("Server says -> %s\n", buffer);

    close(cli_socket);

    return 0;
}