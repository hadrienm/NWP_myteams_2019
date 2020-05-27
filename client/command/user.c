/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "client.h"

void user_decrypt(stoc_header_t *header, size_t readed, client_data **client)
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
