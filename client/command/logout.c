/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout
*/

#include "client.h"

void logout_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&user_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, k + index, DEFAULT_NAME_LENGTH);
    free(k);
    client_event_loggedout(user_id, name);
}

void logout(client_data **client)
{
    ctos_logout_t logout;

    memset(&logout, '\0', sizeof(ctos_logout_t));
    logout.header.name = LOGOUT;
    logout.header.size = 0;
    write((*client)->master_socket, &logout, sizeof(ctos_logout_t));
    free((*client)->command);
    (*client)->command = NULL;
}
