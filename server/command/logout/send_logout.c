/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** send_logout
*/

#include "server.h"

void logout_send_rfc(client_t **client, command_status_t rfc, size_t index)
{
    if (index == 0) {
        (*client)->answer = malloc(RFC_SIZE);
        memset((*client)->answer, 0, RFC_SIZE);
        (*client)->answer_size = RFC_SIZE;
    }
    memcpy((*client)->answer + index, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
}

command_status_t set_logout_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.id, 0, SIZE_ID);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    }
    return rfc;
}

static size_t logout_send(client_t **client, stoc_logout_t logout, \
client_t **all)
{
    size_t size = LOGOUT_SIZE + RFC_SIZE;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer + index, &logout.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &logout.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &logout.user_id, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &logout.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    (*client)->answer_size = size;
    return index;
}

void set_logout(client_t **client, client_t **all)
{
    stoc_logout_t logout;
    command_status_t rfc = set_logout_rfc(200);
    size_t index = 0;

    memset(&logout, 0, sizeof(logout));
    logout.header.name = LOGOUT;
    logout.header.size = LOGIN_CONTENT_SIZE;
    sprintf(logout.user_id, "%s", (*client)->uuid);
    sprintf(logout.name, "%s", (*client)->name);
    index = logout_send(client, logout, all);
    logout_send_rfc(client, rfc, index);
    set_logout_broadcast(logout, all, (*client)->socket);
}
