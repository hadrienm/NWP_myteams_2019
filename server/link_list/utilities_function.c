/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** utilities_function
*/

#include "server.h"

void display_list(server_data *server)
{
    client_t *tmp = server->client;

    while (tmp != NULL) {
        printf("--\n");
        tmp->uuid != NULL ? printf("uuid : %s\n", tmp->uuid) : 0;
        tmp->name != NULL ? printf("name : %s\n", tmp->name) : 0;
        tmp->description != NULL ? \
printf("description : %s\n", tmp->description) : 0;
        tmp->readbuffer != NULL ? printf("readbuffer%s\n", tmp->readbuffer) : \
0;
        printf("----\n");
        tmp = tmp->next;
    }
}