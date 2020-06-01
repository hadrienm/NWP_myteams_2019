/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** init
*/

#include "server.h"

bool init_server_data(server_data **server)
{
    (*server) = malloc(sizeof(server_data));
    if ((*server) == NULL)
        return false;
    (*server)->port = 0;
    (*server)->master_socket = 0;
    (*server)->client = NULL;
    return true;
}

int init_server(server_data *server)
{
    server->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->master_socket == -1) {
        printf("Failed to create TCP socket\n");
        return 84;
    }
    bzero(&(server->address), sizeof(server->address));
    (server->address).sin_family = AF_INET;
    (server->address).sin_port = htons(server->port);
    (server->address).sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server->master_socket, (struct sockaddr *)\
&(server->address), sizeof(server->address)) == -1) {
        printf("Bind failed\n");
        return 84;
    }
    if (listen(server->master_socket, 1024) != 0) {
        printf("Listen failed\n");
        return 84;
    }
    return 0;
}
