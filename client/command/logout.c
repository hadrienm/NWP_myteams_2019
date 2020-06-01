/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout
*/

#include "client.h"

void logout_decrypt(client_data **cli)
{
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    size_t index = HEADER_SIZE;

    memcpy(&user_id, (*cli)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, (*cli)->read_buffer + index, DEFAULT_NAME_LENGTH);
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
