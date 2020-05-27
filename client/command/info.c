/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info
*/

#include "client.h"

void info_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
}

void info(client_data **client)
{
    ctos_info_t info;

    memset(&info, 0, sizeof(info));
    info.header.name = INFO;
    info.header.size = 0;
    write((*client)->master_socket, &info, sizeof(info));
    free((*client)->command);
    (*client)->command = NULL;
}