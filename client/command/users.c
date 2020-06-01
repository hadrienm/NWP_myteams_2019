/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "client.h"

void users_decrypt(client_data **client)
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
    client_print_users(user_id, name, status);
}

void users(client_data **client)
{
    ctos_users_t users;

    memset(&users, 0, sizeof(users));
    users.header.name = USERS;
    users.header.size = 0;
    write((*client)->master_socket, &users, sizeof(users));
    free((*client)->command);
    (*client)->command = NULL;
}