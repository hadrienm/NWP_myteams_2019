/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "client.h"

void login_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char user_id[SIZE_ID];
    char name[DEFAULT_BODY_LENGTH];
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&user_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, k + index, DEFAULT_NAME_LENGTH);
    client_event_loggedin(user_id, name);
    free(k);
}

void login(client_data **client)
{
    ctos_login_t login;

    memset(&login, 0, sizeof(login));
    login.header.name = LOGIN;
    login.header.size = sizeof(login) - sizeof(login.header);
    memset(&login.name, 0, DEFAULT_NAME_LENGTH);
    if (size_array((*client)->command) > 1) {
        if (strlen((*client)->command[1]) > DEFAULT_NAME_LENGTH) {
            printf("403 Too long name\r\n");
        } else {
            (*client)->name = strdup((*client)->command[1]);
            sprintf(login.name, "%s", (*client)->command[1]);
            write((*client)->master_socket, &login, sizeof(ctos_login_t));
        }
    }
    free((*client)->command);
    (*client)->command = NULL;
}