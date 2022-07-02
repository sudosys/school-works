#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 256
#define MAX_CLIENTS 10

int client_no = 1;
int does_exist = FALSE;
char* client_ip;
char txt_row[15];
FILE* ip_list;
struct sockaddr_in client_address;

void* thread_func(void* socket) {
    
    int* new_socket = (int*) socket;

    char buffer[BUFFER_SIZE];

    does_exist = FALSE;
    client_ip = NULL;
    client_no = 1;

    client_ip = inet_ntoa(client_address.sin_addr);

    while (fgets(txt_row, sizeof(txt_row), ip_list) != NULL) {
        txt_row[strcspn(txt_row, "\n")] = 0;
        if (strcmp(txt_row, client_ip) == 0) {
            does_exist = TRUE;
            break;
        }

        client_no++;
    }

    if (!does_exist) { fprintf(ip_list, "%s\n", client_ip); }

    rewind(ip_list);

    read(*new_socket, buffer, sizeof(buffer));

    char temp[2];

    sprintf(temp, "%d", client_no);

    strcat(buffer, " | you are number ");
    strcat(buffer, temp);

    write(*new_socket, buffer, sizeof(buffer));

    close(*new_socket);
    pthread_exit(0);

}

int main(int argc, char** argv) {

    int srv_socket, new_socket;
    struct sockaddr_in srv_address;
    socklen_t client_addrlen;
    pthread_t thread;
    ip_list = fopen("ip_list.txt", "a+");

    if ((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed! Aborting...");
        exit(EXIT_FAILURE);
    }

    srv_address.sin_family = AF_INET;
    srv_address.sin_addr.s_addr = INADDR_ANY;
    srv_address.sin_port = htons(PORT);

    if (bind(srv_socket, (struct sockaddr*) &srv_address, sizeof(srv_address)) < 0) {
        perror("Binding failed! Aborting...");
        exit(EXIT_FAILURE);
    }

    if (listen(srv_socket, MAX_CLIENTS) < 0) {
        perror("An error occurred while listening! Aborting...");
        exit(EXIT_FAILURE);
    }

    while (TRUE) {

        printf("Server is waiting for new connections...\n");
        client_addrlen = sizeof(client_address);

        if ((new_socket = accept(srv_socket, (struct sockaddr*) &client_address, &client_addrlen)) < 0) {
            perror("Connection refused!");
            exit(EXIT_FAILURE);
        }

        printf("Client connected!\n");
        
        pthread_create(&thread, NULL, &thread_func, &new_socket);
    }

    fclose(ip_list);
    close(srv_socket);
    return 0;
 
}