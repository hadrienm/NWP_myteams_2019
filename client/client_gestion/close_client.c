/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** close_client
*/

#include "client.h"

void free_command(client_data **client)
{
    if ((*client)->command == NULL)
        return;

    for (int i = 0; (*client)->command[i] != NULL; ++i)
        free((*client)->command[i]);
    free((*client)->command);
    (*client)->command = NULL;
}

void free_struct(client_data *client)
{
    close(client->master_socket);
    client->command != NULL ? free_command(&client): 0;
    client->ip != NULL ? free(client->ip) : 0;
    client->name != NULL ? free(client->name) : 0;
    client->buffer != NULL ? free(client->buffer) : 0;
    client->data != NULL ? free(client->data) : 0;
    client->user_id != NULL ? free(client->user_id) : 0;
    free(client);
}
