/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** delete
*/

#include "server.h"

void free_server_data(server_data **server)
{
    free(*server);
}
