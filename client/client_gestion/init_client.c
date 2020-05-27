/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** init_client
*/

#include "client.h"

int connect_client(client_data ** client)
{
    (*client)->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ((*client)->master_socket == -1)
        return 84;
    bzero(&(*client)->address, sizeof((*client)->address));
    (*client)->address.sin_family = AF_INET;
    (*client)->address.sin_addr.s_addr = inet_addr((*client)->ip);
    (*client)->address.sin_port = htons((*client)->port);
    if (connect((*client)->master_socket, (struct sockaddr *) \
&(*client)->address, sizeof((*client)->address)) != 0)
        return 84;
    return 0;
}

void init_client(client_data **client)
{
    (*client) = malloc(sizeof(client_data));
    (*client)->command = NULL;
    (*client)->name = NULL;
    (*client)->ip = NULL;
    (*client)->data = NULL;
    (*client)->user_id = NULL;
    (*client)->data_size = 0;
    (*client)->port = 0;
    (*client)->master_socket = 0;
    (*client)->buffer = NULL;
    (*client)->pending_command = NULL;
}
