/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "client.h"

void user_decrypt(client_data **client)
{
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    int status = 0;
    size_t index = HEADER_SIZE;

    memcpy(&user_id, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, (*client)->read_buffer + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&status, (*client)->read_buffer + index, sizeof(int));
    client_print_user(user_id, name, status);
}

void user(client_data **client)
{
    ctos_user_t user;

    memset(&user, '\0', sizeof(ctos_user_t));
    user.header.name = USER;
    user.header.size = sizeof(user) - sizeof(user.header);
    memset(user.uuid, 0, DEFAULT_BODY_LENGTH);
    if (size_array((*client)->command) > 1)
        sprintf(user.uuid, "%s", (*client)->command[1]);
    write((*client)->master_socket, &user, sizeof(ctos_user_t));
    free((*client)->command);
    (*client)->command = NULL;
}
