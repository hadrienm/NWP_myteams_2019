/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** set_client
*/

#include "client.h"

void handle_fd(client_data **client)
{
    FD_ZERO(&((*client)->readfds));
    FD_ZERO(&((*client)->writefds));
    FD_SET(0, &((*client)->readfds));
    FD_SET((*client)->master_socket, &((*client)->readfds));
    if ((*client)->data != NULL)
        FD_SET((*client)->master_socket, &((*client)->writefds));
    if (select(FD_SETSIZE, &(*client)->readfds, \
&(*client)->writefds, NULL, NULL) < 0) {
        stop = 0;
    }
}