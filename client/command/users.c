/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "client.h"

void users_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    int status = 0;
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&user_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, k + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&status, k + index, sizeof(int));
    free(k);
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